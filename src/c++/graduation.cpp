// -----------------------------------------------------------------------
//  File:              graduation.cpp
//  Description:       Graduation functions
//  Author:            Jay Windley <jwindley>
//  Created:           Tue Mar 31 11:40:22 2015
//  Copyright:         (c) 2015 Jay Windley
//                     All rights reserved.
// -----------------------------------------------------------------------

#include <gtkmm.h>

#include "graduation.h"
#include "midget.h"
#include "field.h"


Miffles::Graduation::Graduation( char const *_name ) :
    Midget( _name )
{
}


bool Miffles::Graduation::draw( const Cairo_Context &cr )
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
