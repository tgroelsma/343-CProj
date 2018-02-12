/*
* Conway's Game of Life code
* CIS 343 Section 02
*
*@author Tressa Groelsma
*/
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    /*
    * Checked stack overflow as I forgot the command to convert
    * string to int.
    * https://stackoverflow.com/questions/7021725/how-to-convert-a-string-to-integer-in-c
    */
    /* The width of the board (command line sent) */
    int width = atoi(argv[1]);

    /* The height of the board (command line sent) */
    int height = atoi(argv[2]);

    /* The board itself */
    char** board;

    printf("Hello!\n");
    printf("You have submitted a %dx%d board.\n", width, height);

    /* Used for looping */
    int i,j;
    /*
    * Used this to double check malloc command
    * https://www.geeksforgeeks.org/dynamically-allocate-2d-array-c/
    * Mostly used notes from class.
    */
    board = malloc(height * sizeof(char *));
    for (i=0; i<height; i++)
    {
        board[i] = (int*)malloc(width * sizeof(char));
    }

    for (i=0; i<height; i++)
    {
        for (j=0; j<width; j++)
        {
            board[i][j] = 'O';
        }
    }

    printf("The empty board looks like this:\n\n");
    printBoard(board, height, width);
    printf("For this game, an O is an empty space, an X is a\n");
    printf("dead space, and an @ is a living space.\n\n");

    printf("What would you like to do?\n\n");
    printf("1: Run one iteration\t\t4: Load\n");
    printf("2: Run multiple iterations\t5: Quit\n");
    printf("3: Save\n\n");

    /* Keeps track of the user's input */
    char entry;
    entry = getchar();
    while (entry != '5')
    {
        /* For numbering the board */
        int n=0;

        /* For getting the number of iterations */
        char input[3];
        int iterNum;

        /* Filename for reading or writing file */
        char fname[100];

        fflush(stdin);
        switch(entry)
        {
        case '1':
            updateBoard(board, height, width);
            break;
        case '2':
            printf("How many iterations would you like to do?\n");
            scanf("%s",input);
            iterNum = atoi(input);
            printf("%d",iterNum);
            for (i=0; i<iterNum; i++)
            {
                updateBoard(board, height, width);
            }
            break;
        case '3':
            printf("Please say the name of the file you would like to save to:\n");
            scanf("%s",fname);
            write_file(fname, board, height*width);
            printf("File has been saved.\n");
            break;
        case '4':
            printf("Please say the name of the file you would like to load:\n");
            scanf("%s",fname);
            read_file(fname, board);
            printf("File has been loaded.\n");
            break;
        default:
            printf("Please enter a number 1-5.\n");
            break;
        }
    printf("\n");
    printBoard(board, height, width);
    printf("For this game, an O is an empty space, an X is a\n");
    printf("dead space, and an @ is a living space.\n\n");

    printf("What would you like to do?\n\n");
    printf("1: Run one iteration\t\t4: Load\n");
    printf("2: Run multiple iterations\t5: Quit\n");
    printf("3: Save\n\n");
    entry = getchar();
    }
    for (i=0; i<height; i++)
    {
        free(board[i]);
    }
    free(board);
    printf("Thanks for playing!\n");
    exit(1);

    return 0;
}

/*
* This prints the board.
*
* @param arr The array to be allocated.
* @param w The width of the board.
* @param h The height of the board.
*/
void printBoard( char** arr, int h, int w )
{
    /* Used for looping */
    int i, j;
    printf("\t");
    for (i=0; i < h-1; i++)
    {
        for (j=0; j<w-1; j++)
        {
            printf("%c|",arr[i][j]);
        }
        printf("%c",arr[i][w-1]);
        printf("\n\t");
        for (j=0; j<w-1; j++)
        {
            printf("-|");
        }
        printf("-\n\t");
    }
    for (j=0; j<w-1; j++)
    {
        printf("%c|",arr[h-1][j]);
    }
    printf("%c",arr[h-1][w-1]);
    printf("\n\n");
}

/*
* This checks the previous board and updates the
* new board's cells.
*
* @param prev The previous board
* @param cur The current board
* @param h The height of the board
* @param w The width of the board
*/
void updateBoard( char** cur, int h, int w)
{
    /* The previous iteration of the board */
    char** prev;

    /* Used for looping */
    int i, j;

    prev = cur;
    cur = malloc(h * sizeof(char *));
    for (i=0; i<h; i++)
    {
        cur[i] = (int*)malloc(w * sizeof(char));
    }

    for (i=0; i<h; i++)
    {
        for (j=0; j<w; j++)
        {
            cur[i][j] = prev[i][j];
        }
    }

    /* Used to keep track of neighbors */
    int count;

    for (i=0; i<h; i++)
    {
        for (j=0; j<w; j++)
        {
            if (i != 0 && j != 0) // this is not the top left corner
            {
                if (prev[i-1][j-1] == '@')
                    count++;
            }
            if (i != 0) // this is not the top row
            {
                if (prev[i-1][j] == '@')
                    count++;
            }
            if (i != 0 && j != w-1) // this is not the top right corner
            {
                if (prev[i-1][j+1] == '@')
                    count++;
            }
            if (j != 0) // this is not the leftmost row
            {
                if (prev[i][j-1] == '@')
                    count++;
            }
            if (j != w-1) // this is not the rightmost row
            {
                if (prev[i][j+1] == '@')
                    count++;
            }
            if (i != h-1 && j != 0) // this is not the bottom left corner
            {
                if (prev[i+1][j-1] == '@')
                    count++;
            }
            if (i != h-1) // this is not the bottom row
            {
                if (prev[i+1][j] == '@')
                    count++;
            }
            if (i != h-1 && j != w-1) // this is not the bottom right corner
            {
                if (prev[i+1][j+1] == '@')
                    count++;
            }

            if (prev[i][j] == '@')
            {
                if (count < 2)
                    cur[i][j] = 'X';
                else if (count > 3)
                    cur[i][j] = 'X';
                else
                    cur[i][j] = '@';
            }
            else
            {
                if (count == 3)
                    cur[i][j] = '@';
                else
                {
                    if (prev[i][j] == 'X')
                        cur[i][j] = 'X';
                    else
                        cur[i][j] = 'O';
                }
            }
            count = 0;
        }
    }
    for (i=0; i<h; i++)
    {
        free(prev[i]);
    }
    free(prev);
    printf("\n Here is the next board:\n");
    printBoard(cur, h, w);
    printf("Press enter to continue.\n");
    getchar();
}

int read_file( char* filename, char **buffer )
{
    /* File codes taken from previous C project*/

    /* File to read from */
    FILE *in;

    /* Lines to scan */
    char* input;

    /* Used for looping */
    int i,j;

    in=fopen(filename,"r");
    if(in==NULL)
    { //checks if file is valid
        printf("Cannot open file");
        exit(-1);
    }

    fscanf(in, "%s", input);

    /* Width of board */
    int w = strlen(input);

    /* Height of board */
    int h = 0;

    while(input != NULL)
    {
        h++;
        fscanf(in, "s", input);
    }

    buffer = malloc(h * sizeof(char *));
    for (i=0; i<h; i++)
    {
        buffer[i] = (int*)malloc(w * sizeof(char));
    }

    fclose(in);
    in=fopen(filename,"r");
    fscanf(in, "%s", input);
    for(i=0; i<h; i++)
    {
        for(j=0; j<w; j++)
        {
            buffer[i][j] = input[j];
        }
        fscanf(in, "%s", input);
    }

    return 0;
}

int write_file( char* filename, char *buffer, int size )
{
    /* File codes taken from previous C project*/

    /* File to write to */
    FILE *out;

    /* Used for looping */
    int i;

    /* Used to output a string to file */
    char output[size];

    out=fopen(filename,"w");
    if(out==NULL)
    { //checks if file is valid
        printf("Cannot open file");
        exit(-1);
    }


}
