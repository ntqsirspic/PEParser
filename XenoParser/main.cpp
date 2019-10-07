#include "PEParser.h"

// Wide char, bitch. Imagine a file / path with non-ascii letters.
int wmain( int argc, wchar_t *argv[] )
{
    printf( "PE Parser\n\n" );

    if ( argc <= 1 )
    {
        printf( "Please specify an input file.\n" );
        getchar( );
        return EXIT_FAILURE;
    }

    PortableExecutable *pPortableExecutable = new PortableExecutable( argv[1] );

    if ( !PEParser::GetInstance( ).DoParse( pPortableExecutable ) )
    {
        printf( "Error while parsing.\n" );
    }

    delete pPortableExecutable;

    getchar( );

    return EXIT_SUCCESS;
}