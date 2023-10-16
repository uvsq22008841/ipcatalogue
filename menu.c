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

    
        while (1) {
            printf("\n\n*** GESTION DES ADRESSES IPV4 ***\n\n");
            printf("\n");
            printf("\n");
            printf(" 1- Ajouter une nouvelle adresse IP\n ");
            printf("2- Afficher le catalogue\n");
            printf(" 3- Filtrer par masque sous-reseau \n");
            printf(" 0- Quitter\n\n");
            char choice;
            printf("votre choix: ");
            scanf(" %c", &choice);
        switch (choice) {
            case '1':{
                ajouter()  ; break;
            }
            case '2':{
                voir_struct(fic); break;
            }
            case '3':{
                filtrer(fic); break;
                }
            case '0':
                printf("\nA bientot!\n");
                exit(0);
            default:
                printf("ENTREZ UN NUMERO ENTRE 0 ET 3!! \n");
        }
    }

    fclose(fic); // Ferme le fichier
    return 0;
}