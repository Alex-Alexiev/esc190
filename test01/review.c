#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define NODES 6

struct adjMat {
    int matrix[NODES][NODES];
    int vNodes[NODES];
};


void dfTraversal(struct adjMat *aM, int n){
    aM->vNodes[n] = 1; 
    int *connections = aM->matrix[n];
    printf("%d", n);
    for (int i = 0; i < NODES; i++){
        if (connections[i] == 1){
            if (aM->vNodes[i] != 1){
                dfTraversal(aM, i);
            }
        }
    } 

}

char *concat(const char *s1, const char *s2){
    char *s = (char *)malloc(strlen(s1) + strlen(s2) + 1);
    if (s == NULL) return NULL;
    strcpy(s, s1);
    strcat(s, s2);
    return s; 
}

#define MAX_LEN 80 

FILE *open_file(const char *promt, const char *mode){
    FILE *file;
    char name[MAX_LEN];
    printf("%S file name:, ", promt);
    scanf("%s", name);
    if ((file = fopen(name, mode)) == NULL){
        fprintf(stderr, "Unable to open %s\n", name);
        exit(EXIT_FAILURE);
    }
    return file; 
    //remember to close files with fclose(f), also always check if opening file causes error, 
}

void censor(FILE *in, FILE *out){
    char c;
    while(fscanf(in, "%c", &c) == 1){
        if (c <= '9' && c >= '0'){
            c = '#';
        }
        fprintf(out, "%c", c);
    }
}

/*
the pointer is passed by value, 
and an array is just the next values from  a
pointer, so you can change it

you would pass array bs reference if 
you want to make the array and store it 
in a specific place 
*/

void rot_encode(char *c, int R){
    if (*c <= 'z' && *c >= 'a'){
        *c = (*c + R - 'a')%26 + 'a';
    }
    //same for caps 
}

int file_rot_encoder(int argc, char *argv[]){
    FILE *in_file, *out_file; 
    char *out_filename; 
    int byte; 
    in_file = fopen(argv[1], "rb");
    out_filename = malloc(strlen(argv[1] + 5));
    strcpy(out_filename, argv[1]);
    strcat(out_filename, ".rot");
    out_file = fopen(out_filename, "wb");
    free(out_filename);

    while((byte = getc(in_file)) != EOF){
        char ch = (char) byte; 
        rot_encode(&ch, 13);
        fprintf(out_file, "%c", ch); //or putc(ch, out_file);
    }

    fclose(out_file);
    fclose(in_file);

    return 0;
}



void test(int *a){
    for (int i = 0; i < 3; i++){
        printf("%d\n", *(a++));
    }
}

void test2(int *a){
    for (int i = 0; i < 3; i++){
        *(a++) = 4;
    }
}

void test3(int a[4]){
    printf("%d\n", a);
}

//a is array of pointers not pointer to array - the pointer refers to the thing to its left 
void test4(int *a[]){
    printf("%d\n", a[0]);
}

int main(){

    // char a[] = "hello";
    // a[3] = '\0';
    // printf("%s\n", a+1);
    
    // char *a = malloc(100);
    // strcpy(a, "hello");
    // a[0] = 'i';
    // printf("%s\n", a);
    //basically if you assign a pointer to a string literal you can't change it because it isn't in accessible memory 

    // struct adjMat *a = (struct adjMat *)malloc(sizeof(struct adjMat));
    // a->matrix[0][1] = 1;
    // a->matrix[0][3] = 1;
    // a->matrix[1][4] = 1;
    // a->matrix[2][3] = 1;
    // a->matrix[3][5] = 1;
    // a->matrix[4][2] = 1;
    // a->matrix[4][5] = 1;

    //dfTraversal(a, 0);
    
}