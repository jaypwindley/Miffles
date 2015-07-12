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
#include "scale.hpp"
#include "domain.hpp"


miffles::linear_scale_t::linear_scale_t( domain_t d ) :
    scale_t( d.min(), d.max() )
{
    if ( ( d.min() == MIN_OPEN ) || ( d.max() == MAX_OPEN ) ) {
        /// XXX Throw something besides a string.
        throw "Implicit scale cannot be open-ended";
    }
    m_size = d.max() - d.min();
}


miffles::nonlinear_scale_t::nonlinear_scale_t( double _origin,
                                               double _size,
                                               double _base ) :
    scale_t( _origin, _size ),
    m_base_conv( 1.0 / log( _base ) )       // Because math.
{
}


double miffles::linear_scale_t::fraction( const double measure )
{
    return ( measure - m_origin ) / m_size; 
}


double miffles::linear_scale_t::measure( const double fraction )
{
    return fraction * m_size + m_origin;
}


double miffles::nonlinear_scale_t::fraction( const double measure )
{
    return ( log( measure - m_origin) * m_base_conv ) / m_size;
}


double miffles::nonlinear_scale_t::measure( const double fraction )
{
    return exp( fraction * m_size / m_base_conv );
}
