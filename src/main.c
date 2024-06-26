#include <stdio.h>
#include <stdlib.h> 
#include <string.h> // for string functions
#include <time.h> // for time, used to srand
#include <ctype.h> // for toupper() function for case-insensitive char comparisons

#include "main.h"

// dictionary header files with normalized arrays of capitalized nouns (source: assets/Oxford Dictionary)
#include "oxford3000_a1_nouns.h"
#include "oxford3000_a2_nouns.h"
#include "oxford3000_b1_nouns.h"
#include "oxford3000_b2_nouns.h"
#include "oxford5000_b2_nouns.h"
#include "oxford5000_c1_nouns.h"


void printHangman(int incorrect_count) {
    printf("%s\n\n", stages[incorrect_count]);
}

void clear() {
    printf("\033c%s\n\n", hangman);
}

Difficulty pickDifficulty() {

    clear();
    printf("Please enter a difficulty (easy, normal, hard): ");
    
    while(1) { // infinite loop until user inputs a valid difficulty setting
        fgets(difficulty_input, 8, stdin); // read the first 6 chars (+ \0) and store to difficulty_input

        if (strcasecmp(difficulty_input, "easy\n") == 0) { // \n needed because fgets handles shorter inputs by ending with \n then \0
            return EASY;
        } else if (strcasecmp(difficulty_input, "normal\n") == 0) { // NOTE: having a buffer size limit of 7 and not having an \n here caused the 'e' bug... reason?
            return NORMAL;
        } else if (strcasecmp(difficulty_input, "hard\n") == 0) { // \n needed because fgets handles shorter inputs by ending with \n then \0
            return HARD;
        } else {
            clear();
            printf("Invalid input!\n\n");
            printf("Please enter a difficulty (easy, normal, hard): ");
            fflush(stdout);
        }
    }
}

char const* pickWord(Difficulty current_difficulty) {
    char const* randomWord;

    randomDictionary = rand() % 2; // pick first or second set of dictionaries since each difficulty has 2 choices

    // EASY
    if (current_difficulty == EASY && randomDictionary == 0) { // a_3000_1 (447 elements)
        randomWord = a_3000_1[rand() % 447];
        return randomWord;
    } else if (current_difficulty == EASY && randomDictionary == 1) { // a_3000_2 (462 elements)
        randomWord = a_3000_2[rand() % 462];
        return randomWord;
    }

    // NORMAL -- has an 'e' glitch, probably originated from here
    if (current_difficulty == NORMAL && randomDictionary == 0) { // b_3000_1 (387 elements)
        randomWord = b_3000_1[rand() % 387];
        return randomWord;
    } else if (current_difficulty == NORMAL && randomDictionary == 1) { // b_3000_2 (317 elements)
        randomWord = b_3000_2[rand() % 317];
        return randomWord;  
    }

    // HARD
    if (current_difficulty == HARD && randomDictionary == 0) { // b_5000_2 (389 elements)
        randomWord = b_5000_2[rand() % 389];
        return randomWord;
    } else if (current_difficulty == HARD && randomDictionary == 1) { // c_5000_1 (722 elements)
        randomWord = c_5000_1[rand() % 722];
        return randomWord; 
    }

    else {
        return "";
    }

}

void promptHandler(char const* word) {
    // get length of current word
    wordLength = strlen(word);

    // initialize booleans for each spot
    for (int i = 0; i < wordLength; i++) {
        output_boolean[i] = 0;
    }

    while(1) {
        // print display based on booleans
        clear();
        printHangman(incorrect_count);

        // print available letters
        printBank();

        printf("(%d letters)  ", wordLength);
        
        for (int i = 0; i < wordLength; i++) {
            if (output_boolean[i] == 0) {
                printf("_ ");
            } else if (output_boolean[i] == 1) {
                printf("%c ", word[i]);
            }
        }
        printf("  Guess a letter: ");
        fflush(stdout);

        // input to capture guess char, capped to only capture first char (+ null)
        char const guess = fgetc(stdin);

        // calculate letter index, to be used to check for duplicates and to update the display of the letter bank
        letterIndex = (int)toupper(guess) - 'A';

        // throw out everything above buffersize of 2 (NOTE: from ChatGPT)
        // side effect: when just pressing enter with an empty string, it goes into a new line instead of submitting input
        int charIndex;
        while ((charIndex = getchar()) != '\n' && charIndex != EOF);

        // check guess against all positions and update boolean
        match_flag = 0; // reset incorrect_flag
        for (int i = 0; i < wordLength; i++) {
            if (output_boolean[i] == 0 && toupper(guess) == word[i]) { // if the spot is unguessed and it's a match, it's a valid answer
                output_boolean[i] = 1;
                match_flag = 1;
            }
        }
        
        // check if the user made a duplicate guess
        if (letterBank[letterIndex] == ' ') {
            match_flag = 2;
        }

        // UPDATE BANK: replace guess to empty space in the letterBank
        letterBank[letterIndex] = ' ';

        // if no matches, the guess was incorrect
        if (match_flag == 0 && incorrect_count <= 6) {
            incorrect_count++; // increment
        }

        // check the user has guessed all words
        match_flag = 0; // reset incorrect_flag
        for (int i = 0; i < wordLength; i++) {
            if (output_boolean[i] == 1) { // 
                match_flag++;
            }
        }

        // check for win/lose conditions
        if (match_flag == wordLength) { // if all letters are a match, the user won!
            break;
        } else if (incorrect_count >= 6) { // if the user has 6 incorrect guesses, the user lost
            break;
        }

    } // end while
}

void resetBank() {
    for (char i = 0; i < 26; i++) {
        letterBank[i] = 'A' + i;
    }
}

void printBank() {
    printf("Available letters: ");
    for (char i = 0; i < 26; i++) {
        printf("%c", letterBank[i]);
        printf(" ");
    }
    printf("\n\n");

    fflush(stdout);
}

int main() {
    // initializations
    srand(time(0)); // seed RNG
    resetBank(); // refresh letter bank

    // ask user for difficulty
    Difficulty current_difficulty = pickDifficulty();
    
    while(1) {
        // generate word and print hangman
        clear();
        word = pickWord(current_difficulty);

        if (strcmp(word, "") != 0) { // protect against pickWord() returning an empty string due to error
            printHangman(incorrect_count);
        } else {
            return -1; // exit program with error
        }

        // prompt user for guess (this function also contains guess-checking logic)
        promptHandler(word);
        
        // print available letters
        printBank();

        // one last screen update to account for the fencepost problem
        clear();
        printHangman(incorrect_count);
        
        // print available letters
        printBank();

        printf("(%d letters)  ", wordLength);
        for (int i = 0; i < wordLength; i++) {
            if (output_boolean[i] == 0) {
                printf("_ ");
            } else if (output_boolean[i] == 1) {
                printf("%c ", word[i]);
            }
        }

        // input loop for restart y/n
        while(1) {

            // print win/lose message
            if (match_flag == wordLength) { // user won
            printf("\n\nYou won! Play again (y/n)? ");
            } else if (incorrect_count >= 6) { // user lost
                printf("\n\nYou lost... the word was %s. Play again (y/n)? ", word);
            }

            // ask for y/n
            fgets(command, 2, stdin);
            
            // throw out everything above buffersize of 2 (NOTE: from ChatGPT)
            // side effect: when just pressing enter with an empty string, it goes into a new line instead of submitting input
            int charIndex;
            while ((charIndex = getchar()) != '\n' && charIndex != EOF);

            if (toupper(command[0]) == 'Y') {
                incorrect_count = 0;
                resetBank();
                Difficulty current_difficulty = pickDifficulty();
                break;

            } else if (toupper(command[0]) == 'N') {
                return 0;

            } else {
                printf("Invalid input!");
                fflush(stdout);
                continue;
            }
        }
    }

    return 0; // exit program with no error
}
