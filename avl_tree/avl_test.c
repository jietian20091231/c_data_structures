#include <stdio.h>
#include "avl_tree.h"

int main(int argc, char const *argv[])
{
  int array[ 10 ][ 10 ] = {
        { 95, 66, 73, 97, 83, 35, 79, 78, 28, 80 },     //0
        { 75, 37, 85, 28, 84, 33, 93, 17, 65, 57 },     //1
        { 30, 74, 84, 26, 35, 89, 22, 63, 59, 85 },     //2
        { 20, 25, 70, 61, 98, 49, 39, 26, 82, 66 },     //3
        { 54, 67, 85, 38, 52, 78, 45, 17, 36, 27 },     //4
        { 43, 62, 63, 22, 87, 52, 34, 12, 11, 71 },     //5
        { 22, 27, 44, 40, 42, 84, 31, 58, 66, 88 },     //6
        { 12, 85, 73, 92, 89, 13, 96, 39, 17, 91 },     //7
        { 53, 70, 65, 40, 23, 90, 42, 24, 17, 93 },     //8
        { 57, 51, 85, 89, 87, 17, 10, 15, 95, 12 }      //9
    };

    int i, j;

    // AvlTree t = NULL;
    // for( j = 0; j < 10; j++ ) {
    //     t = insert_avltree( t, array[ 9 ][ j ] );
    //     printf( "[Main]\n" );
    //     print_avltree( t, t -> key , 0 );
    //     printf( "\n" );
    // }
    // destroy_avltree( t );



    for ( i = 0; i < 10; i++ ) {
        printf( "==========array[%d]==========\n", i );
        printf( "Input Numbers : " );
        for( j = 0; j < 10; j++ ) {
            printf( "%d ", array[ i ][ j ] );
        }
        printf( "\n\n" );

        AvlTree t = NULL;
        for ( j = 0; j < 10; j++ ) {
            t = insert_avltree( t, array[ i ][ j ] );
            printf( "[Main]\n" );
            print_avltree( t, t -> key , 0 );
            printf( "\n" );
        }
        destroy_avltree( t );

    }

    return 0;
}


