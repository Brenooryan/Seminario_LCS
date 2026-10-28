# 🔤 Maior Subsequência Comum (LCS)

Implementação em Python do algoritmo **LCS (Longest Common Subsequence)** usando **Programação Dinâmica**. O projeto foi desenvolvido para um seminário de Algoritmos do curso de Engenharia da Computação do UNISAL.

---

## ❓ O problema

Dadas duas palavras, qual é a **maior sequência de letras que aparece nas duas, na mesma ordem**, mesmo que as letras não estejam lado a lado?

```
X = A B C B
Y = B C A B

LCS = "BCB"  (tamanho 3)
```

Em `Y`, a letra `A` é pulada: **B C ~~A~~ B**.

---

## ✂️ Subsequência x Substring

| | Substring | Subsequência |
|---|---|---|
| **Ideia** | Recortar um pedaço com tesoura | Riscar letras com caneta |
| **Letras coladas?** | Sim | Não precisam |
| **Ordem mantida?** | Sim | Sim |
| **"BAL" em "BRASIL"** | ❌ | ✅ |
| **"RAS" em "BRASIL"** | ✅ | ✅ |
| **"LAB" em "BRASIL"** | ❌ | ❌ (ordem trocada) |

Toda substring é também uma subsequência, mas nem toda subsequência é uma substring.

---

## 🎯 Entrada, saída e objetivo

| | Descrição | Exemplo |
|---|---|---|
| **Entrada** | Duas sequências `X` (tamanho `m`) e `Y` (tamanho `n`) | `"ABCB"`, `"BCAB"` |
| **Saída** | O tamanho da LCS e a própria subsequência | `3`, `"BCB"` |
| **Objetivo** | Encontrar a maior sequência comum às duas, na mesma ordem | — |

> Pode existir mais de uma LCS com o mesmo tamanho. O algoritmo devolve uma delas.

---

## 🧠 Estratégia: Programação Dinâmica

### Por que não força bruta?
Uma palavra com `m` letras tem **2^m subsequências**. Com 30 letras, isso já passa de **1 bilhão** de possibilidades para testar.

### Por que programação dinâmica?
O problema tem as duas propriedades que a técnica exige:

1. **Subestrutura ótima:** a resposta para as palavras inteiras é montada a partir das respostas para seus prefixos.
2. **Subproblemas sobrepostos:** os mesmos subproblemas aparecem várias vezes. Cada resultado é guardado em uma tabela e calculado uma única vez.

### Por que não guloso?
Pegar a primeira letra igual que aparece pode estragar a resposta. Em `ABCB` e `BCAB`, casar logo o `A` leva a `"AB"` (tamanho 2) em vez de `"BCB"` (tamanho 3).

### Por que não divisão e conquista?
Divisão e conquista separa o problema em partes **independentes**. Aqui os subproblemas **se repetem**, então resolvê-los separadamente seria refazer trabalho.

---

## ⚙️ Como o algoritmo funciona

### A tabela
`dp[i][j]` guarda o **tamanho da LCS entre as `i` primeiras letras de X e as `j` primeiras letras de Y**.

A linha 0 e a coluna 0 representam a palavra vazia e por isso valem sempre **0**.

### A regra

```
se X[i] == Y[j]:
    dp[i][j] = dp[i-1][j-1] + 1               ← diagonal + 1
senão:
    dp[i][j] = max(dp[i-1][j], dp[i][j-1])    ← maior entre cima e esquerda
```

| Vizinho | Significado |
|---|---|
| Diagonal `dp[i-1][j-1]` | Sem a última letra de X **e** de Y |
| Cima `dp[i-1][j]` | Sem a última letra de X |
| Esquerda `dp[i][j-1]` | Sem a última letra de Y |

### Tabela preenchida (X = ABCB, Y = BCAB)

|       | ∅ | B | C | A | B |
|:-----:|:-:|:-:|:-:|:-:|:-:|
| **∅** | 0 | 0 | 0 | 0 | 0 |
| **A** | 0 | 0 | 0 | 1 | 1 |
| **B** | 0 | **1** | 1 | 1 | 2 |
| **C** | 0 | 1 | **2** | 2 | 2 |
| **B** | 0 | 1 | 2 | 2 | **3** |

A resposta fica no canto inferior direito: `dp[4][4] = 3`.

### Backtracking (montar a palavra)
Partindo do canto inferior direito:
- **Letras iguais:** guarda a letra e anda na **diagonal**.
- **Letras diferentes:** anda para o vizinho **maior** (cima ou esquerda).

As letras saem de trás para frente: `B` → `CB` → `BCB`. As células em negrito na tabela acima mostram as letras guardadas.

### Pseudocódigo

```
LCS(X, Y):
    m ← tamanho de X;  n ← tamanho de Y
    criar tabela dp (m+1) × (n+1) com zeros
    para i de 1 até m:
        para j de 1 até n:
            se X[i] = Y[j]:
                dp[i][j] ← dp[i-1][j-1] + 1
            senão:
                dp[i][j] ← max(dp[i-1][j], dp[i][j-1])
    retornar dp[m][n]
```

---

## ▶️ Como executar

Pré-requisito: **Python 3** (não usa bibliotecas externas).

```bash
git clone <url-do-repositorio>
cd <pasta-do-repositorio>
python lcs.py
```

O programa roda os três testes abaixo e imprime, para cada um, a tabela preenchida e a resposta.

---

## 🧪 Testes

| X | Y | LCS | Tamanho | O que verifica |
|---|---|---|:-:|---|
| `ABCB` | `BCAB` | `BCB` | 3 | Exemplo principal |
| `AGGTAB` | `GXTXAYB` | `GTAB` | 4 | Palavras de tamanhos diferentes |
| `ABC` | `DEF` | `""` | 0 | Caso limite: nada em comum |

### Saída do programa

```
X = ABCB | Y = BCAB
      B  C  A  B
   0  0  0  0  0
A  0  0  0  1  1
B  0  1  1  1  2
C  0  1  2  2  2
B  0  1  2  2  3
Tamanho da LCS: 3 -> 'BCB'

X = AGGTAB | Y = GXTXAYB
      G  X  T  X  A  Y  B
   0  0  0  0  0  0  0  0
A  0  0  0  0  0  1  1  1
G  0  1  1  1  1  1  1  1
G  0  1  1  1  1  1  1  1
T  0  1  1  2  2  2  2  2
A  0  1  1  2  2  3  3  3
B  0  1  1  2  2  3  3  4
Tamanho da LCS: 4 -> 'GTAB'

X = ABC | Y = DEF
      D  E  F
   0  0  0  0
A  0  0  0  0
B  0  0  0  0
C  0  0  0  0
Tamanho da LCS: 0 -> ''
```

---

## 📈 Complexidade

| | Complexidade | Justificativa |
|---|:-:|---|
| **Tempo** | `O(m × n)` | Dois `for` aninhados, e cada célula é calculada em tempo constante. O backtracking adiciona apenas `O(m + n)`. |
| **Espaço** | `O(m × n)` | Tamanho da tabela `(m+1) × (n+1)`. |
| **Força bruta** | `O(2^m × n)` | Gera todas as subsequências de X e procura cada uma em Y. |

Com `m = n = 30`:

| Abordagem | Operações aproximadas |
|---|--:|
| Programação dinâmica | **900** |
| Força bruta | **> 32 bilhões** |

---

## 🌍 Aplicações

- **`diff` e Git:** comparam versões de arquivos e mostram as linhas alteradas.
- **Bioinformática:** comparação de sequências de DNA.
- **Detecção de plágio:** identificação de trechos parecidos entre textos ou códigos.

---

## 📁 Estrutura do projeto

```
.
├── lcs.py      # Implementação do algoritmo, impressão da tabela e testes
└── README.md   # Este arquivo
```

Seminário de Algoritmos · Engenharia da Computação · UNISAL
