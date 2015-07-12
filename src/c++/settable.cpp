// -----------------------------------------------------------------------
//  File:              settable.cpp
//  Description:       Miffles Settable functions
//  Author:            Jay Windley <jwindley>
//  Created:           Tue Apr  7 09:56:02 2015
//  Copyright:         (c) 2015 Jay Windley
//                     All rights reserved.
// -----------------------------------------------------------------------

#include "settable.hpp"
#include "app.hpp"
#include "input_demux.hpp"

// Unless these are overridden in subclasses, print out something if
// they are called.
//
void miffles::settable_t::set( std::string &val ) {
    fprintf( stderr, "miffles::settable_t does not understand std::string\n" );
}

void miffles::settable_t::set( void *thing ) {
    fprintf( stderr, "miffles::settable_t does not understand void *\n" );
}

void miffles::settable_t::set( bool is_on ) {
    fprintf( stderr, "miffles::settable does not understand bool\n" );
}

void miffles::settable_t::set( double value ) {
    fprintf( stderr, "miffles::setting_t does not understand double\n" );
}


void miffles::settable_t::listen( const std::string &channel )
{    
    app_t::app()->m_demux->listen( channel, this );
}
