// -----------------------------------------------------------------------
//  File:              types.h
//  Description:       Basic Miffles types
//  Author:            Jay Windley <jwindley>
//  Created:           Mon Mar 30 23:58:45 2015
//  Copyright:         (c) 2015 Jay Windley
//                     All rights reserved.
// -----------------------------------------------------------------------

#ifndef __MIFFLES_TYPES_H__
#define __MIFFLES_TYPES_H__

#include <map>
#include <vector>
#include <tuple>

namespace Miffles {    

    //******************************************************************
    //
    //  A pair of (width, height) describing the size of a geometric
    //  object.
    //
    //******************************************************************
    class Extent : public std::pair< double, double > {
    public:
        Extent( double _w = 0, double _h = 0 )
        {
            first  = _w;
            second = _h;
        }
        double     width(    void      )  { return first;  }
        double     height(   void      )  { return second; }
        void       width(    double _w )  { first  = _w;   }
        void       height(   double _h )  { second = _h;   }
    };


    //******************************************************************
    //
    //  A geometric 2D point.
    //
    //******************************************************************
    class Point : public std::pair< double, double > {
    public:
        Point( double _x = 0, double _y = 0 )
        {
            first  = _x;
            second = _y;
        }
        double x( void )       { return first;   }
        double y( void )       { return second;  }
        void   x( double _x )  { first = _x;     }
        void   y( double _y )  { second = _y;    }

        //--------------------------------------------------------------
        // A Point plus an Extent is an Extent from the Point's origin.
        //
        Extent operator + ( Extent &r )
        {
            return Extent( first  + r.width(),
                           second + r.height() );
        }
    };


    //******************************************************************
    //
    //   An RGBA color, normalized to [0..1].
    //
    //******************************************************************
    class Color : public std::vector< double > {

    private:
        // Standard X11 color names and RGB values from rgb.txt.
        typedef std::map< std::string,
                          std::tuple< int, int, int > > RGB_Map;
        
        static RGB_Map m_RGB_txt;
        
    public:
        // Some predefined colors.
        const static Color Black;
        const static Color White;
        const static Color Red;
        const static Color Green;
        const static Color Blue;
        
    public:

        // Normalized RGB components.
        Color( double r, double g, double b, double a = 1.0 )
        {
            push_back( r );
            push_back( g );
            push_back( b );
            push_back( a );
        }

        // Standard color names.
        Color( char const *_color, const double = 1.0 );
        virtual ~Color() {}
        
        void r( double _r ) { (*this)[ 0 ] = _r; }
        void g( double _g ) { (*this)[ 1 ] = _g; }
        void b( double _b ) { (*this)[ 2 ] = _b; }
        void a( double _a ) { (*this)[ 3 ] = _a; }
        
        double r( void ) const { return (*this)[ 0 ]; }
        double g( void ) const { return (*this)[ 1 ]; }
        double b( void ) const { return (*this)[ 2 ]; }
        double a( void ) const { return (*this)[ 3 ]; }

    private:
        void load_RGB_txt( void );
    };

    //------------------------------------------------------------------
    // Convenience syntax sugar for breaking out a color into an
    // argument list suitable for cairo::set_source_rgba().
    //
    //    cr->set_source_rgba( COLOR_SPEC( color ) );
    //
#   define COLOR_SPEC(c) (c).r(),(c).g(),(c).b(),(c).a()
    
}

#endif /*__MIFFLES_TYPES_H__*/
