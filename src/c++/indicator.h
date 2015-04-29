// -----------------------------------------------------------------------
//  File:              indicator.h
//  Description:       Miffles Bugs, Marks, and Indicators
//  Author:            Jay Windley <jwindley>
//  Created:           Mon Mar 30 23:53:06 2015
//  Copyright:         (c) 2015 Jay Windley
//                     All rights reserved.
// -----------------------------------------------------------------------

#ifndef __MIFFLES_INDICATOR_H__
#define __MIFFLES_INDICATOR_H__

#include <string>
#include "midget.h"
#include "settable.h"

namespace Miffles {

    class Scale;
    class Sweep;

    //******************************************************************
    //
    //   A Mark is a point on a scale.
    //
    //   A point that is tied to a measured variable is an Indicator.  A
    //   point that is arbitrarily defined is a Bug.
    //
    //******************************************************************
    class Mark : public Midget, public Settable {

    public:
        Scale           *m_scale;
        Sweep           *m_sweep;
        
    public:

        //
        // Caller owns the memory for _scale.  Mark object owns the
        // memory for _sweep.
        //
        
        Mark( char const *_name );
        virtual ~Mark() {}


        //--------------------------------------------------------------
        // Set the value of the Mark.  _value is in Domain coordinates.
        // Any Sweep attached to this Mark is taken into account.
        //
        virtual void set( double value );

        //--------------------------------------------------------------
        // Return the current value of the Mark in Scale coordinates,
        // not Domain coordinates.
        //
        double fraction( void );

    };



    
    //******************************************************************
    //
    // The Indicator is the traditional needle that points to a value on
    // a visual scale, typically located on the interior of a radial
    // meter or on the dominant side (if any) of a linear indicator.  It
    // is the primary visual indication of a metered variable.
    //
    //******************************************************************
    //
    typedef Mark Indicator;


    
    //******************************************************************
    //
    // The Bug identifies a special value on the visual scale, such as
    // peak values, limits, or user-settable values.  While it may be
    // tied to a process variable, this is not necessary.
    //
    //******************************************************************
    //
    typedef Mark Bug;    
}

#endif /*__MIFFLES_INDICATOR_H__*/
