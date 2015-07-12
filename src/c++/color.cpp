#include <assert.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include "types.hpp"

miffles::color_t::RGB_map_t miffles::color_t::m_RGB_txt;

const miffles::color_t miffles::color_t::black( 0, 0, 0 );
const miffles::color_t miffles::color_t::white( 1, 1, 1 );
const miffles::color_t miffles::color_t::red( 1, 0, 0 );
const miffles::color_t miffles::color_t::green( 0, 1, 0 );
const miffles::color_t miffles::color_t::blue( 0, 0, 1 );


miffles::color_t::color_t( char const *_color, const double a ) {
    int r, g, b;

    // Lazy-load the list.
    if ( m_RGB_txt.size() == 0 ) load_RGB_txt();

    // Look up the colors.  Defaults to black if the name lookup fails.
    std::string name( _color );
    std::tie( r, g, b ) = m_RGB_txt[ name ];

    // Normalize the values and create the color.
    m_r = (double) r / 255.0;
    m_g = (double) g / 255.0;
    m_b = (double) b / 255.0;
    m_a = a;
}

void miffles::color_t::load_RGB_txt( void )
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
