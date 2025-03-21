/*laba 3
 * Lakotko Vlad
 * 10 variant
 * napisal 17.03.2025*/
#include "function.h"

int main() {
    SetConsoleOutputCP(CP_UTF8);
    int choice;

    while(1) {
        printf("\nМеню выбора заданий:\n");
        printf("1. Задание 1: Остаток от деления на 4\n");
        printf("2. Задание 2: Управление зоопарком\n");
        printf("0. Выход\n");
        printf("Выберите задание: ");
        scanf("%d", &choice);
        flush_input_buffer(); // Очистка буфера после ввода

        if(choice == 0) {
            return 0;
        } else if(choice == 1) {
            clear_screen();
            devisionByfour();
            printf("\n0 - вернуться на главную панель\n");
            int back;
            scanf("%d", &back);
            flush_input_buffer();
            if(back != 0) {
                printf("Неверный ввод!\n");
                system("pause");
            }
        } else if(choice == 2) {
            clear_screen();
            zooManager();
            printf("\n0 - вернуться на главную панель\n");
            int back;
            scanf("%d", &back);
            flush_input_buffer();
            if(back != 0) {
                printf("Неверный ввод!\n");
                system("pause");
            }
        } else {
            printf("Неверный выбор!\n");
            system("pause");
        }
    }
}

