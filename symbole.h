#pragma once

#include <string>
#include <map>
#include <iostream>
using namespace std;

enum Identificateurs
{
   OPENPAR,
   CLOSEPAR,
   PLUS,
   MULT,
   INT,
   FIN,
   ERREUR,
   EXPR
};

const string Etiquettes[] = {"OPENPAR", "CLOSEPAR", "PLUS", "MULT", "INT", "FIN", "ERREUR", "EXPR"};

class Symbole
{
public:
   Symbole(int i) : ident(i) {}
   virtual ~Symbole() {}
   operator int() const { return ident; }
   virtual void Affiche();
   int getType() const { return ident; }

protected:
   int ident;
};

class Entier : public Symbole
{
public:
   Entier(int v) : Symbole(INT), valeur(v) {}
   ~Entier() {}
   virtual void Affiche();
   int getValeur() const { return valeur; }

protected:
   int valeur;
};

class Expr : public Symbole
{
public:
   Expr() : Symbole(EXPR) {}
   virtual ~Expr() {}
   virtual double eval(const map<string, double> &valeurs) const = 0;
};

class ExprEntier : public Expr
{
public:
   ExprEntier(int v) : valeur(v) {}
   double eval(const std::map<std::string, double> &valeurs) const override
   {
      (void)valeurs;
      return valeur;
   }

   void Affiche() override
   {
      cout << valeur;
   }

private:
   int valeur;
};

class ExprPlus : public Expr
{
public:
   ExprPlus(Expr *gauche, Expr *droite) : gauche(gauche), droite(droite) {}
   ~ExprPlus()
   {
      delete gauche;
      delete droite;
   }

   double eval(const map<string, double> &valeurs) const override
   {
      return gauche->eval(valeurs) + droite->eval(valeurs);
   }

   void Affiche() override
   {
      cout << "(";
      gauche->Affiche();
      cout << " + ";
      droite->Affiche();
      cout << ")";
   }

private:
   Expr *gauche;
   Expr *droite;
};

class ExprMult : public Expr
{
public:
   ExprMult(Expr *gauche, Expr *droite) : gauche(gauche), droite(droite) {}

   ~ExprMult()
   {
      delete gauche;
      delete droite;
   }

   double eval(const map<string, double> &valeurs) const override
   {
      return gauche->eval(valeurs) * droite->eval(valeurs);
   }

   void Affiche() override
   {
      cout << "(";
      gauche->Affiche();
      cout << " * ";
      droite->Affiche();
      cout << ")";
   }

private:
   Expr *gauche;
   Expr *droite;
};
