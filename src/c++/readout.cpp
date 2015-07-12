// -----------------------------------------------------------------------
//  File:              readout.cpp
//  Description:       Miffles Readout functions
//  Author:            Jay Windley <jwindley>
//  Created:           Fri Apr 10 13:02:42 2015
//  Copyright:         (c) 2015 Jay Windley
//                     All rights reserved.
// -----------------------------------------------------------------------

#include "readout.hpp"

miffles::readout_t::readout_t( char const *_name ) :
    label_t( _name ),
    m_value( 0 )
{
}

bool miffles::readout_t::draw( const midget_t::cairo_context_t &cr )
{
    return true;
}
