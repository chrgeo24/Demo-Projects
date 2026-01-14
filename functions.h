/*******************************************************************/
/*    Course:        CPSC237                                       */
/*    Filename:      functions.h                                   */
/*    Author:        Chris George                                  */
/*    Date:          09-Nov-2025                                   */
/*    Purpose:       declares helper utility functions used in     */
/*                   project 2                                     */
/*******************************************************************/
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>
#include "model.h"
using namespace std;

/*****************************************************************/
/*    Function name:   isUpperDigitString                        */
/*    Description:     checks if all characters are uppercase     */
/*                     letters or digits                          */
/*    Parameters:      const string& s                            */
/*    Return Value:    bool                                       */
/*****************************************************************/
bool isUpperDigitString(const string& s);

/*****************************************************************/
/*    Function name:   priceToCents                              */
/*    Description:     converts string price to cents               */
/*    Parameters:      const string& token                        */
/*    Return Value:    int cents or -1 if bad                     */
/*****************************************************************/
int priceToCents(const string& token);

/*****************************************************************/
/*    Function name:   moneyString                               */
/*    Description:     converts integer cents to string            */
/*    Parameters:      long cents                                  */
/*    Return Value:    string                                     */
/*****************************************************************/
string moneyString(long cents);

/*****************************************************************/
/*    Function name:   errorExit                                 */
/*    Description:     prints message and exits program           */
/*    Parameters:      const string& msg                          */
/*    Return Value:    none                                        */
/*****************************************************************/
void errorExit(const string& msg);

/*****************************************************************/
/*    Function name:   errorExitTx                               */
/*    Description:     prints message                              */
/*    Parameters:      msg, tx structure, raw text line           */
/*    Return Value:    none                                       */
/*****************************************************************/
void errorExitTx(const string& msg, const Transaction& tx, const string& raw);

#endif

