// -----------------------------------------------------------------------
//  File:              annunciators.cpp
//  Description:       Miffles assorted Annunciator functions
//  Author:            Jay Windley <jwindley>
//  Created:           Tue Apr  7 12:02:31 2015
//  Copyright:         (c) 2015 Jay Windley
//                     All rights reserved.
// -----------------------------------------------------------------------

#include "annunciators.hpp"
#include "macros.hpp"

miffles::basic_lightbulb_annunciator_t::basic_lightbulb_annunciator_t( char const *_name ) :
    miffles::annunciator_t( _name )
{
}

bool
miffles::basic_lightbulb_annunciator_t::draw( const cairo_context_t &cr )
{
    cr->arc( 0, 0, 20, 0, 2 * PI );
    cr->close_path();
    if ( m_is_on ) {
        cr->set_source_rgb( 1, 0, 0 );
    } else {
        cr->set_source_rgb( 0, 0, 0 );
    }
    cr->fill();
    return true;
}
