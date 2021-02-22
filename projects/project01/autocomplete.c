#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "autocomplete.h"

#define TAB 9
#define SPACE 32

void print_term(struct term t){
    printf("weight:%f, value:%s", t.weight, t.term);
}

void print_term_list(struct term *terms, int nterms){
    for (int i = 0; i < nterms; i++){
        print_term(terms[i]);
    }
}

char *substring(char *str, int start, int end){
    int len = end - start;
    char *ret = (char *)malloc(len);
    for (int i = start; i < end; i++){
        *ret = str[i];
        ret++;
    }

    *ret = '\0';
    return ret - len;
}


int get_weight(char *line){
    int i = 0;
    while(line[i] == SPACE){
        i++;
    }

    int j = i;
    while(line[j] != TAB){
        j++;
    }

    return atoi(substring(line, i, j));
}

char *get_term_text(char *line){
    int i = 0;
    while(line[i++] != TAB);

    int j = i;
    while(line[j++] != '\0');
    
    return substring(line, i, j);
}

int compare_terms(const void *term1_v, const void *term2_v){
    int i = 0;
    struct term const term1 = *((struct term *)term1_v);
    struct term const term2 = *((struct term *)term2_v);
    while(term1.term[i] != '\0' && term2.term[i] != '\0' && term1.term[i] - term2.term[i] == 0){
        i++;
    }
    return term1.term[i] - term2.term[i];
}

int compare_term_string(const void *term_v, const void *str_v){
    int i = 0;
    struct term const term = *((struct term *)term_v);
    char const *str = (char *)str_v;
    while(term.term[i] - str[i] == 0){
        i++;
        if (term.term[i] == '\0' || str[i] == '\0'){
            return 0;
        }
    }
    return term.term[i] - str[i];
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
    N = 15;
    int weight;
    char *term_text =(char *)malloc(200);

    *terms = (struct term *)malloc(N*sizeof(struct term));    
    
    for(int i = 0; i < N; i++){
        fgets(line, sizeof(line), fp); 

        weight = get_weight(line);
        term_text = get_term_text(line);
    
        struct term new_term;
        new_term.weight = weight;
        strcpy(new_term.term, term_text);

        (*terms)[i] = new_term;
    }
    qsort(*terms, N, sizeof(struct term), compare_terms);
    *pnterms = N;

}

int binary_search(char *key, struct term *terms, int left, int right){
    if (right < left) {
        return -1;
    }
    int mid = (left + right)/2;
    int comparison = compare_term_string(&terms[mid], key);
    if (comparison == 0) {
        return mid;
    }
    if (comparison < 0){
        return binary_search(key, terms, mid, right);
    }
    return binary_search(key, terms, left, mid);
}


int lowest_match(struct term *terms, int nterms, char *substr){
    int index = binary_search(substr, terms, 0, nterms-1);
    //struct term *term = (struct term *)bsearch(substr, terms, nterms, sizeof(struct term), compare_term_string);
    while (compare_term_string(&terms[index-1], substr) == 0){
        index--;
    }
    return index;
}

int highest_match(struct term *terms, int nterms, char *substr){
    int index = binary_search(substr, terms, 0, nterms-1);
    //struct term *term = (struct term *)bsearch(substr, terms, nterms, sizeof(struct term), compare_term_string);
    while (compare_term_string(&terms[index+1], substr) == 0){
        index++;
    }
    return index;
}
