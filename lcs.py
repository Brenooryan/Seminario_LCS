# Maior Subsequência Comum (LCS) - Programação Dinâmica

def lcs(x, y):
    m = len(x)
    n = len(y)

    # 1. Tabela (m+1) x (n+1) cheia de zeros
    #    (linha 0 e coluna 0 = comparar com string vazia -> 0)
    dp = [[0] * (n + 1) for _ in range(m + 1)]

    # 2. Preenche a tabela linha por linha
    for i in range(1, m + 1):
        for j in range(1, n + 1):
            if x[i - 1] == y[j - 1]:
                # letras iguais: pega a diagonal e soma 1
                dp[i][j] = dp[i - 1][j - 1] + 1
            else:
                # letras diferentes: o maior entre cima e esquerda
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1])

    # 3. Volta pela tabela (do fim para o começo) para montar a resposta
    resultado = ""
    i, j = m, n
    while i > 0 and j > 0:
        if x[i - 1] == y[j - 1]:
            resultado = x[i - 1] + resultado
            i -= 1
            j -= 1
        elif dp[i - 1][j] >= dp[i][j - 1]:
            i -= 1
        else:
            j -= 1

    return dp[m][n], resultado, dp


def mostrar_tabela(x, y, dp):
    print("      " + "  ".join(y))
    for i in range(len(dp)):
        letra = x[i - 1] if i > 0 else " "
        print(letra + "  " + "  ".join(str(v) for v in dp[i]))


# 4. Testes
testes = [
    ("ABCB", "BCAB"),
    ("AGGTAB", "GXTXAYB"),
    ("ABC", "DEF"),
]

for x, y in testes:
    tamanho, subseq, dp = lcs(x, y)
    print(f"\nX = {x} | Y = {y}")
    mostrar_tabela(x, y, dp)
    print(f"Tamanho da LCS: {tamanho} -> '{subseq}'")
