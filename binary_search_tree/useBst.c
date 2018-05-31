#include "stdio.h"
#include "bst.h"

int main()
{
    int numbers[] = { 1, 5, 4, 3, 2, 6 };

    BSTree bst = NULL;

    int i;
    for( i = 0; i < 6; i++)
        bst = insert_bstree(bst, numbers[i]);

    printf("preorder traversal:\n");
    preorder_bstree(bst);

    printf("\ninorder traversal:\n");
    inorder_bstree(bst);
  
    printf("\npostorder traversal:\n");
    postorder_bstree(bst);


    Node* n = bstree_maximum(bst);
    printf("\nFind bst maximum's %d.", n -> key);

    n = bstree_minimum(bst);
    printf("\nFnd bst minimum's %d.", n -> key);


    int searchKey = 6;
    n = iterative_bstree_search(bst, searchKey);
    if(NULL == n)
    {
        printf("\nCan't found %d in bstree.", searchKey );
    }
    else
    {
        printf("\nthe key[%d] is found in bstree.", n -> key);
        Node* precursor = bstree_precursor(n);
        if( precursor != NULL)
            printf("\nthe Node[%d]'s prcursor is Node[%d].", n -> key, precursor -> key);
    }

    printf("\nshow bstree :\n");
    print_bstree(bst, bst -> key, 0);


    printf("\nDestory bstree.\n");
    destroy_bstree(bst);

}