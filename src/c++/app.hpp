// -----------------------------------------------------------------------
//  File:              app.h
//  Description:       Miffles application class
//  Author:            Jay Windley <jwindley>
//  Created:           Mon Mar 30 21:24:32 2015
//  Copyright:         (c) 2015 Jay Windley
//                     All rights reserved.
// -----------------------------------------------------------------------

#pragma once

#include <assert.h>
#include <gtkmm.h>
#include <string>


namespace miffles {

    class tickable_czar_t;
    class dashboard_t;
    class input_demultiplexer_t;

    //******************************************************************
    //
    //  Base class for top-level applications.  Also an abstract factory
    //  for some of the auxiliary classes that require specialization
    //  according to the toolkit.
    //
    //******************************************************************
    class app_t {

    public:
        static const char                      *domain;

        dashboard_t                            *m_dashboard;
        tickable_czar_t                        *m_tickables;
        input_demultiplexer_t                  *m_demux;

    protected:
        Glib::RefPtr<Gtk::Application>          m_gtk_app;
        Gtk::Window                            *m_window;

    private:
        static miffles::app_t                  *m_me;

    private:
        app_t( int argc, char **argv, char const *title );

    public:
        virtual ~app_t();


        //--------------------------------------------------------------
        // Create an application using the given command line and title.
        //
        static void create( int argc, char **argv, char const *title );


        //--------------------------------------------------------------
        // Retrieve the singleton App instance.
        //
        static miffles::app_t *app( void );

        //--------------------------------------------------------------
        // Add a file descriptor or a named file as an input source to
        // be polled as part of the application main loop.
        //
        void add_input( int fd );
        void add_input( char const *filename );
        
        //--------------------------------------------------------------
        // Resolve all the application parameters and then realize the
        // widgets and windows.
        //
        virtual int run( void );

    private:
        bool handle_IO( Glib::IOCondition condition,
                        Glib::RefPtr<Glib::IOChannel> channel );

    };

}
