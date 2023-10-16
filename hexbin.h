#ifndef HEXBIN_H
#define HEXBIN_H
#include <string.h>
#include <stdbool.h>


struct Ip_conv
{
    int  octet_dec[4];
    int  octet_bin[4];
    char octet_hex[4][3]; 
    int octet_masque[4];
    int cidr;
    char ipClass;
    char type;

};
typedef struct Ip_conv Ip_conv;

int isValidIPv4(int ip[]);
int isValidMask(int ip[]);
int binaire_Compaire(Ip_conv ip, Ip_conv ip3, int cidr, int octet);
char classifyIPAddress(int ip[]);
char classifyIPClass(int ip[]);
int binaire(int nb, Ip_conv ip, int oct_bin);
char* hexa(int nb);
int maskArrayToCIDR(int masque[]);
void ecrire_struct(FILE* fic, Ip_conv ip);
void voir_struct(FILE* fic);
int ajouter();
void filtrer();
char classifyIPAddress(int ip[]);
int isClassABC(int ip[]);
int isValidOctet(int octet);
int isValidIPv4(int ip[]) ;
char classifyIPClass(int ip[]);



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

    fprintf(fic,"%d %d %d %d\n%08d %08d %08d %08d\n%02s %02s %02s %02s\n%d %d %d %d\n%d\n%c\n",
    ip.octet_dec[0], ip.octet_dec[1],ip.octet_dec[2], ip.octet_dec[3],
    ip.octet_bin[0], ip.octet_bin[1], ip.octet_bin[2], ip.octet_bin[3], ip.octet_hex[0],
    ip.octet_hex[1], ip.octet_hex[2], ip.octet_hex[3], ip.octet_masque[0],
    ip.octet_masque[1], ip.octet_masque[2], ip.octet_masque[3],ip.cidr,ip.type);


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
    
        fscanf(fic,"%d %d %d %d\n%08d %08d %08d %08d\n%02s %02s %02s %02s\n%d %d %d %d\n%d\n%c\n",
        &ip.octet_dec[0],&ip.octet_dec[1],&ip.octet_dec[2],&ip.octet_dec[3],
        &ip.octet_bin[0],&ip.octet_bin[1],&ip.octet_bin[2],&ip.octet_bin[3],
        ip.octet_hex[0],ip.octet_hex[1],ip.octet_hex[2],ip.octet_hex[3],
        &ip.octet_masque[0],&ip.octet_masque[1], &ip.octet_masque[2], &ip.octet_masque[3], &ip.cidr,&ip.type);
    
        
        
        
        printf("* Adresse IP %d :\n\n", compteur);
     
        printf("- %d.%d.%d.%d /%d\n- %08d.%08d.%08d.%08d\n- %02s.%02s.%02s.%02s\nMasque: %d.%d.%d.%d\nType: %c\n\n",
        ip.octet_dec[0],ip.octet_dec[1],ip.octet_dec[2],ip.octet_dec[3],ip.cidr,
        ip.octet_bin[0],ip.octet_bin[1],ip.octet_bin[2],ip.octet_bin[3],
        ip.octet_hex[0],ip.octet_hex[1],ip.octet_hex[2],ip.octet_hex[3],
        ip.octet_masque[0],ip.octet_masque[1], ip.octet_masque[2], ip.octet_masque[3],ip.type);

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
            ip3.cidr = maskArrayToCIDR( ip3.octet_masque);
            ip3.ipClass = classifyIPClass(ip3.octet_dec);
            ip3.type = classifyIPAddress(ip3.octet_dec); 
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
            printf(" Classe: %c\n", ip3.ipClass);
            if (ip3.type == 'P') {
                printf("Adresse IP privee\n");
            } 
            else if (ip3.type == 'L') {
                printf("Adresse IP speciale \n");
            } 
            else if (ip3.type == 'O') {
                printf("Adresse IP publique\n");
            } 
            else {
                printf("Non définie\n");
            }

                        
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
    memset(ip3.octet_bin, 0, sizeof(ip3.octet_bin)); 
    // structure lu dans le fichier 'ip.txt'
    Ip_conv ip;
    int compteur = 1;
    

    FILE* fic = NULL;
    if ((fic = fopen("ip.txt", "a+")) == NULL) {
        printf("Pas de fichier à ce nom !");
        exit(1);
    }
    rewind(fic);
    int caractere;
    if((caractere = fgetc(fic)) == EOF) {
        printf("\nLe catalogue d'adresse IP est vide! \n");
        return; 
    }

    printf("\n\nFiltrage:\n\n");
    printf("Entrez une adresse IPv4 decimale sous la forme : XXX.XXX.XXX.XXX\n");
    if (scanf("%u.%u.%u.%u", &ip3.octet_dec[0], &ip3.octet_dec[1], &ip3.octet_dec[2], &ip3.octet_dec[3]) == 4 && isValidIPv4(ip3.octet_dec)) {
        ip.type = classifyIPAddress(ip.octet_dec); 
        for (int i = 0; i < 4; i++) {
        // Mettre le nombre binaire dans la structure
        ip3.octet_bin[i] = binaire(ip3.octet_dec[i], ip3, i);
        }

   
        printf("Entrez le masque sous-reseau sous la forme : XXX.XXX.XXX.XXX\n");
        if ( scanf("%u.%u.%u.%u", &ip3.octet_masque[0], &ip3.octet_masque[1], &ip3.octet_masque[2], &ip3.octet_masque[3]) == 4 && isValidMask(ip3.octet_masque)) {
            
            ip3.cidr = maskArrayToCIDR( ip3.octet_masque) ;
            // METTRE le pointeur au debut du fichier 
            rewind(fic);
            
            while(!feof(fic)){
            
                fscanf(fic,"%d %d %d %d\n%08d %08d %08d %08d\n%02s %02s %02s %02s\n%d %d %d %d\n%d\n%c\n",
                &ip.octet_dec[0],&ip.octet_dec[1],&ip.octet_dec[2],&ip.octet_dec[3],
                &ip.octet_bin[0],&ip.octet_bin[1],&ip.octet_bin[2],&ip.octet_bin[3],
                ip.octet_hex[0],ip.octet_hex[1],ip.octet_hex[2],ip.octet_hex[3],
                &ip.octet_masque[0],&ip.octet_masque[1], &ip.octet_masque[2], &ip.octet_masque[3], &ip.cidr,&ip.type);
                
                if(ip.cidr == ip3.cidr  ){
                    int cidr = ip.cidr;
                    int octet = 0;
                    int res = binaire_Compaire(ip, ip3,cidr,octet);
                    char ip3_octet[9]; // Un tableau de caractères pour stocker la chaîne
                    char ip_octet[9];
                
                
                    
                    if(res == 1){
                        printf("Adresse IP %d :\n ", compteur);
                        printf("IPV4: %d.%d.%d.%d /%d\nBinaire: %08d.%08d.%08d.%08d\nHexadecimale: %02s.%02s.%02s.%02s\nMasque: %d.%d.%d.%d\n\n",
                        ip.octet_dec[0],ip.octet_dec[1],ip.octet_dec[2],ip.octet_dec[3],ip.cidr,
                        ip.octet_bin[0],ip.octet_bin[1],ip.octet_bin[2],ip.octet_bin[3],
                        ip.octet_hex[0],ip.octet_hex[1],ip.octet_hex[2],ip.octet_hex[3],
                        ip.octet_masque[0],ip.octet_masque[1], ip.octet_masque[2], ip.octet_masque[3]);
                        compteur++;
                    }          
                }
                

            }
        
        }
        else {
             printf("Masque invalide. Veuillez reessayer.\n");
        }
    }
    else {
        printf("Adresse IPv4 invalide. Veuillez reessayer.\n");
        printf("Adresse IPv4 invalide ou n'appartient pas à la classe A, B ou C. Veuillez reessayer.\n");
    }

}


int binaire_Compaire(Ip_conv ip, Ip_conv ip3, int cidr, int octet){
    // pour voir si on peut directement comparer un octet(pck sinn comparaison bit par bit)
    if (cidr >= 8){

        char ip3_octet[9]; // Un tableau de caractères pour stocker la chaîne
        char ip_octet[9];
        sprintf(ip_octet, "%08d", ip.octet_bin[octet]);        
        sprintf(ip3_octet, "%08d", ip3.octet_bin[octet]); 
        cidr -= 8;
        
        if (strcmp(ip3_octet, ip_octet) == 0 && cidr == 0) {
            return 1;
            
        } 
        else if (strcmp(ip3_octet, ip_octet) == 0 && cidr >= 8) {
            return binaire_Compaire(ip, ip3, cidr, octet + 1);
            
        } 
        if (strcmp(ip3_octet, ip_octet) == 0 && cidr < 8) {
            octet += 1; // on passe à l'octet suivant
            char ip3_octet[9]; // Un tableau de caractères pour stocker la chaîne
            char ip_octet[9];
            sprintf(ip_octet, "%08d", ip.octet_bin[octet]);
            sprintf(ip3_octet, "%08d", ip3.octet_bin[octet]);
            for (int i = 0; i < cidr; i++) {
                if (ip_octet[i] == ip3_octet[i]) {
                        
                } 
                else {
                    return 0; // pour FALSE
                }
            }
            return 1; // pour TRUE
        } 
        else {
            return 0; // pour FALSE
        }

                    
    }
}




int isClassABC(int ip[]) {
    int firstOctet = ip[0];
    return (firstOctet >= 0 && firstOctet <= 127) ||  // Classe A
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
    // Tableau de masques de sous-réseau valides pour les classes A, B et C
    int validMasks[][4] = {
        {255, 0, 0, 0},    // /8 - Classe A
        {255, 128, 0, 0},  // /9 - Classe A
        {255, 192, 0, 0},  // /10 - Classe A
        {255, 224, 0, 0},  // /11 - Classe A
        {255, 240, 0, 0},  // /12 - Classe A
        {255, 248, 0, 0},  // /13 - Classe A
        {255, 252, 0, 0},  // /14 - Classe A
        {255, 254, 0, 0},  // /15 - Classe A
        {255, 255, 0, 0},  // /16 - Classe B
        {255, 255, 128, 0},  // /17 - Classe B
        {255, 255, 192, 0},  // /18 - Classe B
        {255, 255, 224, 0},  // /19 - Classe B
        {255, 255, 240, 0},  // /20 - Classe B
        {255, 255, 248, 0},  // /21 - Classe B
        {255, 255, 252, 0},  // /22 - Classe B
        {255, 255, 254, 0},  // /23 - Classe B
        {255, 255, 255, 0},  // /24 - Classe C
        {255, 255, 255, 128},  // /25 - Classe C
        {255, 255, 255, 192},  // /26 - Classe C
        {255, 255, 255, 224},  // /27 - Classe C
        {255, 255, 255, 240},  // /28 - Classe C
        {255, 255, 255, 248},  // /29 - Classe C
        {255, 255, 255, 252}   // /30 - Classe C
    };

    for (int i = 0; i < sizeof(validMasks) / sizeof(validMasks[0]); i++) {
        if (ip[0] == validMasks[i][0] &&
            ip[1] == validMasks[i][1] &&
            ip[2] == validMasks[i][2] &&
            ip[3] == validMasks[i][3]) {
            return 1; // Le masque est valide
        }
    }

    return 0; // Le masque n'est pas valide
}


char classifyIPAddress(int ip[]) {
    if ((ip[0] == 10) ||
        (ip[0] == 172 && ip[1] >= 16 && ip[1] <= 31) ||
        (ip[0] == 192 && ip[1] == 168)) {
        return 'P'; // Adresse IP privée
    } else if (ip[0] == 0 || ip[0] == 127) {
        return 'L'; // Adresse IP spéciale (Loopback)
    } else {
        return 'O'; // Adresse IP publique
    }
}

char classifyIPClass(int ip[]) {
    int firstOctet = ip[0];

    if (firstOctet >= 1 && firstOctet <= 126) {
        return 'A'; // Classe A
    } else if (firstOctet >= 128 && firstOctet <= 191) {
        return 'B'; // Classe B
    } else if (firstOctet >= 192 && firstOctet <= 223) {
        return 'C'; // Classe C
    } else if (firstOctet >= 224 && firstOctet <= 239) {
        return 'D'; // Classe D (multicast)
    } else if (firstOctet >= 240 && firstOctet <= 255) {
        return 'E'; // Classe E (réservée)
    } else {
        return 'X'; // Non définie
    }
}



#endif