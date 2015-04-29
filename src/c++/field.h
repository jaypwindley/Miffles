// -----------------------------------------------------------------------
//  File:              field.h
//  Description:       Miffles Field, the visual extent of a Meter
//  Author:            Jay Windley <jwindley>
//  Created:           Mon Mar 30 23:47:50 2015
//  Copyright:         (c) 2015 Jay Windley
//                     All rights reserved.
// -----------------------------------------------------------------------

#ifndef __MIFFLES_FIELD_H__
#define __MIFFLES_FIELD_H__


namespace Miffles {


    //******************************************************************
    //
    //   A Field represents the visual extent of a measurement on the
    //   screen. It relates to a Scale in the sense that the origin and
    //   extent of the Scale are mapped to the visual origin and visual
    //   extent of the Field.
    //
    //******************************************************************
    class Field {

    public:
        double          m_origin;
        double          m_extent;
        bool            m_has_peg;
        
    public:        
        Field( double _origin, double _extent ) :
            m_origin( _origin ),
            m_extent( _extent ),
            m_has_peg( false )
        {
        }
        
        virtual ~Field()
        {
        }
    };



    //******************************************************************
    //
    //   A linear field is a horizontally or vertically oriented region
    //   where measurements are represented along a line.
    //
    //******************************************************************
    class Linear_Field : public Field {
        
    public:        
        enum Orientation { VERTICAL, HORIZONTAL };

    public:
        enum Orientation m_orientation;

    public:
        
        Linear_Field( double _origin,
                      double _extent,
                      enum Orientation _orientation ) :
            Field( _origin, _extent ),
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
    class Radial_Field : public Field {

        
    public:
        Radial_Field( double _rads_origin,
                      double _rads_extent,
                      bool   _has_peg = true ) :
            Field( _rads_origin, _rads_extent )
        {
        }
        
        
        virtual ~Radial_Field() {}
    };
}

#endif /*__MIFFLES_FIELD_H__*/
