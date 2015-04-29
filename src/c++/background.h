// -----------------------------------------------------------------------
//  File:              background.h
//  Description:       Miffles Frame backgrounds
//  Author:            Jay Windley <jwindley>
//  Created:           Fri Apr 10 12:57:46 2015
//  Copyright:         (c) 2015 Jay Windley
//                     All rights reserved.
// -----------------------------------------------------------------------

#ifndef __MIFFLES_BACKGROUND_H__
#define __MIFFLES_BACKGROUND_H__

#include "midget.h"
#include "types.h"

namespace Miffles {

    //******************************************************************
    //
    //  Background that fills with a constant color, default black.
    //
    //******************************************************************
    class Color_Background : public Midget {
    public:
        Miffles::Color m_color;
    public:
        Color_Background( char const *_name,
                          Color _color = Miffles::Color::Black );
        virtual ~Color_Background() {}
        virtual bool draw( const Midget::Cairo_Context &cr );
    };
    
}

#endif /*__MIFFLES_BACKGROUND_H__*/
