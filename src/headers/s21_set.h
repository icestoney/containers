/**
 * @file s21_set.h
 * @authors karstarl (https://edu.21-school.ru/profile/karstarl)
 * @authors shericen (https://edu.21-school.ru/profile/shericen)
 * @brief Header for the set container.
 * @version 1.0
 * @date 2024-12-08
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef SRC_HEADERS_S21_SET_H_
#define SRC_HEADERS_S21_SET_H_

#include <initializer_list>  // for init_list type
#include <limits>            // for max()
#include <string>            // for string type
#include <utility>           // for pair

#include "./s21_vector.h"
#include "./tree.h"

/// @brief Namespace for working with containers
namespace s21 {

/**
 * @brief A set container template class.
 *
 * @details
 * This template class set provides a set similar to std::set in the C++
 * Standard Library. It manages a balanced binary search tree of elements of
 * type K, supporting various operations including iteration, element access,
 * and size management.
 *
 * @tparam K The type of keys stored in the set.
 */
template <typename K>
class set {
 public:
  // Container types

  class SetConstIterator;
  class SetIterator;

  // Type aliases

  using key_type = const K;                    ///< Type of keys
  using value_type = const K;                  ///< Type of values
  using reference = value_type &;              ///< Reference to value
  using const_reference = const value_type &;  ///< Const reference to value
  using size_type = std::size_t;               ///< Containers size type
  using iterator = SetIterator;                ///< For read/write elements
  using const_iterator = SetConstIterator;     ///< For read elements
  using iterator_bool = std::pair<iterator, bool>;  ///< Pair iterator-bool

  // Constructors/assignment operators/destructor

  set() noexcept = default;
  set(std::initializer_list<value_type> const &items);
  set(const set &s);
  set(set &&s);
  set &operator=(set &&s);
  set &operator=(const set &s);

  // Set Iterators

  iterator begin() const noexcept;
  iterator end() const noexcept;
  const_iterator cbegin() const noexcept;
  const_iterator cend() const noexcept;

  // Set Capacity

  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;

  // Set Modifiers

  void clear();
  iterator_bool insert(const_reference value);
  iterator erase(const_iterator pos);
  iterator erase(const_iterator first, const_iterator last);
  void swap(set &other);
  void merge(set &other);

  template <typename... Args>
  std::pair<iterator, bool> emplace(Args &&...args);
  template <typename... Args>
  vector<std::pair<iterator, bool>> insert_many(Args &&...args);

  // Set Lookup

  iterator find(const key_type &key) const noexcept;
  bool contains(const key_type &key) const noexcept;

 private:
  // Fields

  tree<const key_type, const key_type> tree_{};  ///< Tree of elements
};

/**
 * @brief An iterator for the set.
 *
 * @details
 * This class represents an iterator for the set. It allows traversal
 * of the set and access to its elements.
 *
 * @tparam K The type of keys stored in the set.
 */
template <typename K>
class set<K>::SetIterator : public tree<const K, const K>::TreeIterator {
 public:
  // Type aliases

  using _tree_it = typename tree<const K, const K>::TreeIterator;

  // Constructors

  SetIterator() noexcept = default;
  SetIterator(const SetIterator &other) noexcept : _tree_it{other} {}
  SetIterator(const _tree_it &other) noexcept : _tree_it{other} {}

  // Operators

  iterator &operator=(const iterator &other) noexcept;
  iterator &operator++() noexcept;
  iterator &operator--() noexcept;
  iterator operator++(int) noexcept;
  iterator operator--(int) noexcept;
  iterator operator+(size_type shift) const noexcept;
  iterator operator-(size_type shift) const noexcept;
  reference operator*() noexcept;
};

/**
 * @brief A constant iterator for the set.
 *
 * @details
 * This class represents a constant iterator for the set. It allows
 * traversal of the set and read-only access to its elements.
 *
 * @tparam K The type of keys stored in the set.
 */
template <typename K>
class set<K>::SetConstIterator
    : public tree<const K, const K>::TreeConstIterator {
 public:
  // Type aliases

  using _tree_cit = typename tree<const K, const K>::TreeConstIterator;

  // Constructors

  SetConstIterator() noexcept = default;
  SetConstIterator(const iterator &other) noexcept : _tree_cit(other) {}
  SetConstIterator(const const_iterator &other) noexcept : _tree_cit(other) {}
  SetConstIterator(const _tree_cit &other) noexcept : _tree_cit(other) {}

  // Operators

  const_iterator &operator=(const const_iterator &other) noexcept;
  const_iterator &operator++() noexcept;
  const_iterator &operator--() noexcept;
  const_iterator operator++(int) noexcept;
  const_iterator operator--(int) noexcept;
  const_iterator operator+(size_type shift) const noexcept;
  const_iterator operator-(size_type shift) const noexcept;
  const_reference operator*() const noexcept;
};

#include "./../templates/set.tpp"

}  // namespace s21

#endif
