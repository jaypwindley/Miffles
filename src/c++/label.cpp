// -----------------------------------------------------------------------
//  File:              label.cpp
//  Description:       Miffles Label functions
//  Author:            Jay Windley <jwindley>
//  Created:           Tue Apr  7 16:37:17 2015
//  Copyright:         (c) 2015 Jay Windley
//                     All rights reserved.
// -----------------------------------------------------------------------

#include "label.hpp"
#include "text.hpp"

miffles::label_t::label_t( char const *_name ) :
    midget_t( _name ),
    m_text( "" ),
    m_style( new text_style_t() )
{
}


bool miffles::label_t::draw( const cairo_context_t &cr )
{
    render_text( cr, m_style, m_origin, m_text );
}







void miffles::render_text( const midget_t::cairo_context_t &cr,
                           miffles::text_style_t *style,
                           point_t &at,
                           std::string &s )
{
    assert( style );

    // Adjust rendering point based on justification.  Remember to scale
    // the font first before measuring the text extents.
    //
    point_t offset = at;
    cr->set_font_size( style->m_font_size );
    ::Cairo::TextExtents extents;
    cr->get_text_extents( s, extents );
    if ( style->m_h_justify == miffles::text_style_t::CENTER ) {
        offset.x( offset.x() - extents.width / 2 );
    } else if ( style->m_h_justify == miffles::text_style_t::RIGHT ) {
        offset.x( offset.x() - extents.width );
    }
    if ( style->m_v_justify == miffles::text_style_t::MIDDLE ) {
        offset.y( offset.y() - extents.height / 2 );
    } else if ( style->m_v_justify == miffles::text_style_t::TOP ) {
        offset.y( offset.y() - extents.height );
    }

    
    cr->save();

    // "Move" to the offset rendering point by means of a temporary
    // translation.
    //
    cr->translate( offset.x(), offset.y() );

    // The font renderer presumes a y-axis that increases downward.  The
    // Miffles coordinate system is traditional cartesian, so reflect
    // the font rendering across the y-axis.
    //
    cr->scale( 1, -1 );

    // Render the text.
    cr->move_to( 0, 0 );
    cr->set_source_rgba( COLOR_SPEC( style->m_color ) );
    cr->show_text( s.c_str() );
    cr->fill();
    cr->restore();
}
