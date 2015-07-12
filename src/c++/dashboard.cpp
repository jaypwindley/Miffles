// -----------------------------------------------------------------------
//  File:              dashboard.cpp
//  Description:       Miffles dashboard functions
//  Author:            Jay Windley <jwindley>
//  Created:           Mon Mar 30 21:22:17 2015
//  Copyright:         (c) 2015 Jay Windley
//                     All rights reserved.
// -----------------------------------------------------------------------

#include "dashboard.hpp"
#include "types.hpp"
#include "frame.hpp"


miffles::dashboard_t::dashboard_t() :
    m_frames( new frame_list_t() )
{
}


miffles::dashboard_t::~dashboard_t()
{
    delete m_frames;
}


void miffles::dashboard_t::add( point_t _origin, frame_t *f )
{
    f->m_origin = _origin;
    m_frames->push_back( f );
}


miffles::extent_t miffles::dashboard_t::extent( void ) {
    extent_t total( 0, 0 );
    for ( auto i = m_frames->begin(); i != m_frames->end(); ++i ) {

        // For each Frame, determine its Extent from the Dashboard
        // origin to the Frame's extent, then expand the total Extent if
        // needed.
        //
        extent_t e = (*i)->m_origin + (*i)->m_size;
        if ( e.width() > total.width() )
            total.width( e.width() );
        if ( e.height() > total.height() )
            total.height( e.height() );
    }
    return total;
}

