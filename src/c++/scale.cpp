// -----------------------------------------------------------------------
//  File:              scale.cpp
//  Description:       Miffles Scale functions
//  Author:            Jay Windley <jwindley>
//  Created:           Tue Mar 31 00:06:13 2015
//  Copyright:         (c) 2015 Jay Windley
//                     All rights reserved.
// -----------------------------------------------------------------------

#include <stdio.h>
#include <math.h>

#include "scale.h"
#include "domain.h"


Miffles::Linear_Scale::Linear_Scale( Domain d ) :
    Scale( d.min(), d.max() )
{
    if ( ( d.min() == MIN_OPEN ) || ( d.max() == MAX_OPEN ) ) {
        /// XXX Throw something besides a string.
        throw "Implicit scale cannot be open-ended";
    }
    m_size = d.max() - d.min();
}


Miffles::Nonlinear_Scale::Nonlinear_Scale( double _origin,
                                           double _size,
                                           double _base ) :
    Scale( _origin, _size ),
    m_base_conv( 1.0 / log( _base ) )       // Because math.
{
    /*EMPTY*/
}


double Miffles::Linear_Scale::fraction( const double measure )
{
    return ( measure - m_origin ) / m_size; 
}


double Miffles::Linear_Scale::measure( const double fraction )
{
    return fraction * m_size + m_origin;
}


double Miffles::Nonlinear_Scale::fraction( const double measure )
{
    return ( log( measure - m_origin) * m_base_conv ) / m_size;
}


double Miffles::Nonlinear_Scale::measure( const double fraction )
{
    return exp( fraction * m_size / m_base_conv );
}
