#include <stdio.h>
#include <math.h>

#include "c_img.h"


int main(){
    struct rgb_img *img;
    read_in_img(&img, "pres.bin");
    printf("%d\n", get_pixel(img, 10, 10, 2));
}