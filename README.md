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

### Tests

✅ Tests valides (doivent être acceptés et retourner le bon résultat)

Expression Attendu
3+5 8
2*3 6
(1+2)*6 18
(4+2)*(6+1) 42
3+(4*2) 11
42 42
❌ Tests invalides (doivent être rejetés avec "Erreur de syntaxe")

Expression Erreur attendue
-3 Non supporté (-)
10-4 Non supporté (-)
8/2 Non supporté (/)
3+ Opérateur sans opérande droite
() Parenthèses vides
(3+5 Parenthèse ouvrante non fermée
3+5) Parenthèse fermante sans ouverture
3++5 Opérateur en double
3\*/5 Opérateurs consécutifs invalides
3 5 Espaces non gérés entre nombres
abc+3 Caractères invalides
