// -----------------------------------------------------------------------
//  File:              meter.h
//  Description:       Miffles Meter, coordinates Midgets in a Field.
//  Author:            Jay Windley <jwindley>
//  Created:           Tue Mar 31 18:33:12 2015
//  Copyright:         (c) 2015 Jay Windley
//                     All rights reserved.
// -----------------------------------------------------------------------

#ifndef __MIFFLES_METER_H__
#define __MIFFLES_METER_H__

#include <list>
#include <string>
#include "frame.h"
#include "midget.h"

namespace Miffles {

    class Field;
    class Linear_Field;
    class Radial_Field;

    //******************************************************************
    //
    //  A Meter is a specialized Field that considers a contained list
    //  of Midgets as a coordinated set of presentation elements.
    //
    //******************************************************************
    class Meter : public Frame {

    public:
        Field           *m_field;
        
    public:
        Meter( char const *_name );
    };



    //******************************************************************
    //
    //  Meter in which the indicators travel along a linear path, either
    //  horizontal or vertical.
    //
    //******************************************************************
    class Linear_Meter : public Meter {

    public:
        Linear_Meter( char const *_name );
        virtual void set_field( Linear_Field *f );
    };



    //******************************************************************
    //
    //  Meter in which the indicators travel around the perimeter of a
    //  (semi-)circle.
    //
    //******************************************************************
    class Radial_Meter : public Meter {

    public:
        Radial_Meter( char const * _name );
        virtual void set_field( Radial_Field *f );
    };
}

#endif /*__MIFFLES_METER_H__*/
