#include <assert.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include "types.h"

Miffles::Color::RGB_Map Miffles::Color::m_RGB_txt;

const Miffles::Color Miffles::Color::Black( 0, 0, 0 );
const Miffles::Color Miffles::Color::White( 1, 1, 1 );
const Miffles::Color Miffles::Color::Red( 1, 0, 0 );
const Miffles::Color Miffles::Color::Green( 0, 1, 0 );
const Miffles::Color Miffles::Color::Blue( 0, 0, 1 );


Miffles::Color::Color( char const *_color, const double a ) {
    int r, g, b;

    // Lazy-load the list.
    if ( m_RGB_txt.size() == 0 ) load_RGB_txt();

    // Look up the colors.  Defaults to black if the name lookup fails.
    std::string name( _color );
    std::tie( r, g, b ) = m_RGB_txt[ name ];

    // Normalize the values and create the color.
    push_back( (double) r / 255.0 );
    push_back( (double) g / 255.0 );
    push_back( (double) b / 255.0 );
    push_back( a );
}

void Miffles::Color::load_RGB_txt( void )
{
    static const char path[] = "/etc/X11/rgb.txt";    
    static const size_t BUFSIZE = 128;
    char buf[ BUFSIZE ];
    FILE *f;

    if ( ( f = fopen( path, "r" ) ) == NULL ) return;

    while ( fgets( buf, BUFSIZE, f ) ) {
        // Skip comments.
        if ( buf[ 0 ] == '!' ) continue;

        // RGB values are fixed-size fields.
        int r, g, b;
        sscanf( buf, "%3d %3d %3d", &r, &g, &b );

        // Color name is anywhere after column 11 to the end of the
        // line.  Find the first non-whitespace character and then
        // eliminate the newline.
        //
        char *p = &buf[ 11 ];
        while ( ::isspace( *++p ) )
            ;
        if ( char *q = ::strchr( p, '\n' ) )
            *q = 0;

        m_RGB_txt[ std::string( p ) ] = std::make_tuple( r, g, b );
    }
    fclose( f );
}
