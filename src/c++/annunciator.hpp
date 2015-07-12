// -----------------------------------------------------------------------
//  File:              annunciator.hpp
//  Description:       Miffles Annunciator, a simple indicator "light"
//  Author:            Jay Windley <jwindley>
//  Created:           Sun Apr  5 21:47:40 2015
//  Copyright:         (c) 2015 Jay Windley
//                     All rights reserved.
// -----------------------------------------------------------------------

#pragma once

#include "midget.hpp"
#include "settable.hpp"

namespace miffles {

    //******************************************************************
    //
    //  Annunciators are simple binary condition indicators, such as the
    //  "check engine" light in an automobile.  They are either on or
    //  off.
    //
    //******************************************************************
    class annunciator_t : public midget_t, public settable_t {

    public:
        bool            m_is_on;
        
    public:
        annunciator_t( char const *_name );
        virtual ~annunciator_t() {}

        virtual void set( bool is_on );
        
        virtual bool draw( const cairo_context_t &cr );
        
    };


    
}

