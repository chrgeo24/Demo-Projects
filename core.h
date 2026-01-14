/*******************************************************************/
/*    Course:        CPSC237                                       */
/*    Filename:      core.h                                        */
/*    Author:        Chris George                                  */
/*    Date:          11-Nov-2025                                   */
/*    Purpose:       Declares core processing functions            */
/*******************************************************************/
#ifndef CORE_H
#define CORE_H

#include <vector> // for vector class
#include <string> // for formatting
#include "model.h"
using namespace std;

/*****************************************************************/
/*    Function name:   loadTransactions                          */
/*    Description:     reads the Transactions.txt file, checks    */
/*                     each field, and stores all transactions.   */
/*    Parameters: none                                            */
/*    Return Value:    vector<Transaction>                        */
/*****************************************************************/
vector<Transaction> loadTransactions();

/*****************************************************************/
/*    Function name:   buildLots                                 */
/*    Description:     builds LIFO purchase lots for each stock   */
/*                     and applies sell operations, stocks remain */
/*                     in the order they first appear            */
/*    Parameters:      const vector<Transaction>& txs             */
/*    Return Value:    vector<StockLots>                          */
/*****************************************************************/
vector<StockLots> buildLots(const vector<Transaction>& txs);

/*****************************************************************/
/*    Function name:   buildPortfolio                            */
/*    Description:     computes shares and total paid for each    */
/*                     stock from the final lots                  */
/*    Parameters:      const vector<StockLots>& lots              */
/*    Return Value:    vector<PortfolioRow>                       */
/*****************************************************************/
vector<PortfolioRow> buildPortfolio(const vector<StockLots>& lots);

/*****************************************************************/
/*    Function name:   buildAdvisory                             */
/*    Description:     finds the most recent lot                 */
/*                     for each stock that still has              */
/*                     remaining shares.                          */
/*    Parameters:      const vector<StockLots>& lots              */
/*    Return Value:    vector<AdvisoryRow>                        */
/*****************************************************************/
vector<AdvisoryRow> buildAdvisory(const vector<StockLots>& lots);

#endif
