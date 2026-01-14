/*******************************************************************/
/*    Course:        CPSC237                                       */
/*    Filename:      printers.cpp                                  */
/*    Author:        Chris George                                  */
/*    Date:          11-Nov-2025                                   */
/*    Purpose:       outputs formatted tables for transactions,     */
/*                   portfolio, and advisory data                  */
/*******************************************************************/

#include "printers.h"
#include "functions.h"
#include <iostream>     // for input and output
#include <iomanip>      // for formatting

using namespace std;

/*****************************************************************/
/*    Function name:   printAllTransactions                      */
/*    Description:     prints all transactions in table form       */
/*    Parameters:      vector<Transaction>& txs                   */
/*    Return Value:    none                                       */
/*****************************************************************/
void printAllTransactions(const vector<Transaction>& txs) {

    cout << "All Transactions:\n";
    cout << left  << setw(12) << "Date"
         << left  << setw(8)  << "Stock"
         << left  << setw(6)  << "Type"
         << right << setw(10) << "#Shares"
         << right << setw(18) << "Share Price ($)\n";

    cout << string(54, '-') << endl;

    for (const auto& t : txs) {
        cout << left  << setw(12) << t.dateYYYYMMDD
             << left  << setw(8)  << t.symbol
             << left  << setw(6)  << t.type
             << right << setw(10) << t.shares
             << right << setw(18) << moneyString(t.priceCents)
             << endl;
    }
    cout << endl;
}

/*****************************************************************/
/*    Function name:   printPortfolio                            */
/*    Description:     prints the portfolio table showing shares  */
/*                     and price paid                             */
/*    Parameters:      vector<PortfolioRow>& rows                */
/*    Return Value:    none                                       */
/*****************************************************************/
void printPortfolio(const vector<PortfolioRow>& rows) {

    cout << "Portfolio:\n";
    cout << left  << setw(12) << "Stock"
         << right << setw(6) << "#Shares"
         << right << setw(18) << "Price Paid ($)"
         << right << setw(18) << "Avg Price ($)\n";

    cout << string(54, '-') << endl;

    for (const auto& r : rows) {

        string avg = moneyString((r.totalPaidCents + r.totalShares/2) /
                                 r.totalShares);

        cout << left  << setw(12) << r.symbol
             << right << setw(7) << r.totalShares
             << right << setw(18) << moneyString(r.totalPaidCents)
             << right << setw(17) << avg
             << endl;
    }

    cout << endl;
}

/*****************************************************************/
/*    Function name:   printAdvisory                             */
/*    Description:     prints the most recent unsold lot for      */
/*                     each stock                                  */
/*    Parameters:      vector<AdvisoryRow>& rows                 */
/*    Return Value:    none                                       */
/*****************************************************************/
void printAdvisory(const vector<AdvisoryRow>& rows) {

    cout << "Advisory Table (Latest Unsold Stock):\n";
    cout << left  << setw(12) << "Stock"
         << right << setw(4) << "Date"
         << right << setw(20) << "#Unsold Shares"
         << right << setw(19) << "Share Price ($)\n";

    cout << string(54, '-') << endl;

    for (const auto& a : rows) {
        cout << left  << setw(12) << a.symbol
             << right << setw(4) << a.dateYYYYMMDD
             << right << setw(16) << a.unsoldShares
             << right << setw(18) << moneyString(a.priceCents)
             << endl;
    }
}
