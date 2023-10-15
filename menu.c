#include <stdio.h>
#include <stdlib.h>
#include "hexbin.h"
#include <string.h>
#include <stdbool.h>


int main(){

    // ouverture fichier 
    FILE* fic = NULL;
    if ((fic = fopen("ip.txt", "a+")) == NULL) {
        printf("Pas de fichier à ce nom !");
        exit(1);
    }

    int choix;

    do {
    
        // *** MENU***
        printf("\n\n*** GESTION DES IP ***\n\n");
        printf("\n");
        printf("\n");
        printf(" 1- Ajouter une nouvelle adresse IP\n ");
        printf("2- Afficher le catalogue\n");
        printf(" 3- Filtrer par masque sous-reseau \n");
        printf(" 0- Quitter\n\n");
        
        // choix user
        printf("votre choix: \n");
        scanf("%d",&choix);


        switch(choix){

            case 1: {ajouter()  ; break;}
            case 2: {voir_struct(fic); break;}
            case 3: {filtrer(fic); break;}
            case 4: {printf("au revoir\n")  ; break;}
            case 5: {  printf("au revoir\n"); break;}
            case 6: { printf("au revoir\n") ; break;}
            case 0: { printf("au revoir\n") ; break;}
            default : printf("entrez un numero entre 0 et 6!!");
        }
        
    } while (choix!=0);

    fclose(fic); // Ferme le fichier
    return 0;
}