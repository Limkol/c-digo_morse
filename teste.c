/* 
 * Universidade Presbiteriana Mackenzie
 * Algoritmos e Programação II
 * Projeto: Tradutor de Código Morse (com letras corrompidas)
 * Integrantes: [NOME 1 - RA], [NOME 2 - RA], [NOME 3 - RA]
 *
 * Regras (resumo do enunciado):
 * - Letras em Morse separadas por 1 espaço.
 * - Palavras separadas por 2 ou mais espaços.
 * - Saída: letras SEM espaço entre si e APENAS 1 espaço entre palavras.
 * - Letra corrompida termina com '*' e significa que o código recebido é um PREFIXO.
 *   Ex.: ".-*" representa TODAS as letras cujo código começa com ".-" → [AJLPRW].
 *   As letras dentro de [] devem estar em ORDEM ALFABÉTICA.
 *
 * Observação: o programa usa somente conteúdos vistos em aula:
 *  - stdio.h, string.h
 *  - vetores/strings, if/else, laços, funções
 *  - busca linear na tabela de Morse
 */

#include <stdio.h>
#include <string.h>

/* ---------------------------
   Tabela de Código Morse A..Z
   --------------------------- */
static const char *MORSE[26] = {
    ".-","-...","-.-.","-..",".","..-.","--.","....","..",".---",
    "-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-",
    "..-","...-",".--","-..-","-.--","--.."
};
/* A letra na posição i corresponde a (char)('A' + i) */

/* -----------------------------------------------
   Função utilitária: remove o '\n' do fim da string
   ----------------------------------------------- */
void chomp(char *s) {
    size_t n = strlen(s);
    if (n > 0 && s[n-1] == '\n') {
        s[n-1] = '\0';
    }
}

/* --------------------------------------------------------
   Retorna 1 se 's' começa com 'prefix', senão retorna 0.
   Implementado com strncmp (visto em aula com string.h).
   -------------------------------------------------------- */
int starts_with(const char *s, const char *prefix) {
    size_t k = strlen(prefix);
    return (strncmp(s, prefix, k) == 0);
}

/* -----------------------------------------------------------------
   Converte um código Morse "completo" (sem '*') para índice [0..25]
   Retorna -1 se não encontrar.
   Busca linear na tabela (conteúdo de aula).
   ----------------------------------------------------------------- */
int morse_to_index(const char *code) {
    int i;
    for (i = 0; i < 26; i++) {
        if (strcmp(code, MORSE[i]) == 0) {
            return i;
        }
    }
    return -1;
}

/* ----------------------------------------------------------------------------
   Ordena (in-place) um vetor de chars em ordem crescente (A..Z).
   Implementação: insertion sort (algoritmo simples visto em aulas de vetores).
   ---------------------------------------------------------------------------- */
void insertion_sort_chars(char v[], int n) {
    int i, j;
    for (i = 1; i < n; i++) {
        char x = v[i];
        j = i - 1;
        while (j >= 0 && v[j] > x) {
            v[j+1] = v[j];
            j--;
        }
        v[j+1] = x;
    }
}

/* -----------------------------------------------------------------------------------
   Gera as possibilidades para um token corrompido (terminado com '*').
   Ex.: token = ".-*" → prefixo ".-"
   'out' recebe algo como "[AJLPRW]".
   ----------------------------------------------------------------------------------- */
void possibilidades_corrompida(const char *token, char *out) {
    char prefixo[16];
    int i, m = 0;
    char letras[26]; /* no máximo 26 letras possíveis */

    /* copia token sem o '*' final */
    size_t n = strlen(token);
    if (n == 0) { out[0] = '\0'; return; }
    if (token[n-1] != '*') { out[0] = '\0'; return; } /* segurança */
    /* prefixo = tudo menos o último caractere '*' */
    {
        size_t k = n - 1;
        size_t t;
        if (k >= sizeof(prefixo)) k = sizeof(prefixo) - 1; /* segurança */
        for (t = 0; t < k; t++) prefixo[t] = token[t];
        prefixo[k] = '\0';
    }

    /* percorre a tabela e junta as letras cujo código começa com o prefixo */
    for (i = 0; i < 26; i++) {
        if (starts_with(MORSE[i], prefixo)) {
            letras[m++] = (char)('A' + i);
        }
    }

    /* ordena em ordem alfabética (exigência do enunciado) */
    insertion_sort_chars(letras, m);

    /* monta a string final em 'out' no formato [XYZ] */
    {
        int p = 0;
        out[p++] = '[';
        for (i = 0; i < m; i++) out[p++] = letras[i];
        out[p++] = ']';
        out[p]   = '\0';
    }
}

/* ----------------------------------------------------------------------
   Traduz um token (uma "letra" em Morse).
   - Se terminar com '*', gera colchetes com possibilidades.
   - Caso contrário, converte código exato para letra A..Z (ou '?' se não
     encontrar).
   'out' recebe a string correspondente (ex.: "A" ou "[AJLPRW]").
   ---------------------------------------------------------------------- */
void traduz_token(const char *token, char *out) {
    size_t n = strlen(token);
    if (n == 0) { out[0] = '\0'; return; }

    if (token[n-1] == '*') {
        possibilidades_corrompida(token, out);
    } else {
        int idx = morse_to_index(token);
        if (idx >= 0) {
            out[0] = (char)('A' + idx);
            out[1] = '\0';
        } else {
            /* caso de código inválido: imprime '?' como fallback */
            out[0] = '?';
            out[1] = '\0';
        }
    }
}

/* --------------------------------------------------------------------------------
   Traduz uma linha inteira em Morse, respeitando as regras de espaçamento:
   - 1 espaço  → separador de letras (NÃO imprime espaço na saída)
   - >=2 espaços → separador de palavras (imprime UM espaço na saída)
   Estratégia: varredura caractere a caractere montando um "token".
   -------------------------------------------------------------------------------- */
void traduz_linha(const char *linha, char *saida) {
    char token[32];
    int t = 0;                 /* tamanho atual do token */
    int i = 0;
    int out_pos = 0;
    int n = (int)strlen(linha);

    while (i <= n) {
        if (linha[i] != ' ' && linha[i] != '\0') {
            /* acumula caracteres do token (., - ou *) */
            if (t < (int)sizeof(token) - 1) {
                token[t++] = linha[i];
            }
            i++;
        } else {
            /* fim de token (chegou em espaço ou no fim da linha) */
            token[t] = '\0';
            if (t > 0) {
                char piece[64];
                traduz_token(token, piece);
                /* copia o resultado do token para a saída */
                {
                    int j = 0;
                    while (piece[j] != '\0') {
                        saida[out_pos++] = piece[j++];
                    }
                }
                t = 0; /* reinicia o token */
            }

            /* conta quantos espaços consecutivos existem (para diferenciar letra/palavra) */
            {
                int spaces = 0;
                while (linha[i] == ' ') { spaces++; i++; }
                if (spaces >= 2) {
                    /* separador de palavra -> adiciona UM espaço na saída
                       (evita espaço no começo e duplo espaço) */
                    if (out_pos > 0 && saida[out_pos - 1] != ' ') {
                        saida[out_pos++] = ' ';
                    }
                }
                if (linha[i] == '\0') break; /* terminou a linha */
            }
        }
    }

    /* finaliza a string de saída */
    saida[out_pos] = '\0';
}

/* ----------------
   Programa principal
   ---------------- */
int main(void) {
    /* Lê uma linha (ou várias, se preferir: é só colocar num while(fgets...)) */
    char linha[4096];
    char saida[8192];

    if (!fgets(linha, sizeof(linha), stdin)) {
        return 0; /* sem entrada */
    }
    chomp(linha);

    traduz_linha(linha, saida);

    /* Saída final já vem MAIÚSCULA (porque mapeamos A..Z) e com regras de espaço aplicadas */
    puts(saida);
    return 0;
}
