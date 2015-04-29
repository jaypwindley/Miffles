// -----------------------------------------------------------------------
//  File:              dashboard.cpp
//  Description:       Miffles dashboard functions
//  Author:            Jay Windley <jwindley>
//  Created:           Mon Mar 30 21:22:17 2015
//  Copyright:         (c) 2015 Jay Windley
//                     All rights reserved.
// -----------------------------------------------------------------------

#include "dashboard.h"
#include "types.h"
#include "frame.h"


Miffles::Dashboard::Dashboard() :
    m_frames( new Frame_List() )
{
}


Miffles::Dashboard::~Dashboard()
{
    delete m_frames;
}


void Miffles::Dashboard::add( Point _origin, Frame *f )
{
    f->m_origin = _origin;
    m_frames->push_back( f );
}


Miffles::Extent Miffles::Dashboard::extent( void ) {
    Extent total( 0, 0 );
    for ( auto i = m_frames->begin(); i != m_frames->end(); ++i ) {

        // For each Frame, determine its Extent from the Dashboard
        // origin to the Frame's extent, then expand the total Extent if
        // needed.
        //
        Extent e = (*i)->m_origin + (*i)->m_size;
        if ( e.width() > total.width() )
            total.width( e.width() );
        if ( e.height() > total.height() )
            total.height( e.height() );
    }
    return total;
}

