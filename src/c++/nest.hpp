#pragma once

#include <string>
#include "background.hpp"
#include "indicator.hpp"
#include "readout.hpp"

namespace miffles {

    class point_t;

    namespace nest {

        const static double radius = 80.0;
        const static double band_thick = 15.0;
        const static double dash = 1.2;
        const static double bug_offset = 3.0;
        const static double field_org = 250.0;
        const static double field_arc = 320.0;

        class background_t : public ::miffles::color_background_t {
        public:
            background_t( char const *_name );
            virtual bool draw( const midget_t::cairo_context_t &cr );
        };

        class actual_temp_t : public ::miffles::bug_t {
        public:
            Glib::RefPtr< Gdk::Pixbuf > m_pixbuf;
            miffles::point_t m_anchor;
            
        public:
#if 0            
            Actual_Temp( char const *_name );
#else            
            actual_temp_t( char const *_name, std::string file, miffles::point_t _anchor );
#endif            
            virtual bool draw( const midget_t::cairo_context_t &cr );
        };

        class setpoint_temp_t : public ::miffles::indicator_t {
        public:
            setpoint_temp_t( char const *_name );
            virtual bool draw( const midget_t::cairo_context_t &cr );
        };

        class setpoint_readout_t : public ::miffles::readout_t {
        public:
            setpoint_readout_t( char const *_name );
            virtual bool draw( const midget_t::cairo_context_t &cr );
        };
    }
}

