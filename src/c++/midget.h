// -----------------------------------------------------------------------
//  File:              midget.h
//  Description:       Miffles Midget, drawn primitive
//  Author:            Jay Windley <jwindley>
//  Created:           Tue Mar 31 12:06:54 2015
//  Copyright:         (c) 2015 Jay Windley
//                     All rights reserved.
// -----------------------------------------------------------------------

#ifndef __MIFFLES_MIDGET_H__
#define __MIFFLES_MIDGET_H__

#include <gtkmm.h>
#include <assert.h>
#include <list>
#include <string>

#include "types.h"

namespace Miffles {

    class Frame;
    
    //******************************************************************
    //
    //  A Miffles widget.
    //
    //******************************************************************
    class Midget
    {
    public:
        std::string     m_name;
        Frame          *m_frame;
        Point           m_origin;
        
    public:
        Midget( char const *_name );
        virtual ~Midget() {}

        // Shorthand for the thing passed to the draw callback.
        typedef ::Cairo::RefPtr<::Cairo::Context> Cairo_Context;

        //--------------------------------------------------------------
        // Draw with Cairo on the underlying drawing area.
        //
        virtual bool draw( const Cairo_Context &cr ) = 0;

    };



    //******************************************************************
    //
    //  A container of Midgets, useful for implementing meters, dials,
    //  and other screen representations where several Midgets need to
    //  cooperate.
    //
    //******************************************************************
    class Midget_List : public std::list <Midget *> {
    public:
        Midget_List::iterator find( std::string &name );
    };
    
}


#endif /*__MIFFLES_MIDGET_H__*/
