/**
 * @file s21_list.h
 * @author elmatree (https://edu.21-school.ru/profile/elmatree)
 * @brief Header for the list container.
 * @version 1.0
 * @date 2024-12-08
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef SRC_HEADERS_S21_LIST_H_
#define SRC_HEADERS_S21_LIST_H_

#include <iostream>
#include <utility>

/// @brief Namespace for working with containers
namespace s21 {

/**
 * @brief List container template class.
 *
 * @details
 * List is a sequence container that stores a set of elements with arbitrary
 * size, in the form of nodes connected in sequence by pointers. This
 * implementation of the list container uses a doubly linked list. The container
 * class object stores pointers to the "head" and "tail" of the list, pointing
 * to the first and last elements of the list. The List container provides
 * direct access only to the 'head' and 'tail', but allows you to add and delete
 * elements in any part of the list.
 *
 * @tparam The template argument T is a value type of stored in the list.
 */
template <typename T>
class list {
 public:
  // Container types

  class ListIterator;
  class ListConstIterator;

  // Type overrides

  using value_type = T;                      ///< Type of values
  using reference = T &;                     ///< Reference to value
  using const_reference = const T &;         ///< Const reference to value
  using iterator = ListIterator;             ///< For read/write elements
  using const_iterator = ListConstIterator;  ///< For read elements
  using size_type = size_t;                  ///< Containers size type

  // Constructors/assignment operators/destructor

  list();
  explicit list(size_type n);
  list(std::initializer_list<T> const &items);
  list(const list &l);
  list(list &&l);
  ~list();
  list &operator=(const list &l);
  list &operator=(list &&l);

  // List Element access

  const_reference front() const;
  const_reference back() const;

  // List Iterators

  iterator begin() noexcept;
  iterator end() noexcept;
  const_iterator cbegin() const noexcept;
  const_iterator cend() const noexcept;

  // List Capacity

  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;

  // List Modifiers

  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void push_front(const_reference value);
  void pop_front();
  void swap(list &other);
  void merge(list &other);
  void splice(const_iterator pos, list &other);
  void reverse();
  void unique();
  void sort();
  void half_divide(list &tmp);

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args);
  template <typename... Args>
  void insert_many_back(Args &&...args);
  template <typename... Args>
  void insert_many_front(Args &&...args);

 private:
  /**
   * @brief A node in the list.
   *
   * @details
   * This class represents a list node.
   * It contains a pointer to the next node,
   * a pointer to the previous node, and a value
   *
   * @tparam Tn is a value type of stored in the node.
   */
  template <typename Tn>
  class Node {
   public:
    Node *pNext;  ///< pointer to the next node
    Node *pPrev;  ///< pointer to the previous node
    Tn data;      ///< a value
    explicit Node(Tn data = Tn(), Node *pNext = nullptr,
                  Node *pPrev = nullptr) {
      this->data = data;
      this->pNext = pNext;
      this->pPrev = pPrev;
    }
  };
  // Fields

  size_type Size;  ///< Size of list
  Node<T> *head;   ///< Pointer to 'head'
  Node<T> *tail;   ///< Pointer to 'tail'
};

/**
 * @brief Internal class defines the type for iterating through the container.
 *
 * @details
 *
 * This class represents an iterator for a list.
 * Iterator  provides the ability to navigate through the list
 * and retrieve values ​​from any part of the list,
 * as well as change these values
 *
 * @tparam T is a type of the iterator.
 */
template <typename T>
class list<T>::ListIterator {
 public:
  // Type overrides

  using value_type = T;   ///< Type of values
  using pointer = T *;    ///< pointer to value
  using reference = T &;  ///< Reference to value
  using difference_type =
      std::ptrdiff_t;  ///< A signed integer type that can be used to identify
                       ///< distance between iterator steps
  using iterator_category =
      std::bidirectional_iterator_tag;  ///< Iterator categories. The
                                        ///< std::bidirectional_iterator_tag is
                                        ///< what need
  // Constructors/destructor

  ListIterator() noexcept;
  explicit ListIterator(list<T>::Node<T> *node) noexcept;
  ListIterator(list<T>::Node<T> *node, list<T>::Node<T> *last) noexcept;
  ~ListIterator() = default;

  // Convert to ListConstIterator

  iterator it_const_cast() const noexcept;

  // ListIterator element access

  reference operator*() const noexcept;
  pointer operator->() const noexcept;
  list<T>::Node<T> *get();
  void set(list<T>::Node<T> *other);

  // Increment/Decrement

  iterator &operator++() noexcept;
  iterator operator++(int) noexcept;
  iterator &operator--() noexcept;
  iterator operator--(int) noexcept;

  // Comparison

  friend bool operator==(const iterator &a, const iterator &b) noexcept {
    return a.m_ptr == b.m_ptr;
  }
  friend bool operator!=(const iterator &a, const iterator &b) noexcept {
    return a.m_ptr != b.m_ptr;
  }

 protected:
  // Fields

  Node<T> *m_ptr;      ///< points to an element of the container
  Node<T> *last_node;  ///< points to the last element of the container
};

/**
 * @brief Internal class defines the constant type for iterating through the
 * container.
 *
 * @details
 *
 * This class represents an iterator for a list.
 * Iterator  provides the ability to navigate through the list
 * and retrieve values ​​from any part of the list.
 *
 * @tparam T is a type of the iterator.
 */
template <typename T>
class list<T>::ListConstIterator {
 public:
  using value_type = T;   ///< Type of values
  using pointer = T *;    ///< pointer to value
  using reference = T &;  ///< Reference to value
  using difference_type =
      std::ptrdiff_t;  ///< A signed integer type that can be used to identify
                       ///< distance between iterator steps
  using iterator_category =
      std::bidirectional_iterator_tag;  ///< Iterator categories. The
                                        ///< std::bidirectional_iterator_tag is
                                        ///< what need

  // Constructors/destructor

  ListConstIterator() noexcept;
  explicit ListConstIterator(const list<T>::Node<T> *node) noexcept;
  ListConstIterator(const list<T>::Node<T> *node,
                    const list<T>::Node<T> *last) noexcept;
  explicit ListConstIterator(const iterator &other) noexcept;
  ~ListConstIterator() = default;

  // Convert to ListIterator

  iterator it_const_cast() const noexcept;

  // ListConstIterator element access

  const_reference operator*() const;
  pointer operator->();

  // Increment/Decrement

  const_iterator &operator++() noexcept;
  const_iterator operator++(int) noexcept;
  const_iterator &operator--() noexcept;
  const_iterator operator--(int) noexcept;

  // Comparison

  friend bool operator==(const const_iterator &a,
                         const const_iterator &b) noexcept {
    return a.m_ptr == b.m_ptr;
  }
  friend bool operator!=(const const_iterator &a,
                         const const_iterator &b) noexcept {
    return a.m_ptr != b.m_ptr;
  }

 protected:
  // Fields

  const Node<T> *m_ptr;      ///< points to an element of the container
  const Node<T> *last_node;  ///< points to the last element of the container
};

#include "./../templates/list.tpp"

}  // namespace s21

#endif  // SRC_HEADERS_S21_LIST_H_
