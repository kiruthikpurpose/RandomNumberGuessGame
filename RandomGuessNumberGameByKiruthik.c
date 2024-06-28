#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_PLAYERS 1000

// Structure to hold player information
typedef struct {
    char name[50];
    int attempts;
} Player;

// Function to record player's score in a CSV file
void recordScore(const char *name, int attempts) {
    FILE *file = fopen("scoreboard.csv", "a"); // Open file in append mode

    if (file != NULL) {
        fprintf(file, "%s,%d\n", name, attempts); // Write name and attempts to file
        fclose(file);
    } else {
        printf("Error opening file.\n");
    }
}

// Function to display scoreboard
void displayScoreboard() {
    FILE *file = fopen("scoreboard.csv", "r"); // Open file in read mode

    if (file != NULL) {
        Player players[MAX_PLAYERS];
        int numPlayers = 0;

        // Read player data from file
        while (fscanf(file, "%[^,],%d\n", players[numPlayers].name, &players[numPlayers].attempts) != EOF) {
            numPlayers++;
        }
        fclose(file);

        if (numPlayers > 0) {
            // Sort players based on attempts (bubble sort)
            for (int i = 0; i < numPlayers - 1; i++) {
                for (int j = 0; j < numPlayers - i - 1; j++) {
                    if (players[j].attempts > players[j + 1].attempts) {
                        // Swap players
                        Player temp = players[j];
                        players[j] = players[j + 1];
                        players[j + 1] = temp;
                    }
                }
            }

            // Display scoreboard
            printf("\nScoreboard:\n\n");
            printf("Rank\tAttempts\tName\n");
            for (int i = 0; i < numPlayers; i++) {
                printf("%d\t%d\t\t%s\n", i + 1, players[i].attempts, players[i].name);
            }
        } else {
            printf("Scoreboard is empty.\n");
        }
    } else {
        printf("Scoreboard is empty.\n");
    }
}

// Function to clear the scoreboard
void clearScoreboard() {
    FILE *file = fopen("scoreboard.csv", "w"); // Open file in write mode to truncate it

    if (file != NULL) {
        fclose(file);
        printf("Scoreboard cleared.\n");
    } else {
        printf("Error clearing scoreboard.\n");
    }
}

int main() {
    int choice;
    char name[100];
    int number, guess, attempts;
    int c; // To store the newline character

    printf("\n\nWelcome To Random Guess Number Game Created By Kiruthik!\n\n");

    do {
        printf("\n1. Play the game\n");  // Menu
        printf("2. Scoreboard\n");
        printf("3. Exit\n\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        while ((c = getchar()) != '\n' && c != EOF);  // Clear the input buffer

        switch (choice) {
            case 1:
                printf("Enter your name: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0'; // Remove newline character if present

                attempts = 1;
                srand(time(0));
                number = rand() % 100 + 1;

                do {
                    printf("\nAttempt number %d\nEnter your guess: ", attempts);
                    scanf("%d", &guess);

                    if (number > guess) {
                        printf("Try HIGHER!\n");
                    } else if (number < guess) {
                        printf("Try LOWER!\n");
                    } else {
                        printf("\nCongratulations! You guessed the number in %d attempts!\n", attempts);
                        recordScore(name, attempts); // Record the score
                    }

                    attempts++;
                } while (number != guess);

                break;
            case 2:
                displayScoreboard();
                break;
            case 3:
                printf("\nThanks for playing my game! I hope you had a lot of fun playing it.\n\n");
                break;
            case 102938: // Special code to clear the scoreboard
                clearScoreboard();
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);

    return 0;
}
