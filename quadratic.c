#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Решение квадратного уравнения ax^2 + bx + c = 0
void solve(double a, double b, double c, FILE *out) {
    // Проверка на вырождение (a ≈ 0)
    if (fabs(a) < 1e-9) {
        if (fabs(b) < 1e-9) {
            if (fabs(c) < 1e-9)
                fprintf(out, "   Бесконечно много решений\n");
            else
                fprintf(out, "   Нет решений\n");
        } else {
            fprintf(out, "   Линейное уравнение. x = %.4f\n", -c / b);
        }
        return;
    }

    double D = b * b - 4 * a * c;

    if (D > 1e-9) {
        double x1 = (-b + sqrt(D)) / (2 * a);
        double x2 = (-b - sqrt(D)) / (2 * a);
        fprintf(out, "   Дискриминант D = %.4f > 0\n", D);
        fprintf(out, "   x1 = %.4f\n", x1);
        fprintf(out, "   x2 = %.4f\n", x2);
    } else if (D < -1e-9) {
        double real = -b / (2 * a);
        double imag = sqrt(-D) / (2 * a);
        fprintf(out, "   Дискриминант D = %.4f < 0 (комплексные корни)\n", D);
        fprintf(out, "   x1 = %.4f + %.4fi\n", real, fabs(imag));
        fprintf(out, "   x2 = %.4f - %.4fi\n", real, fabs(imag));
    } else {
        double x = -b / (2 * a);
        fprintf(out, "   Дискриминант D = 0\n");
        fprintf(out, "   x = %.4f\n", x);
    }
}

int main(int argc, char *argv[]) {

    /* ===== Вариант (а): ввод/вывод в окне консоли ===== */
    if (argc == 1) {
        double a, b, c;
        printf("=== Квадратное уравнение (консольный режим) ===\n");
        printf("Введите коэффициенты a, b, c через пробел: ");
        if (scanf("%lf %lf %lf", &a, &b, &c) != 3) {
            printf("Ошибка ввода!\n");
            return 1;
        }
        printf("\nРешение:\n");
        solve(a, b, c, stdout);
    }
    /* ===== Вариант (б): чтение из файла, запись в файл ===== */
    else if (argc == 3) {
        FILE *in = fopen(argv[1], "r");
        if (!in) {
            printf("Не удалось открыть входной файл: %s\n", argv[1]);
            return 1;
        }
        FILE *out = fopen(argv[2], "w");
        if (!out) {
            printf("Не удалось открыть выходной файл: %s\n", argv[2]);
            fclose(in);
            return 1;
        }

        double a, b, c;
        int line = 1;
        while (fscanf(in, "%lf %lf %lf", &a, &b, &c) == 3) {
            fprintf(out, "--- Уравнение #%d: %gx^2 + %gx + %g = 0 ---\n",
                    line, a, b, c);
            solve(a, b, c, out);
            fprintf(out, "\n");
            line++;
        }

        fclose(in);
        fclose(out);
        printf("Обработано уравнений: %d\n", line - 1);
        printf("Результаты записаны в файл: %s\n", argv[2]);
    }
    else {
        printf("Использование:\n");
        printf("  %s              - вариант (а): консоль\n", argv[0]);
        printf("  %s input output - вариант (б): файлы\n", argv[0]);
    }

    return 0;
}
