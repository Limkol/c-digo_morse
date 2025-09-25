#include <stdio.h>
#include <string.h> 
#include <ctype.h>


char separar (char entrada[], char separado[50][5]) {
    int b = 0, a = 0;
    for(int i = 0; entrada[i] != '\0'; i++) {
        // igual a diferente de 0, então não é espaço 
        if (entrada[i] != ' ') {
            separado[b][a++] = entrada[i];
        } else {
            if (entrada[i+1] == ' ') {
                a = 0;
                b++;
                separado[b][a++] = '|'; // marca espaço entre palavras
            }
            separado[b][a] = '\0';
            b++;
            a = 0;
        }
    }
}

int traducao() {

}

void main() {
    char banco_tradu[26][2][6] = {
    {"A", ".-"},   {"B", "-..."}, {"C", "-.-."}, {"D", "-.."},
    {"E", "."},    {"F", "..-."}, {"G", "--."},  {"H", "...."},
    {"I", ".."},   {"J", ".---"}, {"K", "-.-"},  {"L", ".-.."},
    {"M", "--"},   {"N", "-."},   {"O", "---"},  {"P", ".--."},
    {"Q", "--.-"}, {"R", ".-."},  {"S", "..."},  {"T", "-"},
    {"U", "..-"},  {"V", "...-"}, {"W", ".--"},  {"X", "-..-"},
    {"Y", "-.--"}, {"Z", "--.."}
    };
    /*for(int i = 0; i < 26; i++) {
        printf("%s = %s\n", banco_tradu[i][0], banco_tradu[i][1]);
    } 
    Talvez usar depois
    */

    char texto[100];
    printf("Digite o texto:");
    fgets(texto, 100, stdin);
    char separado[50][5];

    separar (texto, separado);
    for(int i = 0; i < 50 && separado[i][0] != '\0'; i++) {
        printf("%s\n", separado[i]);
    }
}