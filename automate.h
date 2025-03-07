#ifndef AUTOMATE_H
#define AUTOMATE_H

#include <string>
#include <vector>
#include "lexer.h"
#include "symbole.h"

// Déclaration anticipée de la classe Etat
class Etat;

class Automate
{

private:
    bool expressionAcceptee;

public:
    Automate(std::string flux);
    ~Automate();
    void evaluer();
    void decalage(Symbole *s, Etat *e);
    void reduction(int n, Symbole *s);
    void transitionSimple(Symbole *s, Etat *e);
    void calcul();
    void accepter();
    void setExpressionAcceptee(bool status) { expressionAcceptee = status; }
    bool isExpressionAcceptee() const { return expressionAcceptee; }
    void lancerProg();
    Symbole *popSymbole();
    void popEtDetruireSymbole();

    std::vector<Symbole *> pileSymboles;
    std::vector<Etat *> pileEtats;
    Lexer *lexer;
    Symbole *symboleCourant;
};

#endif
