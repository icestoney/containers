/**
 * @file s21_vector.h
 * @author elmatree (https://edu.21-school.ru/profile/elmatree)
 * @brief Header for the vector container.
 * @version 1.0
 * @date 2024-12-08
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef SRC_HEADERS_S21_VECTOR_H_
#define SRC_HEADERS_S21_VECTOR_H_

#include <algorithm>
#include <iostream>
#include <utility>

/// @brief Namespace for working with containers
namespace s21 {

/**
 * @brief List container template class.
 *
 * @details
 * Vector is a sequence container that encapsulates a dynamic array for more
 * user-friendly usage. Elements in a vector are stored sequentially, allowing
 * iterating over the vector not only through the provided iterator, but also by
 * manually shifting the pointer to the vector element. The dynamic resizing of
 * the array does not occur every time an element is added or removed, only when
 * the specified buffer size is exceeded. So, the vector stores two values for a
 * size: the size of the stored array (size() method) and the size of the buffer
 * (capacity() method).
 *
 * @tparam The template argument T is a value type of stored in the vector.
 */
template <typename T>
class vector {
 public:
  class VectorIterator;
  class VectorConstIterator;

  // Type overrides

  using value_type = T;                        ///< Type of values
  using reference = T &;                       ///< Reference to value
  using const_reference = const T &;           ///< Const reference to value
  using iterator = VectorIterator;             ///< For read/write elements
  using const_iterator = VectorConstIterator;  ///< For read elements
  using size_type = size_t;                    ///< Containers size type
  using difference_type =
      ptrdiff_t;  ///< A signed integer type that can be used to identify
                  ///< distance between iterator steps

  // Vector Member functions

  vector();
  explicit vector(size_type n);
  vector(std::initializer_list<value_type> const &items);
  vector(const vector &v);
  vector(vector &&v);
  ~vector();
  vector &operator=(vector &&v);

  // Vector Element access

  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference operator[](size_type pos) const;
  const_reference front() const;
  const_reference back() const;
  value_type *data() noexcept;

  // Vector Iterators

  iterator begin() noexcept;
  iterator end() noexcept;
  const_iterator cbegin() const noexcept;
  const_iterator cend() const noexcept;

  // Vector Capacity

  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;
  void reserve(size_type size);
  size_type capacity();
  void shrink_to_fit();

  // Vector Modifiers

  void clear() noexcept;
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(vector &other);

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args);
  template <typename... Args>
  void insert_many_back(Args &&...args);

 private:
  // Fields

  T *_array;            ///< Pointer to allocated memory for elements
  size_type _size;      ///< Number of elements
  size_type _capacity;  ///< Currently allocated storage size
};

/**
 * @brief Internal class defines the type for iterating through the container.
 *
 * @details
 * This class represents an iterator for a vector.
 * Iterator  provides the ability to navigate through the vector
 * and retrieve values ​​from any part of the vector,
 * as well as change these values
 * Iterator category -  LegacyRandomAccessIterator
 *
 * @tparam T is a type of the iterator.
 */
template <typename T>
class vector<T>::VectorIterator {
 public:
  using value_type = T;   ///< Type of values
  using pointer = T *;    ///< Pointer to value
  using reference = T &;  ///< Reference to value
  using iterator_category =
      std::random_access_iterator_tag;  ///< Iterator categories. The
                                        ///< std::random_access_iterator_tag is
                                        ///< what need

  // Constructors/destructor

  VectorIterator();
  explicit VectorIterator(pointer other);
  ~VectorIterator() = default;

  // Convert to VectorConstIterator

  iterator it_const_cast() const noexcept;

  // VectorIterator element access

  reference operator*() const noexcept;
  pointer operator->() const noexcept;

  // Increment/Decrement

  iterator &operator++() noexcept;
  iterator operator++(int) noexcept;
  iterator &operator--() noexcept;
  iterator operator--(int) noexcept;

  // Pointer Arithmetic

  iterator &operator+=(value_type n) noexcept;
  iterator operator+(value_type n) const noexcept;
  iterator &operator-=(value_type n) noexcept;
  iterator operator-(value_type n) const noexcept;
  ptrdiff_t operator-(const iterator &other) noexcept;

  // Comparison

  friend bool operator==(const iterator &a, const iterator &b) noexcept {
    return a.m_ptr == b.m_ptr;
  }
  friend bool operator!=(const iterator &a, const iterator &b) noexcept {
    return a.m_ptr != b.m_ptr;
  }
  bool operator<(const iterator &other) noexcept;
  bool operator>(const iterator &other) noexcept;
  bool operator<=(const iterator &other) noexcept;
  bool operator>=(const iterator &other) noexcept;

 private:
  value_type *m_ptr;  ///< points to an element of the container
};

/**
 * @brief Internal class defines the type for iterating through the container.
 *
 * @details
 * This class represents a const iterator for a vector.
 * Const iterator  provides the ability to navigate through the vector
 * and retrieve values ​​from any part of the vector
 * Iterator category -  LegacyRandomAccessIterator
 *
 * @tparam T is a type of the iterator.
 */
template <typename T>
class vector<T>::VectorConstIterator {
 public:
  using value_type = T;               ///< Type of values
  using pointer = T *;                ///< Pointer to value
  using const_pointer = const T *;    ///< Const pointer to value
  using reference = T &;              ///< Reference to value
  using const_reference = const T &;  ///< Const reference to value
  using iterator_category =
      std::random_access_iterator_tag;  ///< Iterator categories. The
                                        ///< std::random_access_iterator_tag is
                                        ///< what need

  // Constructors/destructor

  VectorConstIterator();
  explicit VectorConstIterator(const_pointer other);
  ~VectorConstIterator() = default;

  // Convert to VectorIterator

  VectorIterator it_const_cast() const noexcept;

  // VectorConstIterator element access

  const_reference operator*() const noexcept;
  pointer operator->() const noexcept;

  // Increment/Decrement

  const_iterator &operator++() noexcept;
  const_iterator operator++(int) noexcept;
  const_iterator &operator--() noexcept;
  const_iterator operator--(int) noexcept;

  // Pointer Arithmetic

  const_iterator &operator+=(value_type n) noexcept;
  const_iterator operator+(value_type n) const noexcept;
  const_iterator &operator-=(value_type n) noexcept;
  const_iterator operator-(value_type n) const noexcept;
  ptrdiff_t operator-(const const_iterator &other) noexcept;

  // Comparison

  friend bool operator==(const const_iterator &a,
                         const const_iterator &b) noexcept {
    return a.m_ptr == b.m_ptr;
  }
  friend bool operator!=(const const_iterator &a,
                         const const_iterator &b) noexcept {
    return a.m_ptr != b.m_ptr;
  }
  bool operator<(const const_iterator &other) noexcept;
  bool operator>(const const_iterator &other) noexcept;
  bool operator<=(const const_iterator &other) noexcept;
  bool operator>=(const const_iterator &other) noexcept;

 private:
  const value_type *m_ptr;  ///< const points to an element of the container
};

#include "../templates/vector.tpp"

}  // namespace s21

#endif  // SRC_HEADERS_S21_VECTOR_H_
