/*******************************************************************/
/*    Course:        CPSC237                                       */
/*    Filename:      functions.cpp                                 */
/*    Author:        Chris George                                  */
/*    Date:          11-Nov-2025                                   */
/*    Purpose:       implements helper functions                   */
/*******************************************************************/

#include "functions.h"
#include <iostream>     // for error messages
#include <cstdlib>      // for exit()
#include <iomanip>      // for formatting
#include <sstream>      // for stringstream
#include <cctype>       // for isdigit, isupper

using namespace std;

/*****************************************************************/
/*    Function name:   isUpperDigitString                        */
/*    Description:     checks if all characters are uppercase     */
/*                     letters or digits                          */
/*    Parameters:      const string& s                            */
/*    Return Value:    bool                                       */
/*****************************************************************/
bool isUpperDigitString(const string& s) {
    for (char c : s) {
        if (!isupper(c) && !isdigit(c))
            return false;
    }
    return true;
}

/*****************************************************************/
/*    Function name:   priceToCents                              */
/*    Description:     converts string price to cents               */
/*    Parameters:      const string& token                        */
/*    Return Value:    int cents or -1 if bad                     */
/*****************************************************************/
int priceToCents(const string& token) {
    size_t dot = token.find('.');
    if (dot == string::npos) return -1;

    string dollars = token.substr(0, dot);
    string cents   = token.substr(dot + 1);

    if (cents.length() != 2) return -1;

    for (char c : dollars)
        if (!isdigit(c)) return -1;

    for (char c : cents)
        if (!isdigit(c)) return -1;

    long d = stoll(dollars);
    long c = stoll(cents);

    return (int)(d * 100 + c);
}

/*****************************************************************/
/*    Function name:   moneyString                               */
/*    Description:     converts integer cents to string            */
/*    Parameters:      long cents                                  */
/*    Return Value:    string                                     */
/*****************************************************************/
string moneyString(long cents) {
    ostringstream os;
    os << (cents / 100) << "." << setw(2) << setfill('0') 
       << (llabs(cents) % 100);
    return os.str();
}

/*****************************************************************/
/*    Function name:   errorExit                                 */
/*    Description:     prints message and exits program           */
/*    Parameters:      const string& msg                          */
/*    Return Value:    none                                        */
/*****************************************************************/
void errorExit(const string& msg) {
    cerr << "ERROR: " << msg << endl;
    exit(1);
}

/*****************************************************************/
/*    Function name:   errorExitTx                               */
/*    Description:     prints message                              */
/*    Parameters:      msg, tx structure, raw text line           */
/*    Return Value:    none                                       */
/*****************************************************************/
void errorExitTx(const string& msg, const Transaction& tx, const string& raw) {
    cerr << "ERROR: " << msg << endl;
    cerr << "  line " << tx.lineNo << ": "
         << tx.dateYYYYMMDD << " " << tx.symbol << " "
         << tx.type << " " << tx.shares << " "
         << moneyString(tx.priceCents) << endl;
    cerr << "  raw: " << raw << endl;
    exit(1);
}
