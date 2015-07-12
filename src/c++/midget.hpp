// -----------------------------------------------------------------------
//  File:              midget.hpp
//  Description:       Miffles Midget, drawn primitive
//  Author:            Jay Windley <jwindley>
//  Created:           Tue Mar 31 12:06:54 2015
//  Copyright:         (c) 2015 Jay Windley
//                     All rights reserved.
// -----------------------------------------------------------------------

#pragma once

#include <gtkmm.h>
#include <assert.h>
#include <list>
#include <string>
#include "types.hpp"

namespace miffles {

    class frame_t;
    
    //******************************************************************
    //
    //  A Miffles widget.
    //
    //******************************************************************
    class midget_t
    {
    public:
        std::string     m_name;
        frame_t        *m_frame;
        point_t         m_origin;
        
    public:
        midget_t( char const *_name );
        virtual ~midget_t() {}

        // Shorthand for the thing passed to the draw callback.
        typedef ::Cairo::RefPtr<::Cairo::Context> cairo_context_t;

        //--------------------------------------------------------------
        // Draw with Cairo on the underlying drawing area.
        //
        virtual bool draw( const cairo_context_t &cr ) = 0;

    };



    //******************************************************************
    //
    //  A container of Midgets, useful for implementing meters, dials,
    //  and other screen representations where several Midgets need to
    //  cooperate.
    //
    //******************************************************************
    class midget_list_t : public std::list <midget_t *> {
    public:
        midget_list_t::iterator find( std::string &name );
    };
    
}

