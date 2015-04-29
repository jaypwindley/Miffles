// -----------------------------------------------------------------------
//  File:              background.cpp
//  Description:       Miffles Background functions
//  Author:            Jay Windley <jwindley>
//  Created:           Fri Apr 10 13:07:03 2015
//  Copyright:         (c) 2015 Jay Windley
//                     All rights reserved.
// -----------------------------------------------------------------------

#include "background.h"

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
