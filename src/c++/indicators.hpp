// -----------------------------------------------------------------------
//  File:              indicators.h
//  Description:       Miscellaneous Miffles indicators
//  Author:            Jay Windley <jwindley>
//  Created:           Mon Mar 30 23:44:21 2015
//  Copyright:         (c) 2015 Jay Windley
//                     All rights reserved.
// -----------------------------------------------------------------------

#ifndef __MIFFLES_INDICATORS_H__
#define __MIFFLES_INDICATORS_H__

#include <gtkmm.h>

#include "indicator.h"

namespace Miffles {


    //******************************************************************
    //
    //  The most basic radial indicator.  Simply draws a line of the
    //  given length.
    //
    //******************************************************************
    class Basic_Needle_Indicator : public Indicator {
    public:
        double m_length;
        double m_thick;
        
    public:
        Basic_Needle_Indicator( char const *_name );
        
        virtual bool draw( const Midget::Cairo_Context &cr );
    };


    //******************************************************************
    //
    //******************************************************************
    class Basic_Pointer_Indicator : public Indicator {
    public:
        double m_thick;

    public:
        Basic_Pointer_Indicator( char const *_name );

        virtual bool draw( const Midget::Cairo_Context &cr );
    };
}


#endif /*__MIFFLES_INDICATORS_H__*/
