// -----------------------------------------------------------------------
//  File:              settable.hpp
//  Description:       Miffles automatic Settable object
//  Author:            Jay Windley <jwindley>
//  Created:           Tue Apr  7 09:25:27 2015
//  Copyright:         (c) 2015 Jay Windley
//                     All rights reserved.
// -----------------------------------------------------------------------

#pragma once

#include <string>
#include <list>

namespace miffles {

    //******************************************************************
    //
    //  Encapsulates the methods for setting values of objects like
    //  Midgets or whatever.  By listening on a channel, a Settable can
    //  arrange for a channel decoder and demultipler to call the
    //  appropriate set() method automatically when data arrives on the
    //  channel.
    //
    //******************************************************************
    class settable_t {

    public:
        virtual ~settable_t() {}

        //--------------------------------------------------------------
        // Listen on a channel.  The channel demultiplexer will call the
        // appropriate set() method below for each channel on which data
        // arrives.  A Settable may listen on as many channels as it
        // wants.  The order in which channel information is
        // indeterminate.
        //
        void listen( const std::string &channel );

        //--------------------------------------------------------------
        // Set the value of whatever this thing is, according to
        // whatever the right data type is.  The subclass-specific
        // method implementation is responsible for signalling a redraw
        // if needed.
        //
        // XXX This is a terrible way to be polymorphic, so fix it.
        //
        virtual void set( std::string &val );
        virtual void set( void *thing      );
        virtual void set( bool is_on       );
        virtual void set( double value     );
    };

    typedef std::list<settable_t *> settable_list_t;
}
