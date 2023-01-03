# Minestorm project

Ce projet est notre premier projet de programmation a Isart Digital.

## Presentation
L'objectif est de recoder le jeu Minestorm sorti en 1982 sur Vectrex

https://www.youtube.com/watch?v=pbdccgon96M

## Le jeu

Pour lancer le jeu, entrez cette commande dans le terminal a la racine du projet
```sh
make && ./minestorm
```

Si vous avez deja effectué la commande make, vous pouvez simplement entrer :
```sh
./minestorm
```

Pour supprimer les fichier binaire afin d'alléger le répertoire :
```sh
make clean
```

## Tests
Ces commandes sont a entrer dans le terminal a la racine.

**Test de Colision AABB :**

Ce test initialise 4 carrés dont trois en déplacement, l'un a l'horizontale, l'autre a la verticale et le dermier en diagonale,
l'objectif étant de tester la colision de ces trois carrés avec le dernier immobile.
Un dernier carré suit le curseur.

Pour effectuer le test de collision AABB, enrez cette commande a la racine :
```sh
make TestCollisionAABB && ./a.out
```

**Test de colision SAT**

Ce test a pour but de tester notre application de l'algoritme de colision SAT.

Nous initialisons alors 4 triangles, a l'instar du test de colision AABB, en déplacement,
l'un en horizontale, l'autre a la verticale, un autre en diagonale et le dernier suis le curseur.
Lorsqu'une colision avec la forme quelconque au centre est detecté, le triangle en mouvement s'affiche en rouge.

```sh
make TestColisionSAT && ./TestColisionSAT
```

## Nomenclature du projet

```sh
.
├── a.out
├── assets
│   ├── Assets Mine Storm.jpg
│   ├── logo.png
│   ├── minestorm_background.png
│   ├── minestorm_foreground.jpg
│   ├── minestorm_foreground.png
│   └── minestorm_sprite_atlas_mine_storm.png
├── Makefile
├── README.md
├── src
│   ├── game.c
│   ├── game.h
│   ├── main.c
│   ├── mines.c
│   ├── mines.h
│   ├── myMaths.c
│   ├── myMaths.h
│   ├── player.c
│   └── player.h
├── TestColision_AABB.d
├── tests
│   └── TestColision_AABB.c
└── third_party
    ├── include
    │   └── raylib.h
    ├── libs-x86_64-linux-gnu
    │   └── libraylib.a
    └── libs-x86_64-pc-cygwin
        └── libraylib.a
```

## Auteur
N Masseteau & Tangui Samson

n.masseteau@student.isartdigital.com

t.samson@student.isartdigital.com