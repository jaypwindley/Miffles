// -----------------------------------------------------------------------
//  File:              settable.cpp
//  Description:       Miffles Settable functions
//  Author:            Jay Windley <jwindley>
//  Created:           Tue Apr  7 09:56:02 2015
//  Copyright:         (c) 2015 Jay Windley
//                     All rights reserved.
// -----------------------------------------------------------------------

#include "settable.h"
#include "app.h"
#include "input_demux.h"

// Unless these are overridden in subclasses, print out something if
// they are called.
//
void Miffles::Settable::set( std::string &val ) {
    fprintf( stderr, "Miffles::Settable child does not understand std::string\n" );
}

void Miffles::Settable::set( void *thing ) {
    fprintf( stderr, "Miffles::Settable child does not understand void *\n" );
}

void Miffles::Settable::set( bool is_on ) {
    fprintf( stderr, "Miffles::Settable child does not understand bool\n" );
}

void Miffles::Settable::set( double value ) {
    fprintf( stderr, "Miffles::Setting child does not understand double\n" );
}


void Miffles::Settable::listen( const std::string &channel )
{    
    App::app()->m_demux->listen( channel, this );
}
