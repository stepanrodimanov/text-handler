#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char** input_text(int* len){
    size_t size = 1, size_sym = 1;
    char** text = (char**)malloc(size * sizeof(char*));
    text[0] = (char*)malloc(sizeof(char));
    if (!text) { 
        fprintf(stderr, "Memory allocation error\n"); 
        return NULL; 
    }
    char symbol, last_symbol;
    size_t tmp_size2 = 0;    
    while ((symbol = (char)getchar()) != '\n' || last_symbol != '\n') {
        last_symbol = symbol;
        if (tmp_size2 == 0 && (symbol == ' ' || symbol == '\n'))
        {
            continue;
        }
        if (*len >= size) {
            size++;
            text = (char**)realloc(text, size * sizeof(char*));
            if (!text) { 
                fprintf(stderr, "Memory allocation error\n"); 
                return NULL; 
            }
            text[*len] = (char*)malloc(sizeof(char));
            if (!text[*len]) { 
                fprintf(stderr, "Memory allocation error\n"); 
                return NULL; 
            }
        }
        if (tmp_size2 >= size_sym)
        {
            size_sym++;
            text[*len] = (char*)realloc(text[*len], size_sym * sizeof(char));
            if (!text[*len]) { 
                fprintf(stderr, "Memory allocation error\n"); 
                return NULL; 
            }
        }
        text[*len][tmp_size2++] = symbol;      
        if (symbol == '.'){
            text[*len] = (char*)realloc(text[*len], ++size_sym * sizeof(char));
            text[*len][tmp_size2] = '\0';
            (*len)++;
            tmp_size2 = 0;
            size_sym = 1;
        }        
    }
    return text;
}

char* make_tolower(char* sentence){
    char* result_sentence = (char*)malloc((strlen(sentence) + 1) * sizeof(char)); 
    if (!result_sentence) { 
        fprintf(stderr, "Memory allocation error\n"); 
        return NULL; 
    }
    strcpy(result_sentence, sentence);
    for(int i = 0; sentence[i] != '\0'; i++){
        result_sentence[i] = tolower(sentence[i]);
    }
    result_sentence[strlen(sentence)] = '\0';
    return result_sentence;
}

char** delete_duplicate_sentences(char** text, int* len){
    for(int i = 0; i < *len; i++){
        for(int j = i + 1; j < *len; j++){
            if(strcmp(make_tolower(text[i]), make_tolower(text[j])) == 0){
                free(text[j]);
                for(int g = j; g < *len - 1; g++){
                    text[g] = text[g + 1];
                }
                text[*len - 1] = NULL;
                (*len)--;
                j--;
            }
        }
    }
    return text;
}

char** delete_sentences_with_the_same_start_and_end_characters(char** text, int* len){
    for(int i = 0; i < *len; i++){
        if (make_tolower(text[i])[0] == make_tolower(text[i])[strlen(text[i]) - 2])
        {
            free(text[i]);
            for(int g = i; g < *len - 1; g++){
                text[g] = text[g + 1];
            }
            text[*len - 1] = NULL;
            (*len)--;
            i--;
        }               
    }
    return text;
}

char** delete_numbers(char** text, int* len){
    char numbers[11] = "0123456789";
    for(int i = 0; i < *len; i++){
        char *result = strpbrk(text[i], numbers);
        if(result != NULL){         
            for (int j = result - text[i]; j <= strlen(text[i]) + 1; j++)
            {
                text[i][j] = text[i][j + 1];               
            }
        i--; 
        }
    }
    return text;
}

int is_palindrome(char* sentence){
    int end = strlen(sentence) - 2;
    for(int start = 0; start < end; start++){
        if (sentence[start] == ' ')
        {
            continue;
        }
        if (sentence[end] == ' ')
        {
            start--;
            end--;
            continue;
        }         
        if(sentence[start] != sentence[end]){
            return 0;
        }
        end--;
    }
    return 1;
}

void find_palidrome(char** text, int* len){
    for(int i = 0; i < *len; i++){
        if(is_palindrome(make_tolower(text[i]))){
            printf("Palidrome\n");
        }
        else{
            printf("Nothing interesting\n");
        }
    }
}

int length_of_the_third_word(const char* sentence){
    int i = 0;
    char* sentence_copy = (char*)malloc((strlen(sentence) + 1) * sizeof(char));
    if (!sentence_copy) { 
        fprintf(stderr, "Memory allocation error\n"); 
        return 1; 
    }
    strcpy(sentence_copy, sentence);
    char* words = strtok(sentence_copy, " ,.");
    while (i < 2 && words != NULL)
    {
        words = strtok(NULL, " ,.");           
        i++;
    }
    int result = 3;
    if(words != NULL){
        result = strlen(words);      
    }
    free(sentence_copy);
    return result;
}

int compare(const void* a, const void* b) {
    const char* str_a = *(const char**)a;
    const char* str_b = *(const char**)b;
    return length_of_the_third_word(str_a) - length_of_the_third_word(str_b);
}


void refernce(){  
    printf("0: The program performs primary text processing - removes duplicate sentences.\n");    
    printf("1: In each sentence, the program deletes the numbers found in it.\n");    
    printf("2: For each sentence, the program outputs 'Palindrome' if it is a palindrome, otherwise 'Nothing interesting.'\n");    
    printf("3: The program deletes all sentences with the same first and last character, case-insensitive.\n");    
    printf("4: The program sorts sentences by increasing the length of the third word, if there is no third word, then for such a sentence the length of the third word is 3.\n");    
    printf("5: Displays information about functions.\n"); 
}

void print_text(char** text, int* len){
    for(int i = 0; i < *len; i++){
        printf("%s\n", text[i]);
    } 
}

void free_text(char** text, int* len){
    for(int i = 0; i < *len; i++){
        free(text[i]);
    } 
    free(text);
}

void concatenation(char** text, int* len){
    for (int i = 0; i < *len; i++)
    {   
        for (int j = 0; j < *len; j++)
        {
            char* str1 = malloc((strlen(text[j]) + 1) * sizeof(char));
            strcpy(str1, text[j]);
            str1[strlen(text[j]) - 1] = '\0';  
            for (int g = j; g < *len; g++)
            {
                if (g + 1 >= *len)
                {
                    break;
                }
                char* str2 = malloc((strlen(text[g + 1]) + 1) * sizeof(char));
                strcpy(str2, text[g+1]);
                str2[strlen(text[g+1]) - 1] = '\0';
                if (strstr(text[i], str1) && strstr(text[i], str2) && strlen(text[i]) == strlen(str1) + strlen(str2) + 2) 
                {
                    printf("%s\n", text[i]);
                }
                free(str2);
            }   
            free(str1);      
        }                 
    }   
}

int main(){
    printf("Course work for option 4.14, created by Stepan Rodimanov.\n");
    int value = -1, len = 0;
    char **text;
    scanf("%d", &value);
    if((value >= 0 && value < 5) || value == 9){
        text = input_text(&len);
        text = delete_duplicate_sentences(text, &len);        
    }
    switch(value){
        case 0:
            break;  
        case 1:    
            text = delete_numbers(text, &len);      
            break;        
        case 2: 
            find_palidrome(text, &len);      
            break;    
        case 3:  
            text = delete_sentences_with_the_same_start_and_end_characters(text, &len);    
            break;    
        case 4:
            qsort(text, len, sizeof(text[0]), compare);        
            break;    
        case 5:   
            refernce();  
            return 0;
        case 9:
            concatenation(text, &len);
            free_text(text, &len);
            return 0; 
        default:    
            printf("Error: incorrect option\n");    
            return 0;    
    }
    if(value >= 0 && value < 5 && value != 2){
        print_text(text, &len);
        free_text(text, &len);
    }
    else if(value == 2){        
        free_text(text, &len);
    }
    return 0;
}
