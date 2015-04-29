// -----------------------------------------------------------------------
//  File:              midget.cpp
//  Description:       Miffles Midget functions
//  Author:            Jay Windley <jwindley>
//  Created:           Tue Mar 31 12:35:01 2015
//  Copyright:         (c) 2015 Jay Windley
//                     All rights reserved.
// -----------------------------------------------------------------------

#include "midget.h"


Miffles::Midget::Midget( char const *_name ) :
    m_name( std::string( _name ) ),
    m_frame( NULL )
{
    /*EMPTY*/
}


Miffles::Midget_List::iterator
Miffles::Midget_List::find( std::string &name )
{
    Miffles::Midget_List::iterator i;
    for ( auto i : *this ) {
        if ( i->m_name == name ) break;
    }
    return i;
}
