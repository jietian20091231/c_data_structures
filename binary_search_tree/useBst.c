#include "stdio.h"
#include "bst.h"

int main()
{
    int numbers[] = { 6, 2, 8, 1, 4, 3, 5 };

    SearchTree t = NULL;

    int i = 0;
    for( i = 0; i < 7; i++ )
        t = insert( numbers[i], t );

    printf( "t -> key = %d\n", t -> key );
    
    printf( "the searchTree's height = %d\n", getHeight(t) );

    printf( "Perorder traversal :\n" );
    perorder_traversal(t);

    printf( "\ninorder traversal :\n" );
    inorder_traversal(t);

    printf( "\npostorder traversal :\n" );
    postorder_traversal(t);

    if( NULL != t )
    {
        printf( "\nnumbers max = %d, min = %d\n", findMax(t) -> key, findMin(t) -> key );
        int searchKey = 4;
        Position p = find( searchKey, t) ;
        if(p)
        {
            printf( "Number %d is found!\n", p -> key );
        }
        else
        {
            printf( "Number %d can't be found!\n", searchKey );
        }
    }
    

    printf( "free searchTree.\n" );
    makeEmpty(t);

    return 0;

}