/*
ALGORITMOS E PROGRAMAÇÃO II
    Tradutor de Código Morse - Projeto 1 (Proj1)

Integrantes do grupo:
    Gustavo Francisco Toito – 10438660 – 02G
    Henrique Cunha Alves – 10740428 – 02G
    Guilherme Longo Gouveia Xavier - 10736785 - 02G
    
Vídeo Explicativo
    Link: https://youtu.be/D1Z8pHH2e0s

*/
#include <stdio.h>
#include <string.h> 

#define QTD_BANCO 27 // Quantidade de grupos no banco de tradução
#define QTD_LETRA 2 // Quantidade de elementos por grupo, sendo eles, letra e código morse
#define QTD_CARACTERES_MORSE 6 // Quantidade máxima de caracteres para cada letra em morse
#define QTD_ENTRADA 1000 // Quantidade máxima de caracteres na entrada do usuario
#define QTD_MAX_SEPARADO 500 // Quantidade máxima de letras na qual a entrada pode ser separada

// Função para separar a entrada (em morse) em grupos para realizar a tradução
void separar (char entrada[QTD_ENTRADA], char separado[QTD_MAX_SEPARADO][QTD_CARACTERES_MORSE]) {
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
int encontrar_corrompido(char separado[QTD_MAX_SEPARADO][QTD_CARACTERES_MORSE], int corrompidos[QTD_MAX_SEPARADO][2]) {
    int k = 0;
    for(int i = 0; i < QTD_MAX_SEPARADO; i++) {
       for(int j = 0; j < QTD_CARACTERES_MORSE; j++) {
           if (separado[i][j] == '*') {
                corrompidos[k][0] = i;
                corrompidos[k++][1] = j;
                // Se encontrar um caractere corrompido, salva o indice da letra corrompida e o indice do caractere corrompido
           } 
       }
    }
}

// Função para traduzir o morse para a correspondente letra do alfabeto
void traducao(char separado[QTD_MAX_SEPARADO][QTD_CARACTERES_MORSE], char banco[QTD_BANCO][QTD_LETRA][QTD_CARACTERES_MORSE], char traduzido[QTD_MAX_SEPARADO][3], int corrompidos[QTD_MAX_SEPARADO][2], char possiveis[QTD_MAX_SEPARADO][27][3]) {
    // Essa primeira parte traduz apenas os que não estão corrompidos
    for (int i = 0; i < QTD_MAX_SEPARADO; i++) {
        for (int j = 0; j < QTD_BANCO; j++) {
            if (strcmp(separado[i], banco[j][1]) == 0) {
                strcpy(traduzido[i], banco[j][0]);
                traduzido[i][1] = '\0';
                break;
            }
        }
    }
    // Essa segunda parte encontra as possíveis letras para os corrompidos
    for (int i = 0; i < QTD_MAX_SEPARADO; i++) {
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
int saida(int corrompidos[QTD_MAX_SEPARADO][2], char traduzido[QTD_MAX_SEPARADO][3], char possiveis[QTD_MAX_SEPARADO][27][3]) {
    int z = 0;
    int a = 0;
    for(int i = 0; i < QTD_MAX_SEPARADO ; i++) {
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
    char banco_traducao[QTD_BANCO][QTD_LETRA][QTD_CARACTERES_MORSE] = {
    {"A", ".-"},   {"B", "-..."}, {"C", "-.-."}, {"D", "-.."},
    {"E", "."},    {"F", "..-."}, {"G", "--."},  {"H", "...."},
    {"I", ".."},   {"J", ".---"}, {"K", "-.-"},  {"L", ".-.."},
    {"M", "--"},   {"N", "-."},   {"O", "---"},  {"P", ".--."},
    {"Q", "--.-"}, {"R", ".-."},  {"S", "..."},  {"T", "-"},
    {"U", "..-"},  {"V", "...-"}, {"W", ".--"},  {"X", "-..-"},
    {"Y", "-.--"}, {"Z", "--.."}, {" ", "/"}
    };

    // Cria o vetor para guarda a entrada do usuario
    char entrada[QTD_ENTRADA];
    printf("Digite o texto:");
    // Lê a entrada do usuário
    fgets(entrada, QTD_ENTRADA, stdin);
    
    // Cria a matriz para guardar os códigos morse separados
    char separado[QTD_MAX_SEPARADO][QTD_CARACTERES_MORSE];
    separar (entrada, separado); // Chama a função para separar a entrada

    // Cria a matriz para guardar os indices dos caracteres corrompidos
    int corrompidos[QTD_MAX_SEPARADO][2] = {-1}; // Inicializa com -1 para indicar que não há corrompidos
    encontrar_corrompido(separado, corrompidos); // Chama a função para encontrar os indices dos palavras corrompidas

    // Cria as matrizes para guardar as possíveis traduções para os corrompidos
    char possiveis[QTD_MAX_SEPARADO][27][3] = {'\0'}; // Inicializa com '\0' para evitar transbordo na memória
    // Cria a matriz para guardar o texto traduzido
    char traduzido[QTD_MAX_SEPARADO][3] = {'\0'}; // Inicializa com '\0' para evitar transbordo na memória
    // Chama a função para realizar a tradução
    traducao(separado, banco_traducao, traduzido, corrompidos, possiveis); 
    // Chama a função para imprimir a saída
    saida(corrompidos, traduzido, possiveis);
}