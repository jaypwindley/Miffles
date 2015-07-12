// -----------------------------------------------------------------------
//  File:              sweep.hpp
//  Description:       Sweep delay for meters
//  Author:            Jay Windley <jwindley>
//  Created:           Fri Mar 13 19:29:17 2015
//  Copyright:         (c) 2015 Jay Windley
//                     All rights reserved.
// -----------------------------------------------------------------------

#pragma once

#include "tickable.hpp"

namespace miffles {

    //******************************************************************
    //
    // Controls the sweep of indicators that do not change position
    // instantaneously. m_at, m_setpoint are in Scale-normalized
    // coordinates [0,..].  m_rate is normalized travel per second,
    // independent of update frequency.
    //
    //******************************************************************
    class sweep_t : public tickable_t {
        
    protected:
        double          m_setpoint;
        double          m_rate;

    private:
        double m_at;
        
    public:
        sweep_t( double _rate );
        virtual ~sweep_t()
        {
        }

        virtual double at( void ) const { return m_at; }

        //--------------------------------------------------------------
        // Is the indicator on par with the setpoint?  Use this function
        // to optimize whether redraws are needed.
        //
        virtual bool par( void ) const { return m_setpoint == m_at; }

        
        //--------------------------------------------------------------
        // Set a new setpoint.  This should be the post-scaled value
        // after the Scale transformation.
        //
        void set( double setpoint ) {
            m_setpoint = setpoint;
        }

        //--------------------------------------------------------------
        // Call every 1/Hz second to update the position of sweeping
        // indicators.
        //
        bool tick( void );

        
    };


    //******************************************************************
    //
    // A non-sweeping Sweep such that Meters etc. can use the Sweep
    // interface unviersally.
    //
    //******************************************************************
    class sweep_dummy_t : public sweep_t {
    public:
        sweep_dummy_t( double _val = 0.0 ) :
            sweep_t( 1.0 )
        {
            set( _val );
        }

        virtual ~sweep_dummy_t()
        {
        }

        virtual double at( void ) const { return m_setpoint; }
        virtual bool par( void ) const { return true; }        
    };
    
}
