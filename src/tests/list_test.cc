#include <iterator>
#include <list>

#include "./main_test.h"

TEST(list, Constructor_Default) {
  s21::list<int> our_list;
  std::list<int> std_list;
  EXPECT_EQ(our_list.empty(), std_list.empty());
}

TEST(list, Constructor_Size) {
  s21::list<int> our_list(5);
  std::list<int> std_list(5);
  EXPECT_EQ(our_list.size(), std_list.size());
}

TEST(list, Constructor_List) {
  s21::list<int> our_list = {1, 2, 3};
  std::list<int> std_list = {1, 2, 3};
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
}

TEST(list, Constructor_Copy) {
  s21::list<int> our_list = {1, 2, 3};
  std::list<int> std_list = {1, 2, 3};
  s21::list<int> our_copy(our_list);
  std::list<int> std_copy(std_list);
  EXPECT_EQ(our_copy.front(), std_copy.front());
  EXPECT_EQ(our_copy.back(), std_copy.back());
}

TEST(list, Operator_Copy) {
  s21::list<int> our_list = {1, 2, 3};
  std::list<int> std_list = {1, 2, 3};
  s21::list<int> our_copy;
  our_copy = our_list;
  std::list<int> std_copy;
  std_copy = std_list;
  EXPECT_EQ(our_copy.front(), std_copy.front());
  EXPECT_EQ(our_copy.back(), std_copy.back());
}

TEST(list, Constructor_Move) {
  s21::list<int> our_list = {1, 2, 3};
  std::list<int> std_list = {1, 2, 3};
  s21::list<int> our_copy(std::move(our_list));
  std::list<int> std_copy(std::move(std_list));
  EXPECT_EQ(our_copy.front(), std_copy.front());
  EXPECT_EQ(our_copy.back(), std_copy.back());
  EXPECT_EQ(our_list.empty(), std_list.empty());
}

TEST(list, Operator_Move) {
  s21::list<int> our_list = {1, 2, 3};
  std::list<int> std_list = {1, 2, 3};
  s21::list<int> our_copy;
  our_copy = std::move(our_list);
  std::list<int> std_copy;
  std_copy = std::move(std_list);
  EXPECT_EQ(our_copy.front(), std_copy.front());
  EXPECT_EQ(our_copy.back(), std_copy.back());
  EXPECT_EQ(our_list.empty(), std_list.empty());
}

TEST(list, Size) {
  s21::list<int> our_list = {1, 2, 3};
  std::list<int> std_list = {1, 2, 3};
  EXPECT_EQ(our_list.size(), std_list.size());
}

TEST(list, Size_empty) {
  s21::list<int> our_list;
  std::list<int> std_list;
  EXPECT_EQ(our_list.size(), std_list.size());
}

TEST(list, Push_Front) {
  s21::list<int> our_list;
  std::list<int> std_list;
  our_list.push_front(1);
  std_list.push_front(1);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
  our_list.push_front(2);
  std_list.push_front(2);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
  our_list.push_front(3);
  std_list.push_front(3);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
}

TEST(list, Push_Front2) {
  s21::list<int> our_list{4, 5, 6};
  std::list<int> std_list{4, 5, 6};
  our_list.push_front(1);
  std_list.push_front(1);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
  our_list.push_front(2);
  std_list.push_front(2);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
  our_list.push_front(3);
  std_list.push_front(3);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
  EXPECT_EQ(our_list.size(), std_list.size());
}

TEST(list, Push_Back) {
  s21::list<int> our_list;
  std::list<int> std_list;
  our_list.push_back(1);
  std_list.push_back(1);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
  our_list.push_back(2);
  std_list.push_back(2);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
  our_list.push_back(3);
  std_list.push_back(3);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
  EXPECT_EQ(our_list.size(), std_list.size());
}

TEST(list, Push_Back2) {
  s21::list<int> our_list{4, 5, 6};
  std::list<int> std_list{4, 5, 6};
  our_list.push_back(1);
  std_list.push_back(1);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
  our_list.push_back(2);
  std_list.push_back(2);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
  our_list.push_back(3);
  std_list.push_back(3);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
  EXPECT_EQ(our_list.size(), std_list.size());
}

TEST(list, Pop_Front) {
  s21::list<int> our_list{4, 5, 6};
  std::list<int> std_list{4, 5, 6};
  our_list.pop_front();
  std_list.pop_front();
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
  EXPECT_EQ(our_list.size(), std_list.size());
}

TEST(list, Pop_Back) {
  s21::list<int> our_list{4, 5, 6};
  std::list<int> std_list{4, 5, 6};
  our_list.pop_back();
  std_list.pop_back();
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
  EXPECT_EQ(our_list.size(), std_list.size());
}

TEST(list, Iterator_Begin) {
  s21::list<int> our_list = {1, 2, 3};
  std::list<int> std_list = {1, 2, 3};
  s21::list<int>::iterator our_it = our_list.begin();
  std::list<int>::iterator std_it = std_list.begin();
  EXPECT_EQ(*our_it, *std_it);
}

TEST(list, Iterator_BeginPlusAndMinus) {
  s21::list<int> our_list = {1, 2, 3};
  std::list<int> std_list = {1, 2, 3};
  s21::list<int>::iterator our_it = our_list.begin();
  std::list<int>::iterator std_it = std_list.begin();
  ++our_it;
  ++std_it;
  EXPECT_EQ(*our_it, *std_it);
  --our_it;
  --std_it;
  EXPECT_EQ(*our_it, *std_it);
}

TEST(list, Iterator_End_Last) {
  s21::list<int> our_list = {1, 2, 3};
  std::list<int> std_list = {1, 2, 3};
  s21::list<int>::iterator our_it;
  our_it = our_list.end();
  --our_it;
  std::list<int>::iterator std_it;
  std_it = std_list.end();
  --std_it;
  EXPECT_EQ(*our_it, *std_it);
}

TEST(list, Iterator_End_Last2) {
  s21::list<int> our_list = {3, 2, 1};
  std::list<int> std_list = {3, 2, 1};
  s21::list<int>::iterator our_it;
  our_it = our_list.end();
  our_it--;
  std::list<int>::iterator std_it;
  std_it = std_list.end();
  std_it--;
  EXPECT_EQ(*our_it, *std_it);
}

TEST(list, Iterator_Equals) {
  s21::list<int> first_list = {1, 2, 3};
  s21::list<int>::iterator our_it_first = first_list.begin();
  s21::list<int>::iterator our_it_second = first_list.begin();
  EXPECT_TRUE(our_it_first == our_it_second);
  ++our_it_second;
  EXPECT_TRUE(our_it_first != our_it_second);
}

TEST(list, Insert) {
  s21::list<int> our_list;
  std::list<int> std_list;
  s21::list<int>::iterator our_it;
  our_it = our_list.begin();
  std::list<int>::iterator std_it;
  std_it = std_list.begin();
  our_list.insert(our_it, 5);
  std_list.insert(std_it, 5);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
  our_list.insert(our_it, 7);
  std_list.insert(std_it, 7);
  our_list.insert(our_it, 9);
  std_list.insert(std_it, 9);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
}

TEST(list, Erase) {
  s21::list<int> our_list = {1, 2, 3, 4, 5};
  std::list<int> std_list = {1, 2, 3, 4, 5};
  our_list.erase(our_list.begin());
  std_list.erase(std_list.begin());

  s21::list<int>::iterator our_it = our_list.begin();
  std::list<int>::iterator std_it = std_list.begin();
  for (; our_it != our_list.end(), std_it != std_list.end();
       ++our_it, ++std_it) {
    EXPECT_EQ(*our_it, *std_it);
  }
}

TEST(list, Swap) {
  s21::list<int> our_list_first = {1, 2, 3, 4};
  s21::list<int> our_list_second = {5, 6, 7, 8};

  std::list<int> std_list_first = {1, 2, 3, 4};
  std::list<int> std_list_second = {5, 6, 7, 8};

  our_list_first.swap(our_list_second);
  std_list_first.swap(std_list_second);

  s21::list<int>::iterator our_it = our_list_first.begin();
  std::list<int>::iterator std_it = std_list_first.begin();
  for (; our_it != our_list_first.end(), std_it != std_list_first.end();
       ++our_it, ++std_it) {
    EXPECT_EQ(*our_it, *std_it);
  }
  our_it = our_list_second.begin();
  std_it = std_list_second.begin();
  for (; our_it != our_list_second.end(), std_it != std_list_second.end();
       ++our_it, ++std_it) {
    EXPECT_EQ(*our_it, *std_it);
  }
}

TEST(list, Swap_empty) {
  s21::list<int> our_list_first = {1, 2, 3, 4};
  s21::list<int> our_list_second;
  std::list<int> std_list_first = {1, 2, 3, 4};
  std::list<int> std_list_second;
  our_list_first.swap(our_list_second);
  std_list_first.swap(std_list_second);

  s21::list<int>::iterator our_it = our_list_second.begin();
  std::list<int>::iterator std_it = std_list_second.begin();
  for (; our_it != our_list_second.end(), std_it != std_list_second.end();
       ++our_it, ++std_it) {
    EXPECT_EQ(*our_it, *std_it);
  }
  EXPECT_EQ(our_list_first.empty(), std_list_first.empty());
}

TEST(list, Swap_string) {
  s21::list<std::string> our_list_first = {"One", "Two", "Three", "Four"};
  s21::list<std::string> our_list_second = {"Five", "Six", "Seven", "Eight"};
  std::list<std::string> std_list_first = {"One", "Two", "Three", "Four"};
  std::list<std::string> std_list_second = {"Five", "Six", "Seven", "Eight"};
  our_list_first.swap(our_list_second);
  std_list_first.swap(std_list_second);

  s21::list<std::string>::iterator our_it = our_list_first.begin();
  std::list<std::string>::iterator std_it = std_list_first.begin();
  for (; our_it != our_list_first.end(), std_it != std_list_first.end();
       ++our_it, ++std_it) {
    EXPECT_EQ(*our_it, *std_it);
  }
  our_it = our_list_second.begin();
  std_it = std_list_second.begin();
  for (; our_it != our_list_second.end(), std_it != std_list_second.end();
       ++our_it, ++std_it) {
    EXPECT_EQ(*our_it, *std_it);
  }
}

TEST(list, Merge) {
  s21::list<int> our_list_first = {7, 5, 9, 4};
  s21::list<int> our_list_second = {3, 2, 6, 8};

  std::list<int> std_list_first = {7, 5, 9, 4};
  std::list<int> std_list_second = {3, 2, 6, 8};

  our_list_first.merge(our_list_second);
  std_list_first.merge(std_list_second);

  s21::list<int>::iterator our_it = our_list_first.begin();
  std::list<int>::iterator std_it = std_list_first.begin();
  for (; our_it != our_list_first.end(), std_it != std_list_first.end();
       ++our_it, ++std_it) {
    EXPECT_EQ(*our_it, *std_it);
  }
  EXPECT_EQ(our_list_second.empty(), std_list_second.empty());
}

TEST(list, Merge2) {
  s21::list<int> our_list_first = {3, 4, 5, 6};
  s21::list<int> our_list_second = {3, 7, 8, 9};

  std::list<int> std_list_first = {3, 4, 5, 6};
  std::list<int> std_list_second = {3, 7, 8, 9};

  our_list_first.merge(our_list_second);
  std_list_first.merge(std_list_second);

  s21::list<int>::iterator our_it = our_list_first.begin();
  std::list<int>::iterator std_it = std_list_first.begin();
  for (; our_it != our_list_first.end(), std_it != std_list_first.end();
       ++our_it, ++std_it) {
    EXPECT_EQ(*our_it, *std_it);
  }
  EXPECT_EQ(our_list_second.empty(), std_list_second.empty());
}

TEST(list, Merge3) {
  s21::list<int> our_list_first = {1};
  s21::list<int> our_list_second = {2, 3, 4, 5};

  std::list<int> std_list_first = {1};
  std::list<int> std_list_second = {2, 3, 4, 5};

  our_list_first.merge(our_list_second);
  std_list_first.merge(std_list_second);

  s21::list<int>::iterator our_it = our_list_first.begin();
  std::list<int>::iterator std_it = std_list_first.begin();
  for (; our_it != our_list_first.end(), std_it != std_list_first.end();
       ++our_it, ++std_it) {
    EXPECT_EQ(*our_it, *std_it);
  }
  EXPECT_EQ(our_list_second.empty(), std_list_second.empty());
}

TEST(list, Merge_empty) {
  s21::list<int> our_list_first;
  s21::list<int> our_list_second;

  our_list_first.merge(our_list_second);

  s21::list<int>::iterator our_it = our_list_first.begin();
  EXPECT_EQ(nullptr, our_it.get());
}

TEST(list, Merge_string) {
  s21::list<std::string> our_list_first = {"One", "Two", "Three", "Four"};
  s21::list<std::string> our_list_second = {"Five", "Six", "Seven", "Eight"};
  std::list<std::string> std_list_first = {"One", "Two", "Three", "Four"};
  std::list<std::string> std_list_second = {"Five", "Six", "Seven", "Eight"};

  our_list_first.merge(our_list_second);
  std_list_first.merge(std_list_second);

  s21::list<std::string>::iterator our_it = our_list_first.begin();
  std::list<std::string>::iterator std_it = std_list_first.begin();
  for (; our_it != our_list_first.end(), std_it != std_list_first.end();
       ++our_it, ++std_it) {
    EXPECT_EQ(*our_it, *std_it);
  }
  EXPECT_EQ(our_list_second.empty(), std_list_second.empty());
}

TEST(list, Splice) {
  s21::list<int> our_list_first = {1};
  s21::list<int> our_list_second = {2, 3, 4, 5};

  std::list<int> std_list_first = {1};
  std::list<int> std_list_second = {2, 3, 4, 5};

  s21::list<int>::const_iterator our_it = our_list_first.cbegin();
  std::list<int>::iterator std_it = std_list_first.begin();
  our_list_first.splice(our_it, our_list_second);
  std_list_first.splice(std_it, std_list_second);

  our_it = our_list_first.cbegin();
  std_it = std_list_first.begin();
  for (; our_it != our_list_first.cend(), std_it != std_list_first.end();
       ++our_it, ++std_it) {
    EXPECT_EQ(*our_it, *std_it);
  }
  EXPECT_EQ(our_list_second.empty(), std_list_second.empty());
}

TEST(list, Splice2) {
  s21::list<int> our_list_first = {1, 6};
  s21::list<int> our_list_second = {2, 3, 4, 5};

  std::list<int> std_list_first = {1, 6};
  std::list<int> std_list_second = {2, 3, 4, 5};

  s21::list<int>::const_iterator our_it = our_list_first.cend();
  std::list<int>::iterator std_it = std_list_first.end();
  our_list_first.splice(our_it, our_list_second);
  std_list_first.splice(std_it, std_list_second);

  our_it = our_list_first.cbegin();
  std_it = std_list_first.begin();
  for (; our_it != our_list_first.cend(), std_it != std_list_first.end();
       ++our_it, ++std_it) {
    EXPECT_EQ(*our_it, *std_it);
  }
  EXPECT_EQ(our_list_second.empty(), std_list_second.empty());
}

TEST(list, Splice3) {
  s21::list<int> our_list_first = {1, 2, 3, 4, 5};
  s21::list<int> our_list_second = {10, 20, 30, 40, 50};

  std::list<int> std_list_first = {1, 2, 3, 4, 5};
  std::list<int> std_list_second = {10, 20, 30, 40, 50};

  s21::list<int>::const_iterator our_it = our_list_first.cbegin();
  std::list<int>::iterator std_it = std_list_first.begin();
  std::advance(our_it, 2);
  std::advance(std_it, 2);
  our_list_first.splice(our_it, our_list_second);
  std_list_first.splice(std_it, std_list_second);

  our_it = our_list_first.cbegin();
  std_it = std_list_first.begin();
  for (; our_it != our_list_first.cend(), std_it != std_list_first.end();
       ++our_it, ++std_it) {
    EXPECT_EQ(*our_it, *std_it);
  }
  EXPECT_EQ(our_list_second.empty(), std_list_second.empty());
}

TEST(list, Splice_empty) {
  s21::list<int> our_list_first;
  s21::list<int> our_list_second = {10, 20, 30, 40, 50};

  std::list<int> std_list_first;
  std::list<int> std_list_second = {10, 20, 30, 40, 50};

  s21::list<int>::const_iterator our_it = our_list_first.cbegin();
  std::list<int>::iterator std_it = std_list_first.begin();
  our_list_first.splice(our_it, our_list_second);
  std_list_first.splice(std_it, std_list_second);

  our_it = our_list_first.cbegin();
  std_it = std_list_first.begin();
  for (; our_it != our_list_first.cend(), std_it != std_list_first.end();
       ++our_it, ++std_it) {
    EXPECT_EQ(*our_it, *std_it);
  }
  EXPECT_EQ(our_list_second.empty(), std_list_second.empty());
}

TEST(list, Reverse) {
  s21::list<int> our_list = {1, 2, 3, 4, 5};
  std::list<int> std_list = {1, 2, 3, 4, 5};
  our_list.reverse();
  std_list.reverse();

  s21::list<int>::iterator our_it = our_list.begin();
  std::list<int>::iterator std_it = std_list.begin();
  for (; our_it != our_list.end(), std_it != std_list.end();
       ++our_it, ++std_it) {
    EXPECT_EQ(*our_it, *std_it);
  }
}

TEST(list, Unique) {
  s21::list<int> our_list = {1, 2, 2, 3, 3};
  std::list<int> std_list = {1, 2, 2, 3, 3};
  our_list.unique();
  std_list.unique();

  s21::list<int>::iterator our_it = our_list.begin();
  std::list<int>::iterator std_it = std_list.begin();
  for (; our_it != our_list.end(), std_it != std_list.end();
       ++our_it, ++std_it) {
    EXPECT_EQ(*our_it, *std_it);
  }
}

TEST(list, Unique_char) {
  s21::list<char> our_list = {'a', 'b', 'b', 't', 't'};
  std::list<char> std_list = {'a', 'b', 'b', 't', 't'};
  our_list.unique();
  std_list.unique();

  s21::list<char>::iterator our_it = our_list.begin();
  std::list<char>::iterator std_it = std_list.begin();
  for (; our_it != our_list.end(), std_it != std_list.end();
       ++our_it, ++std_it) {
    EXPECT_EQ(*our_it, *std_it);
  }
}

TEST(list, Sort) {
  s21::list<int> our_list = {2, 4, 1, 3, 5};
  std::list<int> std_list = {2, 4, 1, 3, 5};
  our_list.sort();
  std_list.sort();

  s21::list<int>::iterator our_it = our_list.begin();
  std::list<int>::iterator std_it = std_list.begin();
  for (; our_it != our_list.end(), std_it != std_list.end();
       ++our_it, ++std_it) {
    EXPECT_EQ(*our_it, *std_it);
  }
}

TEST(list, Sort2) {
  s21::list<int> our_list = {49, 7, 31, 40, 1, 52, 14, 13, 67};
  std::list<int> std_list = {49, 7, 31, 40, 1, 52, 14, 13, 67};
  our_list.sort();
  std_list.sort();

  s21::list<int>::iterator our_it = our_list.begin();
  std::list<int>::iterator std_it = std_list.begin();
  for (; our_it != our_list.end(), std_it != std_list.end();
       ++our_it, ++std_it) {
    EXPECT_EQ(*our_it, *std_it);
  }
}

TEST(list, Sort_empty) {
  s21::list<int> our_list;
  std::list<int> std_list;
  our_list.sort();
  std_list.sort();

  s21::list<int>::iterator our_it = our_list.begin();
  std::list<int>::iterator std_it = std_list.begin();
  for (; our_it != our_list.end(), std_it != std_list.end();
       ++our_it, ++std_it) {
    EXPECT_EQ(*our_it, *std_it);
  }
}

TEST(list, Sort_double) {
  s21::list<double> our_list = {9.888881, 9.888880, 6.555559,
                                6.555556, 8.333333, 8.333337};
  std::list<double> std_list = {9.888881, 9.888880, 6.555559,
                                6.555556, 8.333333, 8.333337};
  our_list.sort();
  std_list.sort();

  s21::list<double>::iterator our_it = our_list.begin();
  std::list<double>::iterator std_it = std_list.begin();
  for (; our_it != our_list.end(), std_it != std_list.end();
       ++our_it, ++std_it) {
    EXPECT_EQ(*our_it, *std_it);
  }
}

TEST(list, Sort_char) {
  s21::list<char> our_list = {'c', 'b', 'd', 'a'};
  std::list<char> std_list = {'c', 'b', 'd', 'a'};
  our_list.sort();
  std_list.sort();

  s21::list<char>::iterator our_it = our_list.begin();
  std::list<char>::iterator std_it = std_list.begin();
  for (; our_it != our_list.end(), std_it != std_list.end();
       ++our_it, ++std_it) {
    EXPECT_EQ(*our_it, *std_it);
  }
}

TEST(list, Insert_Many) {
  s21::list<int> list = {1, 2, 3, 4, 5};
  s21::list<int>::const_iterator it = list.cbegin();
  std::advance(it, 2);
  list.insert_many(it, 6, 7, 8, 9);

  s21::list<int> check_list = {1, 2, 6, 7, 8, 9, 3, 4, 5};
  s21::list<int>::iterator our_it = list.begin();
  s21::list<int>::iterator chk_it = check_list.begin();
  for (; our_it != list.end(), chk_it != check_list.end(); ++our_it, ++chk_it) {
    EXPECT_EQ(*our_it, *chk_it);
  }
}

TEST(list, Insert_Many2) {
  s21::list<int> list = {1, 2, 3, 4, 5};
  s21::list<int>::const_iterator it = list.cend();
  list.insert_many(it, 6, 7, 8, 9);

  s21::list<int> check_list = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  s21::list<int>::iterator our_it = list.begin();
  s21::list<int>::iterator chk_it = check_list.begin();
  for (; our_it != list.end(), chk_it != check_list.end(); ++our_it, ++chk_it) {
    EXPECT_EQ(*our_it, *chk_it);
  }
}

TEST(list, Insert_Many3) {
  s21::list<int> list = {1, 2, 3, 4, 5};
  s21::list<int>::const_iterator it = list.cbegin();
  std::advance(it, 2);
  list.insert_many(it);

  s21::list<int> check_list = {1, 2, 3, 4, 5};
  s21::list<int>::iterator our_it = list.begin();
  s21::list<int>::iterator chk_it = check_list.begin();
  for (; our_it != list.end(), chk_it != check_list.end(); ++our_it, ++chk_it) {
    EXPECT_EQ(*our_it, *chk_it);
  }
}

TEST(list, Insert_Many_empty) {
  s21::list<int> list;
  s21::list<int>::const_iterator it = list.cbegin();
  list.insert_many(it, 4, 3, 2, 1);

  s21::list<int> check_list = {4, 3, 2, 1};
  s21::list<int>::iterator our_it = list.begin();
  s21::list<int>::iterator chk_it = check_list.begin();
  for (; our_it != list.end(), chk_it != check_list.end(); ++our_it, ++chk_it) {
    EXPECT_EQ(*our_it, *chk_it);
  }
}

TEST(list, Insert_Many_Back) {
  s21::list<int> list = {1, 2, 3, 4, 5};
  list.insert_many_back(6, 7, 8, 9);

  s21::list<int> check_list = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  s21::list<int>::iterator our_it = list.begin();
  s21::list<int>::iterator chk_it = check_list.begin();
  for (; our_it != list.end(), chk_it != check_list.end(); ++our_it, ++chk_it) {
    EXPECT_EQ(*our_it, *chk_it);
  }
}

TEST(list, Insert_Many_Back2) {
  s21::list<int> list = {1, 2, 3, 4, 5};
  list.insert_many_back();

  s21::list<int> check_list = {1, 2, 3, 4, 5};
  s21::list<int>::iterator our_it = list.begin();
  s21::list<int>::iterator chk_it = check_list.begin();
  for (; our_it != list.end(), chk_it != check_list.end(); ++our_it, ++chk_it) {
    EXPECT_EQ(*our_it, *chk_it);
  }
}

TEST(list, Insert_Many_Back_empty) {
  s21::list<int> list;
  list.insert_many_back(4, 3, 2, 1);

  s21::list<int> check_list = {4, 3, 2, 1};
  s21::list<int>::iterator our_it = list.begin();
  s21::list<int>::iterator chk_it = check_list.begin();
  for (; our_it != list.end(), chk_it != check_list.end(); ++our_it, ++chk_it) {
    EXPECT_EQ(*our_it, *chk_it);
  }
}

TEST(list, Insert_Many_Front) {
  s21::list<int> list = {1, 2, 3, 4, 5};
  list.insert_many_front(6, 7, 8, 9);

  s21::list<int> check_list = {6, 7, 8, 9, 1, 2, 3, 4, 5};
  s21::list<int>::iterator our_it = list.begin();
  s21::list<int>::iterator chk_it = check_list.begin();
  for (; our_it != list.end(), chk_it != check_list.end(); ++our_it, ++chk_it) {
    EXPECT_EQ(*our_it, *chk_it);
  }
}

TEST(list, Insert_Many_Front2) {
  s21::list<int> list = {1, 2, 3, 4, 5};
  list.insert_many_front();

  s21::list<int> check_list = {1, 2, 3, 4, 5};
  s21::list<int>::iterator our_it = list.begin();
  s21::list<int>::iterator chk_it = check_list.begin();
  for (; our_it != list.end(), chk_it != check_list.end(); ++our_it, ++chk_it) {
    EXPECT_EQ(*our_it, *chk_it);
  }
}

TEST(list, Insert_Many_Front_empty) {
  s21::list<int> list;
  list.insert_many_front(5, 4, 3, 2, 1);

  s21::list<int> check_list = {5, 4, 3, 2, 1};
  s21::list<int>::iterator our_it = list.begin();
  s21::list<int>::iterator chk_it = check_list.begin();
  for (; our_it != list.end(), chk_it != check_list.end(); ++our_it, ++chk_it) {
    EXPECT_EQ(*our_it, *chk_it);
  }
}

TEST(list, front_back) {
  s21::list<int> our_list = {1, 2, 3, 4, 5, 6};
  std::list<int> std_list = {1, 2, 3, 4, 5, 6};

  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
}