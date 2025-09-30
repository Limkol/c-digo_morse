#include <stdio.h>
#include <string.h> 

#define QTD_BANCO 27
#define QTD_LETRA 2
#define QTD_CARACTERES 6

int encontrar_corrompido(char separado[50][QTD_CARACTERES], int corrompidos[50][2]) {
    int k = 0;
    for(int i = 0; i < 50; i++) {
       for(int j = 0; j < QTD_CARACTERES; j++) {
           if (separado[i][j] == '*') {
                corrompidos[k][0] = i;
                corrompidos[k++][1] = j;
           } 
       }
    }
} // novo, colocar no main


// contem alterações, colocar no main
void traducao(char separado[50][QTD_CARACTERES], char banco[QTD_BANCO][QTD_LETRA][QTD_CARACTERES], char traduzido[50][3], int corrompidos[50][2], char possiveis[50][27][3]) {
    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < QTD_BANCO; j++) {
            if (strcmp(separado[i], banco[j][1]) == 0) {
                strcpy(traduzido[i], banco[j][0]);
                traduzido[i][1] = '\0';
                break;
            }
        }
    }
    // para traduzir os corrompidos
    for (int i = 0; i < 50; i++) {
        int l = 0;
        if (corrompidos[i][0] != 0) {
            int j = corrompidos[i][0]; 
            for (int k = 0; k < QTD_BANCO; k++) {
                if (strncmp(separado[j], banco[k][1], corrompidos[i][1]) == 0) { // compara até o ponto corrompido
                    strcpy(possiveis[i][l++], banco[k][0]); // guarda a letra possível
                } else if ( k == 26) {
                    possiveis[i][l][0] = '\0'; // marca o fim das possibilidades
                }
            }
        }
    }
}

// colocar no main
int saida(int corrompidos[50][2], char traduzido[50][3], char possiveis[50][27][3]) {
    int z = 0;
    int a = 0;
    for(int i = 0; i < 50 ; i++) {
        if (i == corrompidos[a][0]) {
            printf("[");
            for (int j = 0; j < 27 && possiveis[z][j][0] != '\0'; j++) {
                printf("%s",possiveis[z][j]);
            }
            printf("]");
            z ++;
            a ++;
        } else if (traduzido[i][0] != '\0') {
            printf("%s", traduzido[i]);
        }   
    } // para ver como fica a tradução com o corrompido
    printf("\n");

}

int main() {
    char separado[50][QTD_CARACTERES] = {
        {"-.-."}, {".-"}, {"-.."}, {".-*"}, {}, {}, {}, {}, {}, {},
        {}, {}, {}, {}, {}, {}, {}, {}, {}, {},
        {}, {}, {}, {}, {}, {}, {}, {}, {}, {},
        {}, {}, {}, {}, {}, {}, {}, {}, {}, {},
        {}, {}, {}, {}, {}, {}, {}, {}, {}, {}
    }; // entrada de teste

    char banco_tradu[QTD_BANCO][QTD_LETRA][QTD_CARACTERES] = {
    {"A", ".-"},   {"B", "-..."}, {"C", "-.-."}, {"D", "-.."},
    {"E", "."},    {"F", "..-."}, {"G", "--."},  {"H", "...."},
    {"I", ".."},   {"J", ".---"}, {"K", "-.-"},  {"L", ".-.."},
    {"M", "--"},   {"N", "-."},   {"O", "---"},  {"P", ".--."},
    {"Q", "--.-"}, {"R", ".-."},  {"S", "..."},  {"T", "-"},
    {"U", "..-"},  {"V", "...-"}, {"W", ".--"},  {"X", "-..-"},
    {"Y", "-.--"}, {"Z", "--.."}, {" ", "/"}
    }; // bando de dados para a tradução

    int corrompidos[50][2] = {0}; // novo, colocar no main
    encontrar_corrompido(separado, corrompidos); // novo, colocar no main
    for(int i = 0; i < 50; i++) {
        if (corrompidos[i][0] != 0) {
            printf("Corrompido na posicao: %d Indice: %d\n", corrompidos[i][0], corrompidos[i][1]);
        }
    } // para testar se funcionou

    char possiveis[50][27][3] = {'\0'}; // novo, substituir no main,
    char traduzido[50][3] = {'\0'}; /* novo, substituir no main, serve para definir tudo como vazio, 
    impedindo excesso de lixo na memória*/

    traducao(separado, banco_tradu, traduzido, corrompidos, possiveis); // novo, substituir no main

    saida(corrompidos, traduzido, possiveis); // novo, colocar no main

}

