// -----------------------------------------------------------------------
//  File:              graduation.cpp
//  Description:       Graduation functions
//  Author:            Jay Windley <jwindley>
//  Created:           Tue Mar 31 11:40:22 2015
//  Copyright:         (c) 2015 Jay Windley
//                     All rights reserved.
// -----------------------------------------------------------------------

#include <gtkmm.h>
#include "graduation.hpp"
#include "midget.hpp"
#include "field.hpp"


miffles::graduation_t::graduation_t( char const *_name ) :
    midget_t( _name )
{
}


bool miffles::graduation_t::draw( const cairo_context_t &cr )
{
    assert( m_field );
    cr->set_line_width( 1 );
    cr->set_source_rgb( 1, 0.75, 0.75 );
    cr->arc_negative( 0, 0,
                      95,
                      m_field->m_origin,
                      m_field->m_origin - m_field->m_extent );
    cr->stroke();
}
