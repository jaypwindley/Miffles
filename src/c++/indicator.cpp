// -----------------------------------------------------------------------
//  File:              indicator.cpp
//  Description:       Miffles Indicator functions
//  Author:            Jay Windley <jwindley>
//  Created:           Tue Mar 31 12:08:49 2015
//  Copyright:         (c) 2015 Jay Windley
//                     All rights reserved.
// -----------------------------------------------------------------------

#include <assert.h>

#include "sweep.h"
#include "scale.h"
#include "indicator.h"
#include "frame.h"

Miffles::Mark::Mark( char const *_name ) :
    Midget( _name ),
    m_scale( NULL ),
    m_sweep( new Miffles::Sweep_Dummy() )
{
}


void Miffles::Mark::set( double value ) {
    assert( m_sweep );
    m_sweep->set( m_scale->fraction( value ) );
    m_frame->redraw();
}


double Miffles::Mark::fraction( void ) {
    assert( m_sweep );
    return m_sweep->at();
}
