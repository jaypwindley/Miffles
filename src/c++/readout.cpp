// -----------------------------------------------------------------------
//  File:              readout.cpp
//  Description:       Miffles Readout functions
//  Author:            Jay Windley <jwindley>
//  Created:           Fri Apr 10 13:02:42 2015
//  Copyright:         (c) 2015 Jay Windley
//                     All rights reserved.
// -----------------------------------------------------------------------

#include "readout.h"

Miffles::Readout::Readout( char const *_name ) :
    Label( _name ),
    m_value( 0 )
{
    /*EMPTY*/
}

bool Miffles::Readout::draw( const Midget::Cairo_Context &cr )
{
    return true;
}
