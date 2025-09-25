#include <stdio.h>
#include <string.h> 

// recebe 'entrada' e preenche 'separado'
void traducao(char entrada[], char separado[50][5]) {
    int contador = 0, b = 0, a = 0;
    for (int i = 0; entrada[i] != '\0'; i++) {
        if (entrada[i] != ' ') {
            separado[b][a++] = entrada[i];
        } else {
            separado[b][a] = '\0'; // termina a string
            b++;
            a = 0;
        }
    }
}

void main() {
    char texto[100];
    fgets(texto, 100, stdin);

    char sepa[50][5];   // até 50 "palavras", cada com até 10 caracteres
    traducao(texto, sepa);

    for (int i = 0; i < 50 && sepa[i][0] != '\0'; i++) {
        printf("Token %d: %s\n", i, sepa[i]);
    }

}