#include "stdio.h"
#include "bst.h"

int main()
{
    int numbers[] = { 51, 26, 97, 54, 16, 31, 130, 23, 27, 109 };

    BSTree bst = NULL;

    int i;
    for( i = 0; i < 10; i++)
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

    printf("bst address = %p.\n", bst);

    printf("\nshow bstree :\n");
    print_bstree(bst, bst -> key, 0);

    for(i = 0; i < 10; i++)
    {
        n = bstree_search(bst, 76);
        if(n != NULL && n -> father != NULL)
            printf("%d -> father -> key = %d.\n", n -> key,  n -> father -> key);
        printf("delete %d\n", numbers[i]);
        bst = delete_bstree(bst, numbers[i]);
        if(NULL == bst)
        {
            printf("bstree is none.\n");
            break;
        }
        print_bstree(bst, bst -> key, 0);
    }

    printf("bst address = %p.\n", bst);

    if(NULL == bst)
        printf("bst is NULL.\n");

    printf("\nDestory bstree.\n");
    destroy_bstree(bst);

}