#include "etat.h"
#include "automate.h"
#include "symbole.h"
#include <iostream>

using namespace std;

Etat::~Etat() {}
Etat0::Etat0() : Etat("E0") {}
Etat1::Etat1() : Etat("E1") {}
Etat2::Etat2() : Etat("E2") {}
Etat3::Etat3() : Etat("E3") {}
Etat4::Etat4() : Etat("E4") {}
Etat5::Etat5() : Etat("E5") {}
Etat6::Etat6() : Etat("E6") {}
Etat7::Etat7() : Etat("E7") {}
Etat8::Etat8() : Etat("E8") {}
Etat9::Etat9() : Etat("E9") {}
Etat0::~Etat0() {}
Etat1::~Etat1() {}
Etat2::~Etat2() {}
Etat3::~Etat3() {}
Etat4::~Etat4() {}
Etat5::~Etat5() {}
Etat6::~Etat6() {}
Etat7::~Etat7() {}
Etat8::~Etat8() {}
Etat9::~Etat9() {}

bool Etat0::transition(Automate &automate, Symbole *s)
{
    switch (*s)
    {
    case INT:
        automate.decalage(s, new Etat3);
        break;
    case OPENPAR:
        automate.decalage(s, new Etat2);
        break;
    default:
        cout << "Erreur de syntaxe" << endl;
        return false;
    }
    return true;
}

bool Etat1::transition(Automate &automate, Symbole *s)
{
    switch (*s)
    {
    case PLUS:
        automate.decalage(s, new Etat4);
        break;
    case MULT:
        automate.decalage(s, new Etat5);
        break;
    case FIN:
        automate.accepter();
        break;
    default:
        cout << "Erreur de syntaxe" << endl;
        return false;
    }
    return true;
}

bool Etat2::transition(Automate &automate, Symbole *s)
{
    switch (*s)
    {
    case INT:
        automate.decalage(s, new Etat3);
        break;
    case OPENPAR:
        automate.decalage(s, new Etat2);
        break;
    case EXPR:
        automate.transitionSimple(s, new Etat6);
        break;
    default:
        cout << "Erreur de syntaxe" << endl;
        return false;
    }
    return true;
}

bool Etat3::transition(Automate &automate, Symbole *s)
{
    switch (*s)
    {
    case PLUS:
    case MULT:
    case CLOSEPAR:
    case FIN:
        // E -> val
        automate.reduction(1, s);
        break;
    default:
        cout << "Erreur de syntaxe" << endl;
        return false;
    }
    return true;
}

bool Etat4::transition(Automate &automate, Symbole *s)
{
    switch (*s)
    {
    case INT:
        automate.decalage(s, new Etat3);
        break;
    case OPENPAR:
        automate.decalage(s, new Etat2);
        break;
    case EXPR:
        automate.transitionSimple(s, new Etat7);
        break;
    default:
        cout << "Erreur de syntaxe" << endl;
        return false;
    }
    return true;
}

bool Etat5::transition(Automate &automate, Symbole *s)
{
    switch (*s)
    {
    case INT:
        automate.decalage(s, new Etat3);
        break;
    case OPENPAR:
        automate.decalage(s, new Etat2);
        break;
    case EXPR:
        automate.transitionSimple(s, new Etat8);
        break;
    default:
        cout << "Erreur de syntaxe" << endl;
        return false;
    }
    return true;
}

bool Etat6::transition(Automate &automate, Symbole *s)
{
    switch (*s)
    {
    case PLUS:
        automate.decalage(s, new Etat4);
        break;
    case MULT:
        automate.decalage(s, new Etat5);
        break;
    case CLOSEPAR:
        automate.decalage(s, new Etat9);
        break;
    default:
        cout << "Erreur de syntaxe" << endl;
        return false;
    }
    return true;
}

bool Etat7::transition(Automate &automate, Symbole *s)
{
    Expr *s1, *s2;
    switch (*s)
    {
    case PLUS:
    case CLOSEPAR:
    case FIN:
        if (automate.pileSymboles.size() >= 2) // Vérifie qu'il y a suffisamment d'éléments dans la pile
        {
            s1 = (Expr *)automate.popSymbole();
            automate.popEtDetruireSymbole(); // Supprime le symbole de la pile
            s2 = (Expr *)automate.popSymbole();
            automate.reduction(3, new ExprPlus(s1, s2)); // Réduction de E + E en E
        }
        else
        {
            cout << "Erreur : pile insuffisante pour la réduction" << endl;
            return false;
        }
        break;
    case MULT:
        automate.decalage(s, new Etat5);
        break;
    default:
        cout << "Erreur de syntaxe" << endl;
        return false;
    }
    return true;
}

bool Etat8::transition(Automate &automate, Symbole *s)
{
    Expr *s1, *s2;
    switch (*s)
    {
    case PLUS:
    case MULT:
    case CLOSEPAR:
    case FIN:
        s1 = (Expr *)automate.popSymbole();
        automate.popEtDetruireSymbole(); // Assurez-vous que cette fonction appelle 'delete' pour supprimer les objets
        s2 = (Expr *)automate.popSymbole();
        automate.reduction(3, new ExprMult(s1, s2));
        break;
    default:
        cout << "Erreur de syntaxe" << endl;
        return false;
    }
    return true;
}

bool Etat9::transition(Automate &automate, Symbole *s)
{
    Expr *expr;
    switch (*s)
    {
    case PLUS:
    case MULT:
    case CLOSEPAR:
    case FIN:
        expr = (Expr *)automate.popSymbole();
        automate.popEtDetruireSymbole(); // Assurez-vous que cette fonction appelle 'delete' pour supprimer les objets
        automate.reduction(3, expr);
        break;
    default:
        cout << "Erreur de syntaxe" << endl;
        return false;
    }
    return true;
}

// Permet de retourner l'etat de l'automate
int Etat0::etat() { return 0; }
int Etat1::etat() { return 1; }
int Etat2::etat() { return 2; }
int Etat3::etat() { return 3; }
int Etat4::etat() { return 4; }
int Etat5::etat() { return 5; }
int Etat6::etat() { return 6; }
int Etat7::etat() { return 7; }
int Etat8::etat() { return 8; }
int Etat9::etat() { return 9; }