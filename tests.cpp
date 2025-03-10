#include <iostream>
#include "automate.h"
using namespace std;

void executerTest(string expression, double valeurAttendue, bool doitEchouer = false)
{
    cout << "\n=========================\n";
    cout << "Test en cours: " << expression << endl;

    Automate automate(expression);
    automate.lancerProg();

    if (doitEchouer)
    {
        cout << "ATTENDU: Erreur de syntaxe\n";
    }
    else
    {
        cout << "ATTENDU: " << valeurAttendue << endl;
    }
    cout << "=========================\n";
}

int main()
{
    // Tests valides
    executerTest("3+5", 8);
    executerTest("2*3", 6);
    executerTest("(1+2)*6", 18);
    executerTest("3+(4*2)", 11);
    executerTest("(4+2)*(6+1)", 42);
    executerTest("(4*12)+3*1*6+3", 69);

    // Tests invalides (doivent être rejetés)
    executerTest("+3", 0, true);
    executerTest("3+", 0, true);
    executerTest("()", 0, true);
    executerTest("(3+5", 0, true);
    executerTest("3++5", 0, true);
    executerTest("3*/5", 0, true);
    executerTest("abc+3", 0, true);
    executerTest("3-2", 0, true);

    return 0;
}
