#include <stdio.h>
 int main(void){
     int a = 11; //1011
     int b = 4; //  100 
     a & b; //0000
     a | b; //1111 //15
     /*
     integer is 4 bytes most of the time 
     storing integers 
     big-endian (1024 - byte1, 1025 - byte2, ...)
     little-endian (1024 - byte1, 1025 - byte3 ...)

     mostly arbitrary chioce - origin of name from gullivers travels 

     if sharing bin files across multiepl devices you can set your own standard and write and read accordingly 

    if you have a 16 bit number and want the first 8 bytes from the left 
    bytes[0] = (num & 0XFFFF) >> 8;
    bytes[1] = (num & 0XFF);

    01001001 11001010 -> num 
    00000000 11111111 -> 0XFF
     */



 }