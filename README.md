## Analyse Syntaxique et Évaluation d'une Expression Arithmétique

### Évaluation

- Code commenté et bien structuré.
- Les expressions doivent fonctionner correctement : si elles ne correspondent pas à la grammaire, le programme ne doit pas planter.

### Gestion des Erreurs

- Détecter les cases vides dans la table d’évaluation et fournir un message d'erreur bien construit.
- Inclure dans la classe `Automate` un mécanisme pour stocker les erreurs sans arrêter l'exécution.

### Gestion de la Mémoire

- Utiliser Valgrind pour la gestion de la mémoire.

### Simplification des Classes

- Regrouper les 10 classes d'états en un seul fichier `.h` et `.cpp`.

## TP Compilateur – Analyse Syntaxique et Évaluation d'Expressions Arithmétiques

Ce projet implémente un analyseur syntaxique descendant (bottom-up) basé sur un automate LALR(1) pour la reconnaissance et l'évaluation d'expressions arithmétiques. Il utilise notamment le pattern "State" pour gérer les transitions et les réductions selon la grammaire suivante :

```
E' -> E
E  -> E + E
E  -> E * E
E  -> ( E )
E  -> val
```

Les conflits liés à l'ambiguïté de la grammaire sont résolus en appliquant :

- L'associativité gauche pour l'opérateur `+`
- L'associativité gauche pour l'opérateur `*`
- La priorité de `*` sur `+`

Le document [TP Compil-2024-Anglais.pdf]​ présente le contexte et les spécifications de l'exercice.

### Organisation du Code

- **lexer.h / lexer.cpp** : Contiennent l'implémentation du Lexer qui lit la chaîne d'entrée et extrait les symboles (entiers, parenthèses, opérateurs).
- **symbole.h / symbole.cpp** : Définissent les types de symboles utilisés (par exemple, `OPENPAR`, `CLOSEPAR`, `PLUS`, `MULT`, `INT`, etc.) ainsi que des classes pour représenter des entiers et des expressions.
- **automate.h / automate.cpp** : Implémentent l'automate qui gère la pile d'états et de symboles, réalise les décalages, les réductions et lance l'analyse de l'expression.
- **etat.h / etat.cpp** : Contiennent la définition et l'implémentation des différents états (`Etat0` à `Etat9`) de l'automate, chacun implémentant sa fonction de transition selon le symbole courant.
- **main.cpp** : Programme principal qui crée un Lexer et un Automate, affiche les symboles lus et évalue une expression prédéfinie `(1+2)*3+4*5`.
- **tests.cpp** : Fournit un ensemble de tests automatisés pour vérifier le bon fonctionnement de l'analyseur syntaxique et de l'évaluateur d'expressions.

### Compilation

#### Prérequis

- Un compilateur C++ supportant au moins le standard C++11 (ex. : g++).
- Outils de développement type Make (optionnel).

#### Compilation du Programme Principal

Pour compiler le programme principal, ouvrez un terminal dans le répertoire du projet et exécutez la commande suivante :

```sh
make
```

#### Compilation des Tests

Pour compiler la suite de tests, utilisez la commande :

```sh
make tests
```

### Exécution

#### Exécution du Programme Principal

Pour lancer le programme principal, utiliser la commande :

```sh
./bin/compilateur
```

ou

```sh
valgrind ./bin/compilateur
```

Si vous souhaitez vérifier la gestion de la mémoire (sous Linux).

Ce programme effectue les opérations suivantes :

- Utilise le Lexer pour afficher les symboles extraits de la chaîne `(1+2)*3+4*5`.
- Initialise et lance l'automate pour analyser et évaluer l'expression.
- Affiche le résultat de l'expression évaluée.

#### Exécution des Tests

Pour exécuter la suite de tests, utilisez la commande :

```sh
./bin/tests
```

ou

```sh
valgrind ./bin/tests
```

Si vous souhaitez vérifier la gestion de la mémoire (sous Linux).

Les tests implémentés dans `tests.cpp` comprennent :

- **Tests valides** :
  - `"3+5"` doit être évalué à `8`
  - `"3 + 5"` doit être évalué à `8`
  - `"2*3"` doit être évalué à `6`
  - `"(1+2)*6"` doit être évalué à `18`
  - `"3+(4*2)"` doit être évalué à `11`
  - `"(4+2)*(6+1)"` doit être évalué à `42`
  - `"(4*12)+3*1*6+3"` doit être évalué à `69`
  - `"3"` doit être évalué à `3`
  - `"         5  "` doit être évalué à `5`
  - `"(3)"` doit être évalué à `3`
  - `"((3))"` doit être évalué à `3`
  - `"((3)+2)"` doit être évalué à `5`
- **Tests invalides (détectés comme erreurs de syntaxe)** :
  - `"+3"`
  - `"3+"`
  - `"()"`
  - `"(3+5"`
  - `"3++5"`
  - `"3*/5"`
  - `"abc+3"`
  - `"3-2"`
  - `"6*"`
  - `"*6"`
  - `""`

Chaque test affiche dans le terminal si l'expression a été acceptée ou rejetée, et dans le cas d'une expression correcte, le résultat calculé est affiché.

### Remarques

#### Gestion des Erreurs

L'automate affiche directement des messages d'erreur en cas de problème de syntaxe lors de l'analyse de l'expression.

### Auteurs

Isaline Foissey et Pierrick Brossat
