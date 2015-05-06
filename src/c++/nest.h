#ifndef __MIFFLES_NEST_H__
#define __MIFFLES_NEST_H__

#include <string>
#include "background.h"
#include "indicator.h"
#include "readout.h"

namespace Miffles {

    class Point;

    namespace Nest {

        const static double radius = 80.0;
        const static double band_thick = 15.0;
        const static double dash = 1.2;
        const static double bug_offset = 3.0;
        const static double field_org = 250.0;
        const static double field_arc = 320.0;

        class Background : public ::Miffles::Color_Background {
        public:
            Background( char const *_name );
            virtual bool draw( const Midget::Cairo_Context &cr );
        };

        class Actual_Temp : public ::Miffles::Bug {
        public:
            Glib::RefPtr< Gdk::Pixbuf > m_pixbuf;
            Miffles::Point m_anchor;
            
        public:
#if 0            
            Actual_Temp( char const *_name );
#else            
            Actual_Temp( char const *_name, std::string file, Miffles::Point _anchor );
#endif            
            virtual bool draw( const Midget::Cairo_Context &cr );
        };

        class Setpoint_Temp : public ::Miffles::Indicator {
        public:
            Setpoint_Temp( char const *_name );
            virtual bool draw( const Midget::Cairo_Context &cr );
        };

        class Setpoint_Readout : public ::Miffles::Readout {
        public:
            Setpoint_Readout( char const *_name );
            virtual bool draw( const Midget::Cairo_Context &cr );
        };
    }
}

#endif /*__MIFFLES_NEST_H__*/
