// -----------------------------------------------------------------------
//  File:              indicators.hpp
//  Description:       Miscellaneous Miffles indicators
//  Author:            Jay Windley <jwindley>
//  Created:           Mon Mar 30 23:44:21 2015
//  Copyright:         (c) 2015 Jay Windley
//                     All rights reserved.
// -----------------------------------------------------------------------

#pragma once

#include <gtkmm.h>
#include "indicator.hpp"

namespace miffles {


    //******************************************************************
    //
    //  The most basic radial indicator.  Simply draws a line of the
    //  given length.
    //
    //******************************************************************
    class basic_needle_indicator_t : public indicator_t {
    public:
        double m_length;
        double m_thick;
        
    public:
        basic_needle_indicator_t( char const *_name );
        
        virtual bool draw( const midget_t::cairo_context_t &cr );
    };


    //******************************************************************
    //
    //******************************************************************
    class basic_pointer_indicator_t : public indicator_t {
    public:
        double m_thick;

    public:
        basic_pointer_indicator_t( char const *_name );

        virtual bool draw( const midget_t::cairo_context_t &cr );
    };
}
