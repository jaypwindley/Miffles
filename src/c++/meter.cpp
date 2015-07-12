// -----------------------------------------------------------------------
//  File:              meter.cpp
//  Description:       Miffles Meter functions
//  Author:            Jay Windley <jwindley>
//  Created:           Tue Mar 31 17:19:08 2015
//  Copyright:         (c) 2015 Jay Windley
//                     All rights reserved.
// -----------------------------------------------------------------------

#include "meter.hpp"
#include "field.hpp"


miffles::meter_t::meter_t( char const *_name ) :
    frame_t( _name ),
    m_field( NULL )
{
}


miffles::linear_meter_t::linear_meter_t( char const *_name ) :
    meter_t( _name )
{
}


void miffles::linear_meter_t::set_field( miffles::linear_field_t *f )
{
    m_field = f;
}


miffles::radial_meter_t::radial_meter_t( char const * _name ) :
    meter_t( _name )
{
}


void miffles::radial_meter_t::set_field( miffles::radial_field_t *f )
{
    m_field = f;
}
