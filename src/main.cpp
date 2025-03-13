#include <iostream>
#include "lexer.h"
#include "automate.h"
#include <unistd.h>

using namespace std;

int main(void)
{
   string chaine("(1+2)*3+4*5");
   Automate a(chaine);

   a.lancerProg();
   cout<<"Resultat attendu : 29"<<endl;

   return 0;
}
