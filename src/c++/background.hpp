// -----------------------------------------------------------------------
//  File:              background.hpp
//  Description:       Miffles Frame backgrounds
//  Author:            Jay Windley <jwindley>
//  Created:           Fri Apr 10 12:57:46 2015
//  Copyright:         (c) 2015 Jay Windley
//                     All rights reserved.
// -----------------------------------------------------------------------

#pragma once

#include <string>
#include "midget.hpp"
#include "types.hpp"

namespace miffles {

    //******************************************************************
    //
    //  Background that fills with a constant color, default black.
    //
    //******************************************************************
    class color_background_t : public midget_t {
    public:
        miffles::color_t m_color;
    public:
        color_background_t( char const *_name,
                            color_t _color = miffles::color_t::black );
        virtual ~color_background_t() {}
        virtual bool draw( const midget_t::cairo_context_t &cr );
    };


    //******************************************************************
    //
    //  Background that fills with an image.
    //
    //******************************************************************
    class image_background_t : public midget_t {
    public:
        Glib::RefPtr< Gdk::Pixbuf > m_pixbuf;
    public:
        image_background_t( char const *_name, const std::string &file_name );
        virtual ~image_background_t() {}
        virtual bool draw( const midget_t::cairo_context_t &cr );
    };
}
