#include <stdio.h>
#include <string.h> 
#include <ctype.h>


char traducao (char banco_tradu[][], char entrada[]) {
    int contador = 0;
    int b = 0;
    char separado[50][4];
    for(int i = 0; i < 100; i++) {
        // igual a diferente de 0, então não é espaço 
        if (strcmp(" ", entrada[i]) != 0) {
            contador++;
        } else {
            for (int a = i-contador; a < contador; a++) {
                strcpy(separado[b][a],entrada[a])
            }
            contador = 0;
            b++;
        }
    }

}

// . . . . . .\0

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
}