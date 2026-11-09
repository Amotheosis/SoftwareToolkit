#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int n = 10000000;  // 10 миллионов чисел
    FILE *f = fopen("input.txt", "w");
    fprintf(f, "%d\n", n);
    
    srand(time(NULL));
    int i;
    for (i = 0; i < n; i++) {
        fprintf(f, "%.6f\n", (double)rand() / RAND_MAX * 100.0);
    }
    fclose(f);
    printf("Файл input.txt создан с %d числами\n", n);
    return 0;
}
