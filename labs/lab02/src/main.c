#include <stdio.h>
#include <stdlib.h>

#include "LinkedList.h"
#include "Util.h"

int main(){                                   
    int a = 3, b = 5, c = 5;
    
    node *list = llCreateNode(&a);
    llAppend(list, &b);
    llAppend(list, &c);

    llPrint(list, utIntStringer);                            
    llPrintRec(list, utIntStringer);

    llFree(list);

    return 0;
}