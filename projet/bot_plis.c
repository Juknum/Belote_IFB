#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include "./header/fonctions.h"
#include "./header/syntax.h"

void bot_plis(char* nom_bot, int* cartes_bot, int nb_cartes_jouee, int* tableau_pli, int* tableau_atout, int atout_n, int nb_atout){

	
	printf(side_jeu" %s Examine son jeu...",nom_bot);


	/*

	BELOTE COINCHEE EN C : Groupe F
	- Julien Constant
	- Ewen Bourdon
	- Théo Silva

	*/


	// Au tour du bot, le bot check toutes les cartes du tableau et doit ensuite check son tableau de carte. 
	// S'il a une carte plus élevée que celles déjà jouées (faire un tri préliminaire des tableau) :
		// Il joue sa carte la plus faible pouvant lui permettre de l'emporter sauf s'il y a un atout sur la table
		// S'il a un atout (le plus faible possible), il le joue
	// S'il a une carte moins élevée que celles déjà jouées :
		// Il pose sa carte la plus faible (de préférence une carte non atout)
	// S'il est le premier a jouer : 
		// Il joue sa carte la plus faible 
		// Ou alors il joue n'imp

	
	//Une pseudo intelligence artificielle sera également réalisée pour jouer avec le joueur :
		//• L’IA joue en respectant les règles
		//• Si l’IA est en mesure de remporter le pli avec une de ses cartes, elle le fait en posant la carte
		//la plus faible possible
		//• Si l’IA n’est pas en mesure de remporter le pli, elle joue sa carte la plus faible
		//• Vous pouvez enrichir votre IA avec des règles heurisitiques que vous aurez élaborées et
		//justifiées dans votre rapport.
	

	int tableau_carte_jouable[8] = {0};
	int symb;
	int tableau_carte_jouable_valeur[8] = {0};


	// On traduit numériquement les symboles
	if(tableau_pli[0] >= 1 && tableau_pli[0] <= 8){
		symb = 1; // Pique
	}
	if(tableau_pli[0] >= 9 && tableau_pli[0] <= 16){
		symb = 2; // Carreau
	}
	if(tableau_pli[0] >= 17 && tableau_pli[0] <= 24){
		symb = 3; // Coeur
	}
	if(tableau_pli[0] >= 25 && tableau_pli[0] <= 32){
		symb = 4; // Trèfle
	}

	printf("\nCartes du bot\n");
	for(int i = 0; i < 8 ; i++){
		printf("%d ",cartes_bot[i]);
	}

	if(nb_cartes_jouee > 0){

		if(nb_atout > 0){
		

			// On va mettre toutes ses cartes atouts dans le tableau des cartes jouables
			for(int i = 0; i < 8; i++){
				// On vérifie chaque carte du tableau jusqu'à tomber sur une carte atout
				switch(atout_n){
					case 1 : // Pique
						if(cartes_bot[i] >= 1 && cartes_bot[i] <= 8){
							tableau_carte_jouable[i] = cartes_bot[i];
						}
						break;
					case 2 : // Carreau
						if(cartes_bot[i] >= 9 && cartes_bot[i] <= 16){
							tableau_carte_jouable[i] = cartes_bot[i];
						}
						break;
					case 3 : // Coeur
						if(cartes_bot[i] >= 17 && cartes_bot[i] <= 24){
							tableau_carte_jouable[i] = cartes_bot[i];
						}
						break;
					case 4 : // Trèfle 
						if(cartes_bot[i] >= 25 && cartes_bot[i] <= 32){
							tableau_carte_jouable[i] = cartes_bot[i];
						}
						break;
				}	

			}

			// On tri ensuite de manière croissante le tableau des cartes jouables (qui sont des atouts)
			tableau_tri(tableau_carte_jouable);
			// DEBUG
			printf("TAB CARTE JOUABLE\n");
			for(int i = 0; i < 8; i++){
				printf("%d ",tableau_carte_jouable[i]);
			}
			
			int non_atout_joue = 0;
			if(tableau_carte_jouable[7] == 0){ // Si le bot n'a pas de carte atout (dernière valeur vaut 0) mais que la première carte jouée est un atout
				for(int i = 0; i < 8; i++){ // On place la valeur non atout de ses cartes dans un autre tableau parce qu'on peut pas faire fct(fct(tab))
					tableau_carte_jouable_valeur[i] = cartes_bot[i];
				}
				tableau_tri(tableau_carte_jouable_valeur);
				tableau_tri(cartes_bot);
				for(int i = 0; i < 8; i++){ // On place la valeur non atout de ses cartes dans un autre tableau parce qu'on peut pas faire fct(fct(tab))
					dictionnaire_non_atout(tableau_carte_jouable_valeur[i]);
				}
				tableau_tri(tableau_carte_jouable_valeur);
				for(int i = 0; i < 8; i++){
					for(int h = 0; h < 8 ; h++){
						if(tableau_carte_jouable_valeur[i] != -5){
							if(tableau_carte_jouable_valeur[i] == cartes_bot[h] && non_atout_joue == 0){
								tableau_pli[nb_cartes_jouee] = cartes_bot[h];
								cartes_bot[h] = -5;
								non_atout_joue = 1;
							}
						}	
					}
				}
			}
			/* DEBUG
			printf("\n TAB ATOUT ");
			for(int i = 0;i < 4; i++){
				printf("\n%d",tableau_atout[i]);
			}
			*/
			int atout_joue = 0;
			// Analyse des cartes jouées :
			for(int i = 0; i < 8; i++){ // Pour toutes les cartes jouables du bot on va vérifier si :
			
				for(int j = nb_cartes_jouee; j > -1; j--){ // L'une de ses cartes est supérieure à une des cartes jouées en commencant par la plus petite de son jeu
						

					if(dictionnaire_atout(tableau_carte_jouable[i]) > dictionnaire_atout(tableau_atout[j])){
						for(int h = 0; h < 8 ; h++){
							if(tableau_carte_jouable[i] == cartes_bot[h] && atout_joue == 0){
								tableau_pli[nb_cartes_jouee] = tableau_carte_jouable[i];
								cartes_bot[h] = -5;
								atout_joue = 1;
							}
						}
					}
				}
			}

			int atout_joue2 = 0;
			if(atout_joue == 0){ // tableau_carte_jouable[i] <= tableau_atout[j]
				int g = 0;
				do{
					g++;
				}while(tableau_carte_jouable[g] == 0);
				for(int h = 0; h < 8 ; h++){
					if(tableau_carte_jouable[g] == cartes_bot[h] && atout_joue == 0){
						tableau_pli[nb_cartes_jouee] = tableau_carte_jouable[g];
						cartes_bot[h] = -5;
						atout_joue2 = 1;
					}
				}
			}

			afficher_carte(tableau_pli, nb_cartes_jouee, 0);
		}
		else{// Le bot va mettre dans tab carte jouable ttes les cartes qu'il lui permettre de suivre à la couleur et ensuite on trie ce tab

			// "red" Sinon, pli normal donc pareil que atout ou le bot doit jouer sa carte la plus faible ou forte "red"

			for(int i = 0; i < 8; i++){ // On place toutes les cartes du bot dans un tableau de cartes jouables
				tableau_carte_jouable[i] = cartes_bot[i];
			}
			for(int i = 0; i < 8; i++){
				switch(atout_n){ // On attribue les valeurs des cartes de son tableau selon l'atout pour comparer
					case 1 : // Pique
						if(cartes_bot[i] >= 1 && cartes_bot[i] <= 8){
							tableau_carte_jouable_valeur[i] = dictionnaire_atout(tableau_carte_jouable[i]);
						}
						else{
							tableau_carte_jouable_valeur[i] = dictionnaire_non_atout(tableau_carte_jouable[i]);
						}
						break;
					case 2 : // Carreau
						if(cartes_bot[i] >= 9 && cartes_bot[i] <= 16){
							tableau_carte_jouable_valeur[i] = dictionnaire_atout(tableau_carte_jouable[i]);
						}
						else{
							tableau_carte_jouable_valeur[i] = dictionnaire_non_atout(tableau_carte_jouable[i]);
						}
						break;
					case 3 : // Coeur
						if(cartes_bot[i] >= 17 && cartes_bot[i] <= 24){
							tableau_carte_jouable_valeur[i] = dictionnaire_atout(tableau_carte_jouable[i]);
						}
						else{
							tableau_carte_jouable_valeur[i] = dictionnaire_non_atout(tableau_carte_jouable[i]);
						}
						break;
					case 4 : // Trèfle 
						if(cartes_bot[i] >= 25 && cartes_bot[i] <= 32){
							tableau_carte_jouable_valeur[i] = dictionnaire_atout(tableau_carte_jouable[i]);
						}
						else{
							tableau_carte_jouable_valeur[i] = dictionnaire_non_atout(tableau_carte_jouable[i]);
						}
						break;
				}
				afficher_carte(tableau_pli, nb_cartes_jouee, 0);
			}
			tableau_tri(tableau_carte_jouable_valeur);

			int carte_haute = 0;
			// Analyse des cartes jouées :
			for(int i = 0; i < 8; i++){ // Pour toutes les cartes jouables du bot on va vérifier si :
			
				for(int j = nb_cartes_jouee; j > -1; j--){ // L'une de ses cartes est supérieure à une des cartes jouées en commencant par la plus petite de son jeu
						

					if(tableau_carte_jouable_valeur[i] > dictionnaire_non_atout(tableau_pli[j])){
						carte_haute++;
					}
					if(carte_haute > nb_cartes_jouee){
						for(int h = 0; h < 8 ; h++){
							if((tableau_carte_jouable_valeur[i] == dictionnaire_non_atout(tableau_carte_jouable[h])) || (tableau_carte_jouable_valeur[i] == dictionnaire_atout(tableau_carte_jouable[h]))){
								tableau_pli[nb_cartes_jouee] = tableau_carte_jouable[i];
								cartes_bot[h] = -5;
							}
						}
					}
					if(carte_haute <= nb_cartes_jouee){
						int g = 0;
						do{
							g++;
						}while(tableau_carte_jouable[g] == 0);
						for(int h = 0; h < 8 ; h++){
							if((tableau_carte_jouable_valeur[i] == dictionnaire_non_atout(tableau_carte_jouable[h])) || (tableau_carte_jouable_valeur[i] == dictionnaire_atout(tableau_carte_jouable[h]))){
								tableau_pli[nb_cartes_jouee] = tableau_carte_jouable[g];
								cartes_bot[h] = -5;
							}
						}
					}
				}
			}
		}			
	}
	else{
		

		int carte_choisie = 0; 


		// Evite de au bot de prendre une carte déjà posée au tour précédent
		do{
			carte_choisie = rand()%8 + 1; // A CHANGER
		}while(cartes_bot[carte_choisie-1] == -5);

		switch(carte_choisie){
			case 1 :
				tableau_pli[nb_cartes_jouee] = cartes_bot[0];
				cartes_bot[0] = -5;
			break;
			case 2 :
				tableau_pli[nb_cartes_jouee] = cartes_bot[1];
				cartes_bot[1] = -5;
			break;
			case 3 :
				tableau_pli[nb_cartes_jouee] = cartes_bot[2];
				cartes_bot[2] = -5;
			break;
			case 4 :
				tableau_pli[nb_cartes_jouee] = cartes_bot[3];
				cartes_bot[3] = -5;
			break;
			case 5 :
				tableau_pli[nb_cartes_jouee] = cartes_bot[4];
				cartes_bot[4] = -5;
			break;
			case 6 :
				tableau_pli[nb_cartes_jouee] = cartes_bot[5];
				cartes_bot[5] = -5;
			break;
			case 7 :
				tableau_pli[nb_cartes_jouee] = cartes_bot[6];
				cartes_bot[6] = -5;
			break;
			case 8 :
				tableau_pli[nb_cartes_jouee] = cartes_bot[7];
				cartes_bot[7] = -5;
			break;
			default:
				printf(side_error" switch(%d)",carte_choisie);
			break;
		}
		afficher_carte(tableau_pli, nb_cartes_jouee, 0);
	}
	
	printf(side_only);
}