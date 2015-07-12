// -----------------------------------------------------------------------
//  File:              meter.hpp
//  Description:       Miffles Meter, coordinates Midgets in a Field.
//  Author:            Jay Windley <jwindley>
//  Created:           Tue Mar 31 18:33:12 2015
//  Copyright:         (c) 2015 Jay Windley
//                     All rights reserved.
// -----------------------------------------------------------------------

#pragma once

#include <list>
#include <string>
#include "frame.hpp"
#include "midget.hpp"

namespace miffles {

    class field_t;
    class linear_field_t;
    class radial_field_t;

    //******************************************************************
    //
    //  A Meter is a specialized Field that considers a contained list
    //  of Midgets as a coordinated set of presentation elements.
    //
    //******************************************************************
    class meter_t : public frame_t {

    public:
        field_t           *m_field;
        
    public:
        meter_t( char const *_name );
    };



    //******************************************************************
    //
    //  Meter in which the indicators travel along a linear path, either
    //  horizontal or vertical.
    //
    //******************************************************************
    class linear_meter_t : public meter_t {

    public:
        linear_meter_t( char const *_name );
        virtual void set_field( linear_field_t *f );
    };



    //******************************************************************
    //
    //  Meter in which the indicators travel around the perimeter of a
    //  (semi-)circle.
    //
    //******************************************************************
    class radial_meter_t : public meter_t {

    public:
        radial_meter_t( char const * _name );
        virtual void set_field( radial_field_t *f );
    };
}
