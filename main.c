#include <stdio.h>
#include <string.h> 
#include <ctype.h>


char separar (char entrada[], char separado[50][6]) {
    int b = 0, a = 0;
    for(int i = 0; entrada[i] != '\0'; i++) {
        // igual a diferente de 0, então não é espaço 
        if (entrada[i] != ' ') {
            separado[b][a++] = entrada[i];
        } else {
            if (entrada[i+1] == ' ') {
                a = 0;
                b++;
                i++;
                separado[b][a++] = '|'; // marca espaço entre palavras
            }
            separado[b][a] = '\0';
            b++;
            a = 0;
        }
    }
}

int traducao(char separado[50][6], char banco[27][2][6], char traduzido[50][4]) {
    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < 26; j++) {
            if (strcmp(separado[i], banco[j][1]) == 0) {
                strcpy(traduzido[i], banco[j][0]);
            }
            
        }
    }
}

void main() {
    char banco_tradu[27][2][6] = {
    {"A", ".-"},   {"B", "-..."}, {"C", "-.-."}, {"D", "-.."},
    {"E", "."},    {"F", "..-."}, {"G", "--."},  {"H", "...."},
    {"I", ".."},   {"J", ".---"}, {"K", "-.-"},  {"L", ".-.."},
    {"M", "--"},   {"N", "-."},   {"O", "---"},  {"P", ".--."},
    {"Q", "--.-"}, {"R", ".-."},  {"S", "..."},  {"T", "-"},
    {"U", "..-"},  {"V", "...-"}, {"W", ".--"},  {"X", "-..-"},
    {"Y", "-.--"}, {"Z", "--.."}, {"/", "|"}
    };
    /*for(int i = 0; i < 26; i++) {
        printf("%s = %s\n", banco_tradu[i][0], banco_tradu[i][1]);
    } 
    Talvez usar depois
    */

    char texto[100];
    printf("Digite o texto:");
    fgets(texto, 100, stdin);
    
    char separado[50][6];
    separar (texto, separado);
    for(int i = 0; i < 50 && separado[i][0] != '\0'; i++) {
        printf("%s\n", separado[i]);
    }

    char traduzido[50][4];
    traducao(separado, banco_tradu, traduzido);
    for(int i = 0; i < 50 && traduzido[i][0] != '\0'; i++) {
        printf("%s", traduzido[i]);
    }
    printf("\n");
}