#include <iostream>
#include "automate.h"
using namespace std;

void executerTest(string expression, double valeurAttendue, bool doitEchouer = false)
{
    cout << "\n=========================\n";
    cout << "Test en cours: " << expression << endl;

    Automate automate(expression);
    bool resultat = automate.lancerProg(); // Récupère le résultat de l'analyse

    if (doitEchouer)
    {
        if (!resultat)
            cout << " ATTENDU: Erreur de syntaxe" << endl;
        else
            cout << "ERREUR: Expression acceptée alors qu'elle devrait échouer !" << endl;
    }
    else
    {
        if (resultat)
            cout << " ATTENDU: " << valeurAttendue << endl;
        else
            cout << "ERREUR: Expression invalide alors qu'elle devrait être correcte !" << endl;
    }
    cout << "=========================\n";
}

int main()
{
    // Tests valides
    executerTest("3+5", 8);
    executerTest("3 + 5 ", 8);
    executerTest("2*3", 6);
    executerTest("(1+2)*6", 18);
    executerTest("3+(4*2)", 11);
    executerTest("(4+2)*(6+1)", 42);
    executerTest("(4*12)+3*1*6+3", 69);
    executerTest("3", 3);
    executerTest("         5  ", 5);
    executerTest("(3)", 3);
    executerTest("((3))", 3);
    executerTest("((3)+2)", 5);

    // Tests invalides (doivent être rejetés)
    executerTest("+3", 0, true);
    executerTest("3+", 0, true);
    executerTest("()", 0, true);
    executerTest("(3+5", 0, true);
    executerTest("3++5", 0, true);
    executerTest("3*/5", 0, true);
    executerTest("abc+3", 0, true);
    executerTest("3-2", 0, true);
    executerTest("3/2", 0, true);
    executerTest("6*", 0, true);
    executerTest("*6", 0, true);
    executerTest("", 0, true);

    return 0;
}
