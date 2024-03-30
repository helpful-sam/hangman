#ifndef HANGMAN_MAIN_H
#define HANGMAN_MAIN_H

///////////////////////////
// VARIABLE DECLARATIONS //
///////////////////////////

// hangman banner
char const* const hangman = " _    _          _   _  _____ __  __          _   _   _ \n| |  | |   /\\   | \\ | |/ ____|  \\/  |   /\\   | \\ | | | |\n| |__| |  /  \\  |  \\| | |  __| \\  / |  /  \\  |  \\| | | |\n|  __  | / /\\ \\ | . ` | | |_ | |\\/| | / /\\ \\ | . ` | | |\n| |  | |/ ____ \\| |\\  | |__| | |  | |/ ____ \\| |\\  | |_|\n|_|  |_/_/    \\_\\_| \\_|\\_____|_|  |_/_/    \\_\\_| \\_| (_)\n                                                        ";

char const* const FRESH = "________\n |/   |\n |\n |\n |\n |\n_|_\n";
char const* const FIRST = "________\n |/   |\n |   (_)\n |\n |\n |\n_|_\n";
char const* const SECOND = "________\n |/   |\n |   (_)\n |    |\n |    |\n |\n_|_\n";
char const* const THIRD = "________\n |/   |\n |   (_)\n |   /|\n |    |\n |\n_|_\n";
char const* const FOURTH =  "________\n |/   |\n |   (_)\n |   /|\\\n |    |\n |\n_|_\n";
char const* const FIFTH = "________\n |/   |\n |   (_)\n |   /|\\\n |    |\n |   /\n_|_\n";
char const* const SIXTH = "________\n |/   |\n |   (_)\n |   /|\\\n |    |\n |   / \\\n_|_\n";

char const* const stages[7] = {FRESH, FIRST, SECOND, THIRD, FOURTH, FIFTH, SIXTH};

// dynamic variables
char const* word; // holds the random word chosen at the beginning of the game
char command[2]; // command placeholder for when user wins/loses the game
char difficulty_input[8]; // holds user's input when choosing difficulty
short incorrect_count = 0; // tracks the number of incorrect guesses
short match_flag; // used to track whether guess was a hit or a miss; 0 = miss, 1 = has at least one hit

int randomDictionary; // used in pickWord()
int wordLength; // used in prompt()
short output_boolean[51]; // the boolean values for each guessing spot (handled as 0 or 1)
char output_display[51]; // the underscores that will be dynamically updated as the user guesses correctly

char letterBank[26]; // dynamically display which letters have been used and which are available
short letterIndex; // index of the char based on ASCII

typedef enum Difficulty {
    EASY, // 3000_a1, 3000_a2
    NORMAL, //3000_b1, 3000_b2
    HARD //5000_b2, 5000_c1
} Difficulty;


///////////////////////////
// FUNCTION DECLARATIONS //
///////////////////////////

void resetBank();
void printBank();

void printHangman(int incorrect_count);
void clear();

Difficulty pickDifficulty();
char const* pickWord(Difficulty current_difficulty);
void promptHandler(char const* word);
void replay();

#endif /* HANGMAN_MAIN_H */
