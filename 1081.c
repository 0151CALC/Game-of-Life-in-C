/*
*   Test ID : 15701
*   Returned : Accepted
*   Name : Callum Clarke
*   ID : 201170688
*/

#include <stdio.h>
#include <stdlib.h>

#define aliveCell 'X' /* Program Constants */
#define deadCell '.'

void getStartingInput(); /* Program Functions*/
void allocateArrayMemory();
void getGridStartingPoint();
void equaliseArrays();
void printArray();
void start();
int aliveNeighbours(int row, int col);

char **oldGridArray; /*2D char array for storing the first version of the Grid at the start of the step. */
char **newGridArray; /*2D char array for storing the altered version of the grid at the end of the step. */

int numOfRows; /* Interger variables for holding the starting parameters. */
int numOfColumns;
int numOfSteps;


int main(void) {
    getStartingInput();
    allocateArrayMemory();
    getGridStartingPoint();
    equaliseArrays();
    start();
    printArray();
}

void getStartingInput() {

    scanf("%d %d %d", &numOfRows, &numOfColumns, &numOfSteps); /* Scan in the starting parameters. */

}

void allocateArrayMemory() { /* Function for allocating the memory for the 2D arrays. */

    oldGridArray = (char**)malloc(numOfRows*sizeof(char*));
    newGridArray = (char**)malloc(numOfRows*sizeof(char*));

    for (int i = 0; i < numOfRows; i++) {
        oldGridArray[i] = (char*)malloc(numOfColumns*sizeof(char));
        newGridArray[i] = (char*)malloc(numOfColumns*sizeof(char));
    }
}

void getGridStartingPoint() { /* Get the starting input for the array grid. */
    for (int i = 0; i < numOfRows; i++) { /* Runs once for each row of the grid */
        char line[numOfColumns]; /* A char array that can hold each of the chars for each column of the current row. */
        for (int j = 0; j < numOfColumns; j++) {
            scanf(" %c", &line[j]); /* Scan in each character and put them in the line array*/
        }
        for (int j = 0; j < numOfColumns; j++) { /* for each column  */
            oldGridArray[i][j] = line[j]; /* set the correct column space in the main grid array to the corresponding space in the line array */
        }
    }
}

void equaliseArrays() { /* Equalizes the two arrays. e.g. makes newGridArray the same as oldGridArray */

    for (int i = 0; i < numOfRows; i++) { /* For each row */
        for (int j = 0; j < numOfColumns; j++) { /* For each column*/
            newGridArray[i][j] = oldGridArray[i][j]; /* Set the row and column of i and j of newGridArray equal to the row and column of i and j of oldGridArray*/
        }
    }
}

void printArray() { /* Prints the grid held in oldGridArray to the console. */
    for (int i = 0; i < numOfRows; i++) { /* For each row */
        for (int j = 0; j < numOfColumns; j++) { /* For each column */
            printf("%c", oldGridArray[i][j]); /* Print the char held in oldGridArray at the position of [i][j]*/
        }
        printf("\n");
    }
}

void start() { /* Main Game Loop */
    for (int i = 0; i < numOfSteps; i++) { /* For the number of steps we need to perform */
        for (int j = 0; j < numOfRows; j++) { /* For each row*/
            for (int k = 0; k < numOfColumns; k++) { /* for each column*/
                int alive = aliveNeighbours(j,k); /* Returns the number of alive cells surrounding the current cell we are looking at ([i][j]) and stores it in an integer variable called alive. */
                if (oldGridArray[j][k] == aliveCell) { /* If the current cell we are looking at is alive then... */
                    if (alive < 2) { /* If the cell has less two alive neighbours then...*/
                        newGridArray[j][k] = deadCell; /* change the SAME cell in the NEWGRIDARRAY into a dead cell (The oldGridArray will stay the same.)*/
                    } else if (alive > 3) { /* Else if the current cell has more then 3 alive neighbours then... */
                        newGridArray[j][k] = deadCell; /* change the SAME cell in the NEWGRIDARRAY into a dead cell (The oldGridArray will stay the same.)*/
                    }
                } else if (oldGridArray[j][k] == deadCell) { /* Else if the current cell is dead then... */
                    if (alive == 3) { /* If the current cell has exact three alive neighbours then... */
                        newGridArray[j][k] = aliveCell; /* change the SAME cell in the NEWGRIDARRAY into an alive cell (The oldGridArray will stay the same.)*/
                    }
                }
            }
        }
        for (int j = 0; j < numOfRows; j++) { /* This essentially does the same as the equaliseArrays() function but switches the arrays around. e.g. makes oldGridArray equal to newGridArray */
            for (int k = 0; k < numOfColumns; k++) {
                oldGridArray[j][k] = newGridArray[j][k];
            }
        }
    }
}

int aliveNeighbours(int row, int col) { /* This function counts the number of alive cells surrrounding a cell in oldGridArray. */
    int alive = 0; /* An integer variable that will be used to hold the number of alive cells we have found. */

    for (int i = row - 1; i < row + 2; i++) { /* This will run exactly 3 times every time no matter the value of row. It will run once for row - 1 again for row and lastly for row + 1. */
        if ((!(i == -1)) && (!(i == numOfRows))) { /* Checking to make sure that i isn't -1 or equal to the number of rows (Catches array out of bounds errors). */
            for (int j = col - 1; j < col + 2; j ++) { /* This will run exactly 3 times every time no matter the value of col. It will run once for col - 1 again for col and lastly for col + 1*/
                if ((!(j == -1)) && (!(j == numOfColumns))) { /*Checking to make sure that j isn't -1 or equal to the number of columns. (catches array out of bounds errors). */
                    if (!((i == row) && (j == col))) { /* Checking to make sure that we don't count the cell in the middle. i.e the cell we are getting the alive neighbours of. */
                        if (oldGridArray[i][j] == aliveCell) { /* If the cell we are checking is alive */
                            alive++; /*increment alive. */
                        }
                    }
                }
            }
        }
    }
    return alive; /* Return the value of alive. */
}
