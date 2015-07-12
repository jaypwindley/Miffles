#ifndef __MIFFLES_TEXT_H__
#define __MIFFLES_TEXT_H__

#include "types.h"

namespace Miffles {

    class Text_Style {

    public:

        //**************************************************************
        //
        //  Whether the rendering reference point is to the left,
        //  center, or right of the text.  LEFT, e.g., means the point
        //  is at the far left of the text such that the text starts
        //  there and renders to the right.
        //
        //  Default is LEFT.
        //
        //**************************************************************
        enum H_Justification { LEFT, CENTER, RIGHT };

        //**************************************************************
        //
        //  Whether the rendering reference point is at the top, middle,
        //  or bottom of the text.  TOP, e.g., means that the point is
        //  at the top of the text such that the text starts there and
        //  extends downward.
        //
        //  Default is BOTTOM.
        //
        enum V_Justification { TOP, MIDDLE, BOTTOM };

    public:
        H_Justification     m_h_justify;
        V_Justification     m_v_justify;
        double              m_font_size;
        Miffles::Color      m_color;

    public:
        Text_Style();
        virtual ~Text_Style() {}


        //--------------------------------------------------------------
        // Set the color.
        //
        void set_color( Miffles::Color &_color ) {
            m_color = _color;
        }
    };
}

#endif /*__MIFFLES_TEXT_H__*/
