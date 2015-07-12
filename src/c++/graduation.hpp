// -----------------------------------------------------------------------
//  File:              graduation.hpp
//  Description:       Miffles Graduation, marks on a meter
//  Author:            Jay Windley <jwindley>
//  Created:           Tue Mar 31 18:51:55 2015
//  Copyright:         (c) 2015 Jay Windley
//                     All rights reserved.
// -----------------------------------------------------------------------

#pragma once

#include "midget.hpp"

namespace miffles {

    class scale_t;
    class field_t;
    
    //******************************************************************
    //
    //  Visually represents a Scale within the associated Field.
    //
    class graduation_t : public midget_t {

    public:
        scale_t *m_scale;
        field_t *m_field;

        // I can make the case that this should point to the enclosing
        // Meter, solely so that if changes occur in Field or Scale they
        // are not stale here in this class.  The problem is that a
        // Meter can have more than one Scale.

    public:
        graduation_t( char const * _name );

        virtual bool draw( const cairo_context_t &cr );        
    };
    
}

