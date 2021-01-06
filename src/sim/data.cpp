#include "data.h"

namespace navs {
    namespace sim {
        bool data::has_changed() const
        {
            bool tmp = false;

            tmp |= avionics_on.has_changed();

            return tmp;
        }

        void data::clear_changed()
        {
            avionics_on.clear_changed();
        }

    } // namespace sim
} // namespace navs