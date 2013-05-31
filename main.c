#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define  FIELD_SIZE 9

int **inputField(void);
int displayField(int **);
int freeMemory(int **);
int solveField(int **, int, int);
int checkVertical(int **, int, int);
int checkHorisontal(int **, int, int);
int checkSquare(int **, int, int, int);

int numberOfCalls = 0;

int main()
{
    int **field;
    clock_t t;

    t = clock();

    field = inputField();
    if (solveField(field, 0, 0)) {
        printf("Wrong condition\n");
    }
    else {
        printf("Sudoku is solved\n");
    }
    displayField(field);
    freeMemory(field);


    t = clock() - t;
    printf ("It took %f seconds.\n", ((float)t)/CLOCKS_PER_SEC);
    printf("Number of calls of solveField() = %d", numberOfCalls);
    return 0;
}

int solveField(int **field, int x, int y)
{
    int value = 0, nextX, nextY, last = 0;

    numberOfCalls++;

    if (x == FIELD_SIZE - 1) {
        if (y == FIELD_SIZE - 1) {
            last = 1;
        }
        nextX = 0;
        nextY=y+1;
    } else {
        nextX=x + 1;
        nextY = y;
    }

    if(field[y][x] != 0) {
        return solveField(field, nextX, nextY);
    }

    for (value = 1; value - 1 < FIELD_SIZE; value++) {
        if (checkHorisontal(field, y, value)
            && checkVertical(field, x, value)
            && checkSquare(field, x, y, value)) {

            field[y][x] = value;

            if(last) {
                return 0;
            }
            
            if (solveField(field, nextX, nextY)) {
                field[y][x] = 0;
            } else {
                return 0;
            }
        }
    }
    
    return 1;
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
            return 0;
        }
    }

    return 1;
}

int checkHorisontal(int **field, int y, int value)
{
    int i;

    for (i = 0; i < FIELD_SIZE; i++) {
        if (field[y][i] == value) {
            return 0;
        }
    }

    return 1;
}

int checkSquare(int **field, int x, int y, int value)
{
    int i, j, originX, originY;

    originY = y - y % 3;
    originX = x - x % 3;

    for (i = originY; i < originY + 3; i++) {
        for (j = originX; j <originX + 3; j++) {
            if (field[i][j] == value) {
                return 0;
            }
        }
    }

    return 1;
}
