#ifndef __MIFFLES_ANNUNCIATORS_H__
#define __MIFFLES_ANNUNCIATORS_H__

#include "annunciator.h"

namespace Miffles {

    class Basic_Lightbulb_Annunciator : public Annunciator {

    public:
        Basic_Lightbulb_Annunciator( char const *_name );
        virtual ~Basic_Lightbulb_Annunciator() {}

        virtual bool draw( const Cairo_Context &cr );

    };
    
}

#endif /*__MIFFLES_ANNUNCIATORS_H__*/
