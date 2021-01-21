#include <stdio.h>
#include <stdlib.h>

void f(int a[]){
    a[0] = 5; //same as *a = 5
    //sizeof(a); 8 because it is a pointer 
}

void f2(int *a){
    a[0] = 5; //same as *a = 5
    a[1] = 6;
}

int main (int argc, char *argv[]) {
    int a[3] = {2, 3, 4};
    //a is just the address of the first value
    //a = &a
    //a = a + 1; gives error because is array type 
    //int *p_a; p_a = p_a +1; no issue because is pointer type 

    //*a <=> a[0]
    //*(a+n) <=> a[n]
    printf("%ld\n", *(a+1));
    
    //int *p_a = &a; can't do this 

    int *p_a = &a[0]; //same as *p_a = &a[0]; 
    //p_a is now a pointer that points to the address of a[0]
    //p_a + 1; refers to next address
    *(p_a + 1) = 10; //change hte second value in the array 
    printf("%ld   %ld\n", *(p_a+1), a+1);
    
    // int *np = NULL;
    // np = a;

    int an_int = 0;
    float a_float = 0;
    printf("A float takes up %ld bytes\n", sizeof(a_float));
    double a_double = 0;
    printf("A double takes up %ld bytes\n", sizeof(a_double));
    long int a_long = 0;
    char a_char = 'a';
    printf("A char takes up %ld bytes\n", sizeof(a_char));

    char a_1[3] = {'a', 'b', 'c'};
    printf("sizeof(a)/sizeof(a[0]) is array length = %ld\n", sizeof(a)/sizeof(a[0]));

    return EXIT_SUCCESS;
}