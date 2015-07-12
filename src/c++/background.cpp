// -----------------------------------------------------------------------
//  File:              background.cpp
//  Description:       Miffles Background functions
//  Author:            Jay Windley <jwindley>
//  Created:           Fri Apr 10 13:07:03 2015
//  Copyright:         (c) 2015 Jay Windley
//                     All rights reserved.
// -----------------------------------------------------------------------

#include <gdkmm/pixbuf.h>
#include "background.hpp"
#include "frame.hpp"

miffles::color_background_t::color_background_t( char const *_name,
                                                 miffles::color_t _color ) :
    midget_t( _name ),
    m_color( _color )
{
}


bool miffles::color_background_t::draw( const midget_t::cairo_context_t &cr )
{
    cr->set_source_rgba( COLOR_SPEC( m_color ) );
    cr->rectangle( -100, -100, 200, 200 );
    cr->fill();
    return true;
}


miffles::image_background_t::image_background_t( char const *_name,
                                                 const std::string &file_name ) :
    midget_t( _name )
{
    m_pixbuf = Gdk::Pixbuf::create_from_file( file_name );
}


bool miffles::image_background_t::draw( const midget_t::cairo_context_t &cr )
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
