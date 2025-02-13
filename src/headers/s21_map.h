/**
 * @file s21_map.h
 * @authors karstarl (https://edu.21-school.ru/profile/karstarl)
 * @authors shericen (https://edu.21-school.ru/profile/shericen)
 * @brief Header for the map container.
 * @version 1.0
 * @date 2024-12-08
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef SRC_HEADERS_S21_MAP_H_
#define SRC_HEADERS_S21_MAP_H_

#include <initializer_list>  // for init_list type
#include <limits>            // for max()
#include <string>            // for string type

#include "./s21_vector.h"
#include "./tree.h"

/// @brief Namespace for working with containers
namespace s21 {

/**
 * @brief A map container template class.
 *
 * @details
 * This template class map provides a map similar to std::map in the C++
 * Standard Library. It manages a balanced binary search tree of elements of
 * type K and M, supporting various operations including iteration, element
 * access, and size management.
 *
 * @tparam K The type of keys stored in the map.
 * @tparam M The type of values stored in the map.
 */

template <typename K, typename M>
class map {
 public:
  // Type aliases

  typedef typename tree<K, M>::const_iterator MapConstIterator;
  typedef typename tree<K, M>::iterator MapIterator;
  using key_type = K;                               ///< Type of pairs key
  using mapped_type = M;                            ///< Type of keys value
  using value_type = std::pair<K, M>;               ///< Pair key-value
  using reference = value_type &;                   ///< Reference to pair
  using const_reference = const value_type &;       ///< Const reference to pair
  using size_type = std::size_t;                    ///< Containers size type
  using iterator = MapIterator;                     ///< For read/write elements
  using const_iterator = MapConstIterator;          ///< For read elements
  using iterator_bool = std::pair<iterator, bool>;  ///< Pair iterator-bool

  // Constructors/assignment operators/destructor

  map() noexcept = default;
  map(std::initializer_list<value_type> const &items);
  map(const map &m);
  map(map &&m);
  map &operator=(map &&m);
  map &operator=(const map &m);

  // Map Element access

  mapped_type &at(const key_type &key) const;
  mapped_type &operator[](const key_type &key) noexcept;
  const mapped_type &operator[](const key_type &key) const noexcept;

  // Map Iterators

  iterator begin() const noexcept;
  iterator end() const noexcept;
  const_iterator cbegin() const noexcept;
  const_iterator cend() const noexcept;

  // Map Capacity

  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;

  // Map Modifiers

  void clear();
  iterator_bool insert(const_reference value);
  iterator_bool insert(const key_type &key, const mapped_type &obj);
  iterator_bool insert_or_assign(const key_type &key, const mapped_type &obj);
  iterator erase(const_iterator pos);
  iterator erase(const_iterator first, const_iterator last);
  size_type erase(const key_type &key);
  void swap(map &other);
  void merge(map &other);

  template <typename... Args>
  std::pair<iterator, bool> emplace(Args &&...args);
  template <typename... Args>
  vector<std::pair<iterator, bool>> insert_many(Args &&...args);

  // Map Lookup

  bool contains(const key_type &key) const noexcept;
  std::string structure() const noexcept;

 private:
  // Fields

  tree<key_type, mapped_type> tree_{};  ///< Tree of elements
};

#include "./../templates/map.tpp"

}  // namespace s21

#endif
