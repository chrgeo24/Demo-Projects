/*******************************************************************/
/*    Course:        CPSC237                                       */
/*    Filename:      model.h                                       */
/*    Author:        Chris George                                  */
/*    Date:          11-Nov-2025                                   */
/*    Purpose:       contains all struct definitions used in       */
/*                   project 2 for storing data                    */
/*******************************************************************/
#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <vector>
using namespace std;

// stores one transaction from the file
struct Transaction {
    int dateYYYYMMDD;
    string symbol;
    char type;
    int shares;
    int priceCents;
    int lineNo;
};

// represents one lot (purchase block)
struct Lot {
    int dateYYYYMMDD;
    int shares;
    int priceCents;
};

// holds all lots for a single stock symbol
struct StockLots {
    string symbol;
    vector<Lot> lots;
};

// row for portfolio table
struct PortfolioRow {
    string symbol;
    long long totalShares;
    long long totalPaidCents;
};

// row for advisory table
struct AdvisoryRow {
    string symbol;
    int dateYYYYMMDD;
    int unsoldShares;
    int priceCents;
};

#endif
