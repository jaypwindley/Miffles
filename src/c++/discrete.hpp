#pragma once

#include <string>
#include <vector>
#include "midget.hpp"
#include "frame.hpp"

namespace miffles {

    class discrete_t : public midget_t
    {
    public:
        typedef std::vector<std::string> state_list_t;

    public:
        state_list_t    m_states;
        int             m_state;
        bool            m_is_circular;
        
    public:
        discrete_t( char const *_name );
        virtual ~discrete_t() {}

        void add_state( char const *state );
        void set( char const *state );
        void set( const int state );
        void inc( void );
        void dec( void );

    private:
        int find( char const *name );
    };
    
}
