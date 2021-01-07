#include <gtest/gtest.h>
#include <memory>

#include "sim/data.h"

namespace navs {
    namespace sim {

        class DataTest : public ::testing::Test
        {
        protected:
            data uut;

            void SetUp() override
            {}

            void TearDown() override
            {}
        };

        TEST_F(DataTest, AvionicsData)
        {
            EXPECT_FALSE(uut.has_changed());
            EXPECT_FALSE(uut.avionics_on.has_changed());

            uut.avionics_on = false;
            EXPECT_FALSE(uut.has_changed());
            EXPECT_FALSE(uut.avionics_on.has_changed());

            uut.avionics_on = true;
            EXPECT_TRUE(uut.has_changed());
            EXPECT_TRUE(uut.avionics_on.has_changed());

            uut.clear_changed();
            EXPECT_FALSE(uut.has_changed());
            EXPECT_FALSE(uut.avionics_on.has_changed());
        }

    }
}