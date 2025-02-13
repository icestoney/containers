/**
 * @file s21_array.h
 * @author elmatree (https://edu.21-school.ru/profile/elmatree)
 * @brief Header for the array container.
 * @version 1.0
 * @date 2024-12-08
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef SRC_HEADERS_S21_ARRAY_H_
#define SRC_HEADERS_S21_ARRAY_H_

#include <algorithm>  // for copy
#include <utility>    // for swap

/// @brief Namespace for working with containers
namespace s21 {

/**
 * @brief Array container template class.
 *
 * @details
 * Array is a sequence container that encapsulates a static array.
 * You cannot add new elements to an array container, you can only modify the
 * value of the original ones. Just like a vector, an array occupies a
 * sequential part of memory.
 *
 * @tparam The first template argument T is a value type of stored in the array.
 * @tparam The second template argument N of the array class is its actual size.
 */
template <typename T, std::size_t N>
class array {
 public:
  // Type overrides

  using value_type = T;               ///< Type of values
  using reference = T &;              ///< Reference to value
  using const_reference = const T &;  ///< Const reference to value
  using size_type = std::size_t;      ///< Containers size type
  using iterator = T *;               ///< For read/write elements
  using const_iterator = const T *;   ///< For read elements

  // Constructors/assignment operators/destructor

  array();
  array(std::initializer_list<value_type> const &items);
  array(const array &v);
  array(array &&v);
  ~array();
  array operator=(const array &v);
  array &operator=(array &&v);

  // Array Element access

  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference front() const;
  const_reference back() const;
  iterator data() noexcept;
  const_iterator data() const noexcept;

  // Array Iterators

  iterator begin() noexcept;
  iterator end() noexcept;
  const_iterator cbegin() const noexcept;
  const_iterator cend() const noexcept;

  // Array Capacity

  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;

  // Array Modifiers

  void swap(array &other);
  void fill(const_reference value);

 private:
  T *_elems;  ///< Pointer to allocated memory for elements
};

#include "./../templates/array.tpp"

}  // namespace s21

#endif  // SRC_HEADERS_S21_ARRAY_H_
