// -----------------------------------------------------------------------
//  File:              tickable.h
//  Description:       Miffles timer-based objects
//  Author:            Jay Windley <jwindley>
//  Created:           Mon Mar 30 21:48:18 2015
//  Copyright:         (c) 2015 Jay Windley
//                     All rights reserved.
// -----------------------------------------------------------------------

#ifndef __MIFFLES_TICKABLE_H__
#define __MIFFLES_TICKABLE_H__

#include <map>
#include <list>


namespace Miffles {

    class Dashboard;
    
    //******************************************************************
    //
    //  Base class for any feature that requires updates based solely on
    //  clock ticks,
    //
    //******************************************************************
    class Tickable {

    public:
        const static unsigned int DEFAULT_HERTZ;
        
    public:
        unsigned int    m_hertz;
        
    public:
        Tickable( unsigned int _hertz = DEFAULT_HERTZ ):
            m_hertz( _hertz )
        {
        }
        
        virtual ~Tickable()
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

    typedef std::list<Tickable *> Tickable_List;
    
    class Tickable_Czar : public std::map< int, Tickable_List > {

    public:
        Dashboard       *m_dashboard;
        
    public:
        Tickable_Czar( Dashboard *_dashboard );
        virtual ~Tickable_Czar()
        {
        }

    public:

        //--------------------------------------------------------------
        // Add a Tickable to this Czar.  If defer is true, do not
        // rejigger the toolkit callbacks as a result of this addition.
        //
        void add( Tickable *t, bool defer = true );


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
        // passing a Tickable_List as the closure.
        //
        // XXX handle closure to pass this
        //
        bool on_timer( Tickable_List &me );
    };
}

#endif /*__MIFFLES_TICKABLE_H__*/
