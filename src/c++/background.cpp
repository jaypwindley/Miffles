// -----------------------------------------------------------------------
//  File:              background.cpp
//  Description:       Miffles Background functions
//  Author:            Jay Windley <jwindley>
//  Created:           Fri Apr 10 13:07:03 2015
//  Copyright:         (c) 2015 Jay Windley
//                     All rights reserved.
// -----------------------------------------------------------------------

#include <gdkmm/pixbuf.h>
#include "background.h"
#include "frame.h"

Miffles::Color_Background::Color_Background( char const *_name,
                                             Miffles::Color _color ) :
    Midget( _name ),
    m_color( _color )
{
    /*EMPTY*/
}


bool Miffles::Color_Background::draw( const Midget::Cairo_Context &cr )
{
    cr->set_source_rgba( COLOR_SPEC( m_color ) );
    cr->rectangle( -100, -100, 200, 200 );
    cr->fill();
    return true;
}


Miffles::Image_Background::Image_Background( char const *_name,
                                             std::string file_name ) :
    Midget( _name )
{
    m_pixbuf = Gdk::Pixbuf::create_from_file( file_name );
}


bool Miffles::Image_Background::draw( const Midget::Cairo_Context &cr )
{
    cr->save();

    // Do not pre-scale the image.  Otherwise it gets badly filtered at
    // most resolutions.  When scaling on the fly here, use the scale to
    // flip the image vertically to account for the change in coordinate
    // basis.  This could be precomputed by a flip() transformation on
    // the image, but meh -- it all goes through the transformation
    // matrix anyway, so no computational savings.
    //
    cr->scale( 200.0 / m_pixbuf->get_width(), -200.0 / m_pixbuf->get_height() );

    // Center the image.  Maybe there will someday be a need for offset
    // images in a frame, but it is not today.
    //
    Gdk::Cairo::set_source_pixbuf( cr,
                                   m_pixbuf,
                                   m_pixbuf->get_width() / -2.0,
                                   m_pixbuf->get_height() / -2.0 );
    cr->paint();
    
    cr->restore();
    return true;
}
