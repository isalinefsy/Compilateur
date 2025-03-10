#pragma once
#include <iostream>
#include <string>
#include "automate.h"
#include "symbole.h"

using namespace std;
class Automate; // Déclaration anticipée de la classe Automate

class Etat
{
public:
    Etat(string nomEtat) : nomEtat(nomEtat) {}
    Etat();
    virtual ~Etat();
    void print() const { cout << "Etat: " << nomEtat << endl; }
    virtual bool transition(Automate &automate, Symbole *s) = 0;
    virtual int etat() = 0; // permet de savoir avec quel etat on travail

protected:
    string nomEtat;
};

class Etat0 : public Etat
{
public:
    Etat0();
    ~Etat0();
    bool transition(Automate &automate, Symbole *s) override;
    virtual int etat() override;
};

class Etat1 : public Etat
{
public:
    Etat1();
    ~Etat1();
    bool transition(Automate &automate, Symbole *s) override;
    virtual int etat() override;
};

class Etat2 : public Etat
{
public:
    Etat2();
    ~Etat2();
    bool transition(Automate &automate, Symbole *s) override;
    virtual int etat() override;
};

class Etat3 : public Etat
{
public:
    Etat3();
    ~Etat3();
    bool transition(Automate &automate, Symbole *s) override;
    virtual int etat() override;
};

class Etat4 : public Etat
{
public:
    Etat4();
    ~Etat4();
    bool transition(Automate &automate, Symbole *s) override;
    virtual int etat() override;
};

class Etat5 : public Etat
{
public:
    Etat5();
    ~Etat5();
    bool transition(Automate &automate, Symbole *s) override;
    virtual int etat() override;
};

class Etat6 : public Etat
{
public:
    Etat6();
    ~Etat6();
    bool transition(Automate &automate, Symbole *s) override;
    virtual int etat() override;
};

class Etat7 : public Etat
{
public:
    Etat7();
    ~Etat7();
    bool transition(Automate &automate, Symbole *s) override;
    virtual int etat() override;
};

class Etat8 : public Etat
{
public:
    Etat8();
    ~Etat8();
    bool transition(Automate &automate, Symbole *s) override;
    virtual int etat() override;
};

class Etat9 : public Etat
{
public:
    Etat9();
    ~Etat9();
    bool transition(Automate &automate, Symbole *s) override;
    virtual int etat() override;
};
