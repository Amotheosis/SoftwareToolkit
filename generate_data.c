#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10000000 // 10 миллионов чисел

int main() {
    FILE *file = fopen("input.txt", "w"); // Открываем файл для записи
    if (file == NULL) {
        printf("Ошибка создания файла!\n");
        return 1;
    }

    srand(time(NULL)); // Инициализация генератора случайных чисел

    printf("Генерация 10 миллионов чисел, подождите...\n");
    for (int i = 0; i < N; i++) {
        // Генерируем случайное дробное число от 0 до 100 и пишем в файл
        fprintf(file, "%.2f\n", (float)rand() / RAND_MAX * 100.0);
    }

    fclose(file); // Закрываем файл
    printf("Файл input.txt успешно создан!\n");
    return 0;
}
