// -----------------------------------------------------------------------
//  File:              frame.h
//  Description:       Miffles Frame, the meter-scope container
//  Author:            Jay Windley <jwindley>
//  Created:           Mon Mar 30 23:43:06 2015
//  Copyright:         (c) 2015 Jay Windley
//                     All rights reserved.
// -----------------------------------------------------------------------

#ifndef __MIFFLES_FRAME_H__
#define __MIFFLES_FRAME_H__

#include <gtkmm.h>

#include "types.h"


namespace Miffles {

    class Midget;
    class Midget_List;
    
    //******************************************************************
    //
    //  The Field is the finest-grain object that receives a redraw
    //  event from the toolkit.  It is responsible for transforming the
    //  drawing context to the local coordinate system and calling the
    //  draw methods of all the constituent drawable objects.
    //
    //  Field coordinate system has the origin at the center, positive
    //  y-axis is up, and the size is normalized to 100 units in the
    //  largest dimension.
    //
    //******************************************************************
    class Frame : public Gtk::DrawingArea {

    public:       
        enum Resize_Policy { CLIP, FIT };
        
    public:
        std::string     m_name;
        Point           m_origin;
        Extent          m_size;
        Resize_Policy   m_resize;
        Midget_List     *m_midgets;
        
    public:
        Frame( char const *_name );
        virtual ~Frame();

        //--------------------------------------------------------------
        // Add a Midget to this frame.
        //
        void add( Midget *m );
        

        //--------------------------------------------------------------
        // Generate a redraw event for this region of the display.
        //
        virtual void redraw( void );
        

        //--------------------------------------------------------------
        // This overrides Gtk::DrawingArea::on_draw(), which should be
        // automatically linked to the redraw signal in Gtk.  Since
        // Cairo insists on using Gtk-type crippled-ass
        // reference-counting pointers, the Drawable::draw() methods all
        // have to implement the unwieldy down-cast from void *.
        //
        virtual bool on_draw( const ::Cairo::RefPtr<::Cairo::Context> &cr );


        //--------------------------------------------------------------
        // Return an Extent giving the full width and height of the
        // content in this frame.
        //
        virtual Extent actual_extent( void );
    };
    
}

#endif /*__MIFFLES_FRAME_H__*/
