#include <stdio.h>
#include <stdlib.h>
#include "avlTree.h"

#define LEN(a) ((sizeof(a)) / sizeof(a[0]))

int main()
{
    AvlTree tree = NULL;
    int a[] = {6, 2, 1, 8, 4, 0, 3, 5, 7, 9};
    int length = LEN(a);
    int i;
    for( i = 0; i < length; i++)
        tree = insertNode(tree, a[i]);

    int maxHeight = getHeight(tree);
    printf("tree's height = %d\n", maxHeight);
    printf("inOrder : \n");
    inOrderTraversal(tree);

    printf("print AVL tree: \n");
    printAvlTree(tree, tree -> element, 0);
}