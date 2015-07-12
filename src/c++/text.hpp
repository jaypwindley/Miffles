#include "types.hpp"

namespace miffles {

    class text_style_t {

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
        enum h_justification_t { LEFT, CENTER, RIGHT };

        //**************************************************************
        //
        //  Whether the rendering reference point is at the top, middle,
        //  or bottom of the text.  TOP, e.g., means that the point is
        //  at the top of the text such that the text starts there and
        //  extends downward.
        //
        //  Default is BOTTOM.
        //
        enum v_justification_t { TOP, MIDDLE, BOTTOM };

    public:
        h_justification_t   m_h_justify;
        v_justification_t   m_v_justify;
        double              m_font_size;
        miffles::color_t    m_color;

    public:
        text_style_t();
        virtual ~text_style_t() {}


        //--------------------------------------------------------------
        // Set the color.
        //
        void set_color( const miffles::color_t &_color ) {
            m_color = _color;
        }
    };
}

