// -----------------------------------------------------------------------
//  File:              indicator.cpp
//  Description:       Miffles Indicator functions
//  Author:            Jay Windley <jwindley>
//  Created:           Tue Mar 31 12:08:49 2015
//  Copyright:         (c) 2015 Jay Windley
//                     All rights reserved.
// -----------------------------------------------------------------------

#include <assert.h>
#include "sweep.hpp"
#include "scale.hpp"
#include "indicator.hpp"
#include "frame.hpp"

miffles::mark_t::mark_t( char const *_name ) :
    midget_t( _name ),
    m_scale( NULL ),
    m_sweep( new miffles::sweep_dummy_t() )
{
}


void miffles::mark_t::set( double value ) {
    assert( m_sweep );
    m_sweep->set( m_scale->fraction( value ) );
    m_frame->redraw();
}


double miffles::mark_t::fraction( void ) const {
    assert( m_sweep );
    return m_sweep->at();
}
