// -----------------------------------------------------------------------
//  File:              tickable.hpp
//  Description:       Miffles timer-based objects
//  Author:            Jay Windley <jwindley>
//  Created:           Mon Mar 30 21:48:18 2015
//  Copyright:         (c) 2015 Jay Windley
//                     All rights reserved.
// -----------------------------------------------------------------------

#pragma once

#include <map>
#include <list>


namespace miffles {

    class dashboard_t;
    class frame_t;
    
    //******************************************************************
    //
    //  Base class for any feature that requires updates based solely on
    //  clock ticks,
    //
    //******************************************************************
    class tickable_t {

    public:
        const static unsigned int DEFAULT_HERTZ;
        
    public:
        unsigned int    m_hertz;
        
    public:
        tickable_t( unsigned int _hertz = DEFAULT_HERTZ ):
            m_hertz( _hertz )
        {
        }
        
        virtual ~tickable_t()
        {
        }

        //--------------------------------------------------------------
        // Call at intervals.  Derived classes implement this method to
        // update themselves at each relevant clock tick.  Return true
        // if the area containing this object should be redrawn as a
        // result of the tick.
        //
        virtual bool tick() = 0;
    };



    
    //******************************************************************
    //
    //   Aggregates lists of tickable objects such that their
    //   refreshment method tick() can be called by a single timer
    //   handler function.
    //
    //   Caller owns the objects added to this list.
    //
    //******************************************************************

    typedef std::pair<tickable_t *, frame_t *> tickable_list_element_t;
    typedef std::list<tickable_list_element_t> tickable_list_t;
    
    class tickable_czar_t : public std::map<int, tickable_list_t> {

    public:
        dashboard_t       *m_dashboard;
        
    public:
        tickable_czar_t( dashboard_t *_dashboard );
        virtual ~tickable_czar_t()
        {
        }

    public:

        //--------------------------------------------------------------
        // Add a Tickable to this Czar.  Force a redraw of the given
        // Frame if the tick results in a change in the appearance of
        // the Frame.  If defer is true, do not rejigger the toolkit
        // callbacks as a result of this addition.
        //
        void add( tickable_t *t, frame_t *f, bool defer = true );


        //
        // XXX Flesh out list- and map-handling code for more flexible
        // Tickable handling.  This requires the ability to identify
        // Tickables by some external criteria, which might mean making
        // them Midgets in order to centralize Midget_List code.
        //
        

        //--------------------------------------------------------------
        // Concrete derivations should implement this method to connect
        // all the contained Tickables to the toolkit at the appropriate
        // refresh rate.
        //
        // The closure data to be passed to the timer handler function
        // is a pointer to the "second" of the inherited std::map, the
        // Tickable_List type defined above.
        //
        virtual void link_timers( void );
   

        //--------------------------------------------------------------
        // Suitable for installation as a timer handler function,
        // passing a Tickable_List as the closure data.
        //
        // XXX handle closure to pass this
        //
        bool on_timer( tickable_list_t &me );
    };
}
