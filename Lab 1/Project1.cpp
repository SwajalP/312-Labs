// ECE 312 PA1
// <Your Name Here> Swajal Padhi    
// <Your EID Here> skp2628 
// Slip days used: 0
// Spring 2025
// Santacruz

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

/*
    Wring a function to sort the words in 'words[]' and then print them to the console.
*/
void printSortedWords(char words[]);
void cleanArray(char words[], char cleanedWords[][100], int *size);
void sortArray(char cleanedWords[][100], int size);
int strcomp(const char *c1, const char *c2);

int strcomp (const char * s1, const char * s2){
    for(; *s1 == *s2; ++s1, ++s2)
        if(*s1 == 0)
            return 0;
    return *(const unsigned char *)s1 - *(const unsigned char *)s2;
}

void printSortedWords(char words[]) {
    char cleanedWords[100][100];  //2d arr
    int size = 0;

    cleanArray(words, cleanedWords, &size);
    sortArray(cleanedWords, size);

    for (int i = 0; i < size; i++) {
        printf("%s\n", cleanedWords[i]); //perc s for string  
    }
}

void cleanArray(char words[], char cleanedWords[][100], int *size) {
    int wordLength = 0;
    int index = 0;
    char eachWord[100];  //string every word 
    char prevChar = ' ';

    for (int i = 0; words[i] != '\0'; i++) {
        bool isSpace = (words[i] == ' ' || words[i] == '\n' || words[i] == '\t');
        bool prevIsLetter = (prevChar != ' ' && prevChar != '\n' && prevChar != '\t');

        if (!isSpace) {
            eachWord[wordLength++] = words[i];  //get EACH char
        } 
        else if (isSpace && prevIsLetter && wordLength > 0) {
            eachWord[wordLength] = '\0';

            for (int j = 0; j <= wordLength; j++) 
                cleanedWords[index][j] = eachWord[j]; //paste in arr. we dont have strcpy so REDOO

            index++; wordLength = 0;
        }
        prevChar = words[i];
    }

    if (wordLength > 0) {  
        eachWord[wordLength] = '\0'; //null termmmintaror
        for (int j = 0; j <= wordLength; j++) {
            cleanedWords[index][j] = eachWord[j];
        } //index string into 2d row
        index++;
    }
    *size = index;
}

void sortArray(char cleanedWords[][100], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - 1 - i; j++) {
            if (strcomp(cleanedWords[j], cleanedWords[j + 1]) > 0) {
                char temp[100]; //try to find not triple iterqator if time?
                
                for (int k = 0; k < 100; k++) { //bubble sort pointer 
                    temp[k] = cleanedWords[j][k];
                    cleanedWords[j][k] = cleanedWords[j + 1][k];
                    cleanedWords[j + 1][k] = temp[k];
                }
            }
        }
    }
}
