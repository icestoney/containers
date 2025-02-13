/**
 * @file s21_stack.h
 * @author elmatree (https://edu.21-school.ru/profile/elmatree)
 * @brief Header for the stack container.
 * @version 1.0
 * @date 2024-12-08
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef SRC_HEADERS_S21_STACK_H_
#define SRC_HEADERS_S21_STACK_H_

#include <iostream>
#include <utility>

/// @brief Namespace for working with containers
namespace s21 {

/**
 * @brief Stack container template class.
 *
 * @details
 * Stack is a container with elements organized according to LIFO (Last-In,
 * First-Out) principle. A stack container class object contains pointers to the
 * "head" of the stack; removing and adding elements is done strictly from the
 * "head".
 *
 * @tparam The template argument T is a value type of stored in the stack.
 */
template <typename T>
class stack {
 public:
  // Type overrides

  using value_type = T;               ///< Type of values
  using reference = T &;              ///< Reference to value
  using const_reference = const T &;  ///< Const reference to value
  using size_type = size_t;           ///< Containers size type

  // Constructors/assignment operators/destructor

  stack();
  stack(std::initializer_list<T> const &items);
  stack(const stack &s);
  stack(stack &&s);
  ~stack();
  stack &operator=(const stack &s);
  stack &operator=(stack &&s);

  // Stack Element access

  const_reference top() const;

  // List Capacity

  bool empty() const;
  size_type size() const;

  // List Modifiers

  void push(const_reference value);
  void pop();
  void swap(stack &other) noexcept;

  template <typename... Args>
  void insert_many_back(Args &&...args);

 private:
  /**
   * @brief A node in the stack.
   *
   * @details
   * This class represents a stack node.
   * It contains a pointer to the next node and a value
   *
   * @tparam Tn is a value type of stored in the node.
   */
  template <typename Tn>
  class Node {
   public:
    Node *pNext;  ///< pointer to the next node
    Tn data;      ///< a value
    explicit Node(T data = Tn(), Node *pNext = nullptr) {
      this->data = data;
      this->pNext = pNext;
    }
  };
  // Fields

  size_type Size;  ///< Size of list
  Node<T> *head;   ///< Pointer to 'head'
};

#include "../templates/stack.tpp"

}  // namespace s21

#endif  // SRC_HEADERS_S21_STACK_H_
