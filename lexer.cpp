#include "lexer.h"

Symbole *Lexer::Consulter()
{
   if (!tampon)
   {

      if ((unsigned long)tete == flux.length())
         tampon = new Symbole(FIN);
      else
      {

         switch (flux[tete])
         {
         case '(':
            tampon = new Symbole(OPENPAR);
            tete++;
            break;
         case ')':
            tampon = new Symbole(CLOSEPAR);
            tete++;
            break;
         case '*':
            tampon = new Symbole(MULT);
            tete++;
            break;
         case '+':
            tampon = new Symbole(PLUS);
            tete++;
            break;
         default:
            if (flux[tete] >= '0' && flux[tete] <= '9')
            {
               int resultat = flux[tete] - '0';
               int i = 1;
               while (static_cast<size_t>(tete + i) < flux.size() &&
                      flux[tete + i] >= '0' && flux[tete + i] <= '9')
               {
                  resultat = resultat * 10 + (flux[tete + i] - '0');
                  i++;
               }
               tete = tete + i;
               tampon = new Entier(resultat);
            }
            else
            {
               tampon = new Symbole(ERREUR);
            }
         }
      }
   }
   return tampon;
}

void Lexer::Avancer()
{
   delete tampon;
   tampon = nullptr;
}

void Lexer::avancerSansSuppression()
{
   tampon = nullptr;
}

Lexer::~Lexer()
{
   delete tampon;
}
