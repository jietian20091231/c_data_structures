#include "stdio.h"
#include "bst.h"

int main()
{
    int numbers[] = { 8, 1, 9, 0, 5, 10, 4, 7, 11, 2, 6, 3 };

    BSTree bst = NULL;

    int i;
    for( i = 0; i < 12; i++)
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


    int searchKey = 7;
    n = bstree_search(bst, searchKey);
    if(NULL == n)
    {
        printf("\nCan't found %d in bstree.", searchKey );
    }
    else
    {
        printf("\nthe key[%d] is found in bstree.", n -> key);
        Node* p = bstree_precursor(n);
        if(NULL != p)
        {
            printf("Node[%d] has a precursor Node[%d].\n", n -> key, p -> key);
        }
    }


    printf("\nshow bstree :\n");
    print_bstree(bst, bst -> key, 0);

    for(i = 0; i < 12; i++)
    {
        printf("delete %d\n", i);
        delete_bstree(bst, i);
        print_bstree(bst, bst -> key, 0);
    }


    printf("\nDestory bstree.\n");
    destroy_bstree(bst);

}