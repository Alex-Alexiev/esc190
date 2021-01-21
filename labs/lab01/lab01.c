#include <stdio.h>
#include <stdlib.h>

#define ARR_SIZE 5

void change_int(int* p_a, int val){
    *p_a = val;
}   

void print_arr(int *arr){
    for (int i = 0; i < ARR_SIZE; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void insertion_sort(int *arr){
    for (int i = 1; i < ARR_SIZE; i++){
        int temp = arr[i];
        int j = i; 
        while (j > 0 && arr[j-1] > temp){
            arr[j] = arr[j-1];
            j--;
        }
        arr[j] = temp;
    }
}

int main(){
    int a = 5;
    printf("Before: %d\n", a);
    change_int(&a, 10);
    printf("After: %d\n", a);
    
    int arr[ARR_SIZE] = {5, 1, 3, 2, 4};
    insertion_sort(arr);
    print_arr(arr);

    return 0;
}