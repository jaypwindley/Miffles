#pragma once

#include <gtkmm.h>
#include <string>
#include "midget.hpp"

namespace miffles {

    class text_style_t;
    
    class label_t : public midget_t {

    public:
        text_style_t   *m_style;
        std::string     m_text;
        
    public:
        label_t( char const *_name );
        virtual ~label_t() {}

        virtual bool draw( const cairo_context_t &cr );

    };

    void render_text( const midget_t::cairo_context_t &cr,
                      miffles::text_style_t *style,
                      point_t &at,
                      std::string &s );
    
}
