// -----------------------------------------------------------------------
//  File:              graduation.h
//  Description:       Miffles Graduation, marks on a meter
//  Author:            Jay Windley <jwindley>
//  Created:           Tue Mar 31 18:51:55 2015
//  Copyright:         (c) 2015 Jay Windley
//                     All rights reserved.
// -----------------------------------------------------------------------

#ifndef __MIFFLES_GRADUATION_H__
#define __MIFFLES_GRADUATION_H__

#include "midget.h"

namespace Miffles {

    class Scale;
    class Field;
    
    //******************************************************************
    //
    //  Visually represents a Scale within the associated Field.
    //
    class Graduation : public Midget {

    public:
        Scale *m_scale;
        Field *m_field;

        // I can make the case that this should point to the enclosing
        // Meter, solely so that if changes occur in Field or Scale they
        // are not stale here in this class.  The problem is that a
        // Meter can have more than one Scale.

    public:
        Graduation( char const * _name );

        virtual bool draw( const Cairo_Context &cr );        
    };
    
}

#endif /*__MIFFLES_GRADUATION_H__*/
