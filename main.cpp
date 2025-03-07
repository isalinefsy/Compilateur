#include <iostream>
#include "lexer.h"
#include "automate.h"
#include <unistd.h>

using namespace std;

int main(void)
{
   string chaine("(1+2)*6");

   Lexer l(chaine);

   Symbole *s;
   while (*(s = l.Consulter()) != FIN)
   {
      s->Affiche();
      cout << endl;
      l.Avancer();
   }

   Automate a(chaine);
   a.lancerProg();

   sleep(100);
   return 0;
}
