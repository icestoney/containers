#include <map>

#include "./main_test.h"

using s21_map = s21::map<const int, int>;
using std_map = std::map<const int, int>;
using s21_tree = s21::tree<const int, int>;
using s21_vector = s21::vector<std::pair<s21_map::iterator, bool>>;
// using std::cout;

template <typename tree1, typename tree2>
void compare_map(tree1 m1, tree2 m2) {
  auto s21_it = m1.begin();
  auto std_it = m2.begin();

  if (m1.size()) {
    for (; s21_it != m1.end(); s21_it++, std_it++) {
      EXPECT_EQ((*s21_it).first, (*std_it).first);
      EXPECT_EQ((*s21_it).second, (*std_it).second);
    }
  }

  EXPECT_EQ(m1.size(), m2.size());
  EXPECT_EQ(m1.empty(), m2.empty());
}

TEST(map, defaultConstructor) {
  s21_map s21_m;
  std_map std_m;

  compare_map(s21_m, std_m);
}

TEST(map, initializerListConstructor) {
  s21_map s21_m = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  std_map std_m = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};

  compare_map(s21_m, std_m);
}

TEST(map, initializerListConstructorChar) {
  std::pair<const char, int> x = {'b', 3};
  s21::map<const char, int> s21_m = {{'a', 1}, {'c', 2}, x, {'d', 4}, {'e', 5}};
  std::map<const char, int> std_m = {{'a', 1}, {'c', 2}, x, {'d', 4}, {'e', 5}};
  x.second = 6;
  compare_map(s21_m, std_m);
}

TEST(map, initializerListConstructorString) {
  s21::map<const std::string, int> s21_m = {
      {"abc", 1}, {"dfg", 2}, {"eft", 3}, {"qwer", 4}, {"eft", 5}};
  std::map<const std::string, int> std_m = {
      {"abc", 1}, {"dfg", 2}, {"eft", 3}, {"qwer", 4}, {"eft", 5}};
  compare_map(s21_m, std_m);
}

TEST(map, copyConstructor) {
  s21_map s21_m1 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  s21_map s21_m2 = s21_m1;
  std_map std_m1 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  std_map std_m2 = std_m1;

  compare_map(s21_m2, std_m2);
}

TEST(map, moveConstructor) {
  s21_map s21_m1 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  s21_map s21_m2 = std::move(s21_m1);
  std_map std_m1 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  std_map std_m2 = std::move(std_m1);

  compare_map(s21_m2, std_m2);

  EXPECT_TRUE(s21_m1.empty());
  EXPECT_TRUE(std_m1.empty());
}

TEST(map, copyAssignmentOperator) {
  s21_map s21_m1 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  s21_map s21_m2;
  s21_m2 = s21_m1;
  std_map std_m1 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  std_map std_m2;
  std_m2 = std_m1;

  EXPECT_EQ(s21_m2.empty(), std_m2.empty());
  EXPECT_EQ(s21_m2.size(), std_m2.size());

  compare_map(s21_m2, std_m2);
}

TEST(map, moveAssignmentOperator) {
  s21_map s21_m1 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  s21_map s21_m2;
  s21_m2 = std::move(s21_m1);
  std_map std_m1 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  std_map std_m2;
  std_m2 = std::move(std_m1);

  compare_map(s21_m2, std_m2);

  EXPECT_TRUE(s21_m1.empty());
  EXPECT_TRUE(std_m1.empty());
}

TEST(map, insert) {
  s21_map s21_m;
  std_map std_m;

  auto s21_result = s21_m.insert({1, 1});
  auto std_result = std_m.insert({1, 1});
  compare_map(s21_m, std_m);

  s21_result = s21_m.insert({2, 2});
  std_result = std_m.insert({2, 2});
  compare_map(s21_m, std_m);

  s21_result = s21_m.insert({1, 3});
  std_result = std_m.insert({1, 3});
  compare_map(s21_m, std_m);
}

TEST(map, emplace) {
  s21_map s21_m;
  std_map std_m;

  auto s21_result = s21_m.emplace(1, 1);
  auto std_result = std_m.emplace(1, 1);
  EXPECT_EQ(s21_result.second, std_result.second);
  EXPECT_EQ((*s21_result.first).first, (*std_result.first).first);
  EXPECT_EQ((*s21_result.first).second, (*std_result.first).second);
  EXPECT_EQ(s21_m.size(), std_m.size());

  s21_result = s21_m.emplace(1, 2);
  std_result = std_m.emplace(1, 2);
  EXPECT_EQ(s21_result.second, std_result.second);
  EXPECT_EQ(s21_m.size(), std_m.size());

  s21_result = s21_m.emplace(2, 2);
  std_result = std_m.emplace(2, 2);
  EXPECT_EQ(s21_result.second, std_result.second);
  EXPECT_EQ((*s21_result.first).first, (*std_result.first).first);
  EXPECT_EQ((*s21_result.first).second, (*std_result.first).second);
  EXPECT_EQ(s21_m.size(), std_m.size());

  s21_result = s21_m.emplace(3, 3);
  std_result = std_m.emplace(3, 3);
  EXPECT_EQ(s21_result.second, std_result.second);
  EXPECT_EQ((*s21_result.first).first, (*std_result.first).first);
  EXPECT_EQ((*s21_result.first).second, (*std_result.first).second);
  EXPECT_EQ(s21_m.size(), std_m.size());

  s21_result = s21_m.emplace(4, 4);
  std_result = std_m.emplace(4, 4);
  EXPECT_EQ(s21_result.second, std_result.second);
  EXPECT_EQ((*s21_result.first).first, (*std_result.first).first);
  EXPECT_EQ((*s21_result.first).second, (*std_result.first).second);
  EXPECT_EQ(s21_m.size(), std_m.size());

  s21_result = s21_m.emplace(5, 5);
  std_result = std_m.emplace(5, 5);
  EXPECT_EQ(s21_result.second, std_result.second);
  EXPECT_EQ((*s21_result.first).first, (*std_result.first).first);
  EXPECT_EQ((*s21_result.first).second, (*std_result.first).second);
  EXPECT_EQ(s21_m.size(), std_m.size());
}

TEST(map, insertOrAssign) {
  s21_map s21_m;
  std_map std_m;

  auto s21_result = s21_m.insert_or_assign(1, 1);
  auto std_result = std_m.insert_or_assign(1, 1);
  EXPECT_EQ(s21_result.second, std_result.second);
  EXPECT_EQ((*s21_result.first).first, (*std_result.first).first);
  EXPECT_EQ((*s21_result.first).second, (*std_result.first).second);
  EXPECT_EQ(s21_m.size(), std_m.size());

  s21_result = s21_m.insert_or_assign(1, 2);
  std_result = std_m.insert_or_assign(1, 2);
  EXPECT_EQ(s21_result.second, std_result.second);
  EXPECT_EQ((*s21_result.first).first, (*std_result.first).first);
  EXPECT_EQ((*s21_result.first).second, (*std_result.first).second);
  EXPECT_EQ(s21_m.size(), std_m.size());

  compare_map(s21_m, std_m);
}

TEST(map, erase) {
  s21_map s21_m = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  std_map std_m = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};

  auto s21_it = s21_m.begin();
  auto std_it = std_m.begin();

  s21_m.erase(s21_it);
  std_m.erase(std_it);

  compare_map(s21_m, std_m);

  s21_it = s21_m.begin();
  ++s21_it;
  std_it = std_m.begin();
  ++std_it;

  auto s21_check = s21_m.erase(s21_it);
  auto std_check = std_m.erase(std_it);

  EXPECT_EQ((*s21_check).first, (*std_check).first);

  compare_map(s21_m, std_m);
}

TEST(map, eraseAll) {
  s21_map s21_m = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  std_map std_m = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};

  while (s21_m.size()) {
    s21_m.erase(s21_m.begin());
    std_m.erase(std_m.begin());
  }

  EXPECT_EQ(s21_m.size(), std_m.size());
}

TEST(map, eraseRange_1) {
  s21_map s21_m = {{11, 11}, {256, 256}, {31, 31},   {44, 44}, {15, 15},
                   {1, 1},   {7, 7},     {111, 111}, {22, 22}, {222, 222}};
  std_map std_m = {{11, 11}, {256, 256}, {31, 31},   {44, 44}, {15, 15},
                   {1, 1},   {7, 7},     {111, 111}, {22, 22}, {222, 222}};

  auto s21_it_begin = s21_m.begin();
  ++s21_it_begin;
  ++s21_it_begin;
  auto s21_it_end = s21_it_begin;
  ++s21_it_end;
  ++s21_it_end;

  auto std_it_begin = std_m.begin();
  ++std_it_begin;
  ++std_it_begin;
  auto std_it_end = std_it_begin;
  ++std_it_end;
  ++std_it_end;

  auto s21_it = s21_m.erase(s21_it_begin, s21_it_end);
  auto std_it = std_m.erase(std_it_begin, std_it_end);
  // cout<< (s21_m).structure();
  EXPECT_EQ((*s21_it).first, (*std_it).first);

  compare_map(s21_m, std_m);
}

TEST(map, eraseRange_2) {
  s21_map s21_m = {{11, 11}, {256, 256}, {31, 31},   {44, 44}, {15, 15},
                   {1, 1},   {7, 7},     {111, 111}, {22, 22}, {222, 222}};
  std_map std_m = {{11, 11}, {256, 256}, {31, 31},   {44, 44}, {15, 15},
                   {1, 1},   {7, 7},     {111, 111}, {22, 22}, {222, 222}};

  auto s21_it_begin = s21_m.begin();
  auto s21_it_end = s21_it_begin;
  ++s21_it_end;

  auto std_it_begin = std_m.begin();
  auto std_it_end = std_it_begin;
  ++std_it_end;

  auto s21_it = s21_m.erase(s21_it_begin, s21_it_end);
  auto std_it = std_m.erase(std_it_begin, std_it_end);

  EXPECT_EQ((*s21_it).first, (*std_it).first);

  compare_map(s21_m, std_m);
}

TEST(map, eraseRange_3) {
  s21_map s21_m = {{11, 11}, {256, 256}, {31, 31},   {44, 44}, {15, 15},
                   {1, 1},   {7, 7},     {111, 111}, {22, 22}, {222, 222}};
  std_map std_m = {{11, 11}, {256, 256}, {31, 31},   {44, 44}, {15, 15},
                   {1, 1},   {7, 7},     {111, 111}, {22, 22}, {222, 222}};

  auto s21_it_begin = s21_m.end();
  --s21_it_begin;
  auto s21_it_end = s21_m.end();

  auto std_it_begin = std_m.end();
  --std_it_begin;
  auto std_it_end = std_m.end();

  s21_m.erase(s21_it_begin, s21_it_end);
  std_m.erase(std_it_begin, std_it_end);

  compare_map(s21_m, std_m);
}

TEST(map, eraseRange_4) {
  s21_map s21_m = {{11, 11}, {256, 256}, {31, 31},   {44, 44}, {15, 15},
                   {1, 1},   {7, 7},     {111, 111}, {22, 22}, {222, 222}};
  std_map std_m = {{11, 11}, {256, 256}, {31, 31},   {44, 44}, {15, 15},
                   {1, 1},   {7, 7},     {111, 111}, {22, 22}, {222, 222}};

  auto s21_it_begin = s21_m.begin();
  auto s21_it_end = s21_m.end();

  auto std_it_begin = std_m.begin();
  auto std_it_end = std_m.end();

  s21_m.erase(s21_it_begin, s21_it_end);
  std_m.erase(std_it_begin, std_it_end);

  compare_map(s21_m, std_m);
}

TEST(map, eraseRange_5) {
  s21_map s21_m = {{11, 11}, {256, 256}, {31, 31},   {44, 44}, {15, 15},
                   {1, 1},   {7, 7},     {111, 111}, {22, 22}, {222, 222}};
  std_map std_m = {{11, 11}, {256, 256}, {31, 31},   {44, 44}, {15, 15},
                   {1, 1},   {7, 7},     {111, 111}, {22, 22}, {222, 222}};

  auto s21_it_begin = s21_m.begin();

  auto std_it_begin = std_m.begin();

  s21_m.erase(s21_it_begin, s21_it_begin);
  std_m.erase(std_it_begin, std_it_begin);

  compare_map(s21_m, std_m);
}

TEST(map, clear) {
  s21_map s21_m = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  std_map std_m = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};

  s21_m.clear();
  std_m.clear();
  compare_map(s21_m, std_m);
}

TEST(map, contains) {
  s21_map s21_m = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  std_map std_m = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};

  compare_map(s21_m, std_m);
  EXPECT_FALSE(s21_m.contains(6));
}

TEST(map, at) {
  s21_map s21_m = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  std_map std_m = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};

  compare_map(s21_m, std_m);
  EXPECT_THROW(s21_m.at(6), std::out_of_range);
  EXPECT_THROW(std_m.at(6), std::out_of_range);
}

TEST(map, operatorBracket) {
  s21_map s21_m = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  std_map std_m = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};

  compare_map(s21_m, std_m);
  s21_m[6] = 6;
  std_m[6] = 6;
  compare_map(s21_m, std_m);
  s21_m[3] = 11;
  std_m[3] = 11;
  compare_map(s21_m, std_m);
  EXPECT_EQ(s21_m[7], std_m[7]);
}

TEST(map, swap) {
  s21_map s21_m1 = {{1, 1}, {2, 2}, {3, 3}};
  s21_map s21_m2 = {{4, 4}, {5, 5}, {6, 6}};
  std_map std_m1 = {{1, 1}, {2, 2}, {3, 3}};
  std_map std_m2 = {{4, 4}, {5, 5}, {6, 6}};

  s21_m1.swap(s21_m2);
  std_m1.swap(std_m2);
  compare_map(s21_m1, std_m1);
  compare_map(s21_m2, std_m2);
}

TEST(map, merge_1) {
  s21_map s21_m1 = {{1, 1}, {2, 2}, {3, 3}};
  s21_map s21_m2 = {{4, 4}, {5, 5}, {6, 6}};
  std_map std_m1 = {{1, 1}, {2, 2}, {3, 3}};
  std_map std_m2 = {{4, 4}, {5, 5}, {6, 6}};

  s21_m1.merge(s21_m2);
  std_m1.merge(std_m2);

  compare_map(s21_m1, std_m1);
  compare_map(s21_m2, std_m2);
}

TEST(map, merge_2) {
  s21_map s21_m1 = {{1, 1},   {2, 2},   {3, 3},   {10, 10},
                    {20, 20}, {30, 30}, {40, 40}, {50, 50}};
  s21_map s21_m2 = {{4, 4},    {5, 5},    {6, 6},   {10, 100},
                    {20, 200}, {30, 300}, {60, 60}, {70, 70}};

  std_map std_m1 = {{1, 1},   {2, 2},   {3, 3},   {10, 10},
                    {20, 20}, {30, 30}, {40, 40}, {50, 50}};
  std_map std_m2 = {{4, 4},    {5, 5},    {6, 6},   {10, 100},
                    {20, 200}, {30, 300}, {60, 60}, {70, 70}};

  s21_m1.merge(s21_m2);
  std_m1.merge(std_m2);

  compare_map(s21_m1, std_m1);
  compare_map(s21_m2, std_m2);
}

TEST(map, insert_many) {
  s21_map map1 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  std_map map_std = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  s21_vector vec =
      map1.insert_many(std::make_pair(10, 9), std::make_pair(3, 9),
                       std::make_pair(5, 9), std::make_pair(16, 9));
  s21::vector<std::pair<int, int>> check = {{10, 9}, {0, 0}, {0, 0}, {16, 9}};
  s21::vector<bool> check2 = {1, 0, 0, 1};

  int i = 0;
  for (auto it_vec = vec.begin(); it_vec != vec.end(); it_vec++, i++) {
    EXPECT_EQ((*((*it_vec).first)).first, check[i].first);
    EXPECT_EQ((*((*it_vec).first)).second, check[i].second);
    EXPECT_EQ((*it_vec).second, check2[i]);
  }

  map_std.insert({10, 9});
  map_std.insert({3, 9});
  map_std.insert({5, 9});
  map_std.insert({16, 9});

  compare_map(map1, map_std);
}

TEST(map, insert_many_empty) {
  s21_map map1 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  std_map map_std = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  s21_vector vec = map1.insert_many();
  s21::vector<std::pair<int, int>> check = {{}};
  s21::vector<bool> check2 = {};

  int i = 0;
  for (auto it_vec = vec.begin(); it_vec != vec.end(); it_vec++, i++) {
    EXPECT_EQ((*((*it_vec).first)).first, check[i].first);
    EXPECT_EQ((*((*it_vec).first)).second, check[i].second);
    EXPECT_EQ((*it_vec).second, check2[i]);
  }

  compare_map(map1, map_std);
}