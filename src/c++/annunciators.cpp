// -----------------------------------------------------------------------
//  File:              annunciators.cpp
//  Description:       Miffles assorted Annunciator functions
//  Author:            Jay Windley <jwindley>
//  Created:           Tue Apr  7 12:02:31 2015
//  Copyright:         (c) 2015 Jay Windley
//                     All rights reserved.
// -----------------------------------------------------------------------

#include "annunciators.h"
#include "macros.h"

Miffles::Basic_Lightbulb_Annunciator::Basic_Lightbulb_Annunciator( char const *_name ) :
    Miffles::Annunciator( _name )
{
    /*EMPTY*/
}

bool
Miffles::Basic_Lightbulb_Annunciator::draw( const Cairo_Context &cr )
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
