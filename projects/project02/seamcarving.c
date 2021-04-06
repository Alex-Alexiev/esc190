#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

#include "seamcarving.h"
#include "c_img.h"

/*HELPERS*/
int wrap_num(int n, int max);
int get_index(int y, int x, int width);
void print_double_arr(double *arr, int height, int width);
double get_min(double *arr, int items);



void calc_energy(struct rgb_img *im, struct rgb_img **grad){
    create_img(grad, im->height, im->width);
    for (int i = 0; i < im->height; i++){
        for (int j = 0; j < im->width; j++){

            int sum = 0;

            for(int col = 0; col < 3; col++){
                int below = (int)get_pixel(im, wrap_num(i + 1, im->height), j, col);
                int above = (int)get_pixel(im, wrap_num(i - 1, im->height), j, col);
                sum += pow((above - below), 2);

                int right = (int)get_pixel(im, i, wrap_num(j + 1, im->width), col); 
                int left = (int)get_pixel(im, i, wrap_num(j - 1, im->width), col); 
                sum += pow((right - left), 2);
            }
            int root = sqrt((double)sum);
            uint8_t energy = (uint8_t)(root/10);
            set_pixel(*grad, i, j, energy, energy, energy);

        }
    }
    return;
}

void dynamic_seam(struct rgb_img *grad, double **best_arr){
    int width = grad->width;
    int height = grad->height;
    (*best_arr) = (double *)malloc(width*height);
    int j;
    for (j = 0; j < width; j++){
        (*best_arr)[get_index(0, j, width)] = get_pixel(grad, 0, j, 0);
    }
    
    for (int i = 1; i < grad->height; i++){
        for (j = 0; j < grad->width; j++){
            int left = (j == 0) ? 0: j-1;
            int right = (j == width - 1) ? j : j + 1;
            int middle = j; 
            double curr_energy = get_pixel(grad, i, j, 0);
            double options[3] = {curr_energy + (*best_arr)[get_index(i-1,left,width)], curr_energy + (*best_arr)[get_index(i-1,middle,width)], curr_energy + (*best_arr)[get_index(i-1,right,width)]};
            (*best_arr)[get_index(i, j, width)] = get_min(options, 3);
        }
    }

    print_double_arr(*best_arr, height, width);

}

double get_min(double *arr, int items){
    double min = DBL_MAX;
    for (int i = 0; i < items; i++){
        min = (arr[i] < min) ? arr[i] : min;
    }
    return min;
}

void print_double_arr(double *arr, int height, int width){
    for(int i = 0; i < height; i++){
        printf("\n");
        for(int j = 0; j  < width; j++){
            printf("%f ", arr[get_index(i, j, width)]);
        }
    }
}

int get_index(int y, int x, int width){
    return y*width + x;
}

int wrap_num(int n, int max){
    if (n + 1 > max){
        return n-max;
    }
    if (n < 0){
        return max + n;
    }
    return n;
}


int main(){
    struct rgb_img *im;
    read_in_img(&im, "6x5.bin");
    struct rgb_img *grad;
    double *best;
    printf("%s", "start");
    calc_energy(im, &grad);
    dynamic_seam(grad, &best);
    // print_grad(grad); 
}

