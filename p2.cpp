/********************************************************************************/
/*    File:        p2.cpp                                                       */
/*    Course:      CPSC 237 - Data Structures: 010                              */
/*    Instructor:  Dr. Hussain                                                  */
/*    Author:      Chris George                                                 */
/*    Date:        11-Nov-2025                                                  */
/*    Purpose:     write a software that can process                            */
/*                 various trading transactions for a trader                    */
/*    COMPILE COMMAND: g++ p2.cpp core.cpp functions.cpp printers.cpp           */
/*                        ./a.out                                               */
/********************************************************************************/

#include "core.h"  // for functions in the file  
#include "printers.h"  // for functions in the file
using namespace std; // for formatting


int main() {

    // loads and validates all transactions
    vector<Transaction> txs = loadTransactions();

    // makes LIFO lots
    vector<StockLots> lots  = buildLots(txs);

    // makes reports
    vector<PortfolioRow> portfolio = buildPortfolio(lots);
    vector<AdvisoryRow>  advisory  = buildAdvisory(lots);

    // prints output
    printAllTransactions(txs);
    printPortfolio(portfolio);
    printAdvisory(advisory);

    return 0;
}

