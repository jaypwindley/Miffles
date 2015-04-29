// -----------------------------------------------------------------------
//  File:              Clock.java
//  Description:       Real-time clock in Java
//  Author:            Jay Windley <jwindley>
//  Created:           Mon Mar  9 23:20:45 2015
//  Copyright:         (c) 2015 Jay Windley
//                     All rights reserved.
// -----------------------------------------------------------------------


import org.freedesktop.cairo.Context;

import org.gnome.gdk.Event;
import org.gnome.gtk.DrawingArea;
import org.gnome.gtk.Gtk;
import org.gnome.gtk.Widget;
import org.gnome.gtk.Window;

import java.lang.Math;
import java.util.*;



public class Clock extends DrawingArea implements Widget.Draw {

    //------------------------------------------------------------------
    // Since we can't multiply-inherit, this inner object receives the
    // timer signal.
    //
    class Ticker extends TimerTask {
	private Clock m_app;
	
	public Ticker( Clock app ) { m_app = app; }
	
	public void run() {
	    // Update the sweep hand and signal a redraw.
	    m_app.m_speedy = ( m_app.m_speedy + 1 ) % 100;
	    queueDraw();
	}
    }

    
    static final long serialVersionUID = 1;


    private Ticker   m_ticker;
    public  int      m_speedy;
    private int      m_width;
    private int      m_height;
    

    
    public Clock( int width, int height ) {
	m_width  = width;
	m_height = height;

	// Instantiate the inner timer signal-handling object.
	m_ticker = new Ticker( this );
	m_speedy = 1;

	// Have to register this object with the signal dispather.
	connect( this );

	// Create the Java timer and schedule it for 1/100 second.
	Timer timer = new Timer();
	timer.schedule( m_ticker, 10, 10 );
    }


    //------------------------------------------------------------------
    // Transform the canvas so that the origin is in the center,
    // positive Y is up, and the square extent is (-1,1).
    //
    private void normalize_canvas( Context cr ) {
	cr.scale( m_width / 2.0, m_height / -2.0 );
	cr.translate( 1.0, -1.0 );
    }


    //------------------------------------------------------------------
    // Clear the screen to black.
    //
    private void clear_to_black( Context cr ) {
	cr.setSource( 0.0, 0.0, 0.0 );
	cr.rectangle( -1.0, -1.0, 2.0, 2.0 );
	cr.fill();
    }


    //------------------------------------------------------------------
    // Convert a fraction of a circle into a clockwise angle in radians.
    //
    public double fraction_to_radians( double f ) {
	return f * ( -2.0 * Math.PI );
    }


    //------------------------------------------------------------------
    // Draw the clock.
    //
    // Apparently the Java culture insists on renaming all the standard
    // Cairo calls in BiCaps.  This is why we hate you.
    //
    public boolean onDraw( Widget w, Context cr ) {
	normalize_canvas( cr );
	clear_to_black( cr );

	// Get the time of day.  Because "Calendar" is that thing.
	Calendar tm = Calendar.getInstance();

	// Minute hand.
	double min_frac = tm.get( Calendar.MINUTE ) / 60.0;
	double ang = fraction_to_radians( min_frac );
	cr.rotate( ang );
	cr.setSource( 1, 1, 1 );
	cr.setLineWidth( 0.04 );
	cr.moveTo( 0.0, 0.0 );
	cr.lineTo( 0.0, 0.85 );
	cr.stroke();
	cr.rotate( -ang );

	// Hour hand, including the increment from the minute hand.
	ang = fraction_to_radians( ( ( tm.get( Calendar.HOUR ) % 12 ) / 12.0 )
				   + ( min_frac / 12.0 ) );
	cr.rotate( ang );
	cr.setLineWidth( 0.05 );
	cr.moveTo( 0.0, 0.0 );
	cr.lineTo( 0.0, 0.45 );
	cr.stroke();
	cr.rotate( -ang );

	// Second hand.
	ang = fraction_to_radians( tm.get( Calendar.SECOND ) / 60.0 );
	cr.rotate( ang );
	cr.setSource( 1.0, 0.75, 0.80 );
	cr.setLineWidth( 0.01 );
	cr.moveTo( 0.0, -0.1 );
	cr.lineTo( 0.0, 0.95 );
	cr.stroke();
	cr.rotate( -ang );

	// 1/100 second sweep.
	ang = fraction_to_radians( m_speedy / 100.0 );
	cr.rotate( ang );
	cr.setSource( 1.0, 0.0, 0.0 );
	cr.moveTo( 0.0, 0.0 );
	cr.lineTo( 0.0, 0.3 );
	cr.stroke();
	cr.rotate( -ang );

	return true;
    }

    
    public static void main( String[] args ) {
	final int wid = 480;
	final int ht  = 480;
	
	Gtk.init( args );
	Window w = new Window();
	Clock b = new Clock( wid, ht);
	w.add( b );
	w.setTitle( "Miffles" );
	w.setDefaultSize( wid, ht );
	w.connect( new Window.DeleteEvent() {
		public boolean onDeleteEvent( Widget source, Event event ) {
		    Gtk.mainQuit();
		    return false;
		}
	    }
	    );
	w.showAll();
	Gtk.main();
    }

}
