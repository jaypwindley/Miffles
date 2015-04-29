#!/usr/bin/python
# -----------------------------------------------------------------------
#  File:              foo.py
#  Description:       Real-time clock in Python
#  Author:            Jay Windley <jwindley>
#  Created:           Mon Mar  9 23:24:17 2015
#  Copyright:         (c) 2015 Jay Windley
#                     All rights reserved.
# -----------------------------------------------------------------------

import cairo
import sys
import time
from math           import pi
from gi.repository  import Gtk, GObject


class Clock( Gtk.Window ):

    def __init__( self ):
        super( Clock, self ).__init__()
        self.width  = 480
        self.height = 480

        self.speedy = 0
        
        self.init_ui()



    def init_ui( self ):

        # Create a basic drawing area and connect the render function to
        # the expose event.  Then add it to the present widget set.
        #
        da = Gtk.DrawingArea()
        da.connect( "draw", self.on_draw )
        self.add( da )

        GObject.timeout_add( 10, self.on_tick, self )

        # Set window properties, app exit policy, and draw the widget
        # set.
        #
        self.set_title( "Miffles" )
        self.resize( self.width, self.height )
        self.connect( "delete-event", Gtk.main_quit )
        self.show_all()




    def clear_to_black( self, cr ):
        """
        Clear the window to black.
        """
        cr.set_source_rgb( 0, 0, 0 )
        cr.rectangle( -1.0, -1.0, 2.0, 2.0 )
        cr.fill()


        
    def normalize_canvas( self, cr ):
        """
        Transform the canvas so that the origin is in the center, positive
        Y is up, and the square extent is (-1,1).
        """
        cr.scale( self.width / 2.0, self.height / -2.0 )
        cr.translate( 1.0, -1.0 )


        
    def fraction_to_radians( self, frac ):
        """
        Convert a fraction of a circle to the clockwise angle in radians.
        """
        return frac * ( -2.0 * pi )


    
    def on_tick( self, toplevel ):
        """
        Respond to the 1/100 second timer signal.
        """
        for w in toplevel:
            cr = w.props.window.cairo_create()
            self.on_draw( w, cr )
        return True


    
    def on_draw( self, w, cr ):
        """
        Draw the clock.
        """        
        self.normalize_canvas( cr )
        self.clear_to_black( cr )

        # Get the time of day.
        now = time.localtime()

        # Minute hand.
        min_frac = now.tm_min / 60.0
        ang = self.fraction_to_radians( now.tm_min / 60.0 )
        cr.rotate( ang )
        cr.set_source_rgb( 1, 1, 1 )
        cr.set_line_width( 0.04 )
        cr.move_to( 0, 0 )
        cr.line_to( 0, 0.85 )
        cr.stroke()
        cr.rotate( -ang )

        # Hour hand, including the fractional minute-hand angle.
        ang = self.fraction_to_radians(
            ( now.tm_hour % 12 ) / 12.0 + min_frac / 12.0
        )
        cr.rotate( ang )
        cr.set_line_width( 0.05 )
        cr.move_to( 0, 0 )
        cr.line_to( 0, 0.45 )
        cr.stroke()
        cr.rotate( -ang )

        # Second hand.
        ang = self.fraction_to_radians( now.tm_sec / 60.0 )
        cr.rotate( ang )
        cr.set_source_rgb( 1, 0.75, 0.80 )
        cr.set_line_width( 0.01 )
        cr.move_to( 0, -0.1 )
        cr.line_to( 0, 0.95 )
        cr.stroke()
        cr.rotate( -ang )

        # Sweep hand.
        self.speedy = ( self.speedy + 1 ) % 100
        ang = self.fraction_to_radians( self.speedy / 100.0 )
        cr.set_source_rgb( 1, 0, 0 )
        cr.rotate( ang )
        cr.move_to( 0, 0 )
        cr.line_to( 0, 0.3 )
        cr.stroke()
        cr.rotate( -ang )


        
def main():
    try:
        app = Clock()
        Gtk.main()

    except AttributeError as e:
        print e
        sys.exit( 1 )
        
if __name__ == "__main__":    
    main()
    
