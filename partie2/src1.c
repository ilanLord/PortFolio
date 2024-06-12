#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

/********************************
***DECLARATION DES CONSTANTES****
*********************************/
/**
 * \file src1.c
 * \brief Jeu du Pierre Feuille Ciseau
 * \author Ilan MATHIEU
 * \version 1.0
 * \date 3 Décembre 2023
 */

/**
 * \def char PIERRE
 * 
 * \brief constante pour le choix PIERRE
*/
const char PIERRE='P';
/**
 * \def char CISEAU
 * 
 * \brief constante pour le choix CISEAU
*/
const char CISEAU='C';
/**
 * \def char FEUILLE
 * 
 * \brief constante pour le choix FEUILLE
*/
const char FEUILLE='F';
/**
 * \def char VICTOIRE
 * 
 * \brief constante pour indiquer le résultat de la manche gagnée
*/
const char VICTOIRE='G';
/**
 * \def char DEFAITE
 * 
 * \brief constante pour indiquer le résultat de la manche perdue
*/
const char DEFAITE='P';
/**
 * \def char EGALITE
 * 
 * \brief constante pour indiqué le résultat de la manche égalité
*/
const char EGALITE='N';
/**
 * \def char HUMAIN
 * 
 * \brief constante pour indiquer le gagnant HUMAIN
*/
const char HUMAIN='H';
/**
 * \def char ORDI
 * 
 * \brief constante pour indiquer le gagnat ORDI
*/
const char ORDI='O';
/**
 * \def int PTS_VICTOIRE
 * 
 * \brief constante pour indiquer le nombre de points pour gagner
*/
const int PTS_VICTOIRE=3;

/********************************
****LISTE FONCTIONS/CONSTANTES***
*********************************/
char PFC(char action1, char action2);
char genererAction();
char jouer();

/********************************
****PROGRAMME PRINCIPAL**********
*********************************/
int main(){
	char res;
    res = jouer();
    if (res == HUMAIN) {
        printf("Victoire !\n");
    } else {
        printf("Défaite !\n");
    }
   	return EXIT_SUCCESS;
}

/**
 * \fn char PFC(char action1, char action2)
 * 
 * \brief Manche du jeu pierre feuille ciseaux
 * 
 * \param action1 action parmis Pierre, Feuille ou Ciseau
 * \param action2 action parmis Pierre, Feuille ou Ciseau
 * 
 * \return Résultat selon les deux choix du point de vue de l'action 1, Victoire, Défaite ou égalité
*/
char PFC(char action1, char action2) {
    char resultat;
    if (action1==PIERRE && action2==CISEAU) {
        resultat = VICTOIRE;
    } else if (action1==PIERRE && action2==PIERRE) {
        resultat = EGALITE;
    } else if (action1==PIERRE && action2==FEUILLE) {
        resultat = DEFAITE;
    } else if (action1==CISEAU && action2==CISEAU) {
        resultat = EGALITE;
    } else if (action1==CISEAU && action2==PIERRE) {
        resultat = DEFAITE;
    } else if (action1==CISEAU && action2==FEUILLE) {
        resultat = VICTOIRE;
    } else if (action1==FEUILLE && action2==CISEAU) {
        resultat = DEFAITE;
    } else if (action1==FEUILLE && action2==PIERRE) {
        resultat = VICTOIRE;
    } else {
        resultat = EGALITE;
    }
    return resultat;
}

/**
 * \fn char genererAction()
 * 
 * \brief Génère une action aléatoire entre Pierre, Feuille ou Ciseau
 * 
 * \return L'action choisis aléatoirement
*/
char genererAction() {
    char actionAléatoire;
    srand(time(NULL));
    if (rand()%2 == 0) {
        actionAléatoire = PIERRE;
    } else if (rand()%2 == 1) {
        actionAléatoire = FEUILLE;
    } else {
        actionAléatoire = CISEAU;
    }
    return actionAléatoire;
}

/**
 * \fn char jouer()
 * 
 * \brief Dérouler d'une partie de Pierre, Feuille, Ciseau, le joueur choisis une action et une action aléatoire est
 * donné par l'ordinateur, le premier à 3 points gagne
 * 
 * \return Résultat de la partie, HUMAIN si le joueur gagner, ORDI si inverse
*/
char jouer() {
    int ptsOrdi;
    int ptsJoueur;
    ptsJoueur = 0;
    ptsOrdi = 0;
    char choix;
    char res;
    char poubelle;

    while (ptsOrdi != PTS_VICTOIRE && ptsJoueur != PTS_VICTOIRE) {
        printf("Choix: ");
        scanf("%c%c",&choix,&poubelle);
        if (PFC(choix, genererAction()) == VICTOIRE) {
            printf("Gagné !\n");
            ptsJoueur++;
        } else if (PFC(choix, genererAction()) == DEFAITE) {
            ptsOrdi++;
            printf("Perdu !\n");
        } else {
            printf("Match Nul !\n");
        }
    }
    if (ptsJoueur == PTS_VICTOIRE) {
        res = HUMAIN;
    } else {
        res = ORDI;
    }
    return res;
}