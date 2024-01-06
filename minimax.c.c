//MİN-MAX
#include <stdio.h>

#define SIZE 3

// Oyun tahtasini temsil eden struct
struct Board {
    char cells[SIZE][SIZE];
};

// Oyuncularıtemsil eden enum
enum Player {
    PLAYER_X,
    PLAYER_O
};

// Hamle yapılan konumu temsil eden struct
struct Move {
    int row, col;
};

// Fonksiyon prototipleri
void initializeBoard(struct Board* board);
void printBoard(const struct Board* board);
int isMovesLeft(const struct Board* board);
int evaluate(const struct Board* board);
int minimax(struct Board* board, int depth, int isMax);
struct Move findBestMove(struct Board* board);

// Oyun tahtasını baslangic durumuna getirme
void initializeBoard(struct Board* board) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            board->cells[i][j] = ' ';
        }
    }
}

// Oyun tahtasını ekrana yazdırma
void printBoard(const struct Board* board) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            printf("%c ", board->cells[i][j]);
        }
        printf("\n");
    }
}

// Oyunda yapılacak hamleleri kontrol etme
int isMovesLeft(const struct Board* board) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (board->cells[i][j] == ' ')
                return 1; // Hala boþ bir hücre var
        }
    }
    return 0; // Boþ hücre kalmadi
}

// Oyun durumunu degerlendirme
int evaluate(const struct Board* board) {
    // Satır kontrolü
    for (int i = 0; i < SIZE; ++i) {
        if (board->cells[i][0] == board->cells[i][1] && board->cells[i][1] == board->cells[i][2]) {
            if (board->cells[i][0] == 'X')
                return 1;
            else if (board->cells[i][0] == 'O')
                return -1;
        }
    }

    // Sütun kontrolü
    for (int i = 0; i < SIZE; ++i) {
        if (board->cells[0][i] == board->cells[1][i] && board->cells[1][i] == board->cells[2][i]) {
            if (board->cells[0][i] == 'X')
                return 1;
            else if (board->cells[0][i] == 'O')
                return -1;
        }
    }

    // Çapraz kontrol
    if (board->cells[0][0] == board->cells[1][1] && board->cells[1][1] == board->cells[2][2]) {
        if (board->cells[0][0] == 'X')
            return 1;
        else if (board->cells[0][0] == 'O')
            return -1;
    }

    if (board->cells[0][2] == board->cells[1][1] && board->cells[1][1] == board->cells[2][0]) {
        if (board->cells[0][2] == 'X')
            return 1;
        else if (board->cells[0][2] == 'O')
            return -1;
    }

    return 0; // Oyun devam ediyor
}

// Minimax algoritması
int minimax(struct Board* board, int depth, int isMax) {
    int score = evaluate(board);

    // Terminal durum kontrolü
    if (score == 1)
        return score;
    if (score == -1)
        return score;
    if (!isMovesLeft(board))
        return 0;

    // Maksimizer (X) için
    if (isMax) {
        int best = -1000;

        // Tüm boş hücreleri dene
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                if (board->cells[i][j] == ' ') {
                    board->cells[i][j] = 'X';
                    best = (best > minimax(board, depth + 1, !isMax)) ? best : minimax(board, depth + 1, !isMax);
                    board->cells[i][j] = ' '; // Geri alma
                }
            }
        }
        return best;
    }
    // Minimizer (O) için
    else {
        int best = 1000;

        // Tüm boş hücreleri dene
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                if (board->cells[i][j] == ' ') {
                    board->cells[i][j] = 'O';
                    best = (best < minimax(board, depth + 1, !isMax)) ? best : minimax(board, depth + 1, !isMax);
                    board->cells[i][j] = ' '; // Geri alma
                }
            }
        }
        return best;
    }
}

// En iyi hamleyi bulma
struct Move findBestMove(struct Board* board) {
    int bestVal = -1000;
    struct Move bestMove;
    bestMove.row = -1;
    bestMove.col = -1;

    // Tüm boş hücreleri dene ve minimax çagır
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (board->cells[i][j] == ' ') {
                board->cells[i][j] = 'X';
                int moveVal = minimax(board, 0, 0);
                board->cells[i][j] = ' '; // Geri alma

                // Eger bu hamle daha iyiyse güncelle
                if (moveVal > bestVal) {
                    bestMove.row = i;
                    bestMove.col = j;
                    bestVal = moveVal;
                }
            }
        }
    }

    return bestMove;
}

int main() {
    struct Board board;
    initializeBoard(&board);

    int gameOver = 0;
    int turn = PLAYER_X;

    while (!gameOver) {
        printBoard(&board);

        int row, col;

        if (turn == PLAYER_X) {
            printf("Sira X oyuncusunda\n");
            printf("Satir ve sutun numaralarini girin (0-2 arasi): ");
            scanf("%d %d", &row, &col);
        } else {
            struct Move bestMove = findBestMove(&board);
            row = bestMove.row;
            col = bestMove.col;
            printf("Bilgisayarin hamlesi: %d %d\n", row, col);
        }

        if (board.cells[row][col] == ' ') {
            if (turn == PLAYER_X)
                board.cells[row][col] = 'X';
            else
                board.cells[row][col] = 'O';

            int gameResult = evaluate(&board);

            if (gameResult == 1) {
                printBoard(&board);
                printf("X oyuncusu kazandi!\n");
                gameOver = 1;
            } else if (gameResult == -1) {
                printBoard(&board);
                printf("O oyuncusu kazandi!\n");
                gameOver = 1;
            } else if (!isMovesLeft(&board)) {
                printBoard(&board);
                printf("Berabere!\n");
                gameOver = 1;
            }

            turn = (turn == PLAYER_X) ? PLAYER_O : PLAYER_X;
        } else {
            printf("Bu hucre zaten dolu. Tekrar deneyin.\n");
        }
    }

    return 0;
}
