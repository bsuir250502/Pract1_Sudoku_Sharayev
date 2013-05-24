#include <stdio.h>
#include <stdlib.h>
#define  FIELD_SIZE 9

int **inputField(void);
int displayField(int **);
int freeMemory(int **);

int main()
{
    int **field;

    field = inputField();
    displayField(field);

    freeMemory(field);
    return 0;
}

int **inputField(void)
{
    int i, j, **field;
    FILE *fp;

    fp = fopen("input.in", "r");
    field = (int **) calloc(FIELD_SIZE, sizeof(int *));
    for (i = 0; i < FIELD_SIZE; i++) {
        if (!(field[i] = (int *) calloc(FIELD_SIZE, sizeof(int)))) {
            printf("Memory allocation error\n");
            exit(1);
        }
    }

    for (i = 0; i < FIELD_SIZE; i++) {
        for (j = 0; j < FIELD_SIZE; j++) {
            field[i][j] = getc(fp) - '0';
            if (field[i][j] < 0 || field[i][j] > FIELD_SIZE) {
                printf("Input error\n");
                exit(1);
            }
        }
        getc(fp);
    }

    fclose(fp);
    return field;
}

int displayField(int **field)
{
    int i, j;

    printf(" _________________________");
    printf("\n\n");
    for (i = 0; i < FIELD_SIZE; i++) {
        printf(" |");
        for (j = 0; j < FIELD_SIZE; j++) {
            printf("%2d", field[i][j]);
            if ((j + 1) % 3 == 0) {
                printf(" |");
            }
        }
        printf("\n");
        if ((i + 1) % 3 == 0) {
            printf(" _________________________");
            printf("\n\n");
        }
    }

    return 0;
}

int freeMemory(int **field)
{
    int i;

    for (i = 0; i < FIELD_SIZE; i++) {
        free(field[i]);
    }
    free(field);

    return 0;
}
