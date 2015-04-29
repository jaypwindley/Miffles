// -----------------------------------------------------------------------
//  File:              meter.cpp
//  Description:       Miffles Meter functions
//  Author:            Jay Windley <jwindley>
//  Created:           Tue Mar 31 17:19:08 2015
//  Copyright:         (c) 2015 Jay Windley
//                     All rights reserved.
// -----------------------------------------------------------------------

#include "meter.h"
#include "field.h"


Miffles::Meter::Meter( char const *_name ) :
    Frame( _name ),
    m_field( NULL )
{
    /*EMPTY*/
}


Miffles::Linear_Meter::Linear_Meter( char const *_name ) :
    Meter( _name )
{
    /*EMPTY*/
}


void Miffles::Linear_Meter::set_field( Miffles::Linear_Field *f )
{
    m_field = f;
}


Miffles::Radial_Meter::Radial_Meter( char const * _name ) :
    Meter( _name )
{
    /*EMPTY*/
}


void Miffles::Radial_Meter::set_field( Miffles::Radial_Field *f )
{
    m_field = f;
}
