#ifndef __MIFFLES_LABEL_H__
#define __MIFFLES_LABEL_H__

#include <gtkmm.h>
#include <string>
#include "midget.h"

namespace Miffles {

    class Text_Style;
    
    class Label : public Midget {

    public:
        Text_Style     *m_style;
        std::string     m_text;
        
    public:
        Label( char const *_name );
        virtual ~Label() {}

        virtual bool draw( const Cairo_Context &cr );

    };

    void render_text( const Midget::Cairo_Context &cr,
                      Miffles::Text_Style *style,
                      Point &at,
                      std::string &s );
    
}

#endif /*__MIFFLES_LABEL_H__*/
