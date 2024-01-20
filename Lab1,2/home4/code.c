#include <stdio.h>
#include <string.h>

char *characters[] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M","N", "O", "P", "Q", "R", "S", "T", "U",
                      "V", "W", "X", "Y", "Z", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0"};

char *morsecode[] = {".-","-...","-.-.","-..",".","..-.","--.","....","..",".---", "-.-",".-..","--","-.","---",".--.","--.-",
                     ".-.","...","-","..-", "...-",".--","-..-","-.--","--..", ".----","..---","...--","....-", ".....", "-....",
                     "--...","---..","----.","-----"};

#define __NAME__ "msg.txt"

void decodeMorse(char *morseCode) {
    char *token = strtok(morseCode, " ");
    while (token != NULL) {
        if (strcmp(token, "/") == 0) {
            printf(" ");
        } else {
            for (int i = 0; i < sizeof(morsecode) / sizeof(morsecode[0]); i++) {
                if (strcmp(token, morsecode[i]) == 0) {
                    printf("%s", characters[i]);
                    break;
                }
            }
        }
        token = strtok(NULL, " ");
    }
}

int main() {
    char line[1024];
    FILE *fptr;

    fptr = fopen(__NAME__, "r");
    if (fptr == NULL) {
        printf("Error opening file");
    } else {
        while(fgets(line, 1024, fptr)) {
            decodeMorse(line);
        }

        fclose(fptr);
        return 0;
    }
}
