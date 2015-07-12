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
#include "tickable.hpp"
#include "dashboard.hpp"
#include "frame.hpp"

const unsigned int miffles::tickable_t::DEFAULT_HERTZ = 100;


miffles::tickable_czar_t::tickable_czar_t( miffles::dashboard_t *_dashboard ) :
    m_dashboard( _dashboard )
{   
    assert( m_dashboard );
}


void miffles::tickable_czar_t::add( miffles::tickable_t *t,
                                    miffles::frame_t *f, bool defer )
{
    assert( t );
    (*this)[ t->m_hertz ].push_back( tickable_list_element_t( t, f ) );
    if ( ! defer ) link_timers();
}   


void miffles::tickable_czar_t::link_timers( void )
{
    // The iterator is decomposed into a tuple ( Hz, tickable_t *).
    for ( auto i : *this ) {

        // This is how Glib abstracts callables.  Be sure to pass
        // an explicit "this".
        //
        auto slot =
            sigc::bind( sigc::mem_fun( *this,
                                       &tickable_czar_t::on_timer ),
                        i.second );

        // Timer intervals are specifid in Hz, and Glib wants the
        // timeout value in milliseconds.
        //
        Glib::signal_timeout().connect( slot, 1000 / i.first );
    }   
}


bool miffles::tickable_czar_t::on_timer( tickable_list_t &me )
{
    for ( auto i : me ) {
        if ( i.first->tick() ) {
            i.second->redraw();
        }
    }

    return true;
}
