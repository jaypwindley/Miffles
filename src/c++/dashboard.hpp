// -----------------------------------------------------------------------
//  File:              dashboard.h
//  Description:       Miffles dashboard collection of meters
//  Author:            Jay Windley <jwindley>
//  Created:           Mon Mar 30 21:25:41 2015
//  Copyright:         (c) 2015 Jay Windley
//                     All rights reserved.
// -----------------------------------------------------------------------

#ifndef __MIFFLES_DASHBOARD___
#define __MIFFLES_DASHBOARD___

#include <string>
#include <list>

#include "types.h"

namespace Miffles {

    class Frame;
    typedef std::list< Frame * > Frame_List;
    
    //******************************************************************
    //
    //  Base class for top-level Miffles GUI programs -- anything that
    //  opens a window and paints pixels on a screen.
    //
    //******************************************************************
    class Dashboard
    {
    public:
        Frame_List      *m_frames;
        
    public:
        Dashboard();
        virtual ~Dashboard();


        //--------------------------------------------------------------
        // Add a Frame to the dashboard.
        void add( Point _origin, Frame *f );

        //--------------------------------------------------------------
        // Return an Extent representing the total width and height of
        // all the contained Frames.
        //
        Extent extent( void );
    };
    
}

#endif /*__MIFFLES_DASHBOARD___*/
