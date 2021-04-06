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
int get_smallest_index(double *best, int start_col, int row, int num, int width);
void recover_path(double *best, int height, int width, int **path);

/*i is height, j is width*/


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
    (*best_arr) = (double *)malloc(sizeof(double) * width * height);
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

    // print_double_arr(*best_arr, height, width);

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

void print_int_arr(int *arr, int height, int width){
    for(int i = 0; i < height; i++){
        printf("\n");
        for(int j = 0; j  < width; j++){
            printf("%d ", arr[get_index(i, j, width)]);
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

int get_smallest_index(double *best, int start_col, int row, int num, int width){
    int min_index = start_col;
    for (int i = start_col; i < start_col + num; i++){
        if (i < 0){
            i++;
        }
        if (i == width){
            break;
        }
        if (best[get_index(row, i, width)] < best[get_index(row, min_index, width)]){
            min_index = i;
        }
    }
    return min_index;
}

void recover_path(double *best, int height, int width, int **path){
    *path = malloc(sizeof(int) * height);
    // initial pass
    int min_ind = get_smallest_index(best, 0, height - 1, width, width);
    (*path)[height - 1] = min_ind;

    for(int j = height - 2; j > -1; j--){
        min_ind = get_smallest_index(best, min_ind - 1, j, 3, width);       
        (*path)[j] = min_ind;
    }
}

void remove_seam(struct rgb_img *src, struct rgb_img **dest, int *path){
    create_img(dest, src->height, src->width-1);
    for(int i = 0; i < src->height; i++){
        int skip = 0;
        for(int j = 0; j < src->width; j++){
            if(path[i] == j){
                skip++;
                continue;
            }
        uint8_t r = get_pixel(src, i, j, 0);
        uint8_t g = get_pixel(src, i, j, 1);
        uint8_t b = get_pixel(src, i, j, 2);    
        set_pixel(*dest, i, j-skip, r, g, b);
        }
    }
}

// int main(){
//     // struct rgb_img *im;
//     // read_in_img(&im, "HJ.bin");
//     // struct rgb_img *grad;
//     // double *best;
//     // struct rgb_img *dest;
//     // calc_energy(im, &grad);
//     // dynamic_seam(grad, &best);
//     // int *path;
//     // recover_path(best, 5, 6, &path);
//     // struct rgb_img *dest2;
//     // remove_seam(im, &dest2, path);
//     // print_int_arr(path, 1, 5);
//     // printf("\n");
//     // print_grad(im);
//     // printf("\n");
//     // print_grad(dest2);
//     struct rgb_img *im;
//     struct rgb_img *cur_im;
//     struct rgb_img *grad;
//     double *best;
//     int *path;

//     read_in_img(&im, "HJoceanSmall.bin");
    
//     for(int i = 0; i < 150; i++){
//         calc_energy(im,  &grad);
//         dynamic_seam(grad, &best);
//         recover_path(best, grad->height, grad->width, &path);
//         remove_seam(im, &cur_im, path);

//         destroy_image(im);
//         destroy_image(grad);
//         free(best);
//         free(path);
//         im = cur_im;
//     }
//     char filename[200];
//     sprintf(filename, "img5.bin");
//     write_img(cur_im, filename);

//     destroy_image(im);
// }

