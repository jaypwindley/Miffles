// -----------------------------------------------------------------------
//  File:              field.h
//  Description:       Miffles Field, the visual extent of a Meter
//  Author:            Jay Windley <jwindley>
//  Created:           Mon Mar 30 23:47:50 2015
//  Copyright:         (c) 2015 Jay Windley
//                     All rights reserved.
// -----------------------------------------------------------------------

#pragma once

namespace miffles {


    //******************************************************************
    //
    //   A Field represents the visual extent of a measurement on the
    //   screen. It relates to a Scale in the sense that the origin and
    //   extent of the Scale are mapped to the visual origin and visual
    //   extent of the Field.
    //
    //******************************************************************
    class field_t {

    public:
        double          m_origin;
        double          m_extent;
        bool            m_has_peg;
        
    public:        
        field_t( double _origin, double _extent ) :
            m_origin( _origin ),
            m_extent( _extent ),
            m_has_peg( false )
        {
        }
        
        virtual ~field_t()
        {
        }
    };



    //******************************************************************
    //
    //   A linear field is a horizontally or vertically oriented region
    //   where measurements are represented along a line.
    //
    //******************************************************************
    class linear_field_t : public field_t {
        
    public:        
        enum orientation_t { VERTICAL, HORIZONTAL };

    public:
        enum orientation_t m_orientation;

    public:
        
        linear_field_t( double _origin,
                        double _extent,
                        enum orientation_t _orientation ) :
            field_t( _origin, _extent ),
            m_orientation( _orientation )
        {
        }

    };


    //******************************************************************
    //
    //   The radial coordinate system is the standard trigonometry
    //   system.  Zero is the positive x-axis (3 o'clock position).
    //   Angles in the positive direction rotate toward the positive
    //   y-axis (counter-clockwise).
    //
    //   If m_has_peg is true, bugs and indicators are not rendered
    //   beyond m_rads_origin + m_extent.  If false, bugs and indicators
    //   will render beyond that limit, extrapolated from the scale.
    //
    class radial_field_t : public field_t {

        
    public:
        radial_field_t( double _rads_origin,
                        double _rads_extent,
                        bool   _has_peg = true ) :
            field_t( _rads_origin, _rads_extent )
        {
        }
        
        
        virtual ~radial_field_t() {}
    };
}
