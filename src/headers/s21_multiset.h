/**
 * @file s21_multiset.h
 * @authors karstarl (https://edu.21-school.ru/profile/karstarl)
 * @authors shericen (https://edu.21-school.ru/profile/shericen)
 * @brief Header for the multiset container.
 * @version 1.0
 * @date 2024-12-08
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef SRC_HEADERS_S21_MULTISET_H_
#define SRC_HEADERS_S21_MULTISET_H_

#include <initializer_list>  // for init_list type
#include <limits>            // for max()
#include <string>            // for string type

#include "./s21_set.h"
#include "./s21_vector.h"

/// @brief Namespace for working with containers
namespace s21 {

/**
 * @brief A multiset container template class.
 *
 * @details
 * This template class multiset provides a multiset similar to std::multiset in
 * the C++ Standard Library. It manages a balanced binary search tree of
 * elements of type K, supporting various operations including iteration,
 * element access, and size management.
 *
 * @tparam K The type of keys stored in the multiset.
 */
template <typename K>
class multiset {
 private:
  // Container types

  typedef typename set<K>::const_iterator MultisetConstIterator;
  typedef typename set<K>::iterator MultisetIterator;

 public:
  // Type aliases

  using key_type = const K;                      ///< Type of keys
  using value_type = const K;                    ///< Type of values
  using reference = value_type &;                ///< Reference to value
  using const_reference = const value_type &;    ///< Const reference to value
  using size_type = std::size_t;                 ///< Containers size type
  using iterator = MultisetIterator;             ///< For read/write elements
  using const_iterator = MultisetConstIterator;  ///< For read elements
  using iterator_range = std::pair<iterator, iterator>;  ///< Pair iterator-bool

 private:
  tree<const key_type, const key_type> tree_{
      tree<const key_type, const key_type>::kNON_UNIQUE};  ///< Tree of elements

 public:
  // Constructors/assignment operators/destructor

  multiset() noexcept = default;
  multiset(std::initializer_list<value_type> const &items);
  multiset(const multiset &ms);
  multiset(multiset &&ms);
  multiset &operator=(multiset &&ms);
  multiset &operator=(const multiset &ms);

  // Multiset Iterators

  iterator begin() const noexcept;
  iterator end() const noexcept;
  const_iterator cbegin() const noexcept;
  const_iterator cend() const noexcept;

  // Multiset Capacity

  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;

  // Multiset Modifiers

  void clear();
  iterator insert(const_reference value);
  iterator erase(const_iterator pos);
  void swap(multiset &other);
  void merge(multiset &other);

  template <typename... Args>
  iterator emplace(Args &&...args);
  template <typename... Args>
  vector<std::pair<iterator, bool>> insert_many(Args &&...args);

  // Multiset Lookup

  size_type count(const key_type &key) const noexcept;
  iterator find(const key_type &key) const noexcept;
  bool contains(const key_type &key) const noexcept;
  iterator_range equal_range(const key_type &key) const noexcept;
  iterator lower_bound(const key_type &key);
  iterator upper_bound(const key_type &key);
  std::string structure() const noexcept;
};

#include "./../templates/multiset.tpp"

}  // namespace s21

#endif