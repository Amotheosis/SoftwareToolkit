// Подключаем необходимые библиотеки
#include <stdio.h>      // для работы с файлами и ввода-вывода
#include <stdlib.h>     // для функции exit()
#include <math.h>       // для функции sqrt() (квадратный корень)
#include <omp.h>        // для OpenMP (параллельные вычисления)
#include <time.h>       // для измерения времени

int main() {
    // === ЧТЕНИЕ ИЗ ФАЙЛА ===
    
    FILE *input_file = fopen("input.txt", "r");  // открываем файл для чтения
    if (input_file == NULL) {  // проверяем, открылся ли файл
        printf("Ошибка: не удалось открыть input.txt\n");
        return 1;  // ошибка
    }
    
    // Считываем количество чисел
    int n;
    fscanf(input_file, "%d", &n);  // читаем первое число — размер массива
    
    // Создаём массив
    double *numbers = (double *)malloc(n * sizeof(double));
    
    // Читаем числа из файла
    for (int i = 0; i < n; i++) {
        fscanf(input_file, "%lf", &numbers[i]);
    }
    
    fclose(input_file);  // закрываем файл
    
    // === ВЫЧИСЛЕНИЯ ===
    
    double sum = 0.0;           // сумма всех чисел
    double sum_sq = 0.0;        // сумма квадратов
    
    // Измеряем время начала
    double start_time = omp_get_wtime();
    
    // ПАРАЛЛЕЛЬНЫЙ ЦИКЛ (OpenMP)
    #pragma omp parallel for reduction(+:sum,sum_sq)
    for (int i = 0; i < n; i++) {
        sum += numbers[i];           // добавляем число к сумме
        sum_sq += numbers[i] * numbers[i];  // добавляем квадрат числа
    }
    
    // Измеряем время окончания
    double end_time = omp_get_wtime();
    
    // Вычисляем среднее арифметическое
    double mean = sum / n;
    
    // Вычисляем среднеквадратичное отклонение
    // Формула: sqrt( (sum(x^2)/n) - mean^2 )
    double variance = (sum_sq / n) - (mean * mean);
    double stddev = sqrt(variance);
    
    // === ЗАПИСЬ В ФАЙЛ ===
    
    FILE *output_file = fopen("output.txt", "w");  // открываем файл для записи
    if (output_file == NULL) {
        printf("Ошибка: не удалось создать output.txt\n");
        return 1;
    }
    
    // Записываем результаты
    fprintf(output_file, "Среднее арифметическое: %.4f\n", mean);
    fprintf(output_file, "Среднеквадратичное отклонение: %.4f\n", stddev);
    fprintf(output_file, "Время выполнения: %.6f секунд\n", end_time - start_time);
    
    fclose(output_file);  // закрываем файл
    
    // Выводим на экран
    printf("Результаты записаны в output.txt\n");
    printf("Среднее: %.4f\n", mean);
    printf("Отклонение: %.4f\n", stddev);
    printf("Время: %.6f секунд\n", end_time - start_time);
    
    // Освобождаем память
    free(numbers);
    
    return 0;
}
