
#ifndef __MIFFLES_DISCRETE_H__
#define __MIFFLES_DISCRETE_H__

#include <string>
#include <vector>

#include "midget.h"
#include "frame.h"

namespace Miffles {

    class Discrete : public Midget
    {
    public:
        typedef std::vector<std::string> State_List;

    public:
        State_List      m_states;
        int             m_state;
        bool            m_is_circular;
        
    public:
        Discrete( char const *_name );
        virtual ~Discrete() {}

        void add_state( char const *state );
        void set( char const *state );
        void set( const int state );
        void inc( void );
        void dec( void );

    private:
        int find( char const *name );
    };
    
}

#endif /*__MIFFLES_DISCRETE_H__*/
