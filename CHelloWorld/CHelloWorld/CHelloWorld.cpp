/*
* The program randomly generates numbers
* between 1 and 1000 for the user to guess.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define MIN_NUMBER 1
const int MAX_NUMBER = 100;

void guessGame(void);
int isCorrect(int, int);


int main(void)
{
    srand(time(0));
    guessGame();

    return 0;
} // end main


void guessGame(void)
{
    int answer = 0;
    int guess = 0;
    int response = 0;

    do {
        answer = MIN_NUMBER + rand() % MAX_NUMBER;

        printf("Hello, I have a number between %d and %d .\n"
            "Can you guess my number?\n"
            "Please type your first guess.", MIN_NUMBER, MAX_NUMBER);

        printf("%s", "? ");
        scanf("%d", &guess);

        while (!isCorrect(guess, answer))
            scanf("%d", &guess);

        puts("\nExcellent! You guessed the number!\n"
            "Would you like to play again?");
        printf("%s", "Please type ( 1=yes, 2=no )? ");
        scanf("%d", &response);

        puts("");
    } while (response == 1);
}


int isCorrect(int g, int a)
{
    if (g == a) {
        return 1;
    }

    if (g < a)
        printf("%s", "Too low. Try again.\n? ");
    else
        printf("%s", "Too high. Try again.\n? ");

    return 0;
}
