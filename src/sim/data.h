#ifndef DATA_H
#define DATA_H

#include "datapoint.h"

namespace navs {
    namespace sim {
        struct data
        {
            datapoint<bool> avionics_on = false;

            bool has_changed() const;
            void clear_changed();
        };

    } // namespace sim
} // namespace navs

#endif /* DATA_H */