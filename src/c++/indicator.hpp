// -----------------------------------------------------------------------
//  File:              indicator.hpp
//  Description:       Miffles Bugs, Marks, and Indicators
//  Author:            Jay Windley <jwindley>
//  Created:           Mon Mar 30 23:53:06 2015
//  Copyright:         (c) 2015 Jay Windley
//                     All rights reserved.
// -----------------------------------------------------------------------

#include <string>
#include "midget.hpp"
#include "settable.hpp"

namespace miffles {

    class scale_t;
    class sweep_t;

    //******************************************************************
    //
    //   A Mark is a point on a scale.
    //
    //   A point that is tied to a measured variable is an Indicator.  A
    //   point that is arbitrarily defined is a Bug.
    //
    //******************************************************************
    class mark_t : public midget_t, public settable_t {

    public:
        scale_t         *m_scale;
        sweep_t         *m_sweep;
        
    public:

        //
        // Caller owns the memory for _scale.  Mark object owns the
        // memory for _sweep.
        //
        
        mark_t( char const *_name );
        virtual ~mark_t() {}


        //--------------------------------------------------------------
        // Set the value of the Mark.  _value is in Domain coordinates.
        // Any Sweep attached to this Mark is taken into account.
        //
        virtual void set( double value );

        //--------------------------------------------------------------
        // Return the current value of the Mark in Scale coordinates,
        // not Domain coordinates.
        //
        double fraction( void ) const;

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
    typedef mark_t indicator_t;


    
    //******************************************************************
    //
    // The Bug identifies a special value on the visual scale, such as
    // peak values, limits, or user-settable values.  While it may be
    // tied to a process variable, this is not necessary.
    //
    //******************************************************************
    //
    typedef mark_t bug_t;    
}
