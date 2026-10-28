/* Maior Subsequência Comum (LCS) - Programação Dinâmica */

#include <stdio.h>   /* biblioteca de entrada e saída: printf */
#include <string.h>  /* biblioteca de strings: strlen */

#define MAX 100      /* tamanho máximo das palavras aceitas */

/*
 * Função que recebe duas palavras x = "ABCB" e y = "BCAB".
 * Preenche a tabela dp e a string resultado, e devolve o tamanho da LCS.
 * (Em C não dá para devolver 3 valores como no Python, então a tabela
 *  e o resultado são passados como parâmetros e preenchidos aqui dentro.)
 */
int lcs(const char *x, const char *y, int dp[MAX + 1][MAX + 1], char *resultado) { /* início da função lcs */
    int m = strlen(x);  /* strlen devolve o tamanho da palavra x */
    int n = strlen(y);  /* strlen devolve o tamanho da palavra y */
    int i, j;           /* i = índice da linha, j = índice da coluna */

    /* 1. Tabela (m+1) x (n+1) cheia de zeros
          (linha 0 e coluna 0 = comparar com string vazia -> 0) */
    for (i = 0; i <= m; i++)        /* percorre todas as linhas, de 0 até m */
        for (j = 0; j <= n; j++)    /* percorre todas as colunas, de 0 até n */
            dp[i][j] = 0;           /* coloca zero na célula [i][j] */

    /* 2. Preenche a tabela linha por linha */
    for (i = 1; i <= m; i++) {          /* i é a linha, ligada às letras de X (começa em 1, a linha 0 já é zero) */
        for (j = 1; j <= n; j++) {      /* j é a coluna, ligada às letras de Y (começa em 1, a coluna 0 já é zero) */
            if (x[i - 1] == y[j - 1]) { /* compara a letra da linha com a letra da coluna (i-1 e j-1 porque a string começa em 0) */
                dp[i][j] = dp[i - 1][j - 1] + 1;  /* letras iguais: pega o valor da diagonal e soma 1 */
            } else {                    /* se as letras forem diferentes... */
                dp[i][j] = (dp[i - 1][j] > dp[i][j - 1])  /* compara o valor de cima com o da esquerda */
                         ? dp[i - 1][j]                   /* se o de cima for maior, usa o de cima */
                         : dp[i][j - 1];                  /* senão, usa o da esquerda */
            }                           /* fim do if/else */
        }                               /* fim do laço das colunas */
    }                                   /* fim do laço das linhas */

    /* 3. Volta pela tabela (do fim para o começo) para montar a resposta */
    int tamanho = dp[m][n];       /* o tamanho da LCS fica na última célula da tabela */
    int k = tamanho - 1;          /* k é a posição onde a próxima letra será escrita (começa no fim da string) */
    resultado[tamanho] = '\0';    /* coloca o '\0' que marca o fim da string em C */

    i = m;                        /* começa na última linha da tabela */
    j = n;                        /* começa na última coluna da tabela */
    while (i > 0 && j > 0) {      /* repete enquanto não chegar na linha 0 ou na coluna 0 */
        if (x[i - 1] == y[j - 1]) {  /* se as letras forem iguais, ela faz parte da LCS */
            resultado[k] = x[i - 1]; /* escreve a letra na posição k da resposta */
            k--;                     /* a próxima letra vai uma posição para trás */
            i--;                     /* sobe uma linha (movimento na diagonal) */
            j--;                     /* volta uma coluna (movimento na diagonal) */
        } else if (dp[i - 1][j] >= dp[i][j - 1]) { /* se o valor de cima for maior ou igual ao da esquerda... */
            i--;                     /* ...sobe uma linha */
        } else {                     /* se o valor da esquerda for maior... */
            j--;                     /* ...volta uma coluna */
        }                            /* fim do if/else */
    }                                /* fim do while */

    return tamanho;               /* retorna o tamanho da LCS (a tabela e a string já foram preenchidas) */
}                                 /* fim da função lcs */

void mostrar_tabela(const char *x, const char *y, int dp[MAX + 1][MAX + 1]) { /* função que imprime a tabela dp */
    int m = strlen(x);            /* tamanho da palavra x (número de linhas com letra) */
    int n = strlen(y);            /* tamanho da palavra y (número de colunas com letra) */
    int i, j;                     /* índices da linha e da coluna */

    printf("      ");             /* espaços para alinhar o cabeçalho com os números */
    for (j = 0; j < n; j++)       /* percorre cada letra de y */
        printf("%c  ", y[j]);     /* imprime a letra de y seguida de dois espaços */
    printf("\n");                 /* pula para a próxima linha depois do cabeçalho */

    for (i = 0; i <= m; i++) {                   /* percorre cada linha da tabela, de 0 até m */
        char letra = (i > 0) ? x[i - 1] : ' ';   /* na linha 0 não tem letra (espaço); nas outras, pega a letra de x */
        printf("%c  ", letra);                   /* imprime a letra da linha seguida de dois espaços */
        for (j = 0; j <= n; j++)                 /* percorre cada coluna da linha */
            printf("%d  ", dp[i][j]);            /* imprime o valor da célula seguido de dois espaços */
        printf("\n");                            /* pula para a próxima linha da tabela */
    }                                            /* fim do laço das linhas */
}                                                /* fim da função mostrar_tabela */

int main(void) {                  /* função principal, onde o programa começa */
    /* 4. Testes */
    const char *testes[][2] = {   /* lista de pares de palavras para testar */
        {"ABCB", "BCAB"},         /* teste 1 */
        {"AGGTAB", "GXTXAYB"},    /* teste 2 */
        {"ABC", "DEF"},           /* teste 3 (nenhuma letra em comum) */
    };                            /* fim da lista de testes */
    int qtd = sizeof(testes) / sizeof(testes[0]);  /* calcula quantos testes existem na lista */

    static int dp[MAX + 1][MAX + 1];  /* tabela dp (static para não ocupar a pilha com um vetor grande) */
    char subseq[MAX + 1];             /* string onde a LCS será guardada (+1 para o '\0') */

    for (int t = 0; t < qtd; t++) {   /* percorre cada teste da lista */
        const char *x = testes[t][0]; /* pega a primeira palavra do par */
        const char *y = testes[t][1]; /* pega a segunda palavra do par */

        int tamanho = lcs(x, y, dp, subseq);       /* calcula a LCS, preenchendo dp e subseq */
        printf("\nX = %s | Y = %s\n", x, y);       /* mostra quais palavras estão sendo comparadas */
        mostrar_tabela(x, y, dp);                  /* imprime a tabela dp preenchida */
        printf("Tamanho da LCS: %d -> '%s'\n", tamanho, subseq); /* mostra o tamanho e a subsequência */
    }                                 /* fim do laço dos testes */

    return 0;                         /* indica que o programa terminou sem erros */
}                                     /* fim da função main */