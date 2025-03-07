#include <iostream>
#include "automate.h"
using namespace std;

void runTest(string expression, double expectedValue, bool shouldFail = false)
{
    cout << "\n=========================\n";
    cout << "Testing: " << expression << endl;

    Automate automate(expression);
    automate.lancerProg();

    if (shouldFail)
    {
        cout << "EXPECTED: Syntax error\n";
    }
    else
    {
        cout << "EXPECTED: " << expectedValue << endl;
    }
    cout << "=========================\n";
}

int main()
{
    // Tests valides
    runTest("3+5", 8);
    runTest("2*3", 6);
    runTest("(1+2)*6", 18);
    runTest("3+(4*2)", 11);
    runTest("(4+2)*(6+1)", 42);

    // Tests invalides (doivent être rejetés)
    runTest("+3", 0, true);
    runTest("3+", 0, true);
    runTest("()", 0, true);
    runTest("(3+5", 0, true);
    runTest("3++5", 0, true);
    runTest("3*/5", 0, true);
    runTest("abc+3", 0, true);

    return 0;
}
