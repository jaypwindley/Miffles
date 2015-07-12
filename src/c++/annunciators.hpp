#pragma once

#include "annunciator.hpp"

namespace miffles {

    class basic_lightbulb_annunciator_t : public annunciator_t {

    public:
        basic_lightbulb_annunciator_t( char const *_name );
        virtual ~basic_lightbulb_annunciator_t() {}

        virtual bool draw( const cairo_context_t &cr );

    };
    
}
