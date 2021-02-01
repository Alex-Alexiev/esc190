#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARR_SIZE 5

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

void change_int(int* p_a, int val){
    *p_a = val;
}   

int my_strcmp_rec(char *str1, char *str2){
    int diff = *str1 - *str2;
    if (*str1 == 0 || *str2 == 0){
        return diff;
    }
    if (diff == 0){
        return my_strcmp_rec(++str1, ++str2);
    }
    return diff;
}

int main(){
    printf("%d\n", my_strcmp_rec("alexi", "alex"));
    // int a = 5;
    // printf("Before: %d\n", a);
    // change_int(&a, 10);
    // printf("After: %d\n", a);
    
    // int arr[ARR_SIZE] = {5, 1, 3, 2, 4};
    // insertion_sort(arr);
    // print_arr(arr);

    return 0;
}