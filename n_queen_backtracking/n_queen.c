#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#define MAX_N 25  // max oyun size

int solutionCount = 0; // ��z�m say�s� sayac�

// tahtay� yazd�ran fonksiyon
void printBoard(int board[MAX_N][MAX_N], int N) {
    int i, j;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            printf("%c ", board[i][j] ? 'Q' : '-');  // tahtada vezirlerin yerini Q olarak belirledim. bo� yerler -
        }
        printf("\n");
    }
    printf("\n");
}

// brute force kontrol
bool isSafeBruteForce(int board[MAX_N][MAX_N], int N) {  // tahta �zerindeki vezirlerin birbirini al�p alamad���n� teyit etmek i�in. alam�yorlarsa true
    int row1, col1, row2, col2;
    for (row1 = 0; row1 < N; row1++) {  // ilk vezirin konumu i�in iki for loop
        for (col1 = 0; col1 < N; col1++) {
            if (board[row1][col1]) { // taranan indexte vezir varsa
                for (row2 = 0; row2 < N; row2++) { // ikinci vezirin konumu i�in iki for loop
                    for (col2 = 0; col2 < N; col2++) {
                        if ((row1 != row2 || col1 != col2) && board[row2][col2]) { // vezirler ayn� yerde de�ilse ve 2.vezir ilgili indexte varsa
                            if (col1 == col2 || row1 == row2 || abs(row1 - row2) == abs(col1 - col2)) { // ayn� sat�r veya s�tundalarsa, ya da �aprazlar�ndaysa tehdit var
                                return false; // birbirlerini alabiliyorlarsa false
                            }
                        }
                    }
                }
            }
        }
    }
    return true;
}
// brute force ��z�m
void bruteForce(int board[MAX_N][MAX_N], int placedQueens, int N, int row, int col) {  // placedqueens = �u ana kadar yerle�tirilen vezir say�s�
    int nextRow, nextCol;
    if (placedQueens == N) { // yerle�tirilen vezir say�s� N ise bunun bir ��z�m olup olmad���n� kontrol eder
        if (isSafeBruteForce(board, N)) { 
            printf("cozum %d:\n", ++solutionCount);
            printBoard(board, N);
        }
        return;
    }

    if (row >= N) return;  // tahtan�n s�n�r� a��ld�ysa bitir
    // sonraki indexe ge�i�
    nextRow = (col + 1 == N) ? row + 1 : row;  // e�er s�t�nun son eleman�ndaysak sonraki sat�r�n ilk eleman�na ge�i�
    nextCol = (col + 1) % N;

    board[row][col] = 1;  // veziri yerle�tir ve fonksiyonu tekrar �a��r
    bruteForce(board, placedQueens + 1, N, nextRow, nextCol);
    board[row][col] = 0;  // �imdiki indexteki veziri kald�r�r. farkl� yerle�im kombinasyonlar�n� denemek i�in 
    bruteForce(board, placedQueens, N, nextRow, nextCol); //  �u anki h�creye vezir yerle�tirmeden bir sonraki h�creyi kontrol etmek i�in
} 
 // brute force ��z�m�n� ba�lat�r
void solveBruteForce(int board[MAX_N][MAX_N], int row, int N) {
    bruteForce(board, 0, N, 0, 0);
}

// optimized1 kontrol
bool isSafeOptimized1(int board[MAX_N][MAX_N], int row, int col, int N) {
    int i, j;

    for (i = 0; i < row; i++) { // ayn� s�tunda vezir olup olmad���
        if (board[i][col]) return false;
    }

    for (i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) { // sol �st �aprazlarda vezir olup olmad���
        if (board[i][j]) return false;
    }

    for (i = row - 1, j = col + 1; i >= 0 && j < N; i--, j++) { // sa� �st �aprazlarda vezir olup olmad���
        if (board[i][j]) return false;
    }

    return true;  // vezirler birbirini alam�yorsa true
}
// optimized1 ��z�m
void solveOptimized1(int board[MAX_N][MAX_N], int row, int N) {
    int col;
    if (row >= N) { // t�m sat�rlar yerle�tirildi�inde ��z�m bulunmu�tur
        printf("cozum %d:\n", ++solutionCount);
        printBoard(board, N);
        return;
    }

    for (col = 0; col < N; col++) { 
        if (isSafeOptimized1(board, row, col, N)) {
            board[row][col] = 1;  // true d�nerse veziri yerle�tir
            solveOptimized1(board, row + 1, N); // sonraki rowa ge�ip yerle�tirmeye devam
            board[row][col] = 0;  // backtracking yap�larak veziri kald�r. alternatif ��z�mler i�in
        }
    }
}

// optimized2 ��z�m�
void solveOptimized2(int board[MAX_N][MAX_N], int row, int N, bool leftDiagonal[], bool rightDiagonal[], bool cols[]) {
	 // leftdiagonal sol �aprazlarda right diagonal sa� �aprazlarda cols s�tunlarda tehdit olup olmad���n� tutar
    int col;
    if (row >= N) {
        printf("cozum %d:\n", ++solutionCount);
        printBoard(board, N);
        return;
    }

    for (col = 0; col < N; col++) {
        if (!cols[col] && !leftDiagonal[row - col + N - 1] && !rightDiagonal[row + col]) { // hepsi true d�nerse tehdit yoktur d�ng�ye girer
            board[row][col] = 1; 
            cols[col] = leftDiagonal[row - col + N - 1] = rightDiagonal[row + col] = true; // veziri yerle�tirip bu pozisyonu tehdit olarak i�aretle

            solveOptimized2(board, row + 1, N, leftDiagonal, rightDiagonal, cols); // sonraki sat�ra ge�ip fonksiyonu tekrar �a��r

            board[row][col] = 0; // alternatif ��z�mler i�in veziri kald�r.
            cols[col] = leftDiagonal[row - col + N - 1] = rightDiagonal[row + col] = false; // kald�r�lan vezir b�lgesini tehdit b�lgesinden ��kar
        }
    }
}

// backtracking ��z�m
bool isSafeBacktracking(int board[MAX_N][MAX_N], int row, int col, int N) {
    int i, j;

    for (i = 0; i < row; i++) {  // �stte vezir var m� kontrol�
        if (board[i][col]) return false;
    }

    for (i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {  //  sol �st �apraz kontrol
        if (board[i][j]) return false;
    }

    for (i = row - 1, j = col + 1; i >= 0 && j < N; i--, j++) { // sa� �st �apraz kontrol
        if (board[i][j]) return false;
    }

    return true;
}

void solveBacktracking(int board[MAX_N][MAX_N], int row, int N) {
    int col;
    if (row >= N) {
        printf("cozum %d:\n", ++solutionCount);
        printBoard(board, N);
        return;
    }

    for (col = 0; col < N; col++) {
        if (isSafeBacktracking(board, row, col, N)) {  // tehdit yoksa d�ng�ye gir
            board[row][col] = 1;  // veziri yerle�tir
            solveBacktracking(board, row + 1, N); // sonraki sat�ra ge�ip fonksiyonu tekrar �a��r
            board[row][col] = 0; // veziri silip ba�ka olas�l�klar� da denemek. backtracking i�lemi
        }
    }
}

// �al��ma s�relerini �l�mek ve sonu�lar�n� yazd�rma
void runMode(char *modeName, void (*solver)(int[MAX_N][MAX_N], int, int), int N) { 
 // modename �al��t�r�lacak modun ad� . solver ��z�m modunu i�aret eden pointer �rn : solveBacktracking
    int board[MAX_N][MAX_N];
    clock_t start, end;
    int i, j;

    for (i = 0; i < MAX_N; i++) {  // tahtay� s�f�rlar
        for (j = 0; j < MAX_N; j++) {
            board[i][j] = 0;
        }
    }

    solutionCount = 0;
    start = clock();  // ba�lang�� zaman�

    printf("\n%s modu cozumleri:\n", modeName); 
    solver(board, 0, N); // ��z�m modunu �a��rmak

    end = clock(); // biti� zaman�
    double elapsedTime = (double)(end - start) / CLOCKS_PER_SEC; // saniye cinsinden hesap
    printf("%s modu calisma suresi: %.6f saniye\n", modeName, elapsedTime); 
    printf("toplam cozum sayisi: %d\n", solutionCount);
} 

int main() {
    int N, choice;
    printf("N degerini giriniz: ");
    scanf("%d", &N);

    if (N > MAX_N) {
        printf("Maksimum desteklenen N degeri %d.\n", MAX_N);
        return 1;
    }

    printf("\n--- Mod Secimleri ---\n");
    printf("1. BRUTE_FORCE\n");
    printf("2. OPTIMIZED_1\n");
    printf("3. OPTIMIZED_2\n");
    printf("4. BACKTRACKING\n");
    printf("5. TUM MODLARI CALISTIR\n");
    printf("Se�iminiz: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
        runMode("BRUTE_FORCE", solveBruteForce, N);
        break;
    case 2:
        runMode("OPTIMIZED_1", solveOptimized1, N);
        break;
    case 3: {
        bool leftDiagonal[MAX_N * 2] = {0}, rightDiagonal[MAX_N * 2] = {0}, cols[MAX_N] = {0};
        solutionCount = 0;
        clock_t start = clock();
        printf("\nOPTIMIZED_2 modu cozumleri:\n");
        solveOptimized2((int[MAX_N][MAX_N]){0}, 0, N, leftDiagonal, rightDiagonal, cols);
        clock_t end = clock();
        double elapsedTime = (double)(end - start) / CLOCKS_PER_SEC;
        printf("OPTIMIZED_2 modu calisma suresi: %.6f saniye\n", elapsedTime);
        printf("Toplam cozum sayisi: %d\n", solutionCount);
        break;
    }
    case 4:
        runMode("BACKTRACKING", solveBacktracking, N);
        break;
    case 5:
        printf("\n--- tum modlar calistiriliyor ---\n");
        runMode("BRUTE_FORCE", solveBruteForce, N);
        runMode("OPTIMIZED_1", solveOptimized1, N);
        {
            bool leftDiagonal[MAX_N * 2] = {0}, rightDiagonal[MAX_N * 2] = {0}, cols[MAX_N] = {0};
            solutionCount = 0;
            clock_t start = clock();
            printf("\nOPTIMIZED_2 modu cozumleri:\n");
            solveOptimized2((int[MAX_N][MAX_N]){0}, 0, N, leftDiagonal, rightDiagonal, cols);
            clock_t end = clock();
            double elapsedTime = (double)(end - start) / CLOCKS_PER_SEC;
            printf("OPTIMIZED_2 modu calisma suresi: %.6f saniye\n", elapsedTime);
            printf("Toplam cozum sayisi: %d\n", solutionCount);
        }
        runMode("BACKTRACKING", solveBacktracking, N);
        break;
    default:
        printf("Gecersiz secim.\n");
        break;
    }

    return 0;
}

