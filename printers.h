/*******************************************************************/
/*    Course:        CPSC237                                       */
/*    Filename:      printers.h                                    */
/*    Author:        Chris George                                  */
/*    Date:          11-Nov-2025                                   */
/*    Purpose:       declares printing functions                   */
/*******************************************************************/
#ifndef PRINTERS_H
#define PRINTERS_H

#include <vector>
#include "model.h"
using namespace std;

/*****************************************************************/
/*    Function name:   printAllTransactions                      */
/*    Description:     prints all transactions in table form       */
/*    Parameters:      vector<Transaction>& txs                   */
/*    Return Value:    none                                       */
/*****************************************************************/
void printAllTransactions(const vector<Transaction>& txs);

/*****************************************************************/
/*    Function name:   printPortfolio                            */
/*    Description:     prints the portfolio table showing shares  */
/*                     and price paid                             */
/*    Parameters:      vector<PortfolioRow>& rows                */
/*    Return Value:    none                                       */
/*****************************************************************/
void printPortfolio(const vector<PortfolioRow>& rows);

/*****************************************************************/
/*    Function name:   printAdvisory                             */
/*    Description:     prints the most recent unsold lot for      */
/*                     each stock                                  */
/*    Parameters:      vector<AdvisoryRow>& rows                 */
/*    Return Value:    none                                       */
/*****************************************************************/
void printAdvisory(const vector<AdvisoryRow>& rows);

#endif

