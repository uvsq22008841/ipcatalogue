#ifndef HEXBIN_H
#define HEXBIN_H
#include <string.h>
#include <stdbool.h>



int isValidIPv4(int ip[]);
int isValidMask(int ip[]);

struct Ip_conv
{
    int  octet_dec[4];
    int  octet_bin[4];
    char octet_hex[4][3]; 
    int octet_masque[4];
    int cidr;
};
typedef struct Ip_conv Ip_conv;

// Conversion decimale -> binaire
int binaire(int nb, Ip_conv ip, int oct_bin) {
    int diviseur = 2;
    int taille = 8;
    int res; 
    int reste[8]={0};

   
    for(int i = 7; nb > 0; i-- ){
        reste[i] = nb % diviseur; 
        nb /= diviseur;
    }
    
    for (int i = 7; i >= 0; i--){
        ip.octet_bin[oct_bin] = ip.octet_bin[oct_bin]*10+ reste[taille -1 -i];
        
    }

    res = ip.octet_bin[oct_bin];
    return res;
}

// Conversion decimale -> hexadecimale
char* hexa(int nb) {

    int diviseur = 16;
    int i = 0;
    char hex[3] = {'\0'};

    while (nb != 0) {
        int reste = nb % diviseur;
        if (reste < 10) {
            hex[i++] = '0' + reste;
        } else {
            hex[i++] = 'A' + (reste - 10);
        }
        nb /= 16;
    }
    
    // Si la chaîne hex a un seul caractère, ajouter un zéro 
    if (i == 1) {
        hex[1] = '0';
    }
    if (nb = 0 ){
        hex[0] = '0';
        hex[1] = '0';
    }

   
    char* hexaa = malloc(3);
    if (hexaa == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        exit(1);
    }

    int length = strlen(hex);
    
    // Copie les caractères de hex dans hexaa en sens inverse
    for (int i = 0; i < length; i++) {
        hexaa[i] = hex[length - 1 - i];
    }

    hexaa[length] = '\0'; 
    
    return hexaa;
}


int maskArrayToCIDR(int masque[]) {
    int cidr = 0;

    for (int i = 0; i < 4; i++) {
        unsigned int octet = masque[i];
        
        // Compter les bits à 1 dans l'octet
        while (octet) {
            cidr += octet & 1;
            octet >>= 1;
        }
    }

    return cidr;
}


// Ecrire la nouvelle adresse IP dans le fichier 'ip.txt'
void ecrire_struct(FILE* fic, Ip_conv ip){
    
    fic = NULL;
    if ((fic = fopen("ip.txt", "a+")) == NULL) {
        printf("Pas de fichier à ce nom !");
        exit(1);
    }

    fprintf(fic,"%d %d %d %d\n%08d %08d %08d %08d\n%02s %02s %02s %02s\n%d %d %d %d\n%d\n",
    ip.octet_dec[0], ip.octet_dec[1],ip.octet_dec[2], ip.octet_dec[3],
    ip.octet_bin[0], ip.octet_bin[1], ip.octet_bin[2], ip.octet_bin[3], ip.octet_hex[0],
    ip.octet_hex[1], ip.octet_hex[2], ip.octet_hex[3], ip.octet_masque[0],
    ip.octet_masque[1], ip.octet_masque[2], ip.octet_masque[3],ip.cidr);


    fclose(fic);
}

// Voir le contenu du fichier 'ip.txt'
void voir_struct(FILE* fic){
    
    fic = NULL;
    if ((fic = fopen("ip.txt", "r")) == NULL) {
        printf("Pas de fichier à ce nom !");
        exit(1);
    }

    Ip_conv ip;
    int compteur = 1;
    
   

    int caractere;
    if((caractere = fgetc(fic)) == EOF) {
        printf("\nLe catalogue d'adresse IP est vide! \n");
        return; 
    }

    rewind(fic);
    while(!feof(fic)){
    
    fscanf(fic,"%d %d %d %d\n%08d %08d %08d %08d\n%02s %02s %02s %02s\n%d %d %d %d\n%d\n",
    &ip.octet_dec[0],&ip.octet_dec[1],&ip.octet_dec[2],&ip.octet_dec[3],
    &ip.octet_bin[0],&ip.octet_bin[1],&ip.octet_bin[2],&ip.octet_bin[3],
    ip.octet_hex[0],ip.octet_hex[1],ip.octet_hex[2],ip.octet_hex[3],
    &ip.octet_masque[0],&ip.octet_masque[1], &ip.octet_masque[2], &ip.octet_masque[3], &ip.cidr);

    
    
    
    printf("Adresse IP %d :\n\n", compteur);

    printf("- %d.%d.%d.%d /%d\n- %08d.%08d.%08d.%08d\n- %02s.%02s.%02s.%02s\n Masque: %d.%d.%d.%d\n",
    ip.octet_dec[0],ip.octet_dec[1],ip.octet_dec[2],ip.octet_dec[3],ip.cidr,
    ip.octet_bin[0],ip.octet_bin[1],ip.octet_bin[2],ip.octet_bin[3],
    ip.octet_hex[0],ip.octet_hex[1],ip.octet_hex[2],ip.octet_hex[3],
    ip.octet_masque[0],ip.octet_masque[1], ip.octet_masque[2], ip.octet_masque[3] );

    compteur++;
}


fclose(fic);    
}

// Ajouter une adresse IP
int ajouter() {
    Ip_conv ip3;
    
    memset(ip3.octet_bin, 0, sizeof(ip3.octet_bin)); //initialise le tableau ip3.octet_bin a 0
    
    // Ouverture du fichier
    FILE* fic = NULL;
    if ((fic = fopen("ip.txt", "a+")) == NULL) {
        printf("Pas de fichier à ce nom !");
        exit(1);
    }


    printf("Entrez une adresse IPv4 decimale sous la forme : XXX.XXX.XXX.XXX\n");
    
   

if (scanf("%u.%u.%u.%u", &ip3.octet_dec[0], &ip3.octet_dec[1], &ip3.octet_dec[2], &ip3.octet_dec[3]) == 4 && isValidIPv4(ip3.octet_dec)) {

   
    printf("Entrez le masque sous-reseau sous la forme : XXX.XXX.XXX.XXX\n");
    if ( scanf("%u.%u.%u.%u", &ip3.octet_masque[0], &ip3.octet_masque[1], &ip3.octet_masque[2], &ip3.octet_masque[3]) == 4 && isValidMask(ip3.octet_masque)) {
        
        ip3.cidr = maskArrayToCIDR( ip3.octet_masque) ;
        while (getchar() != '\n'); // Nettoie le buffer d'entrée
        
        for (int i = 0; i < 4; i++) {
        // Mettre le nombre binaire dans la structure
        ip3.octet_bin[i] = binaire(ip3.octet_dec[i], ip3, i);
        // Mettre le nombre hexadécimal dans la structure
        char* hex = hexa(ip3.octet_dec[i]);
        strcpy(ip3.octet_hex[i], hex);
        // Libérer la mémoire allouée dynamiquement
        free(hex); 
                        
        }

        // ecrire dans le fichier fic
        ecrire_struct(fic,ip3);

        printf("L'adresse IP suivante a ete ajoute au fichier 'ip.txt' :\n");
        printf(" IPV4: %d.%d.%d.%d /%d\n", ip3.octet_dec[0], ip3.octet_dec[1], ip3.octet_dec[2], ip3.octet_dec[3],ip3.cidr);
        printf(" Binaire: %08d.%08d.%08d.%08d\n", ip3.octet_bin[0], ip3.octet_bin[1], ip3.octet_bin[2], ip3.octet_bin[3]);
        printf(" Hexadecimale: %02s.%02s.%02s.%02s\n", ip3.octet_hex[0], ip3.octet_hex[1], ip3.octet_hex[2], ip3.octet_hex[3]);
        printf(" Masque: %d.%d.%d.%d\n", ip3.octet_masque[0], ip3.octet_masque[1], ip3.octet_masque[2], ip3.octet_masque[3]);
                    
    }
    else{
        printf("Masque invalide. Veuillez reessayer.\n");
    }
    
    while (getchar() != '\n'); // Nettoie le buffer d'entrée
} 
else {
    printf("Adresse IPv4 invalide. Veuillez reessayer.\n");
    printf("Adresse IPv4 invalide ou n'appartient pas à la classe A, B ou C. Veuillez reessayer.\n");
    }

   
    fclose(fic); 

    return 0;
}


// filtre les adresse ip selon leur masque

void filtrer(){
    // structure entrée par l'utilisateur
    Ip_conv ip3;
    // structure lu dans le fichier 'ip.txt'
    Ip_conv ip;
    int compteur = 1;
    

    FILE* fic = NULL;
    if ((fic = fopen("ip.txt", "a+")) == NULL) {
        printf("Pas de fichier à ce nom !");
        exit(1);
    }

    int caractere;
    if((caractere = fgetc(fic)) == EOF) {
        printf("\nLe catalogue d'adresse IP est vide! \n");
        return; 
    }

    printf("\n\nFiltrage:\n\n");
    printf("Entrez une adresse IPv4 decimale sous la forme : XXX.XXX.XXX.XXX\n");
    if (scanf("%u.%u.%u.%u", &ip3.octet_dec[0], &ip3.octet_dec[1], &ip3.octet_dec[2], &ip3.octet_dec[3]) == 4 && isValidIPv4(ip3.octet_dec)) {

   
    printf("Entrez le masque sous-reseau sous la forme : XXX.XXX.XXX.XXX\n");
    // && isValidMask(ip3.octet_masque)
    if ( scanf("%u.%u.%u.%u", &ip3.octet_masque[0], &ip3.octet_masque[1], &ip3.octet_masque[2], &ip3.octet_masque[3]) == 4 && isValidMask(ip3.octet_dec)) {
        
        rewind(fic);
        while(!feof(fic)){
    
        fscanf(fic,"%d %d %d %d\n%08d %08d %08d %08d\n%02s %02s %02s %02s\n%d\n\n",
        &ip.octet_dec[0],&ip.octet_dec[1],&ip.octet_dec[2],&ip.octet_dec[3],
        &ip.octet_bin[0],&ip.octet_bin[1],&ip.octet_bin[2],&ip.octet_bin[3],
        ip.octet_hex[0],ip.octet_hex[1],ip.octet_hex[2],ip.octet_hex[3],
        &ip.octet_masque[0]);
        // && ip.octet_dec[0] == ip3.octet_dec[0]
        if(ip.octet_masque[0] == ip3.octet_masque[0]  ){
            if (ip3.octet_dec[0] >= 1 && ip3.octet_dec[0]  <= 126){
                if (ip.octet_dec[0] >= 1 && ip.octet_dec[0]  <= 126){
                    
                    printf("Adresse IP %d : ", compteur);
                    printf("%d.%d.%d.%d\n",ip.octet_dec[0],ip.octet_dec[1],ip.octet_dec[2],ip.octet_dec[3]);
                    compteur++;
                }
            }
            else if (ip3.octet_dec[0] >= 128 && ip3.octet_dec[0] <= 191){
                if (ip.octet_dec[0] >= 128 && ip.octet_dec[0] <= 191){
                    int compteur = 1;
                    printf("Adresse IP %d : ", compteur);
                    printf("%d.%d.%d.%d\n",ip.octet_dec[0],ip.octet_dec[1],ip.octet_dec[2],ip.octet_dec[3]);
                    compteur++;
                }
            }
            else if (ip3.octet_dec[0] >= 192 && ip3.octet_dec[0] <= 223){
                if (ip.octet_dec[0] >= 192 && ip.octet_dec[0] <= 223){
                    int compteur = 1;
                    printf("Adresse IP %d : ", compteur);
                    printf("%d.%d.%d.%d\n",ip.octet_dec[0],ip.octet_dec[1],ip.octet_dec[2],ip.octet_dec[3]);
                    compteur++;
                }
            }
            // printf(" voici les adresses trouvees avec les filtres: \n");
            // printf(" %d.%d.%d.%d",ip.octet_dec[0],ip.octet_dec[1],ip.octet_dec[2],ip.octet_dec[3]);

        }
        }
    
    }
    }

}


int isClassABC(int ip[]) {
    int firstOctet = ip[0];
    return (firstOctet >= 1 && firstOctet <= 126) ||  // Classe A
           (firstOctet >= 128 && firstOctet <= 191) ||  // Classe B
           (firstOctet >= 192 && firstOctet <= 223);    // Classe C
}

int isValidOctet(int octet) {
    return (octet >= 0 && octet <= 255);
}

int isValidIPv4(int ip[]) {
    if (!isClassABC(ip)) {
        return 0; // Adresse n'est pas de classe A, B ou C
    }

    for (int i = 0; i < 4; i++) {
        if (!isValidOctet(ip[i])) {
            return 0; // Adresse invalide si un octet est invalide
        }
    }
    return 1;
}

int isValidMask(int ip[]) {
    for (int i = 0; i < 4; i++) {
        if (!isValidOctet(ip[i])) {
            return 0; // Adresse invalide si un octet est invalide
        }
    }
    return 1;
}



#endif