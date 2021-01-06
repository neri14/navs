#ifndef DATAPOINT_H
#define DATAPOINT_H

namespace navs {
    namespace sim {
        template <typename T>
        class datapoint
        {
        public:
            datapoint(T value_) :
                value(value_),
                changed(false)
            {}

            ~datapoint() = default;

            datapoint<T>& operator=(const T& value_)
            {
                if (value != value_) {
                    value = value_;
                    changed = true;
                }
                return *this;
            }

            operator T() const
            {
                return value;
            }

            bool has_changed() const
            {
                return changed;
            }

            void clear_changed()
            {
                changed = false;
            }

        private:
            T value;
            bool changed;
        };
    } // namespace sim
} // namespace navs

#endif /* DATAPOINT_H */
