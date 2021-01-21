#include <stdio.h>
#include <stdlib.h>

//here a is just a pointer like doing int *b = a in main
void f(int a[]){
    a[0] = 3;
}

void print_arr(int *arr, int size){
    int i = 0; 
    for(i = 0; i < size; i++){
        printf("%d, ", arr[i]);
    }
}

//contents of struct get copied when passed to a function, basically everything does in c 
struct student_record { 
    int esc180_mark;
    int phy180_mark; 
    char letter1; 
    char letter2; //same size with letter1 and letter 1 and 2 since it pads a 4 byte space to store the letter1 
};

int main(){
    int a[3] = {3, 1, 2}; //here a is an array type 
    //sizeof(a) here gives 3*8 because it is array type, but in the function arr is a pointer so it will just give 8 
    //print_arr(a, 3);
  
    struct student_record student0 = {84, 23};
    printf("%d\n", student0.phy180_mark);

    struct student_record student1;
    student1.esc180_mark = 85;
    student1.phy180_mark = 82;

    printf("%ld\n", sizeof(struct student_record));
    return 0;
}