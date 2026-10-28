#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h> // Библиотека OpenMP

#define N 10000000 // Должно совпадать с generate_data.c
#define REPEAT 20  // Повторяем вычисления 20 раз, чтобы увидеть разницу во времени

int main() {
    // 1. Выделяем память под массив
    double *arr = (double *)malloc(N * sizeof(double));
    if (arr == NULL) {
        printf("Недостаточно памяти!\n");
        return 1;
    }

    // 2. Считываем массив из файла
    FILE *file = fopen("input.txt", "r");
    if (file == NULL) {
        printf("Файл input.txt не найден! Сначала запустите generate_data.\n");
        free(arr);
        return 1;
    }

    printf("Чтение файла...\n");
    for (int i = 0; i < N; i++) {
        fscanf(file, "%lf", &arr[i]); // %lf для чтения double
    }
    fclose(file);
    printf("Файл прочитан. Начинаем вычисления...\n\n");

    double mean, stddev, sum, sum_sq_diff;
    double start_time, end_time;

    // Открываем файл для записи результатов
    FILE *out_file = fopen("output.txt", "w");
    fprintf(out_file, "Результаты вычислений для %d элементов:\n", N);

    // Тестируем 1, 2 и 4 потока
    int threads_to_test[] = {1, 2, 4};

    for (int t = 0; t < 3; t++) {
        int num_threads = threads_to_test[t];
        omp_set_num_threads(num_threads); // Устанавливаем кол-во потоков

        start_time = omp_get_wtime(); // Засекаем время начала

        // Цикл для увеличения времени вычислений (чтобы разница была видна)
        for (int r = 0; r < REPEAT; r++) {
            sum = 0.0;
            // Параллельное вычисление суммы (редукция)
            #pragma omp parallel for reduction(+:sum)
            for (int i = 0; i < N; i++) {
                sum += arr[i];
            }
            mean = sum / N; // Среднее арифметическое

            sum_sq_diff = 0.0;
            // Параллельное вычисление суммы квадратов разностей
            #pragma omp parallel for reduction(+:sum_sq_diff)
            for (int i = 0; i < N; i++) {
                double diff = arr[i] - mean;
                sum_sq_diff += diff * diff;
            }
            stddev = sqrt(sum_sq_diff / N); // Среднеквадратическое отклонение
        }

        end_time = omp_get_wtime(); // Засекаем время конца
        double elapsed = end_time - start_time;

        printf("Потоков: %d | Время: %.4f сек | Среднее: %.4f | СКО: %.4f\n", 
               num_threads, elapsed, mean, stddev);
        
        // Записываем в файл
        fprintf(out_file, "Потоков: %d | Время: %.4f сек | Среднее: %.4f | СКО: %.4f\n", 
                num_threads, elapsed, mean, stddev);
    }

    fclose(out_file);
    free(arr); // Освобождаем память
    printf("\nРезультаты сохранены в output.txt\n");

    return 0;
}
