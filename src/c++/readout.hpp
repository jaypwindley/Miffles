// -----------------------------------------------------------------------
//  File:              readout.hpp
//  Description:       Miffles numerical readout
//  Author:            Jay Windley <jwindley>
//  Created:           Fri Apr 10 13:03:14 2015
//  Copyright:         (c) 2015 Jay Windley
//                     All rights reserved.
// -----------------------------------------------------------------------

#pragma once

#include "label.hpp"
#include "settable.hpp"

namespace miffles {

    //******************************************************************
    //
    //  Numerical (and later, possibly textual) readout of a
    //  measurement.
    //
    //******************************************************************
    class readout_t : public label_t, public settable_t {
    public:
        // XXX Figure out the best way to make this sweepable.
        // XXX Label should have an anchor.
        double m_value;
    public:
        readout_t( const char *_name );
        virtual ~readout_t() {}
        virtual void set( double _value ) { m_value = _value; }
        virtual bool draw( const cairo_context_t &cr );
    };

}
