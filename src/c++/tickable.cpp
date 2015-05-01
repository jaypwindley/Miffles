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


void Miffles::Tickable_Czar::add( Miffles::Tickable *t, Miffles::Frame *f, bool defer )
{
    assert( t );
    (*this)[ t->m_hertz ].push_back( Tickable_List_Element( t, f ) );
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
        if ( i.first->tick() ) {
            i.second->redraw();
        }
    }

    return true;
}
