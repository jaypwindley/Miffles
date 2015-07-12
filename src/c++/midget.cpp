// -----------------------------------------------------------------------
//  File:              midget.cpp
//  Description:       Miffles Midget functions
//  Author:            Jay Windley <jwindley>
//  Created:           Tue Mar 31 12:35:01 2015
//  Copyright:         (c) 2015 Jay Windley
//                     All rights reserved.
// -----------------------------------------------------------------------

#include "midget.hpp"


miffles::midget_t::midget_t( char const *_name ) :
    m_name( std::string( _name ) ),
    m_frame( NULL )
{
}


miffles::midget_list_t::iterator
miffles::midget_list_t::find( std::string &name )
{
    miffles::midget_list_t::iterator i;
    for ( auto i : *this ) {
        if ( i->m_name == name ) break;
    }
    return i;
}
