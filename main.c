#include <stdio.h>
#include <string.h> 
#include <ctype.h>

#define QTD_BANCO 27 // Quantidade de letras no banco de tradução (A-Z e espaço)
#define QTD_LETRA 2 // Quantidade de elementos por letra (letra e código morse)
#define QTD_CARACTERES 6 // Quantidade máxima de caracteres por código morse
#define QTD_ENTRADA 100 // Quantidade máxima de caracteres na entrada do usuario

// Função para separar a entrada (em morse) em grupos para realizar a tradução
void separar (char entrada[QTD_ENTRADA], char separado[50][QTD_CARACTERES]) {
    int b = 0, a = 0;
    
    for(int i = 0; entrada[i] != '\0'; i++) { // Enquanto a string não acabar (\0), vai percorrendo
        if (entrada[i] != ' ') {
            // Se o caractere não for espaço, adiciona na matriz separado
            separado[b][a++] = entrada[i]; 
        } else {
            // Se o caractere for espaço e o próximo caractere tambem for espaço, marca espaço entre palavras
            if (entrada[i+1] == ' ') {
                a = 0;
                b++;
                i++;
                separado[b][a++] = '/'; // Marca espaço entre palavras
            }
            // Se o caractere for espaço e o próximo caractere não for espaço, finaliza a letra
            separado[b][a] = '\0';
            b++;
            a = 0;
        }
    }
    separado[b][a-1] = '\0'; // Finaliza a última letra apagando o enter, pois o enter também é lido na entrada
}


// Função para encontrar os caracteres corrompidos na matriz separado
int encontrar_corrompido(char separado[50][QTD_CARACTERES], int corrompidos[50][2]) {
    int k = 0;
    for(int i = 0; i < 50; i++) {
       for(int j = 0; j < QTD_CARACTERES; j++) {
           if (separado[i][j] == '*') {
                corrompidos[k][0] = i;
                corrompidos[k++][1] = j;
                // Se encontrar um caractere corrompido, salva o indice da letra corrompida e o indice do caractere corrompido
           } 
       }
    }
}

// Função para traduzir o morse para a correspondente letra do alfabeto
void traducao(char separado[50][QTD_CARACTERES], char banco[QTD_BANCO][QTD_LETRA][QTD_CARACTERES], char traduzido[50][3], int corrompidos[50][2], char possiveis[50][27][3]) {
    // Essa primeira parte traduz apenas os que não estão corrompidos
    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < QTD_BANCO; j++) {
            if (strcmp(separado[i], banco[j][1]) == 0) {
                strcpy(traduzido[i], banco[j][0]);
                traduzido[i][1] = '\0';
                break;
            }
        }
    }
    // Essa segunda parte encontra as possíveis letras para os corrompidos
    for (int i = 0; i < 50; i++) {
        int l = 0;
        if (corrompidos[i][0] != -1) {
            int j = corrompidos[i][0]; 
            for (int k = 0; k < QTD_BANCO; k++) {
                if (strncmp(separado[j], banco[k][1], corrompidos[i][1]) == 0) { // Compara os caracteres antes do sinal de corrompido (*)
                    strcpy(possiveis[i][l++], banco[k][0]); // Guarda as possiveis letras
                } else if ( k == 26) {
                    possiveis[i][l][0] = '\0'; // Marca o fim das possibilidades para evitar transbordo na memoria
                }
            }
        }
    }
}

// Função para imprimir a saída, ou seja, o texto traduzido
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
    }
    printf("\n");
}

int main() {
    // Banco de tradução do código morse para o alfabeto
    char banco_tradu[QTD_BANCO][QTD_LETRA][QTD_CARACTERES] = {
    {"A", ".-"},   {"B", "-..."}, {"C", "-.-."}, {"D", "-.."},
    {"E", "."},    {"F", "..-."}, {"G", "--."},  {"H", "...."},
    {"I", ".."},   {"J", ".---"}, {"K", "-.-"},  {"L", ".-.."},
    {"M", "--"},   {"N", "-."},   {"O", "---"},  {"P", ".--."},
    {"Q", "--.-"}, {"R", ".-."},  {"S", "..."},  {"T", "-"},
    {"U", "..-"},  {"V", "...-"}, {"W", ".--"},  {"X", "-..-"},
    {"Y", "-.--"}, {"Z", "--.."}, {" ", "/"}
    };

    // Cria o vetor para guarda a entrada do usuario
    char texto[QTD_ENTRADA];
    printf("Digite o texto:");
    // Lê a entrada do usuário
    fgets(texto, QTD_ENTRADA, stdin);
    
    // Cria a matriz para guardar os códigos morse separados
    char separado[50][QTD_CARACTERES];
    separar (texto, separado); // Chama a função para separar a entrada

    // Cria a matriz para guardar os indices dos caracteres corrompidos
    int corrompidos[50][2] = {-1}; // Inicializa com -1 para indicar que não há corrompidos
    encontrar_corrompido(separado, corrompidos); // Chama a função para encontrar os indices dos palavras corrompidas

    // Cria as matrizes para guardar as possíveis traduções para os corrompidos
    char possiveis[50][27][3] = {'\0'}; // Inicializa com '\0' para evitar transbordo na memória
    // Cria a matriz para guardar o texto traduzido
    char traduzido[50][3] = {'\0'}; // Inicializa com '\0' para evitar transbordo na memória
    // Chama a função para realizar a tradução
    traducao(separado, banco_tradu, traduzido, corrompidos, possiveis); 
    // Chama a função para imprimir a saída
    saida(corrompidos, traduzido, possiveis);
}