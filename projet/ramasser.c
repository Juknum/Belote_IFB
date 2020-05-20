#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include <math.h>
#include <time.h>

#include "./header/fonctions.h"

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

void ramasser(int redistribue, int distributeur, char *nom_joueur, int * cartes_west, int * cartes_north, int * cartes_east, int * cartes_joueur){
	printf("§ "GRN"INFO :"WHT" Ramassage des cartes... ");

	int cartes[32] = {0};

	switch(distributeur){
		case 1: // Joueur a distribué -> on ramasse en premier Ouest -> Nord -> Est -> Joueur
			printf("%s ramasse...",nom_joueur);
			for(int i = 0; i < 8; i++){cartes[i]    = cartes_west[i];   }
			for(int i = 0; i < 8; i++){cartes[i+8]  = cartes_north[i];  }
			for(int i = 0; i < 8; i++){cartes[i+16] = cartes_east[i];   }
			for(int i = 0; i < 8; i++){cartes[i+24] = cartes_joueur[i]; }
			break;
		case 2: // Ouest a distribué -> on ramasse en premier Nord -> Est -> Joueur -> Ouest
			printf("Ouest ramasse...");
			for(int i = 0; i < 8; i++){cartes[i]    = cartes_north[i];  }
			for(int i = 0; i < 8; i++){cartes[i+8]  = cartes_east[i];   }
			for(int i = 0; i < 8; i++){cartes[i+16] = cartes_joueur[i]; }
			for(int i = 0; i < 8; i++){cartes[i+24] = cartes_west[i];   }
			break; 
		case 3: // Nord a distribué -> on ramasse en premier Est -> Joueur -> Ouest -> Nord
			printf("Nord ramasse...");
			for(int i = 0; i < 8; i++){cartes[i]    = cartes_east[i];   }
			for(int i = 0; i < 8; i++){cartes[i+8]  = cartes_joueur[i]; }
			for(int i = 0; i < 8; i++){cartes[i+16] = cartes_west[i];   }
			for(int i = 0; i < 8; i++){cartes[i+24] = cartes_north[i];  }
			break;
		case 4: // Est a distribué -> on ramasse en premier Joueur -> Ouest -> Nord -> Est
			printf("Est ramasse...");
			for(int i = 0; i < 8; i++){cartes[i]    = cartes_joueur[i]; }
			for(int i = 0; i < 8; i++){cartes[i+8]  = cartes_west[i];   }
			for(int i = 0; i < 8; i++){cartes[i+16] = cartes_north[i];  }
			for(int i = 0; i < 8; i++){cartes[i+24] = cartes_east[i];   }
			break;
		default:
			printf("Erreur switch ramasser(%d)",distributeur);
			break;
	}
	
	// Les mains sont vides donc on vides chaque joueur (on met à 0)
	for(int i = 0; i < 8; i++){
		cartes_joueur[i] = 0;
		cartes_west[i]   = 0;
		cartes_north[i]  = 0;
		cartes_east[i]   = 0;
	}

	printf("Fait!\n");

	if(redistribue == 1){
		distribuer(distributeur+1, cartes, nom_joueur, cartes_west, cartes_north, cartes_east, cartes_joueur);
	}

}