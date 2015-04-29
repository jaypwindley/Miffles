// -----------------------------------------------------------------------
//  File:              sweep.cpp
//  Description:       Miffles Sweep functions
//  Author:            Jay Windley <jwindley>
//  Created:           Mon Mar 30 23:50:45 2015
//  Copyright:         (c) 2015 Jay Windley
//                     All rights reserved.
// -----------------------------------------------------------------------

#include <math.h>
#include "sweep.h"

Miffles::Sweep::Sweep( double _rate ) :
    Tickable(),
    m_rate( _rate / double( m_hertz ) ),
    m_setpoint( 0.0 ),
    m_at( 0.0 )
{
    /*EMPTY*/
}


bool Miffles::Sweep::tick( void )
{
    if ( par() ) return false;

    double error = m_setpoint - m_at;

    // If the error is smaller than the timeout time slice, the at-point
    // is close enough to the set-point to simply consider it par.
    //
    if ( fabs( error ) < m_rate ) {
        m_at = m_setpoint;

    } else {
        if ( error > 0.0 ) {
            m_at += m_rate;
        } else {
            m_at -= m_rate;
        }
    }
    return true;
}
