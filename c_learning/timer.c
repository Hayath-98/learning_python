
#include <stdio.h>
#include <time.h>
#include <unistd.h>

void clearScreen() {
    // Clear the screen (for UNIX-like systems)
    printf("\e[1;1H\e[2J");
}

int main() {
    while (1) {
        time_t now;
        struct tm *local;

        // Get the current time
        time(&now);

        // Convert the current time to the local time
        //local = localtime(&now);

        // Clear the screen
       clearScreen();

        // Display the current time in HH:MM:SS format
        printf("%02d:%02d:%02d\n", local->tm_hour, local->tm_min, local->tm_sec);

        // Sleep for 1 second
        sleep(1);
    }

    return 0;
}
