#include "automate.h"
#include <iostream>

using namespace std;

Automate::Automate(string flux) : lexer(new Lexer(flux))
{
    Etat *etat0 = new Etat0();
    pileEtats.push_back(etat0);
}

void Automate::decalage(Symbole *s, Etat *e)
{
    // On ajoute le symbole et l'état à la pile
    pileSymboles.push_back(s);
    pileEtats.push_back(e);

    // On avance le lexer pour lire le prochain symbole
    lexer->Avancer();
}

void Automate::transitionSimple(Symbole *s, Etat *e)
{
    // On ajoute le symbole et l'état à la pile
    pileSymboles.push_back(s);
    pileEtats.push_back(e);
}

void Automate::reduction(int n, Symbole *s)
{
    // On récupère les n derniers symboles de la pile
    for (int i = 0; i < n; i++)
    {
        delete (pileEtats.back());
        pileEtats.pop_back();
    }

    pileEtats.back()->transition(*this, s);
}

// Cette méthode permet de calculer l'expression de l'automate
void Automate::evaluer()
{
    bool retourTransition = true;

    // Tant que l'on peut effectuer une transition, on continue
    while (retourTransition)
    {
        Symbole *symbole = lexer->Consulter();
        retourTransition = pileEtats.back()->transition(*this, symbole);
    }

    cout << "Fin la lecture de l'expression" << endl;
    for (int i = 0; i < pileSymboles.size(); ++i)
    {
        pileSymboles[i]->Affiche();
    }
}

Symbole *Automate::popSymbole()
{
    if (!pileSymboles.empty())
    {
        Symbole *s = pileSymboles.back();
        pileSymboles.pop_back();
        return s;
    }
    return nullptr; // Gestion d'erreur si la pile est vide
}

void Automate::popEtDetruireSymbole()
{
    if (!pileSymboles.empty())
    {
        delete pileSymboles.back(); // Libération de la mémoire
        pileSymboles.pop_back();
    }
}
