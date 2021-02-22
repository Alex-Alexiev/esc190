#include <stdio.h>
#include <stdlib.h>

int main(){
    const int a = 1;
    printf("%d\n", a);
    //a = a+2; //error cuz const 
    int *b = (int *)&a; //gives a warning 
    *b = 5;
    printf("%d\n", a);

    int d = 5;
    const int *p_d = &d; //cannot change *p_d but CAN change p_d 
    int *const p_d1 = &d; //cannot change p_d1, can change *p_d1
    const int *const p_d2; //cannot change both p_d2 and *p_d2
    


    return 0;
}