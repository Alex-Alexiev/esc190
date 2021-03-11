#include<stdio.h>
#include<stdlib.h>

double get_pow(double a, int b);
int str_len(char *str);
int get_before_dec(char *str);

double my_atof(char *str){
    int bef = get_before_dec(str);
    int aft = str_len(str) - bef - 1;
    double res = 0;
    for (int i = 0; i < bef; i++){
        res += get_pow(10, bef-i-1)*(str[i]-'0');
    }
    for (int i = 0; i < aft; i++){
        res += get_pow(0.1, i+1) * (str[i+bef+1]-'0');
    }
    return res;
}

double get_pow(double a, int b){
    double ret = 1;
    for (int i = 0; i < b; i++){
        ret *= a;
    }
    return ret;
}

int str_len(char *str){
    int i = 0;
    char curr = str[0];
    while(curr != '\0'){
        curr = str[++i];
    }
    return i;
}

int get_before_dec(char *str){
    int i = 0;
    char curr = str[0];
    while(curr != '\0'){
        if (curr == '.'){
            return i;
        }
        curr = str[++i];
    }
    return i;
}

// int main(){
//     printf("%f", my_atof("23.000123"));
// }
