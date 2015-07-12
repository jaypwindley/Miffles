// -----------------------------------------------------------------------
//  File:              annunciator.h
//  Description:       Miffles Annunciator, a simple indicator "light"
//  Author:            Jay Windley <jwindley>
//  Created:           Sun Apr  5 21:47:40 2015
//  Copyright:         (c) 2015 Jay Windley
//                     All rights reserved.
// -----------------------------------------------------------------------

#ifndef __MIFFLES_ANNUNCIATOR_H__
#define __MIFFLES_ANNUNCIATOR_H__

#include "midget.h"
#include "settable.h"

namespace Miffles {

    //******************************************************************
    //
    //  Annunciators are simple binary condition indicators, such as the
    //  "check engine" light in an automobile.  They are either on or
    //  off.
    //
    //******************************************************************
    class Annunciator : public Midget, public Settable {

    public:
        bool            m_is_on;
        
    public:
        Annunciator( char const *_name );
        virtual ~Annunciator() {}

        virtual void set( bool is_on );
        
        virtual bool draw( const Cairo_Context &cr );
        
    };


    
}

#endif /*__MIFFLES_ANNUNCIATOR_H__*/
