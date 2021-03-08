#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "autocomplete.h"

#define TAB 9
#define SPACE 32

void print_term(struct term t){
    printf("weight:%f, value:%s\n", t.weight, t.term);
}

void print_term_list(struct term *terms, int nterms){
    for (int i = 0; i < nterms; i++){
        print_term(terms[i]);
    }
}

char *substring(char *dest, char *str, int start, int end){
    int len = end - start;
    for (int i = start; i < end; i++){
        *dest = str[i];
        dest++;
    }
    *dest = '\0';
    return dest - len;
}


void get_weight(int *weight, char *line){
    int i = 0;
    while(line[i] == SPACE){
        i++;
    }

    int j = i;
    while(line[j] != TAB){
        j++;
    }
    char *dest = (char *)malloc(sizeof(char)*200);
    *weight = atoi(substring(dest, line, i, j));
    free(dest);
}

void get_term_text(char **term_text, char *line){
    int i = 0;
    while(line[i++] != TAB);

    int j = i;
    while(line[j++] != '\0');

    if (line[j-2] == '\n'){
        *term_text = substring(*term_text, line, i, j-2);
    } else {
        *term_text = substring(*term_text, line, i, j-1);
    }
    
    
}

int compare_terms(const void *term1_v, const void *term2_v){
    int i = 0;
    struct term const *term1 = ((struct term *)term1_v);
    struct term const *term2 = ((struct term *)term2_v);
    while(term1->term[i] != '\0' && term2->term[i] != '\0' && term1->term[i] - term2->term[i] == 0){
        i++;
    }
    return term1->term[i] - term2->term[i];
}

int compare_term_string(const void *term_v, const void *substr_v){
    int i = 0;
    struct term const *tterm = (struct term *)term_v;
    char const *substr = (char *)substr_v;
    while(tterm->term[i] - substr[i] == 0){
        i++;
        if (tterm->term[i] == '\0' || substr[i] == '\0'){
            if (substr[i] == '\0'){
                return 0;
            }
            return -substr[i];
        }
    }
    return tterm->term[i] - substr[i];
}

int compare_term_weights(const void *term1_v, const void *term2_v){
    struct term const *term1 = ((struct term *)term1_v);
    struct term const *term2 = ((struct term *)term2_v);
    return term2->weight - term1->weight;
}


void read_in_terms(struct term **terms, int *pnterms, char *filename) {
    char line[200];
    FILE *fp;
    if ((fp = fopen(filename, "r")) == NULL){
        printf("Error");
        exit(1);
    }
    char n[100];
    fgets(n, sizeof(n), fp);
    int N = atoi(n);
    
    int weight;
    char *term_text =(char *)malloc(200);
    
    *terms = (struct term *)malloc(N*sizeof(struct term));    
    
    for(int i = 0; i < N; i++){
        fgets(line, sizeof(line), fp); 

        get_weight(&weight, line);
        get_term_text(&term_text, line);

        struct term new_term;
        new_term.weight = weight;
        strcpy(new_term.term, term_text);

        (*terms)[i] = new_term;
    }

    fclose(fp);

    qsort(*terms, N, sizeof(struct term), compare_terms);
    *pnterms = N;

}

int binary_search(char *substr, struct term *terms, int left, int right){
    if (right < left){
        return -1;
    }
    int mid = (left + right)/2;
    int comparison = compare_term_string(&terms[mid], substr);
    if (comparison == 0){
        return mid;
    }
    if (comparison < 0) {
        return binary_search(substr, terms, mid+1, right);
    }
    return binary_search(substr, terms, left, mid-1);
}


int lowest_match(struct term *terms, int nterms, char *substr){
    size_t index = binary_search(substr, terms, 0, nterms - 1);
    
    while(index > 0 && compare_term_string(&terms[index - 1], substr) == 0){
        index--;
    }
    return index;
}

int highest_match(struct term *terms, int nterms, char *substr){
    size_t index = binary_search(substr, terms, 0, nterms - 1);
    
    while(index < nterms && compare_term_string(&terms[index + 1], substr) == 0){
        index++;
    }
    return index;
}

void autocomplete(struct term **answer, int *n_answer, struct term *terms, int nterms, char *substr){
    int lowest = lowest_match(terms, nterms, substr);
    int highest = highest_match(terms, nterms, substr);
    *n_answer = highest - lowest + 1;
    if (lowest == -1 || highest == -1){
        *n_answer = 0;
    }
    *answer = (struct term *)malloc(sizeof(struct term)*(*n_answer));
    for(int i = 0; i < *n_answer; i++){
        (*answer)[i] = terms[i + lowest];
    }
    qsort(*answer, *n_answer, sizeof(struct term), compare_term_weights);
}