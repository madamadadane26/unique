#include <stdio.h>

#define MAX_STRING_LENGTH 1024
#define MAX_TOKENS 1024
#define MAX_WORD_LENGTH 64


// returns true if the given character is a letter.
int is_alpha(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

// vonverts the given character to lowercase. 
char to_lower(char c) {
    // If the given character is uppercase, convert it to lowercase. Otherwise, leave it unchanged. 
    return (c >= 'A' && c <= 'Z') ? (c - 'A' + 'a') : c;
}

// compares two strings case-insensitively.
int strcasecmp(const char *s1, const char *s2) {
    // Compare the two strings character-by-character until a difference is found, or until one of the strings ends. 
    for (; *s1 != '\0' && *s2 != '\0' && to_lower(*s1) == to_lower(*s2); s1++, s2++);
    // if both strings have ended, they are equal. Otherwise, the difference between the last two characters is returned. 
    return to_lower(*s1) - to_lower(*s2);
}

// returns true if the given word is already in the list of tokens. 
int is_token_duplicate(char tokens[][MAX_WORD_LENGTH], int token_count, const char *word) {
    for (int i = 0; i < token_count; i++) {
        if (strcasecmp(tokens[i], word) == 0) {
            return 1;
        }
    }
    return 0;
}

// adds the given word to the list of tokens if it is not already present. 
void add_unique_word(char tokens[][MAX_WORD_LENGTH], int *token_count, const char *word) {
    // if the given word is already in the list of tokens, do nothing. 
    if (is_token_duplicate(tokens, *token_count, word)) {
        return;
    }
   // if the list of tokens is full, print an error message and do nothing. 
    if (*token_count >= MAX_TOKENS) {
        fprintf(stderr, "Too many unique words\n");
        return;
    }
    // otherwise, add the word to the list of tokens.
    int i = *token_count;
    for (int j = 0; j < MAX_WORD_LENGTH && word[j] != '\0'; j++) {
        tokens[i][j] = to_lower(word[j]);
    }
    // makes sure the token is null-terminated.
    tokens[i][MAX_WORD_LENGTH - 1] = '\0';
    (*token_count)++;
}

int main() {
    char input_string[MAX_STRING_LENGTH];
    char tokens[MAX_TOKENS][MAX_WORD_LENGTH];
    int token_count = 0;
    
    while (fgets(input_string, MAX_STRING_LENGTH, stdin) != NULL) {
        int input_length = 0;
        for (int i = 0; input_string[i] != '\0'; i++) {
            // if the character is a letter and the word is not too long, add the lowercase letter to the current word.
            if (is_alpha(input_string[i])) {
                if (input_length < MAX_WORD_LENGTH - 1) {
                    input_string[input_length] = to_lower(input_string[i]);
                    input_length++;
                } else {
                    // if the word is too long, skip to the end of the word 
                    while (input_string[i] != '\0' && is_alpha(input_string[i])) {
                        i++;
                    }
                    input_length = 0;
                }
            } else if (input_length > 0) {
                //if the character is not a letter and a word has been found, add the word to the list of tokens
                input_string[input_length] = '\0';
                add_unique_word(tokens, &token_count, input_string);
                input_length = 0;
            }
        }
        // if there is a word at the end of the string, add it to the list of token
        if (input_length > 0) {
            input_string[input_length] = '\0';
            add_unique_word(tokens, &token_count, input_string);
            input_length = 0;
        }
    }
    
    //print out the list of unique words
    for (int i = 0; i < token_count; i++) {
        printf("%s ", tokens[i]);
    }
    printf("\n");
    
    return 0;
}
