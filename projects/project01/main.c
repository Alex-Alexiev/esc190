#include <stdio.h>
#include <stdlib.h> 

#include "autocomplete.h"



int main(void)
{
    struct term *terms;
    int nterms;
    read_in_terms(&terms, &nterms, "wikitionary.txt");
    // lowest_match(terms, nterms, "Mex");
    // highest_match(terms, nterms, "Mex");
    
    struct term *answer;
    int n_answer;
    autocomplete(&answer, &n_answer, terms, nterms, "her");
    print_term_list(answer, n_answer);
    //free allocated blocks here -- not required for the project, but good practice
    return 0;
}



