// -----------------------------------------------------------------------
//  File:              dashboard.h
//  Description:       Miffles dashboard collection of meters
//  Author:            Jay Windley <jwindley>
//  Created:           Mon Mar 30 21:25:41 2015
//  Copyright:         (c) 2015 Jay Windley
//                     All rights reserved.
// -----------------------------------------------------------------------

#pragma once

#include <string>
#include <list>
#include "types.hpp"

namespace miffles {

    class frame_t;
    typedef std::list<frame_t *> frame_list_t;
    
    //******************************************************************
    //
    //  Base class for top-level Miffles GUI programs -- anything that
    //  opens a window and paints pixels on a screen.
    //
    //******************************************************************
    class dashboard_t
    {
    public:
        frame_list_t      *m_frames;
        
    public:
        dashboard_t();
        virtual ~dashboard_t();


        //--------------------------------------------------------------
        // Add a frame to the dashboard.
        void add( point_t _origin, frame_t *f );

        //--------------------------------------------------------------
        // Return an Extent representing the total width and height of
        // all the contained Frames.
        //
        extent_t extent( void );
    };
    
}

