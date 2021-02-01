#include <stdio.h>
#include <stdlib.h>

struct student_record{
    int esc180;
    int phy180; 
};

//has no effect 
void f(struct student_record s){
    s.esc180 = 100;
}

void f1(int *a){
    *a = 100;

}

void f2(struct student_record *ps){
    (*ps).esc180 = 100; //works to change the value in main 
    //dot takes precedence over the astrix, so you need to use brackets 
    ps->phy180 = 20;
    //(*a).b is equivalent to a->b   only when a is a pointer to a struct 
}

int *make_arr(int size_arr){
    return (int *)malloc(size_arr * sizeof(int));
}

// int *make_arr10_wrong(){
//     int a[10]; //this array is a local variable so when you leave the function the memory could get cleaned up and the array will no longer exist 
//     return a;
// }

// int *make_int_wrong(){
//     int *a; //this array is a local variable so when you leave the function the memory could get cleaned up and the array will no longer exist 
//     return a;
// }

int main(){

    struct student_record s = {94, 95};
    printf("%ld %ld %ld\n", &s, &s.esc180, &s.phy180); //stored consecutively 
    f(s); //the local s gets copied then the local s is changed so the main s isn't changed, so it isn't like an array in that sense 
    f1(&s.esc180); 
    f2(&s);
    printf("%d %d\n", s.esc180, s.phy180);

    // int a = 5;
    // float b = (float)a;

    printf("size of %ld\n", sizeof(int));

    int *a = (int *)malloc(10 *sizeof(int)); //stores on the heap so it isn't local 
    //malloc returns a variable of type void * so we cast it to type int *
    *(a+1) = 10;
    a[5] = 15;
    printf("%d\n", *(a+1));

    int dub_arr_size = 10;
    double *b = (double *)malloc(dub_arr_size * sizeof(double));
    a[1] = 8;
    printf("%ld\n", a[1]);
    //malloc lets us define an array of any size with a 

    int *c = make_arr(50);
    c[10] = 40;
    free(c); //frees the block that was allocated by make_arr so it is not reserved, but c still points to the spot in memory  
    //deallocated memory previously allocated by malloc 
    c[10] = 50; 
    printf("%ld\n", c[10]);

    int *ab = malloc(sizeof(int));
    *ab = 10;
    void *va = ab;
    printf("%d\n", *(int *)va);


    return 0;
}