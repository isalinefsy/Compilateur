#include "automate.h"
#include <iostream>
#include "etat.h" // Include the header file where Etat0 is defined

using namespace std;

Automate::Automate(string flux) : lexer(new Lexer(flux)), expressionAcceptee(false)
{
    Etat *etat0 = new Etat0();
    pileEtats.push_back(etat0);
}

bool Automate::lancerProg()
{
    evaluer(false); // Analyse et évaluation de l'expression

    if (isExpressionAcceptee()) // Si l'expression est valide
    {
        afficherResultat();
        return true; // Indique que l'expression est correcte
    }

    return false; // Indique une erreur de syntaxe
}

void Automate::afficherResultat()
{
    if (!pileSymboles.empty())
    {
        Symbole *resultat = pileSymboles.back();
        if (resultat->getType() == EXPR)
        {
            Expr *exprResultat = dynamic_cast<Expr *>(resultat);
            if (exprResultat)
            {
                map<string, double> valeurs;
                double valeurFinale = exprResultat->eval(valeurs);
                cout << "Le résultat de l'expression est : " << valeurFinale << endl;
                return;
            }
        }
    }
    cout << "Erreur : impossible d'évaluer l'expression." << endl;
}

void Automate::decalage(Symbole *s, Etat *e)
{
    // On ajoute le symbole et l'état à la pile
    pileSymboles.push_back(s);
    pileEtats.push_back(e);

    // On avance le lexer sans supprimer le token transféré
    lexer->avancerSansSuppression();
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
        if (!pileEtats.empty()) // Vérifie que la pile n'est pas vide
        {
            delete (pileEtats.back());
            pileEtats.pop_back();
        }
    }

    // On applique la transition avec le nouveau symbole
    if (!pileEtats.empty()) // Vérifie que la pile n'est pas vide
    {
        pileEtats.back()->transition(*this, s);
    }
}

void Automate::evaluer(bool debug)
{
    bool retourTransition = true;

    while (retourTransition)
    {
        Symbole *symbole = lexer->Consulter();
        if (debug)
        {
            cout << "Symbole courant : ";
            symbole->Affiche();
            cout << endl;

            cout << "Etat actuel : " << pileEtats.back()->etat() << endl;

            cout << "Pile des symboles : ";
            for (Symbole *s : pileSymboles)
            {
                s->Affiche();
                cout << " ";
            }
            cout << endl;

            cout << "Pile des états : ";
            for (Etat *e : pileEtats)
            {
                cout << e->etat() << " ";
            }
            cout << endl;
        }

        retourTransition = pileEtats.back()->transition(*this, symbole);

        if (!retourTransition)
        {
            if (!isExpressionAcceptee()) // Si l'expression est invalide
            {
                cout << "Erreur de syntaxe, arrêt de l'automate." << endl;
                expressionAcceptee = false; // Arrête immédiatement avec un code d'erreur
            }
            break;
        }
    }

    cout << "Fin de la lecture de l'expression" << endl;
}

void Automate::accepter()
{
    cout << "L'expression est correcte" << endl;
    expressionAcceptee = true;
    afficherResultat();
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

Automate::~Automate()
{
    // Libérer le lexer
    delete lexer;

    // Libérer la mémoire des symboles
    while (!pileSymboles.empty())
    {
        delete pileSymboles.back();
        pileSymboles.pop_back();
    }

    // Libérer la mémoire des états
    while (!pileEtats.empty())
    {
        delete pileEtats.back();
        pileEtats.pop_back();
    }
}
