#include <stdio.h>
#include <string.h> 

#define QTD_BANCO 27
#define QTD_LETRA 2
#define QTD_CARACTERES 6
#define QTD_ENTRADA 100


int separar(const char entrada[QTD_ENTRADA], char separado[50][QTD_CARACTERES]) {
    int b = 0, a = 0;
    // zera primeiro token
    separado[0][0] = '\0';

    for (int i = 0; entrada[i] != '\0'; i++) {
        char c = entrada[i];

        // ignora \n do fgets
        if (c == '\n' || c == '\r') continue;

        if (c != ' ') {
            if (a < QTD_CARACTERES - 1) separado[b][a++] = c; // evita overflow
        } else {
            // fecha token atual
            separado[b][a] = '\0';

            // checa se é separação de palavra (>= 2 espaços)
            if (entrada[i + 1] == ' ') {
                // consome todos os espaços extras
                while (entrada[i + 1] == ' ') i++;
                // adiciona token "/"
                if (b < 49) {
                    b++;
                    strcpy(separado[b], "/");
                }
            }

            // prepara novo token
            if (b < 49) {
                b++;
                a = 0;
                separado[b][0] = '\0';
            }
        }
    }

    // fecha último token se estava em construção
    if (separado[b][0] != '\0') {
        separado[b][a] = '\0';
        b++;
    }

    // sentinela (opcional se você usar o retorno)
    if (b < 50) separado[b][0] = '\0';

    return b; // quantidade de tokens válidos
}

int traducao(char separado[50][QTD_CARACTERES],
             int qtd_tokens,
             char banco[QTD_BANCO][QTD_LETRA][QTD_CARACTERES],
             char traduzido[50][QTD_CARACTERES]) {

    int k = 0;
    for (int i = 0; i < qtd_tokens && i < 50; i++) {
        if (strcmp(separado[i], "/") == 0) {           // separador de palavras
            strcpy(traduzido[k++], " ");               // vira espaço
            continue;
        }
        for (int j = 0; j < QTD_BANCO; j++) {          // 0..26
            if (strcmp(separado[i], banco[j][1]) == 0) {
                strcpy(traduzido[k++], banco[j][0]);   // letra
                break;
            }
        }
    }
    return k;
}

int main(void) {
    char banco_tradu[QTD_BANCO][QTD_LETRA][QTD_CARACTERES] = {
        {"A", ".-"},   {"B", "-..."}, {"C", "-.-."}, {"D", "-.."},
        {"E", "."},    {"F", "..-."}, {"G", "--."},  {"H", "...."},
        {"I", ".."},   {"J", ".---"}, {"K", "-.-"},  {"L", ".-.."},
        {"M", "--"},   {"N", "-."},   {"O", "---"},  {"P", ".--."},
        {"Q", "--.-"}, {"R", ".-."},  {"S", "..."},  {"T", "-"},
        {"U", "..-"},  {"V", "...-"}, {"W", ".--"},  {"X", "-..-"},
        {"Y", "-.--"}, {"Z", "--.."}, {"/", "/"} // mantém '/' como token de palavra
    };

    char texto[QTD_ENTRADA];
    printf("Digite o texto em Morse (letras por 1 espaço; palavras por 2+ espaços):\n");
    if (!fgets(texto, sizeof(texto), stdin)) return 0;

    char separado[50][QTD_CARACTERES];
    int qtd = separar(texto, separado);

    // debug opcional
    /*
    for (int i = 0; i < qtd; i++) printf("[%s]\n", separado[i]);
    */

    char traduzido[50][QTD_CARACTERES];
    int out = traducao(separado, qtd, banco_tradu, traduzido);

    for (int i = 0; i < out; i++) printf("%s", traduzido[i]);
    printf("\n");

    return 0;
}


    
