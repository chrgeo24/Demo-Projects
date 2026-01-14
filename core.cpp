/*******************************************************************/
/*    Course:        CPSC237                                       */
/*    Filename:      core.cpp                                      */
/*    Author:        Chris George                                  */
/*    Date:          11-Nov-2025                                   */
/*    Purpose:       implements loading, lot building, and          */
/*                   report generation for project 2.              */
/*******************************************************************/

#include "core.h"       
#include "functions.h"      
#include <fstream>      // for file reading
#include <sstream>      // for stringstream parsing
#include <algorithm>    // for sorting

using namespace std;

/*****************************************************************/
/*    Function name:   loadTransactions                          */
/*    Description:     reads the Transactions.txt file, checks    */
/*                     each field, and stores all transactions   */
/*    Parameters: none                                            */
/*    Return Value:    vector<Transaction>                        */
/*****************************************************************/
vector<Transaction> loadTransactions() {

    ifstream fin("Transactions.txt");  // open file
    if (!fin) errorExit("could not open the file.");

    vector<Transaction> txs;           // stores all transactions
    string line;                       // holds each line from file
    int lineNo = 0;                    // tracks line number

    // skip documentation line
    getline(fin, line);
    lineNo++;

    // read each transaction line
    while (getline(fin, line)) {
        lineNo++;

        if (line.length() == 0) 
            continue; // skip empty lines

        istringstream is(line); // break line into tokens

        string dateStr, symbol, typeStr, sharesStr, priceStr;

        // read 5 fields
        if (!(is >> dateStr >> symbol >> typeStr >> sharesStr >> priceStr)) {
            Transaction stub; 
            stub.lineNo = lineNo;
            errorExitTx("line must contain 5 fields", stub, line);
        }

        Transaction t;
        t.lineNo = lineNo;

        // date format check 
        if (dateStr.length() != 8 || 
            !all_of(dateStr.begin(), dateStr.end(), ::isdigit))
        {
            errorExitTx("invalid date format", t, line);
        }
        t.dateYYYYMMDD = stoi(dateStr);

        // symbol check
        for (char& c : symbol) c = toupper(c);
        if (!isUpperDigitString(symbol) || symbol.length() > 5)
            errorExitTx("invalid stock symbol", t, line);
        t.symbol = symbol;

        // type must be B or S
        if (typeStr.length() != 1)
            errorExitTx("type must be one character", t, line);
        char type = toupper(typeStr[0]);
        if (type != 'B' && type != 'S')
            errorExitTx("type must be B or S", t, line);
        t.type = type;

        // shares numeric check
        if (!all_of(sharesStr.begin(), sharesStr.end(), ::isdigit))
            errorExitTx("shares must be numeric", t, line);
        long long sh = stoll(sharesStr);
        if (sh <= 0)
            errorExitTx("shares must be positive", t, line);
        t.shares = (int)sh;

        // convert price to cents
        int cents = priceToCents(priceStr);
        if (cents < 0)
            errorExitTx("invalid price format", t, line);
        t.priceCents = cents;

        // store transaction
        txs.push_back(t);
    }

    // sort all transactions by date
    sort(txs.begin(), txs.end(),
        [](const Transaction& a, const Transaction& b) {
            return a.dateYYYYMMDD < b.dateYYYYMMDD;
        });

    return txs;
}

/*****************************************************************/
/*    Function name:   buildLots                                 */
/*    Description:     builds LIFO purchase lots for each stock   */
/*                     and applies sell operations, stocks remain */
/*                     in the order they first appear            */
/*    Parameters:      const vector<Transaction>& txs             */
/*    Return Value:    vector<StockLots>                          */
/*****************************************************************/
vector<StockLots> buildLots(const vector<Transaction>& txs) {

    vector<StockLots> stocks;  // will stay in first-appearance order

    for (const auto& t : txs) {

        // find the stock's index, if it already exists
        int index = -1;
        for (int i = 0; i < stocks.size(); i++) {
            if (stocks[i].symbol == t.symbol) {
                index = i;
                break;
            }
        }

        // if not found, create new stock entry
        if (index == -1) {
            StockLots s;
            s.symbol = t.symbol;
            stocks.push_back(s);
            index = stocks.size() - 1;
        }

        // reference to the purchase lots
        vector<Lot>& stack = stocks[index].lots;

        // push a new lot if buying
        if (t.type == 'B') {
            stack.push_back({t.dateYYYYMMDD, t.shares, t.priceCents});
        }

        // remove from most recent lot
        else {
            long held = 0;
            for (auto& L : stack) 
                held += L.shares;

            if (t.shares > held)
                errorExitTx("sell exceeds available shares", t, "N/A");

            int remain = t.shares;

            // subtract shares starting from last lot
            while (remain > 0) {
                Lot& L = stack.back();
                if (L.shares <= remain) {
                    remain -= L.shares;
                    stack.pop_back();
                } else {
                    L.shares -= remain;
                    remain = 0;
                }
            }
        }
    }

    return stocks; // stocks stay in appearance order
}

/*****************************************************************/
/*    Function name:   buildPortfolio                            */
/*    Description:     computes shares and total paid for each    */
/*                     stock from the final lots                  */
/*    Parameters:      const vector<StockLots>& lots              */
/*    Return Value:    vector<PortfolioRow>                       */
/*****************************************************************/
vector<PortfolioRow> buildPortfolio(const vector<StockLots>& lots) {

    vector<PortfolioRow> rows;

    for (const auto& s : lots) {

        long shares = 0;
        long total  = 0;

        // sum shares and cost from all remaining lots
        for (const auto& L : s.lots) {
            shares += L.shares;
            total += static_cast<long>(L.shares) * L.priceCents;
        }

        if (shares > 0) {
            rows.push_back({s.symbol, shares, total});
        }
    }

    return rows; // order preserved
}

/*****************************************************************/
/*    Function name:   buildAdvisory                             */
/*    Description:     finds the most recent lot                 */
/*                     for each stock that still has              */
/*                     remaining shares.                          */
/*    Parameters:      const vector<StockLots>& lots              */
/*    Return Value:    vector<AdvisoryRow>                        */
/*****************************************************************/
vector<AdvisoryRow> buildAdvisory(const vector<StockLots>& lots) {

    vector<AdvisoryRow> rows;

    for (const auto& s : lots) {

        if (!s.lots.empty()) {
            const Lot& top = s.lots.back();

            if (top.shares > 0) {
                rows.push_back({
                    s.symbol,
                    top.dateYYYYMMDD,
                    top.shares,
                    top.priceCents
                });
            }
        }
    }

    return rows; // order preserved
}
