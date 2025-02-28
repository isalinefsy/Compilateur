#ifndef AUTOMATE_H
#define AUTOMATE_H

#include <string>
#include <vector>
#include "lexer.h"
#include "etat.h"
#include "symbole.h"

class Automate
{
public:
    Automate(string flux);
    ~Automate();
    void evaluer();
    void decalage(Symbole *s, Etat *e);
    void reduction(int n, Symbole *s);
    void transitionSimple(Symbole *s, Etat *e);
    void calcul();
    void accepter();
    Symbole *popSymbole();
    void popEtDetruireSymbole();

private:
    vector<Symbole *> pileSymboles;
    vector<Etat *> pileEtats;
    Lexer *lexer;
    Symbole *symboleCourant;
};

#endif