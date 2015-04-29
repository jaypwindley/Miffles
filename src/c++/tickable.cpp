// -----------------------------------------------------------------------
//  File:              tickable.cpp
//  Description:       Miffles Tickable functions
//  Author:            Jay Windley <jwindley>
//  Created:           Mon Mar 30 23:43:42 2015
//  Copyright:         (c) 2015 Jay Windley
//                     All rights reserved.
// -----------------------------------------------------------------------

#include <assert.h>
#include <gtkmm.h>

#include "tickable.h"
#include "dashboard.h"
#include "frame.h"

const unsigned int Miffles::Tickable::DEFAULT_HERTZ = 100;


Miffles::Tickable_Czar::Tickable_Czar( Miffles::Dashboard *_dashboard ) :
    m_dashboard( _dashboard )
{   
    assert( m_dashboard );
}


void Miffles::Tickable_Czar::add( Miffles::Tickable *t, bool defer )
{
    assert( t );
    (*this)[ t->m_hertz ].push_back( t );
    if ( ! defer ) link_timers();
}   


void Miffles::Tickable_Czar::link_timers( void )
{
    // The iterator is decomposed into a tuple ( Hz, Tickable *).
    for ( auto i : *this ) {

        // This is how Glib abstracts callables.  Be sure to pass
        // an explicit "this".
        //
        auto slot =
            sigc::bind( sigc::mem_fun( *this,
                                       &Tickable_Czar::on_timer ),
                        i.second );

        // Timer intervals are specifid in Hz, and Glib wants the
        // timeout value in milliseconds.
        //
        Glib::signal_timeout().connect( slot, 1000 / i.first );
    }   
}


bool Miffles::Tickable_Czar::on_timer( Tickable_List &me )
{
    for ( auto i : me ) {
        bool dirty = i->tick();
        /// XXX invalidate only the Frame that a Midget belongs to.        
    }

    // Hack to invalidate all Frames during development.
    assert( m_dashboard );
    for ( auto i : *m_dashboard->m_frames ) {
        i->redraw();
    }
    return true;
}
