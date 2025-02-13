#ifndef MAIN_TEST_H
#define MAIN_TEST_H

#include <gtest/gtest.h>

#include "./../s21_containersplus.h"

template <typename tree1, typename tree2>
void compare(tree1 s1, tree2 s2) {
  auto s21_it = s1.begin();
  auto std_it = s2.begin();

  if (s1.size()) {
    for (; s21_it != s1.end(); s21_it++, std_it++) {
      EXPECT_EQ(*s21_it, *std_it);
    }
  }

  EXPECT_EQ(s1.size(), s2.size());
  EXPECT_EQ(s1.empty(), s2.empty());
}

#endif