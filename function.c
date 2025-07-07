#include "function.h"

void clear_screen() {
    system("cls");
}

void devisionByfour() {
    Number number;
    unsigned int temp;
    printf("Введите число: ");
    scanf("%u", &temp);
    number.value = temp;
    unsigned int result = number.value - ((number.value >> 2) << 2);
    printf("Остаток от деления на 4: %u\n", result);
}

void zooManager() {
    Animal *zoo = NULL;
    int zoo_size = 0;
    int choice;
    const char *filename = "animals.txt";

    // .........................................................................Загрузка данных из файла
    if (load_animals_from_file(&zoo, &zoo_size, filename)) {
        printf("Данные о животных загружены из файла %s\n", filename);
    } else {
        printf("Файл %s не найден или пуст. Начинаем с нуля.\n", filename);
    }

    while(1) {
        printf("\nМеню управления зоопарком:\n");
        printf("1. Добавить животное\n");
        printf("2. Показать всех животных\n");
        printf("3. Найти животных по названию\n");
        printf("4. Удалить животных по количеству\n");
        printf("5. Сохранить и выйти на главную панель\n");
        printf("Выберите действие: ");
        scanf("%d", &choice);
        flush_input_buffer();

        switch(choice) {
            case 1: {
                Animal *temp = realloc(zoo, (zoo_size + 1) * sizeof(Animal));
                if(!temp) {
                    printf("Ошибка выделения памяти!\n");
                    exit(1);
                }
                zoo = temp;
                input_animal(&zoo[zoo_size]);
                char date_str[11];
                printf("Введите дату поступления (ДД.ММ.ГГГГ): ");
                scanf("%10s", date_str);
                flush_input_buffer();
                while(!validate_birth_date(date_str)) {
                    printf("Некорректная дата! Введите дату в формате ДД.ММ.ГГГГ: ");
                    scanf("%10s", date_str);
                    flush_input_buffer();
                }
                strcpy(zoo[zoo_size].arrival_date.date_str, date_str);
                printf("Введите среднюю продолжительность жизни: ");
                scanf("%f", &zoo[zoo_size].lifespan);
                flush_input_buffer();
                zoo_size++;
                break;
            }
            case 2: {
                for(int i = 0; i < zoo_size; i++) {
                    printf("\nЖивотное #%d:\n", i+1);
                    print_animal(&zoo[i]);
                    printf("Дата поступления: %s\n", zoo[i].arrival_date.date_str);
                    printf("Средняя продолжительность жизни: %.2f\n", zoo[i].lifespan);
                }
                break;
            }
            case 3: {
                char search_name[100];
                printf("Введите название для поиска: ");
                fgets(search_name, sizeof(search_name), stdin);
                search_name[strcspn(search_name, "\n")] = 0;
                Animal *found = find_animals(zoo, zoo_size, search_name);
                if(found) {
                    printf("Найдены животные:\n");
                    Animal *current = found;
                    while(current < zoo + zoo_size && strcmp(current->name, search_name) == 0) {
                        print_animal(current);
                        printf("Дата поступления: %s\n", current->arrival_date.date_str);
                        printf("Средняя продолжительность жизни: %.2f\n", current->lifespan);
                        current++;
                    }
                } else {
                    printf("Животные не найдены.\n");
                }
                break;
            }
            case 4: {
                char animal_name[100];
                printf("Введите название животного для удаления: ");
                fgets(animal_name, sizeof(animal_name), stdin);
                animal_name[strcspn(animal_name, "\n")] = 0;
                int quantity_to_remove;
                printf("Введите количество особей для удаления: ");
                if (scanf("%d", &quantity_to_remove) != 1 || quantity_to_remove <= 0) {
                    printf("Некорректный ввод количества особей!\n");
                    flush_input_buffer();
                    break;
                }
                flush_input_buffer();

                int new_size = remove_animals(&zoo, &zoo_size, animal_name, quantity_to_remove);


                zoo_size = new_size;
                zoo = realloc(zoo, zoo_size * sizeof(Animal));
                if (zoo_size > 0 && zoo == NULL) {
                    printf("Ошибка выделения памяти при перераспределении!\n");
                    exit(1);
                }
                printf("Удаление завершено.\n");

                break;
            }
            case 5: {
                if (save_animals_to_file(zoo, zoo_size, filename)) {
                    printf("Данные о животных сохранены");
                } else {
                    printf("Ошибка при сохранении данных в файл %s\n", filename);
                }
                for(int i = 0; i < zoo_size; i++) {
                    free(zoo[i].name);
                }
                free(zoo);
                return;
            }
            default:
                printf("Неверный выбор!\n");
        }
    }
}



// ..................................................................Ввод данных животного
void input_animal(Animal *a) {
    printf("Введите количество особей: ");
    while(scanf("%d", &a->quantity) != 1 || a->quantity <= 0) {
        printf("Некорректный ввод! Введите положительное число: ");
        flush_input_buffer();
    }
    flush_input_buffer();

    printf("Введите название: ");
    char buffer[100];
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    a->name = malloc(strlen(buffer) + 1);
    if (a->name == NULL) {
        perror("malloc failed");
        exit(1);
    }
    strcpy(a->name, buffer);
}

// ..........................................................................................Вывод данных животного
void print_animal(Animal *a) {
    printf("Название: %s\n", a->name);
    printf("Количество: %d\n", a->quantity);
}

// ...............................................................................................Поиск животных по названию
Animal* find_animals(Animal *arr, int size, const char *name) {
    for(int i = 0; i < size; i++) {
        if(strcmp(arr[i].name, name) == 0) {
            return &arr[i];
        }
    }
    return NULL;
}

// ...........................................................................................Удаление животных по количеству
int remove_animals(Animal **arr, int *size, const char *name, int quantity) {
    int initial_size = *size;
    int new_size = 0;
    Animal *new_arr = malloc(initial_size * sizeof(Animal));

    if (!new_arr) {
        perror("malloc failed");
        exit(1);
    }

    int found = 0;
    for (int i = 0; i < initial_size; i++) {
        if (strcmp((*arr)[i].name, name) == 0) {
            found = 1;

            if (quantity <= (*arr)[i].quantity) {
                (*arr)[i].quantity -= quantity;

                if ((*arr)[i].quantity > 0) {
                    new_arr[new_size++] = (*arr)[i];
                } else {
                    free((*arr)[i].name);
                }
            } else {
                printf("Указанное количество особей превышает доступное.\n");
                free(new_arr);
                return *size;
            }
        } else {
            new_arr[new_size++] = (*arr)[i];
        }
    }

    free(*arr);

    if (new_size > 0) {
        *arr = realloc(new_arr, new_size * sizeof(Animal));
        if (*arr == NULL) {
            perror("realloc failed");
            free(new_arr);
            exit(1);
        }
    } else {
        free(new_arr);
        *arr = NULL;
    }

    *size = new_size;

    if (!found) {
        printf("Такого питомца нету!\n");
    }

    return new_size;
}

//.............................чистка буфера
void flush_input_buffer() {
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

//.................................................................. Проверка даты рождения
int validate_birth_date(const char *date) {
    int day, month, year;
    if (sscanf(date, "%2d.%2d.%4d", &day, &month, &year) != 3) return 0;
    if (month < 1 || month > 12 || year < 1900 || year > 2025) return 0;
    if (day < 1 || day > 31) return 0;
    if (month == 2) {
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
            if (day > 29) return 0;
        } else {
            if (day > 28) return 0;
        }
    } else if (month == 4 || month == 6 || month == 9 || month == 11) {
        if (day > 30) return 0;
    }
    return 1;
}

// ................................................................................Загрузка данных о животных из файла
int load_animals_from_file(Animal **zoo, int *zoo_size, const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) return 0;

    int loaded_size = 0;
    Animal *loaded_zoo = NULL;
    char line[256];

    while (fgets(line, sizeof(line), fp)) {
        Animal animal;
        char name_buffer[100];

        if (sscanf(line, "%d %99[^;]; %10s; %f", &animal.quantity, name_buffer,
                   animal.arrival_date.date_str, &animal.lifespan) == 4) {
            animal.name = malloc(strlen(name_buffer) + 1);
            if (animal.name == NULL) {
                perror("malloc failed");
                fclose(fp);
                for (int i = 0; i < loaded_size; i++) {
                    free(loaded_zoo[i].name);
                }
                free(loaded_zoo);
                return 0;
            }
            strcpy(animal.name, name_buffer);

            Animal *temp = realloc(loaded_zoo, (loaded_size + 1) * sizeof(Animal));
            if (!temp) {
                perror("realloc failed");
                fclose(fp);
                for (int i = 0; i < loaded_size; i++) {
                    free(loaded_zoo[i].name);
                }
                free(loaded_zoo);
                return 0;
            }
            loaded_zoo = temp;
            loaded_zoo[loaded_size++] = animal;
        } else {
            printf("Ошибка при чтении строки: %s", line);
            for (int i = 0; i < loaded_size; i++) {
                free(loaded_zoo[i].name);
            }
            free(loaded_zoo);
            fclose(fp);
            return 0;
        }
    }

    fclose(fp);
    *zoo = loaded_zoo;
    *zoo_size = loaded_size;
    return 1;
}

//........................................................................Сохранение данных о животных в файл
int save_animals_to_file(Animal *zoo, int zoo_size, const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (!fp) return 0;

    for (int i = 0; i < zoo_size; i++) {
        fprintf(fp, "%d %s; %s; %.2f\n", zoo[i].quantity, zoo[i].name,
                zoo[i].arrival_date.date_str, zoo[i].lifespan);
    }

    fclose(fp);
    return 1;
}
