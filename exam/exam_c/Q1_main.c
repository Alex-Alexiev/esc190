#include "Q1.h"
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
  char *strs[] = {"ESC", "MAT", "MSE", "CIV"};
  char *all = concat_all(strs, 4); 
  printf("%s\n", all); //ESCMATMSECIV
  free(all);
}
