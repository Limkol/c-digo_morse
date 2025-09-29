#include <stdio.h>
#include <string.h> 
#include <ctype.h>

#define QTD_BANCO 27
#define QTD_LETRA 2
#define QTD_CARACTERES 6
#define QTD_ENTRADA 100

void separar (char entrada[QTD_ENTRADA], char separado[50][QTD_CARACTERES]) {
    int b = 0, a = 0;
    for(int i = 0; entrada[i] != '\0'; i++) {
        if (entrada[i] != ' ') {
            separado[b][a++] = entrada[i];
        } else {
            if (entrada[i+1] == ' ') {
                a = 0;
                b++;
                i++;
                separado[b][a++] = '/'; // marca espaço entre palavras
            }
            separado[b][a] = '\0';
            b++;
            a = 0;
        }
    }
    separado[b][a-1] = '\0';
}

void traducao(char sepa[50][QTD_CARACTERES], char banco[QTD_BANCO][QTD_LETRA][QTD_CARACTERES], char traduzido[50][3]) {
    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < QTD_BANCO; j++) {
            if (strcmp(sepa[i], banco[j][1]) == 0) {
                strcpy(traduzido[i], banco[j][0]);
                traduzido[i][1] = '\0';
                break;
            } else{
                traduzido[i][0] = '\0';
            }
        }
    }
}

int main() {
    char banco_tradu[QTD_BANCO][QTD_LETRA][QTD_CARACTERES] = {
    {"A", ".-"},   {"B", "-..."}, {"C", "-.-."}, {"D", "-.."},
    {"E", "."},    {"F", "..-."}, {"G", "--."},  {"H", "...."},
    {"I", ".."},   {"J", ".---"}, {"K", "-.-"},  {"L", ".-.."},
    {"M", "--"},   {"N", "-."},   {"O", "---"},  {"P", ".--."},
    {"Q", "--.-"}, {"R", ".-."},  {"S", "..."},  {"T", "-"},
    {"U", "..-"},  {"V", "...-"}, {"W", ".--"},  {"X", "-..-"},
    {"Y", "-.--"}, {"Z", "--.."}, {" ", "/"}
    };
    /*for(int i = 0; i < 26; i++) {
        printf("%s = %s\n", banco_tradu[i][0], banco_tradu[i][1]);
    } 
    Talvez usar depois
    */

    char texto[QTD_ENTRADA];
    printf("Digite o texto:");
    fgets(texto, QTD_ENTRADA, stdin);
    
    char separado[50][QTD_CARACTERES];
    separar (texto, separado);
    for(int i = 0; i < 50 && separado[i][0] != '\0'; i++) {
        printf("%s", separado[i]);
    }
    printf("\n");

    char traduzido[50][3];
    traducao(separado, banco_tradu, traduzido); //problema aqui!!!
    for(int i = 0; i < 50 && traduzido[i][0] != '\0'; i++) {
        printf("%s", traduzido[i]);
    }
    printf("\n");
    return 0;
}