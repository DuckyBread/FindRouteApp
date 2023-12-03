#include <gtest/gtest.h>

#include "../back/EllersAlgorithm.h"
#include "../back/Data.h"

TEST(EllersAlgorithmTest, GenerateMaze) {
    frp::Data data;
    data.set_cols(4);
    data.set_rows(4);
    frp::EllersAlgorithm ellersAlgorithm{&data};

    EXPECT_NO_THROW(ellersAlgorithm.GenerateMaze());
    EXPECT_EQ(ellersAlgorithm.get_right_walls().size(), (data.get_rows() * (data.get_cols())));
    EXPECT_EQ(ellersAlgorithm.get_bottom_walls().size(), ((data.get_rows() ) * data.get_cols()));
}

TEST(EllersAlgorithmTest, WallValues) {
    frp::Data data;
    data.set_cols(50);
    data.set_rows(50);
    frp::EllersAlgorithm ellersAlgorithm{&data};

    EXPECT_NO_THROW(ellersAlgorithm.GenerateMaze());
    EXPECT_TRUE(ellersAlgorithm.get_right_walls(0, 0));
}
