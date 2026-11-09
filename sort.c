#include <stdio.h>

// Функция сортировки пузырьком (bubble sort)
void bubbleSort(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {           // внешний цикл
        for (j = 0; j < n - i - 1; j++) {   // внутренний цикл
            if (arr[j] > arr[j + 1]) {      // сравниваем соседние элементы
                // меняем местами
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Функция вывода массива
void printArray(int arr[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);  // вычисляем размер массива

    printf("Исходный массив: ");
    printArray(arr, n);

    bubbleSort(arr, n);  // вызываем сортировку

    printf("Отсортированный массив: ");
    printArray(arr, n);

    return 0;
}
