#include <stdio.h>
#include <stdlib.h>
#define  FIELD_SIZE 9

int **inputField(void);
int displayField(int **);
int freeMemory(int **);
int solveField(int **, int, int);
int checkVertical(int **, int, int);
int checkHorisontal(int **, int, int);
int checkSquare(int **, int, int, int);

int main()
{
    int **field;

    field = inputField();
    displayField(field);

    freeMemory(field);
    return 0;
}

int solveField(int **field, int x, int y)
{
    int i, j, value = 0;

    while (value < FIELD_SIZE) {
        if (checkHorisontal(field, y, value)
            || checkVertical(field, x, value)
            || checkSquare(field, x, y, value)) {
            value++;
        }
    }

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
            if (field[i][j] != 0) {
                printf("%2d", field[i][j]);
            } else {
                printf("  ");
            }
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

int checkVertical(int **field, int x, int value)
{
    int i;

    for (i = 0; i < FIELD_SIZE; i++) {
        if (field[i][x] == value) {
            return 1;
        }
    }

    return 0;
}

int checkHorisontal(int **field, int y, int value)
{
    int i;

    for (i = 0; i < FIELD_SIZE; i++) {
        if (field[y][i] == value) {
            return 1;
        }
    }

    return 0;
}

int checkSquare(int **field, int x, int y, int value)
{
    int i, j, originX, originY;

    originY = y - y % 3;
    originX = x - x % 3;

    for (i = originY; i < 3; i++) {
        for (j = originX; j < 3; j++) {
            if (field[i][j] == value) {
                return 1;
            }
        }
    }

    return 0;
}
