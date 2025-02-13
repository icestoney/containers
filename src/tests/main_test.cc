#include "./main_test.h"

/**
 * @brief Main running testing
 *
 * @param[in] argc number of arguments supplied
 * @param[in] argv array of arguments
 * @return int - overall test result
 */
int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  //::testing::GTEST_FLAG(filter) = "multiset*";
  return RUN_ALL_TESTS();
}