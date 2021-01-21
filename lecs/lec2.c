#include <stdio.h>

void swap(int *p_a, int *p_b){
    int temp = *p_a;
    *p_a = *p_b;
    *p_b = temp;
}

int main(){
    int a = 10;
    int b = 12;
    swap(&a, &b);
    printf("a:%d, b:%d\n", a, b);
    return 0;
}
