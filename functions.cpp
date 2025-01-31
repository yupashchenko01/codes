#define _CRT_SECURE_NO_WARNINGS
#include "functions.h"
#include <stdio.h>
#include <string.h>

typedef struct
{
    char name[50];
    char symptom[100];
    char procedures[100];
    char medication[100];
} disease_base;

typedef struct {
    char name[50];
    char interchange[50];
    int quantity;
} medication_base;

disease_base diseases[50];
medication_base medications[50];
int disease_count = 0;
int medication_count = 0;

void disease_add()
    {
        if (disease_count >= 50)
        {
            printf("\nБаза заповнена. Щоб додати нову хворобу, видаліть вже існуючу.\n\n");
            return;
        }

        getchar();
        printf("\nНазва хвороби: ");
        fgets(diseases[disease_count].name, sizeof(diseases[disease_count].name), stdin);
        strtok(diseases[disease_count].name, "\n");

        printf("Симптоми: ");
        fgets(diseases[disease_count].symptom, sizeof(diseases[disease_count].symptom), stdin);
        strtok(diseases[disease_count].symptom, "\n");

        printf("Процедури: ");
        fgets(diseases[disease_count].procedures, sizeof(diseases[disease_count].procedures), stdin);
        strtok(diseases[disease_count].procedures, "\n");

        printf("Рекомендовані медикаменти: ");
        fgets(diseases[disease_count].medication, sizeof(diseases[disease_count].medication), stdin);
        strtok(diseases[disease_count].medication, "\n");

        disease_count++;
        printf("\033[1;32mХворобу додано успішно.\033[1;37m\n");

        printf("\n");
    }

void medication_add() {
    if (medication_count >= 50) {
        printf("\nБаза заповнена. Щоб додати нові медикаменти, видаліть вже існуючі.\n\n");
        return;
    }

    getchar();
    printf("\nНазва медикаменту: ");
    fgets(medications[medication_count].name, sizeof(medications[medication_count].name), stdin);
    strtok(medications[medication_count].name, "\n");

    printf("Замінник: ");
    fgets(medications[medication_count].interchange, sizeof(medications[medication_count].interchange), stdin);
    strtok(medications[medication_count].interchange, "\n");

    printf("Кількість: ");
    while (scanf("%d", &medications[medication_count].quantity) != 1 || medications[medication_count].quantity < 0)
    {
        printf("Некоректне значення. Введіть додатнє число: ");
        while (getchar() != '\n'); // Очищення буфера
    }

    medication_count++;
    printf("\033[1;32mМедикамент додано успішно.\033[1;37m\n");

    printf("\n");
}

void diseases_display()
{
    if (disease_count == 0)
    {
        printf("\033[1;31mБаза порожня.\033[1;37m\n\n");
        return;
    }
    printf("\n");
    printf("+--------------------+----------------------------------------------+----------------------------------------------+------------------------------------+\n");
    printf("| \033[1;36m%-18s \033[1;37m| \033[1;36m%-44s \033[1;37m| \033[1;36m%-44s \033[1;37m| \033[1;36m%-34s\033[1;37m |\n", "Назва хвороби", "Симптоми", "Процедури", "Медикаменти");

    for (int i = 0; i < disease_count; i++)
    {
        printf("+--------------------+----------------------------------------------+----------------------------------------------+------------------------------------+\n");
        printf("| %-18s | %-44s | %-44s | %-34s |\n",
            diseases[i].name, diseases[i].symptom, diseases[i].procedures, diseases[i].medication);
    }
    printf("+--------------------+----------------------------------------------+----------------------------------------------+------------------------------------+\n");
    printf("\n");
}

void medications_display()
{
    if (medication_count == 0)
    {
        printf("\033[1;31mБаза порожня.\033[1;37m\n\n");
        return;
    }
    printf("\n");
    printf("+--------------------+--------------------+-----------+\n");
    printf("| \033[1;36m%-18s \033[1;37m| \033[1;36m%-18s \033[1;37m| \033[1;36m%-9s \033[1;37m|\n", "Назва медикаменту", "Замінник", "Кількість");

    for (int i = 0; i < medication_count; i++)
    {
        printf("+--------------------+--------------------+-----------+\n");
        printf("| %-18s | %-18s | %-9d |\n",
            medications[i].name, medications[i].interchange, medications[i].quantity);
    }
    printf("+--------------------+--------------------+-----------+\n");
    printf("\n");
}

void disease_delete() {
    char disease_name[50];
    getchar();
    printf("\nНазва хвороби, яку потрібно видалити: ");
    fgets(disease_name, sizeof(disease_name), stdin);
    strtok(disease_name, "\n");


    int found = 0;
    for (int i = 0; i < disease_count; i++)
    {
        if (strcmp(diseases[i].name, disease_name) == 0)
        {
            for (int j = i; j < disease_count - 1; j++)
            {
                diseases[j] = diseases[j + 1];
            }
            disease_count--;
            found = 1;
            printf("\033[1;32mХворобу видалено успішно.\033[1;37m\n\n");
            break;
        }
    }
    if (!found) {
        printf("\033[1;31mХворобу не знайдено.\033[1;37m\n");
    }
    printf("\n");
}

void medication_delete() {
    char medication_name[50];
    getchar();
    printf("\nНазва медикаменту, який потрібно видалити: ");
    fgets(medication_name, sizeof(medication_name), stdin);
    strtok(medication_name, "\n");

    int found = 0;
    for (int i = 0; i < medication_count; i++) {
        if (strcmp(medications[i].name, medication_name) == 0) {
            for (int j = i; j < medication_count - 1; j++) {
                medications[j] = medications[j + 1];
            }
            medication_count--;
            found = 1;
            printf("\033[1;32mМедикамент видалено успішно.\033[1;37m\n\n");
            break;
        }
    }
    if (!found) {
        printf("\033[1;31mМедикамент не знайдено.\033[1;37m\n\n");
    }
}

void disease_find()
{
    char search_name[50];
    getchar();
    printf("\nНазва хвороби: ");
    fgets(search_name, sizeof(search_name), stdin);
    strtok(search_name, "\n");

    int found = 0;
    for (int i = 0; i < disease_count; i++)
    {
        if (strstr(diseases[i].name, search_name))
        {
            printf("\n\033[1;32mЗнайдено хворобу:\033[1;37m\n\n");
            printf("Назва: %s\nСимптоми: %s\nПроцедури: %s\nМедикаменти: %s\n\n",
                diseases[i].name, diseases[i].symptom, diseases[i].procedures, diseases[i].medication);
            found = 1;
        }
    }
    if (!found)
    {
        printf("\033[1;31mХворобу не знайдено.\033[1;37m\n\n");
    }
}

void medications_find()
{
    char search_name[50];
    getchar();
    printf("\nНазва медикаменту: ");
    fgets(search_name, sizeof(search_name), stdin);
    strtok(search_name, "\n");

    int found = 0;
    for (int i = 0; i < medication_count; i++)
    {
        if (strstr(medications[i].name, search_name) || strstr(medications[i].interchange, search_name))
        {
            printf("\n\033[1;32mЗнайдено медикамент:\033[1;37m\n\n");
            printf("Назва: %s\nЗамінник: %s\nКількість: %d\n\n",
                medications[i].name, medications[i].interchange, medications[i].quantity);
            found = 1;
        }
    }

    if (!found)
    {
        printf("\033[1;31mМедикамент не знайдено.\033[1;37m\n\n");
    }
}

void adjust_quantity()
{
    char medication_name[50];
    getchar();
    printf("\nВведіть назву медикаменту для коригування запасів: ");
    fgets(medication_name, sizeof(medication_name), stdin);
    strtok(medication_name, "\n");

    int found = 0;
    for (int i = 0; i < medication_count; i++)
    {
        if (strcmp(medications[i].name, medication_name) == 0)
        {
            int new_quantity;
            printf("Поточна кількість: %d\n", medications[i].quantity);
            printf("Введіть нову кількість: ");
            while (scanf("%d", &new_quantity) != 1 || new_quantity < 0)
            {
                printf("\033[1;31mНекоректне значення. Введіть додатнє число:\033[1;37m ");
                while (getchar() != '\n');
            }
            medications[i].quantity = new_quantity;
            printf("\033[1;32mКількість медикаментів успішно змінена.\033[1;37m\n\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\033[1;31mМедикамент не знайдено.\n\n");
    }
}

void disease_sort()
{
    for (int i = 0; i < disease_count - 1; i++)
    {
        for (int j = i + 1; j < disease_count; j++)
        {
            if (strcmp(diseases[i].name, diseases[j].name) > 0)
            {
                disease_base temp = diseases[i];
                diseases[i] = diseases[j];
                diseases[j] = temp;
            }
        }
    }
    printf("\033[1;32mБаза хвороб відсортована за алфавітом.\033[1;37m\n\n");
}

void medications_sort()
{
    for (int i = 0; i < medication_count - 1; i++)
    {
        for (int j = i + 1; j < medication_count; j++)
        {
            if (strcmp(medications[i].name, medications[j].name) > 0)
            {
                medication_base temp = medications[i];
                medications[i] = medications[j];
                medications[j] = temp;
            }
        }
    }
    printf("\033[1;32mБаза медикаментів відсортована за алфавітом.\033[1;37m\n\n");
}

void diseases_read()
{
    FILE* file = fopen("diseases.txt", "rb");
    if (!file)
    {
        printf("\n\033[1;31mНе вдалося відкрити файл!\033[1;37m\n\n");
        return;
    }

    if (file)
    {
        fread(&disease_count, sizeof(int), 1, file);
        fread(diseases, sizeof(disease_base), disease_count, file);
        fclose(file);
    }

}

void medications_read()
{
    FILE* file = fopen("medications.txt", "rb");
    if (!file)
    {
        printf("\n\n\033[1;31mНе вдалося відкрити файл!\033[1;37m\n");
        return;
    }

    if (file)
    {
        fread(&medication_count, sizeof(int), 1, file);
        fread(medications, sizeof(medication_base), medication_count, file);
        fclose(file);
    }

}

void diseases_save()
{
    FILE* file = fopen("diseases.txt", "wb");
    if (file)
    {
        fwrite(&disease_count, sizeof(int), 1, file);
        fwrite(diseases, sizeof(disease_base), disease_count, file);
        fclose(file);
    }

}

void medications_save()
{
    FILE* file = fopen("medications.txt", "wb");
    if (file)
    {
        fwrite(&medication_count, sizeof(int), 1, file);
        fwrite(medications, sizeof(medication_base), medication_count, file);
        fclose(file);
    }
}
