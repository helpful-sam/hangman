///////////////////////////
// VARIABLE DECLARATIONS //
///////////////////////////

// hangman banner
const char *hangman = " _    _          _   _  _____ __  __          _   _   _ \n| |  | |   /\\   | \\ | |/ ____|  \\/  |   /\\   | \\ | | | |\n| |__| |  /  \\  |  \\| | |  __| \\  / |  /  \\  |  \\| | | |\n|  __  | / /\\ \\ | . ` | | |_ | |\\/| | / /\\ \\ | . ` | | |\n| |  | |/ ____ \\| |\\  | |__| | |  | |/ ____ \\| |\\  | |_|\n|_|  |_/_/    \\_\\_| \\_|\\_____|_|  |_/_/    \\_\\_| \\_| (_)\n                                                        ";

// hangman drawing based on how many lives lost
// using macros because initiating an array of pointers is not a constant expression, which can't be initialized as a global variable
#define FRESH "________\n |/   |\n |\n |\n |\n |\n_|_\n"
#define FIRST "________\n |/   |\n |   (_)\n |\n |\n |\n_|_\n"
#define SECOND "________\n |/   |\n |   (_)\n |    |\n |    |\n |\n_|_\n"
#define THIRD "________\n |/   |\n |   (_)\n |   /|\n |    |\n |\n_|_\n"
#define FOURTH "________\n |/   |\n |   (_)\n |   /|\\\n |    |\n |\n_|_\n"
#define FIFTH "________\n |/   |\n |   (_)\n |   /|\\\n |    |\n |   /\n_|_\n"
#define SIXTH "________\n |/   |\n |   (_)\n |   /|\\\n |    |\n |   / \\\n_|_\n"

// dynamic variables
char *word; // holds the random word chosen at the beginning of the game
char guess[2]; // holds the 1 letter guess
char command[2]; // command placeholder for when user wins/loses the game
char difficulty_input[7]; // holds user's input when choosing difficulty
short int incorrect_count = 0; // tracks the number of incorrect guesses
short int match_flag; // used to track whether guess was a hit or a miss; 0 = miss, 1 = has at least one hit

int randomDictionary; // used in pickWord()
int wordLength; // used in prompt()
char *randomWord; // contains the random word
short int output_boolean[51]; // the boolean values for each guessing spot (handled as 0 or 1)
char output_display[51]; // the underscores that will be dynamically updated as the user guesses correctly

const char *stages[7] = {FRESH, FIRST, SECOND, THIRD, FOURTH, FIFTH, SIXTH};

typedef enum difficulty {
    EASY, // 3000_a1, 3000_a2
    NORMAL, //3000_b1, 3000_b2
    HARD //5000_b2, 5000_c1
} difficulty;


///////////////////////////
// FUNCTION DECLARATIONS //
///////////////////////////

void checkOS() {
    #if defined(_WIN32) || defined(_WIN64)
        printf("Sorry, this can't run on Windows...\n");
        exit(EXIT_FAILURE);
    #endif
}

void printHangman(int incorrect_count);
void clear();

difficulty pickDifficulty();
char * pickWord(difficulty current_difficulty);
void promptHandler(char *word);
void replay();