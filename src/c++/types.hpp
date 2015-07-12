// -----------------------------------------------------------------------
//  File:              types.hpp
//  Description:       Basic Miffles types
//  Author:            Jay Windley <jwindley>
//  Created:           Mon Mar 30 23:58:45 2015
//  Copyright:         (c) 2015 Jay Windley
//                     All rights reserved.
// -----------------------------------------------------------------------

#pragma once

#include <map>

namespace miffles {    

    //******************************************************************
    //
    //  A pair of (width, height) describing the size of a geometric
    //  object.
    //
    //******************************************************************
    class extent_t {
    private:
        double m_w;
        double m_h;
    public:
        extent_t( const double _w = 0, const double _h = 0 ) :
            m_w( _w ), m_h( _h )
        {
        }
        const double width(  void            )  const { return m_w;  }
        const double height( void            )  const { return m_h; }
        void         width(  const double _w )  { m_w  = _w;   }
        void         height( const double _h )  { m_h = _h;   }
    };


    //******************************************************************
    //
    //  A geometric 2D point.
    //
    //******************************************************************
    class point_t {
    private:
        double m_x;
        double m_y;
    public:
        point_t( const double _x = 0, const double _y = 0 ) :
            m_x( _x ), m_y( _y )
        {
        }
        const double x( void ) const { return m_x;   }
        const double y( void ) const { return m_y;;  }
        void   x( const double _x )  { m_x = _x;  }
        void   y( const double _y )  { m_y = _y; }

        //--------------------------------------------------------------
        // A Point plus an Extent is an Extent from the Point's origin.
        //
        extent_t operator + ( const extent_t &r ) const
        {
            return extent_t( m_x + r.width(),
                             m_y + r.height() );
        }
    };


    //******************************************************************
    //
    //   An RGBA color, normalized to [0..1].
    //
    //******************************************************************
    class color_t {
    private:
        double m_r;
        double m_g;
        double m_b;
        double m_a;
    private:
        // Standard X11 color names and RGB values from rgb.txt.
        typedef std::map< std::string,
                          std::tuple<int, int, int>> RGB_map_t;
        
        static RGB_map_t m_RGB_txt;
        
    public:
        // Some predefined colors.
        const static color_t black;
        const static color_t white;
        const static color_t red;
        const static color_t green;
        const static color_t blue;
        
    public:

        // Normalized RGB components.
        color_t( const double r,
                 const double g,
                 const double b,
                 const double a = 1.0 ) :
            m_r( r ), m_g( g ), m_b( b ), m_a( a )
        {
        }

        // Standard color names.
        color_t( char const *_color, const double = 1.0 );
        virtual ~color_t() {}
        
        void r( const double _r ) { m_r = _r; }
        void g( const double _g ) { m_g = _g; }
        void b( const double _b ) { m_b = _b; }
        void a( const double _a ) { m_a = _a; }
        
        double r( void ) const { return m_r; }
        double g( void ) const { return m_g; }
        double b( void ) const { return m_b; }
        double a( void ) const { return m_a; }

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
