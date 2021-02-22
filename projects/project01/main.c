#include <stdio.h>
#include <stdlib.h> 

#include "autocomplete.h"


int main(void){

    struct term *terms;
    int nterms;
    read_in_terms(&terms, &nterms, "cities.txt");
    print_term_list(terms, nterms);
    lowest_match(terms, nterms, "Sha");
    highest_match(terms, nterms, "Sha");
    //highest_match(terms, nterms, "Tor");
    
    struct term *answer;
    int n_answer;
    //autocomplete(&answer, &n_answer, terms, int nterms, "Tor");
    //free allocated blocks here -- not required for the project, but good practice
    return 0;
}
