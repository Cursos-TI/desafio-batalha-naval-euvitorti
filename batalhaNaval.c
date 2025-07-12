#include <stdio.h>

#define MAX_ROWS 10  // Máximo de linhas suportadas
#define MAX_COLS 10  // Máximo de colunas suportadas

// --- MÓDULOS NÍVEL NOVATO ---

// Posiciona um navio verticalmente: preenche 'tamanho' células a partir de (startRow, col)
void posicionaNavioVertical(int tab[][MAX_COLS], int startRow, int col, int tamanho, int marcador) {
    for (int i = 0; i < tamanho; i++) {
        // Para cada parte do navio, marcamos o tabuleiro na coluna fixa
        tab[startRow + i][col] = marcador;
    }
}

// Posiciona um navio horizontalmente: preenche 'tamanho' células a partir de (row, startCol)
void posicionaNavioHorizontal(int tab[][MAX_COLS], int row, int startCol, int tamanho, int marcador) {
    for (int j = 0; j < tamanho; j++) {
        // Para cada parte do navio, marcamos o tabuleiro na linha fixa
        tab[row][startCol + j] = marcador;
    }
}

// Exibe as coordenadas de todas as células marcadas como 1 (navio nível Novato)
void exibeCoordenadas(int tab[][MAX_COLS], int rows, int cols) {
    printf("Coordenadas dos navios (Novato):\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (tab[i][j] == 1) {
                // Quando encontra parte de navio, imprime coordenada
                printf(" - Parte em: (%d, %d)\n", i, j);
            }
        }
    }
}

// Limpa o tabuleiro, definindo todas as células para 0
void limpaTabuleiro(int tab[][MAX_COLS], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            tab[i][j] = 0;  // Marca como célula vazia
        }
    }
}

// Executa o nível Novato: cria um tabuleiro 5x5, posiciona dois navios e exibe coordenadas
void nivelNovato() {
    int tab[5][MAX_COLS];
    // Prepara a matriz 5x5 dentro do buffer de largura MAX_COLS
    limpaTabuleiro((int(*)[MAX_COLS])tab, 5, 5);

    // Posiciona navio vertical de tamanho 3 em (1,2)
    posicionaNavioVertical((int(*)[MAX_COLS])tab, 1, 2, 3, 1);
    // Posiciona navio horizontal de tamanho 2 em (3,0)
    posicionaNavioHorizontal((int(*)[MAX_COLS])tab, 3, 0, 2, 1);

    // Exibe todas as partes do navio
    exibeCoordenadas((int(*)[MAX_COLS])tab, 5, 5);
}

// --- MÓDULOS NÍVEL AVENTUREIRO ---

enum DiagonalDirecao { DESCENDENTE, ASCENDENTE };

// Posiciona um navio diagonal: cresce em colunas e varia linhas conforme direção
void posicionaNavioDiagonal(int tab[][MAX_COLS],
                            int startRow, int startCol,
                            int tamanho, enum DiagonalDirecao dir, int marcador) {
    for (int i = 0; i < tamanho; i++) {
        // Calcula linha: aumenta ou diminui conforme direção desejada
        int r = (dir == DESCENDENTE) ? (startRow + i) : (startRow - i);
        int c = startCol + i;  // coluna sempre avança
        tab[r][c] = marcador;  // marca parte do navio diagonal
    }
}

// Exibe todo o tabuleiro em modo aventura, imprimindo 0 para vazio e valor para marcados
void exibeTabuleiro(int tab[][MAX_COLS], int rows, int cols) {
    printf("Tabuleiro (Aventureiro):\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", tab[i][j]);  // imprime cada célula seguida de espaço
        }
        printf("\n");  // nova linha ao final de cada linha do tabuleiro
    }
}

// Executa o nível Aventureiro: monta tabuleiro 10x10 e posiciona quatro navios de diferentes orientações
void nivelAventureiro() {
    int tab[MAX_ROWS][MAX_COLS];
    int rows = 10, cols = 10;
    limpaTabuleiro(tab, rows, cols);  // limpa o tabuleiro completo

    // Posiciona barco vertical de tamanho 4 em (0,0)
    posicionaNavioVertical(tab, 0, 0, 4, 3);
    // Posiciona barco horizontal de tamanho 3 em (5,5)
    posicionaNavioHorizontal(tab, 5, 5, 3, 3);
    // Posiciona barco diagonal descendente de tamanho 4 em (2,2)
    posicionaNavioDiagonal(tab, 2, 2, 4, DESCENDENTE, 3);
    // Posiciona barco diagonal ascendente de tamanho 3 em (9,0)
    posicionaNavioDiagonal(tab, 9, 0, 3, ASCENDENTE, 3);

    // Exibe todo o tabuleiro após posicionamentos
    exibeTabuleiro(tab, rows, cols);
}

// --- MÓDULOS NÍVEL MESTRE ---

// Aplica padrão de cone: triângulo simétrico no topo da matriz
void aplicaCone(int mat[][MAX_COLS], int size) {
    int mid = size / 2;  // ponto central da largura
    for (int i = 0; i <= mid; i++) {
        // Para cada linha até o meio, define início e fim do cone
        for (int j = mid - i; j <= mid + i; j++) {
            mat[i][j] = 1;  // marca área de habilidade
        }
    }
}

// Aplica padrão de cruz: linha e coluna centrais marcadas
void aplicaCruz(int mat[][MAX_COLS], int size) {
    int mid = size / 2;
    for (int i = 0; i < size; i++) {
        mat[mid][i] = 1;  // marca linha central
        mat[i][mid] = 1;  // marca coluna central
    }
}

// Aplica padrão de octaedro: losango centrado em torno da linha média
void aplicaOctaedro(int mat[][MAX_COLS], int size) {
    int mid = size / 2;
    for (int i = 0; i < size; i++) {
        int dist = abs(mid - i);  // distância vertical do centro
        // Preenche colunas em forma de losango, pulando bordas
        for (int j = dist; j < size - dist; j++) {
            mat[i][j] = 1;
        }
    }
}

// Exibe a matriz de habilidade com nome, imprimindo 0 ou 1
void exibeHabilidade(int mat[][MAX_COLS], int size, const char *nome) {
    printf("Habilidade '%s':\n", nome);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
    printf("\n");  // linha em branco após exibir a habilidade
}

// Executa o nível Mestre: gera e exibe três padrões de habilidade distintos
void nivelMestre() {
    int size = 5;
    int mat[MAX_ROWS][MAX_COLS] = {0};  // matriz maior, mas usaremos apenas 5x5 no canto superior

    // Cone: limpa, aplica e exibe padrão de cone
    limpaTabuleiro(mat, size, size);
    aplicaCone(mat, size);
    exibeHabilidade(mat, size, "Cone");

    // Cruz: limpa, aplica e exibe padrão de cruz
    limpaTabuleiro(mat, size, size);
    aplicaCruz(mat, size);
    exibeHabilidade(mat, size, "Cruz");

    // Octaedro: limpa, aplica e exibe padrão de octaedro
    limpaTabuleiro(mat, size, size);
    aplicaOctaedro(mat, size);
    exibeHabilidade(mat, size, "Octaedro");
}

int main() {
    // Início do programa: executa todos os níveis em sequência
    printf("🔥 Execução do nível Novato:\n");
    nivelNovato();

    printf("\n🔥 Execução do nível Aventureiro:\n");
    nivelAventureiro();

    printf("\n🔥 Execução do nível Mestre:\n");
    nivelMestre();

    return 0;  // fim da execução
}
