#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>

/**
 * \def TAILLE
 * \brief Constante pour définir la taille du Sudoku.
 */
#define TAILLE 9

/**
 * \def N
 * \brief Les cubes de N*N selon la taille du Sudoku.
 */
const int N = sqrt(TAILLE);

/**
 * \typedef tGrille
 * \brief Type tableau de TAILLE entier.
 *
 * Le type tGrille sert de plateau pour le jeu Sudoku.
 */
typedef int tGrille[TAILLE][TAILLE];

/**
 * \file sudoku.c
 * \brief Sudoku adaptable en taille selon la constante TAILLE.
 * \author Ilan MATHIEU
 * \version 1.0
 * \date 3 Décembre 2023
 *
 * \mainpage Sudoku
 *
 * Ce programme implémente un Sudoku jouable de taille TAILLE*TAILLE.
 *
 * \section intro Introduction
 * - Permet grâce à l'utilisation des différentes procédures et fonctions de jouer au Sudoku.
 * - Pour se faire, il faut au lancement, donner un nom de fichier avec l'extension .sud qui soit valide.
 * - Le programme permet de donner la ligne puis la colonne à choisir pour y placer la valeur souhaitée.
 * - Les règles sont les mêmes qu'au Sudoku standard et sont adaptables à la taille du Sudoku.
 *
 * \tableofcontents
 *
 *
 * \defgroup ProcSaisie Fonctions de Saisie des données
 * @{
 * 	 \fn void chargerGrille(tGrille g)
 *   \fn void saisir(int *valeur)
 * @}
 *
 * \defgroup Affichage Fonctions d'Affichage
 * @{
 * 	 \fn void afficherLigne(tGrille grille1, int numLigne)
 *   \fn void afficherTransition()
 *   \fn void afficherGrille(tGrille grille1)
 * @}
 *
 * \defgroup Tests Fonctions de Tests
 * @{
 *   \fn bool possible(tGrille grille1, int numLigne, int numColonne, int valeur)
 *   \fn bool estPasPlein(tGrille grille1)
 * @}
 *
 * \defgroup ProgrammePrincipal Programme Principal
 * @{
 *   \page ProgrammePrincipal
 *   \section main Fonction principale
 *   \brief Fonction principale du programme.
 *   \return EXIT_SUCCESS si le programme se termine correctement.
 * @}
 */

/*****************************************************
 * \defgroup ProcSaisie Fonctions de Saisie des données
 * @{
 */

/**
 * \fn void chargerGrille(tGrille g)
 * \brief Procédure initialisant le début de la partie.
 *
 * \param g : le tableau représentant le plateau de Sudoku qui est à remplir.
 *
 * Consiste à remplir une partie du Sudoku en chargeant un fichier.sud.
 */
void chargerGrille(tGrille g);

/**
 * \fn void saisir(int *valeur)
 * \brief Permet la saisie d'une valeur.
 *
 * \param *valeur : variable à qui la valeur entrée sera assignée.
 *
 * Permet la saisie d'une valeur pour une variable en vérifiant que la valeur respecte
 * bien les conditions (affiche un message d'erreur si la valeur est une erreur).
 */
void saisir(int *valeur);

/** @} */  // Fin du groupe Fonctions de Saisie des données

/*****************************************************
 * \defgroup FonctionsAffichage Affichage
 * @{
 */

/**
 * \fn void afficherLigne(tGrille grille1, int numLigne)
 * \brief Procédure affichant la ligne de la Grille.
 *
 * \param grille1 : Le tableau correspondant au plateau du Sudoku.
 * \param numLigne : Entier correspondant au numéro de la ligne à afficher.
 *
 * Affiche la ligne correspondant à numLigne de la grille Sudoku.
 */
void afficherLigne(tGrille grille1, int numLigne);

/**
 * \fn void afficherTransition()
 * \brief Affiche les transitions entre les lignes du tableau.
 *
 * Affiche la transition entre les différents carrés de N*N pour les séparer (horizontalement).
 */
void afficherTransition();

/**
 * \fn void afficherGrille(tGrille grille1)
 * \brief Affiche le plateau de Sudoku.
 *
 * \param grille1 : Le tableau correspondant au plateau du Sudoku.
 *
 * Affiche le tableau du Sudoku en entier.
 */
void afficherGrille(tGrille grille1);

/** @} */  // Fin du groupe FonctionsAffichage

/*****************************************************
 * \defgroup Fonctions Tests
 * @{
 */

/**
 * \fn bool possible(tGrille grille1, int numLigne, int numColonne, int valeur)
 * \brief Fonction qui indique s'il est possible de placer la valeur dans le Sudoku.
 *
 * \param grille1 : Le tableau correspondant au plateau du Sudoku.
 * \param numLigne : Numéro de la ligne où la valeur doit être placée.
 * \param numColonne : Numéro de la colonne où la valeur doit être placée.
 * \param valeur : Valeur à placer.
 *
 * Fonction indiquant si la valeur peut être mise dans le plateau de Sudoku
 * tout en respectant les règles du jeu Sudoku.
 */
bool possible(tGrille grille1, int numLigne, int numColonne, int valeur);

/**
 * \fn bool estPasPlein(tGrille grille1)
 * \brief Fonction vérifiant si le plateau est plein ou non.
 *
 * \param grille1 : Le tableau correspondant au plateau du Sudoku.
 *
 * Fonction indiquant si le plateau ne contient aucun 0 et donc, aucune case vide.
 */
bool estPasPlein(tGrille grille1);

/** @} */  // Fin du groupe Fonctions

/*****************************************************
 * \defgroup ProgrammePrincipal Programme Principal
 * @{
 */

/**
 * \fn int main()
 * \brief Programme principal du Sudoku.
 *
 * \return EXIT_SUCCESS en cas de succès.
 * 
 */
int main();

/** @} */  // Fin du groupe ProgrammePrincipal


int main(){
   	//déclaration des variables
	tGrille grille1;
	int numLigne, numColonne, valeur;

   	// saisie des données
	chargerGrille(grille1);
	
	// programme principale
	while (estPasPlein(grille1)) {
		afficherGrille(grille1); // Affichage de la grille à chaque début de tour puis on lance le tour du joueur
		printf("Indices de la case ? ");
		saisir(&numLigne);
		saisir(&numColonne);
		if (grille1[numLigne-1][numColonne-1]!=0) { // On décale de 1 puisque les tableaux ont un indice 0, ainsi la valeur saisie est bien utilisé
			printf("IMPOSSIBLE, la case n'est pas libre.\n"); // On vérifie si la case est vide ou non et on met un message d'erreur si c'est le cas
		} else {
			printf("Valeur à insérer ? ");
			saisir(&valeur);
			if (possible(grille1, numLigne, numColonne, valeur)) { // Si la valeur qu'on veut ajouter respecte les règles du Sudoku
				grille1[numLigne-1][numColonne-1] = valeur; // On décale de 1 pour la même raison qu'au-dessus
			}
		}
	}
	printf("Grille pleine, fin de partie\n");

   	return EXIT_SUCCESS;
}


/*****************************************************
		* LISTE DES PROCÉDURES/FONCTIONS *
*****************************************************/




/*****************************************************
		* PROCÉDURES DE SAISIE DES DONNÉES *
*****************************************************/


void chargerGrille(tGrille g){
	char nomFichier[30];
	FILE * f;
	printf("Nom du fichier ? ");
	scanf("%s", nomFichier);
	f = fopen(nomFichier, "rb");
	while (f==NULL) { // On traite le cas d'erreur
		printf("\n Un nom de fichier valide est attendu\n");
		printf("Nom du fichier ? ");
		scanf("%s", nomFichier);
		f = fopen(nomFichier, "rb");	
	}
	fread(g, sizeof(int), TAILLE*TAILLE, f);
	fclose(f);
}

void saisir(int *valeur) {
	bool continuer;
	continuer = true;
	char ch[2];
	printf("Veuillez rentrer un nombre entier entre 1 et %d: ",N*N);
	scanf("%s", ch);
	while (continuer) {
		if (sscanf(ch, "%d", valeur) !=0 && (*valeur > 0 && *valeur <= N*N)) { // on vérifie que la valeur est entre 0 et 9 et si on peut aussi la transformer en entier, alors on arrete la boucle et la valeur est attribué
			continuer = false;
		} else { // Sinon on reste dans la boucle jusqu'à avoir une saisie valide
			printf("Saisie incorrecte, veuillez saisir un nombre entier entre 1 et %d: ",N*N);
			scanf("%s", ch);
		}
	}
}


/*****************************************************
		* PROCÉDURES D'AFFICHAGE DE LA GRILLE *
*****************************************************/


void afficherLigne(tGrille grille1, int numLigne) { //affichage de la ligne numLigne de la grille

	printf("%3d  |",numLigne);

	for (int col=0 ; col < TAILLE ; col++) {
		if (grille1[numLigne-1][col] == 0) {
			printf(" . ");
		} else {
			printf(" %d ",grille1[numLigne-1][col]);
		}
		if ((col+1)%N == 0) {
			printf("|");
		}
	}
	printf("\n");
}


void afficherTransition() { // Affichage de la transition entre les blocs avec les - et les +
	printf("     ");
	for (int j=0 ; j < N ; j++) {
		printf("+");
		for (int l=0 ; l < N ; l++) {
			printf("---");
		}
	}
	printf("+\n");
}


void afficherGrille(tGrille grille1) { //affichage de la grille en entier
	printf("\n");
	printf("     ");
	for (int nombre = 1 ; nombre < TAILLE+1 ; nombre++) {
		if (nombre%N==0) {
			printf("%3d",nombre);
			printf(" ");
		} else {
			printf("%3d",nombre);
		}
	}
	printf("\n");
	for (int i=0 ; i < TAILLE ; i=i+N) {
		afficherTransition();
		for (int k=1 ; k < N+1 ; k++) {
			afficherLigne(grille1, i+k);
		}
		
	}
	afficherTransition();
}


/*****************************************************
		* FONCTIONS RÉALISANT LES TESTS *
*****************************************************/


bool possible(tGrille grille1, int numLigne, int numColonne, int valeur) {
	bool resultat;
	resultat = true;
	int carre_ligne, carre_colonne;

	carre_ligne = N * (numLigne / N); //calcul de l'indice de la première ligne du carré 3x3 auquel la case appartient
	carre_colonne = N * (numColonne / N); //même chose pour la colonne

	for (int i=0 ; i<N*N ; i++) {
		if (grille1[i][numColonne-1] == valeur) { //on parcourt toutes les valeurs de la ligne où est la valeur pour vérifier qu'elle n'apparait pas
			resultat = false;
			printf("IMPOSSIBLE, %d est déjà présent sur la ligne !",valeur);
		}
		if (grille1[numLigne-1][i] == valeur) { //on parcourt toutes les valeurs de la colonne où est la valeur pour vérifier qu'elle n'apparait pas
			resultat = false;
			printf("IMPOSSIBLE, %d est déjà présent sur la colonne !",valeur);
		}
	}


	// On parcourt les lignes et les colonnes de la case 3x3 puis on vérifie que la valeur n'apparait pas, si c'est le cas, on renvoie que on ne peut pas avec un message d'erreur
	for (int i = carre_ligne ; i<carre_ligne + N ; i++) {
		for (int k = carre_colonne ; k<carre_colonne + N ; k++) {
			if (grille1[i][k] == valeur) {
				resultat = false;
				printf("IMPOSSIBLE, %d est déjà présent dans le carré !",valeur);
			}
		}
	}
	
	return resultat;
}


bool estPasPlein(tGrille grille1) {
	bool resultat;
	resultat = false;
	for (int ligne=0 ; ligne < TAILLE ; ligne++) { // On parcourt toutes les valeurs pour vérifier qu'il ne reste pas un 0 et donc, une case vide
		for (int colonne=0 ; colonne < TAILLE ; colonne++) {
			if (grille1[ligne][colonne] == 0) {
				resultat = true;
			}
		}
	}
	return resultat;
}