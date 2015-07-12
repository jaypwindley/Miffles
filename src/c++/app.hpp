// -----------------------------------------------------------------------
//  File:              app.h
//  Description:       Miffles application class
//  Author:            Jay Windley <jwindley>
//  Created:           Mon Mar 30 21:24:32 2015
//  Copyright:         (c) 2015 Jay Windley
//                     All rights reserved.
// -----------------------------------------------------------------------

#ifndef __MIFFLES_APP_H__
#define __MIFFLES_APP_H__

#include <assert.h>
#include <gtkmm.h>
#include <string>


namespace Miffles {

    class Tickable_Czar;
    class Dashboard;
    class Input_Demultiplexer;

    //******************************************************************
    //
    //  Base class for top-level applications.  Also an abstract factory
    //  for some of the auxiliary classes that require specialization
    //  according to the toolkit.
    //
    //******************************************************************
    class App {

    public:
        static const char                      *domain;

        Dashboard                              *m_dashboard;
        Tickable_Czar                          *m_tickables;
        Input_Demultiplexer                    *m_demux;

    protected:
        Glib::RefPtr<Gtk::Application>          m_gtk_app;
        Gtk::Window                            *m_window;

    private:
        static Miffles::App                    *m_me;

    private:
        App( int argc, char **argv, char const *title );

    public:
        virtual ~App();


        //--------------------------------------------------------------
        // Create an application using the given command line and title.
        //
        static void create( int argc, char **argv, char const *title );


        //--------------------------------------------------------------
        // Retrieve the singleton App instance.
        //
        static Miffles::App *app( void );

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

#endif /*__MIFFLES_APP_H__*/
