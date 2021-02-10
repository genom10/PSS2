#include <iostream>

using namespace std;

FILE * inp;
FILE * outp;

bool caseInsensetiveComporator (char a, char b){
    a = (a >= 'A' && a <= 'Z') ? (a - 'A' + 'a') : a;
    b = (b >= 'A' && b <= 'Z') ? (b - 'A' + 'a') : b;
    return a == b;
}

bool checkForWord(char *text, char (&request)[100]) { //compares word at the beginning of the text and request
    for (int i = 0; request[i] != '\000'; i++){
        if (!caseInsensetiveComporator(text[i], request[i]))
            return false; //stop if found difference
    }
    return true; //no differences. words are matched
}

char toUpper(char a){
    return (a >= 'a' && a <= 'z') ? (a - 'a' + 'A') : a;
}

void printAllMatches(char (&text)[5001], char (&request)[100]) {
    int sentenceNumber = 1;
    int sentencePos[100];//positions of sentences' starts
    sentencePos[0] = 0;
    int matchesNumber = 0;
    int matchesPos[50];//positions of words matching 'request'
    int i;
    for (i = 0; text[i] != '\000'; i++){
        if(checkForWord(text, request))
            matchesPos[matchesNumber++] = i; //check first word

        if (text[i] == '.')
            sentencePos[sentenceNumber++] = i + 2; //record position of sentence's start

        if (text[i] == ' '){ //searching for matches after each space
            if(checkForWord(text+i+1, request)){
                matchesPos[matchesNumber++] = i+1; // record position of word matching 'request'
                //printf("%i ", i);
            }
        }
    }
    sentencePos[sentenceNumber] = i; // last sentence's end

    printf("%i\n", matchesNumber);
    fprintf(outp, "%i\n", matchesNumber);

    for (int i = 0, j = 0; i < sentenceNumber; i++) {//loop through sentences
        if (j >= matchesNumber) // no more matches
            return;
        if (sentencePos[i+1] > matchesPos[j] ) { // if there's a match in this sentence
            bool upper = false;
            for (int k = sentencePos[i]; text[k] != '.'; k++) {
                if (k == matchesPos[j]){ //this word matches
                    upper = true;
                    j++;
                }
                if (text[k] == ' '){ //end of [THE WORLD]
                    upper = false;
                }
                printf("%c", upper ? toUpper(text[k]) : text[k]);
                fprintf(outp, "%c", upper ? toUpper(text[k]) : text[k]);
            }
            printf(".\n");
            fprintf(outp, ".\n");
        }
    }
}

int main() {
    char text[5001];
    int n;
    char request[100];
    inp = fopen ("in.txt", "r+");
    outp = fopen ("out.txt", "w+");
    fscanf(inp, "%[^\n]\n", text); //sentences
    fscanf(inp, "%i\n", &n); //number of searches
    for (int i = 0; i < n; i++)
    {
        fscanf(inp, "%[^\n]\n", request); //request
        printAllMatches(text, request);
        //printf("\n");
    }
    return 0;
}