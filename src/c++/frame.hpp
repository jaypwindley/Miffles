// -----------------------------------------------------------------------
//  File:              frame.hpp
//  Description:       Miffles Frame, the meter-scope container
//  Author:            Jay Windley <jwindley>
//  Created:           Mon Mar 30 23:43:06 2015
//  Copyright:         (c) 2015 Jay Windley
//                     All rights reserved.
// -----------------------------------------------------------------------

#pragma once

#include <gtkmm.h>
#include "types.hpp"


namespace miffles {

    class midget_t;
    class midget_list_t;
    
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
    class frame_t : public Gtk::DrawingArea {

    public:       
        enum resize_policy_t { CLIP, FIT };
        
    public:
        std::string     m_name;
        point_t         m_origin;
        extent_t        m_size;
        resize_policy_t m_resize;
        midget_list_t  *m_midgets;
        
    public:
        frame_t( char const *_name );
        virtual ~frame_t();

        //--------------------------------------------------------------
        // Add a Midget to this frame.
        //
        void add( midget_t *m );
        

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
        virtual extent_t actual_extent( void );
    };
    
}

