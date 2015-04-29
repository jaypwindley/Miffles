// -----------------------------------------------------------------------
//  File:              app.cpp
//  Description:       Miffles app
//  Author:            Jay Windley <jwindley>
//  Created:           Mon Mar 30 21:17:41 2015
//  Copyright:         (c) 2015 Jay Windley
//                     All rights reserved.
// -----------------------------------------------------------------------

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <gtkmm.h>
#include <glibmm/iochannel.h>
#include <string>
#include "app.h"
#include "dashboard.h"
#include "tickable.h"
#include "input_demux.h"


const char *Miffles::App::domain = "com.monkeygiblets.miffles";
Miffles::App *Miffles::App::m_me = NULL;


Miffles::App::App( int argc, char **argv, char const *title ) :
    m_dashboard( new Dashboard() ),
    m_tickables( new Tickable_Czar( m_dashboard ) ),
    m_demux( new Input_Demultiplexer )
{
    // Create the toolkit app.
    m_gtk_app = Gtk::Application::create( argc,
                                          argv,
                                          domain );

    // Put a top-level window in it.
    m_window = new Gtk::Window();

    // Set default size now to something just big enough to see.
    m_window->set_default_size( 128, 128 );
    m_window->set_title( title );
}



Miffles::App::~App()
{
    delete m_window;
    delete m_dashboard;
    delete m_tickables;
}


Miffles::App *Miffles::App::app( void )
{
    assert( m_me );
    return Miffles::App::m_me;
}



void
Miffles::App::create( int argc, char **argv, char const *title )
{
    if ( m_me ) return;
    m_me = new ::Miffles::App( argc, argv, title );
}


void Miffles::App::add_input( int fd )
{
    if ( fd < 0 ) return;

    // Create an IOChannel out of the file descriptor and arrange for it
    // to be passed to the IO handler function.
    //
    auto channel = Glib::IOChannel::create_from_fd( fd );
    auto slot = sigc::bind( sigc::mem_fun( *this,
                                           &Miffles::App::handle_IO ),
                            channel );

    // Connect the IO handler function to the Glib IO signal.
    Glib::signal_io().connect( slot, fd, Glib::IO_IN );
}


void Miffles::App::add_input( char const *filename )
{
    // Open the named file and add the file descriptor.  O_NONBLOCK must
    // be specified in case the named file is an unopened named pipe.
    //
    return add_input( open( filename, O_RDONLY | O_NONBLOCK ) );
}


int Miffles::App::run( void )
{
    assert( m_gtk_app );
            
    // Accumulate the application size.
    Extent e = m_dashboard->extent();
    m_window->set_default_size( e.width(), e.height() );

    // Add all the Midgets to the top-level window.
    for ( auto i = m_dashboard->m_frames->begin();
          i != m_dashboard->m_frames->end();
          ++i ) {
        m_window->add( *( (Gtk::DrawingArea *) (*i) ) );
    }                

    // Activate all the widgets.
    m_window->show_all();

    // Start the timers.
    m_tickables->link_timers();

    // Run the main loop.
    return m_gtk_app->run( *m_window );
}


bool Miffles::App::handle_IO( Glib::IOCondition condition,
                              Glib::RefPtr<Glib::IOChannel> channel )
{
    Glib::ustring buf;

    switch ( condition ) {

    case Glib::IO_IN:
        (void) channel->read_line( buf );
        m_demux->dispatch( buf );
        break;
        
    default:
        break;
    }

    return true;
}
