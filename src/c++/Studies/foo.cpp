#include <gtkmm.h>
// -----------------------------------------------------------------------
//  File:              foo.cpp
//  Description:       Real-time clock in C++
//  Author:            Jay Windley <jwindley>
//  Created:           Mon Mar  9 22:48:38 2015
//  Copyright:         (c) 2015 Jay Windley
//                     All rights reserved.
// -----------------------------------------------------------------------

#include <iostream>
#include <time.h>



class Clock : public Gtk::DrawingArea
{
public:
    Clock( int width, int height );
    virtual ~Clock() {};

protected:
    virtual bool on_draw( const Cairo::RefPtr<Cairo::Context>& cr );
    virtual bool on_tick( void );

private:
    int m_speedy;
    int m_width;
    int m_height;

    //------------------------------------------------------------------
    // Transform the canvas so that the origin is in the center,
    // positive Y is up, and the square extent is (-1,1).
    //
    void normalize_canvas( const Cairo::RefPtr<Cairo::Context> &cr ) {
        cr->scale( m_width / 2.0, m_height / -2.0 );
        cr->translate( 1.0, -1.0 );
    }
};



//----------------------------------------------------------------------
// The Clock object is also the target for the timer signal, so connect
// the timer tick function to the 1/100 second timer signal.
//
Clock::Clock( int width, int height ) :
    m_width( width ),
    m_height( height )
{
    Glib::signal_timeout().connect( sigc::mem_fun( *this,
                                                   &Clock::on_tick ),
                                    10 );    
}


//----------------------------------------------------------------------
// Clear the window to black.
static void clear_to_black( const Cairo::RefPtr<Cairo::Context>& cr )
{
    cr->set_source_rgb( 0, 0, 0 );
    cr->rectangle( -1.0, -1.0, 2.0, 2.0 );
    cr->fill();
}



#define PI 3.14159

//----------------------------------------------------------------------
// Convert a fraction of a circle to a clockwise angle in radians.
//
static float fraction_to_radians( float frac )
{
    return frac * ( -2.0 * PI );
}


//----------------------------------------------------------------------
// Draw the clock.
//
bool Clock::on_draw( const Cairo::RefPtr<Cairo::Context>& cr )
{
    float ang;

    // Get the time of day.
    struct tm *tm;
    time_t t = time( NULL );
    tm = localtime( &t );

    // Set up the canvas.
    normalize_canvas( cr );
    clear_to_black( cr );

    // Minute hand.
    float min_frac = tm->tm_min / 60.0;
    ang = fraction_to_radians( min_frac );
    cr->rotate( ang );
    cr->set_source_rgb( 1, 1, 1 );
    cr->set_line_width( 0.04 );
    cr->move_to( 0, 0 );
    cr->line_to( 0, 0.85 );
    cr->stroke();
    cr->rotate( -ang );

    // Hour hand, adjusted for partial hour movement.
    ang = fraction_to_radians( tm->tm_hour % 12 ) / 12.0 + min_frac / 12.0;
    cr->rotate( ang );
    cr->set_line_width( 0.05 );
    cr->move_to( 0, 0 );
    cr->line_to( 0, 0.45 );
    cr->stroke();
    cr->rotate( -ang );

    // Second hand.
    ang = fraction_to_radians( tm->tm_sec / 60.0 );
    cr->rotate( ang );
    cr->set_source_rgb( 1, 0.75, 0.80 );
    cr->set_line_width( 0.01 );
    cr->move_to( 0, -0.1 );
    cr->line_to( 0, 0.95 );
    cr->stroke();
    cr->rotate( -ang );

    // 1-second sweep hand.
    ang = fraction_to_radians( m_speedy / 100.00 );
    cr->set_source_rgb( 1, 0, 0 );
    cr->rotate( ang );
    cr->move_to( 0, 0 );
    cr->line_to( 0, 0.3 );
    cr->stroke();
    cr->rotate( -ang );
    
    return true;
}


//----------------------------------------------------------------------
// Signal handler for the timer signal.
//
bool Clock::on_tick( void )
{
    // If there's no window, stop the timer.
    Glib::RefPtr<Gdk::Window> win = get_window();
    if ( ! win ) return false;

    // Force a redraw by invalidating the entire canvas.
    Gdk::Rectangle r( 0, 0,
                      get_allocation().get_width(),
                      get_allocation().get_height() );
    win->invalidate_rect( r, false );

    // Advance the sweep hand.
    m_speedy = (m_speedy + 1) % 100;
    return true;
}



int main( int argc, char **argv )
{
    static const int width  = 480;
    static const int height = 480;

    // Create the top-level widget.
    Glib::RefPtr<Gtk::Application> app =
        Gtk::Application::create( argc, argv,
                                  "com.monkeygiblets.miffles" );

    Gtk::Window window;
    window.set_default_size( width, height );
    window.set_title( "Miffles" );

    Clock c( width, height );

    // Connect the drawing area and map it.
    window.add( c );
    window.show_all();

    // Run the application main loop.
    return app->run( window );
}
