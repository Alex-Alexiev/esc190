#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

#include "c_img.h"

#define MIN_PIX_VAL 0
#define MAX_PIX_VAL 255

#define MIN_SCALE 0
#define MAX_SCALE 2

int cutoff(double val){
    if (val < MIN_PIX_VAL){
        return MIN_PIX_VAL;
    }
    if (val > MAX_PIX_VAL){
        return MAX_PIX_VAL;
    }
    return val;
}

struct rgb_img *change_all_pixels(struct rgb_img *img, double a){
    struct rgb_img *ret;
    create_img(&ret, img->height, img->width); 
    for(int i = 0; i < img->width; i++){
        for(int j = 0; j < img->height; j++){
            int r = cutoff(a * get_pixel(img, j, i, 0));
            int g = cutoff(a * get_pixel(img, j, i, 1));
            int b = cutoff(a * get_pixel(img, j, i, 2));
            set_pixel(ret, j, i, r, g, b);            
        }
    }

    return ret;

}

double get_scale(int i, int n){
    return i*((MAX_SCALE - MIN_SCALE)/(double)n) + MIN_SCALE;
}

void make_n(struct rgb_img *img, int n){
    char *outfile = malloc(200);
    for (int i = 0; i < n; i++){
        struct rgb_img *img_1 = change_all_pixels(img, get_scale(i, n));
        sprintf(outfile, "%d.bin", i);
        write_img(img_1, outfile);
    }
    free(outfile);
}


int main(){
    struct rgb_img *img;
    read_in_img(&img, "image.bin");
    // struct rgb_img *img_1 = change_all_pixels(img, 10);
    // write_img(img_1, "0.bin");
    make_n(img, 5);
    return 0;
}