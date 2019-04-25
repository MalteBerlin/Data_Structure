#include <stdio.h>
#include <stdlib.h>
#include "Predefined_const.h"
#include "BiTree.h"

int main()
{
/*    BiThrTree T,Thr;
    CreateThrBiTree(&T);
    InOrderThreading(&Thr,T);
    InOrderTraverse_Thr(Thr,PrintElement);
 */
    BiTree T;
    CreateBiTree(&T);
    PostOrderTraverse_NR(T,PrintElement);
    printf("\n");
    PostOrderTraverse(T,PrintElement);
    return 0;
}
