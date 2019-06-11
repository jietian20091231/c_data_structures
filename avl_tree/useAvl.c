#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROW  5
#define COL  10

int array[ ROW ][ COL ];


static void initArray( void )
{
    int i,j;
    for ( i = 0; i < ROW; i++ ) {
        for ( j = 0; j < COL; j++ )
            array[ i ][ j ] = 0;
    }
}

static void randomGen( int r[] )
{
    r[ 0 ] = rand() % 90 + 10;
    
    int i, j ;
    for ( i = 1; i < COL; i++ ) {
        int n = rand() % 90 + 10;
        int flag = 1;
        do {
            for ( j = 0; j < i; j++ ) {
                if ( n == r[ j ] ) {
                    n = rand() % 90 + 10;
                } else {
                    flag = 0;
                }
            }

        } while ( flag );

        r[ i ] = n;
    }
}

int main(int argc, char const *argv[])
{
    int i, j;

    srand( time( NULL  ) );

    for ( i = 0; i < ROW; i++ ) {
        randomGen( array [ i ] );
    }

    for( i = 0 ; i < ROW; i++ ) {
        printf( "[%d] ", i );
        for( j = 0; j < COL; j++ ) {
            printf( "%d ", array[ i ][ j ] );
        }
        printf( "\n" );
    }

    return 0;
}
