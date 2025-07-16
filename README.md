# Minishell

Minishell est un projet du cursus 42 qui consiste à réaliser un shell minimaliste en C, capable d'interpréter et d'exécuter des commandes comme un vrai terminal Unix.

## Auteurs
- **sabejaou** ([sabejaou@student.42lyon.fr](mailto:sabejaou@student.42lyon.fr))
- **anfichet** ([anfichet@student.42lyon.fr](mailto:anfichet@student.42lyon.fr))

## Sommaire
- [Description](#description)
- [Fonctionnalités](#fonctionnalités)
- [Arborescence](#arborescence)
- [Installation](#installation)
- [Utilisation](#utilisation)
- [Exemples](#exemples)

---

## Description
Minishell est un shell interactif qui gère :
- L'exécution de commandes avec leurs arguments
- Les redirections (`>`, `>>`, `<`, `<<`)
- Les pipes (`|`)
- Les variables d'environnement
- Les builtins (`cd`, `echo`, `pwd`, `export`, `unset`, `env`, `exit`)
- La gestion des signaux (Ctrl+C, Ctrl+D, Ctrl+\)
- Les quotes simples et doubles
- L'expansion de variables (`$VAR`, `$?`)

---

## Fonctionnalités
- Exécution de commandes Unix classiques
- Gestion des redirections et des pipes
- Support du heredoc (`<<`)
- Gestion complète des variables d'environnement
- Implémentation des builtins
- Gestion des erreurs et messages explicites
- Utilisation de la bibliothèque readline pour l'historique et l'édition de ligne

---

## Arborescence
```
42-minishell/
├── includes/
│   └── minishell.h
├── src/
│   ├── core/
│   │   └── main.c
│   ├── builtins/
│   │   ├── cd.c ...
│   ├── exec/
│   │   ├── exec.c ...
│   ├── parsing/
│   │   ├── parsing.c ...
│   ├── expand/
│   │   ├── expand.c ...
│   ├── signal/
│   │   └── signal.c
│   └── utils/
│       ├── free_utils.c ...
├── libft/
│   ├── incs/
│   │   └── libft.h
│   └── srcs/
│       └── ...
├── obj/
├── Makefile
├── .gitignore
└── README.md
```

---

## Installation

1. **Cloner le dépôt**
   ```sh
   git clone https://github.com/sabejaou/42-minishell.git
   cd 42-minishell
   ```
2. **Compiler le projet**
   ```sh
   make
   ```

---

## Utilisation

Lancer le shell :
```sh
./minishell
```

Vous pouvez alors taper des commandes comme dans un terminal classique :
```sh
ls -l | grep minishell > result.txt
export VAR=42
cat << EOF
Hello $VAR
EOF
```

---

## Exemples

- **Commande simple** :
  ```sh
  minishell$ ls -la
  ```
- **Redirection** :
  ```sh
  minishell$ echo Hello > file.txt
  ```
- **Pipe** :
  ```sh
  minishell$ cat file.txt | grep Hello
  ```
- **Heredoc** :
  ```sh
  minishell$ cat << EOF
  > Bonjour
  > EOF
  ```
- **Variable d'environnement** :
  ```sh
  minishell$ export NAME=World
  minishell$ echo Hello $NAME
  Hello World
  ```
- **Builtins** :
  ```sh
  minishell$ cd ..
  minishell$ pwd
  minishell$ env
  minishell$ exit
  ```

---

## Remarques
- Le projet respecte les normes et contraintes de l'école 42.
- L'utilisation de la bibliothèque readline est obligatoire.
- La gestion des erreurs et des signaux est soignée.

---

## Auteurs
- **sabejaou**
- **anfichet**