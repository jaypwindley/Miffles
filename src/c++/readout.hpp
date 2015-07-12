// -----------------------------------------------------------------------
//  File:              readout.h
//  Description:       Miffles numerical readout
//  Author:            Jay Windley <jwindley>
//  Created:           Fri Apr 10 13:03:14 2015
//  Copyright:         (c) 2015 Jay Windley
//                     All rights reserved.
// -----------------------------------------------------------------------

#ifndef __MIFFLES_READOUT_H__
#define __MIFFLES_READOUT_H__

#include "label.h"
#include "settable.h"

namespace Miffles {

    //******************************************************************
    //
    //  Numerical (and later, possibly textual) readout of a
    //  measurement.
    //
    //******************************************************************
    class Readout : public Label, public Settable {
    public:
        // XXX Figure out the best way to make this sweepable.
        // XXX Label should have an anchor.
        double m_value;
    public:
        Readout( const char *_name );
        virtual ~Readout() {}
        virtual void set( double _value ) { m_value = _value; }
        virtual bool draw( const Cairo_Context &cr );
    };

}

#endif /*__MIFFLES_READOUT_H__*/
