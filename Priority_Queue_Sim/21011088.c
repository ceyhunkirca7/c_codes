#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void randomMatrix(int **matrix, int n, int m, int *queue_sizes, int total_elements) {
    int i, j;
    int k = n * m + 5;  // Üretilecek sayýlar (k > n*m)
    int *values = (int *)malloc(total_elements * sizeof(int));
    int count = 0;
    int count2 = 0;

    while (count < total_elements) {
        int value = rand() % k + 1;
        int duplicate = 0;
        int index;

        // önceden üretilen sayýlarla karþýlaþtýrma
        for (index = 0; index < count; index++) {
            if (values[index] == value) {
                duplicate = 1;
                break;
            }
        }

        if (!duplicate) {
            values[count] = value;
            count++;
        }
    }
     
     // matris doldurma
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            if (j < queue_sizes[i]) {
                matrix[i][j] = values[count2];
                count2++;
            }
        }
    }

    // Matrisi ekrana yazdýrma
    printf("Rastgele uretilen %d adet kuyruktan olusan matris:\n\n", n);
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            printf(" | ");
            printf("%d\t", matrix[i][j]);
        }
        printf("|\n");
    }

    free(values);
}

void heapifyRow(int *row, int length, int index) {
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < length && row[left] > row[largest]) {
        largest = left;
    }

    if (right < length && row[right] > row[largest]) {
        largest = right;
    }

    if (largest != index) {
        swap(&row[index], &row[largest]);
        heapifyRow(row, length, largest);
    }
}

void printMatrix(int **matrix, int n, int m) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            printf(" | ");
            printf("%d\t", matrix[i][j]);
        }
        printf("|\n");
    }
}

void heapify(int **matrix, int n, int m) {
    int i,j;
    for (i = 0; i < n; i++) {
        for (j = m / 2 - 1; j >= 0; j--) {
            heapifyRow(matrix[i], m, j);
        }
    }
    printMatrix(matrix,n,m);
}

void dequeue(int **matrix, int n, int m, int *queue_sizes, int *empty_queues, int *empty_count) {
    int i;
    int max = matrix[0][0];
    int maxRowIndex = 0;
    
    printf("Kuyruklardan degerleri okunan elemanlar:");
    for(i=0;i<n;i++) {
    	printf("%d,",matrix[i][0]);
	}
	printf("\n");

    // Matristeki maksimum deðeri bul
    for (i = 0; i < n; i++) {
        if (matrix[i][0] > max) {
            max = matrix[i][0];
            maxRowIndex = i;
        }
    }

    // En büyük elemaný çýkar
    int lastIndex = queue_sizes[maxRowIndex] - 1;
    matrix[maxRowIndex][0] = matrix[maxRowIndex][lastIndex];
    matrix[maxRowIndex][lastIndex] = -1;
    queue_sizes[maxRowIndex] -= 1;

    // Heapify iþlemi uygula
    heapifyRow(matrix[maxRowIndex], m, 0);
    printf("Matristen cikarilan en buyuk eleman: %d\n", max);
    printMatrix(matrix, n, m);

    // Elemanlarý tükenen kuyruðun numarasýný sakla
    if (queue_sizes[maxRowIndex] == 0) {
        empty_queues[*empty_count] = maxRowIndex + 1;
        (*empty_count)++;
    }
}

int main() {
    int N, M, i, j, count = 0;
    printf("Matris boyutlarini giriniz (N M): ");
    scanf("%d %d", &N, &M);

    int num_queues = N;
    int *queue_sizes = (int *)malloc(num_queues * sizeof(int));

    printf("Her bir kuyrugun kapasitesini giriniz:\n");
    for (i = 0; i < num_queues; i++) {
        printf("Kuyruk %d kapasitesi: ", i + 1);
        scanf("%d", &queue_sizes[i]);
        count += queue_sizes[i];
    }

    int **matrix = (int **)malloc(N * sizeof(int *));
    for (i = 0; i < N; i++) {
        matrix[i] = (int *)malloc(M * sizeof(int));
        for (j = 0; j < M; j++) {
            matrix[i][j] = -1;
        }
    }

    int *empty_queues = (int *)malloc(num_queues * sizeof(int));
    int empty_count = 0;

    // Rastgele matris oluþtur
    randomMatrix(matrix, N, M, queue_sizes, count);

    printf("\nMax-Heap ozelligi tasiyan %d adet kuyruktan olusan matris\n", N);
    heapify(matrix, N, M);

    // Kuyruklarý boþalt
    while (1) {
        dequeue(matrix, N, M, queue_sizes, empty_queues, &empty_count);

        // Tüm kuyruklar boþsa iþlemi sonlandýr
        int all_empty = 1;
        for (i = 0; i < N; i++) {
            if (queue_sizes[i] > 0) {
                all_empty = 0;
                break;
            }
        }
        if (all_empty) {
            printf("Tum kuyruklar bos!\n");
            break;
        }
    }

    // Elemanlarý tükenen kuyruklarýn sýrasýný yazdýr
    printf("Sirasiyla elemanlari tukenen kuyruklar: ");
    for (i = 0; i < empty_count; i++) {
        printf("%d", empty_queues[i]);
        if (i != empty_count - 1) {
            printf(",");
        }
    }
    printf("\n");

    // Bellekten serbest býrak
    for (i = 0; i < N; i++) {
        free(matrix[i]);
    }
    free(matrix);
    free(queue_sizes);
    free(empty_queues);

    return 0;
}




