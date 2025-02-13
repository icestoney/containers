/**
 * @file s21_queue.h
 * @author elmatree (https://edu.21-school.ru/profile/elmatree)
 * @brief Header for the queue container.
 * @version 1.0
 * @date 2024-12-08
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef SRC_HEADERS_S21_QUEUE_H_
#define SRC_HEADERS_S21_QUEUE_H_

#include <iostream>
#include <utility>

/// @brief Namespace for working with containers
namespace s21 {

/**
 * @brief Queue container template class.
 *
 * @details
 * Queue is a container with elements organized according to FIFO (First-In,
 * First-Out) principle. Just like a list, an object of the queue container
 * class has pointers to the "tail" and "head" of the queue, but the deletion is
 * performed strictly from the "head", and the addition of new elements is
 * performed strictly in the "tail".
 *
 * @tparam The template argument T is a value type of stored in the queue.
 */
template <typename T>
class queue {
 public:
  // Type overrides

  using value_type = T;               ///< Type of values
  using reference = T &;              ///< Reference to value
  using const_reference = const T &;  ///< Const reference to value
  using size_type = size_t;           ///< Containers size type

  // Constructors/assignment operators/destructor

  queue();
  queue(std::initializer_list<T> const &items);
  queue(const queue &q);
  queue(queue &&q);
  ~queue();
  queue &operator=(const queue &q);
  queue &operator=(queue &&q);

  // Queue Element access

  const_reference front() const;
  const_reference back() const;

  // Queue Capacity

  bool empty() const;
  size_type size() const;

  // Queue Modifiers

  void clear();
  void push(const_reference value);
  void pop();
  void swap(queue &other) noexcept;

  template <typename... Args>
  void insert_many_back(Args &&...args);

 private:
  /**
   * @brief A node in the queue.
   *
   * @details
   * This class represents a queue node.
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
    explicit Node(T data = Tn(), Node *pNext = nullptr, Node *pPrev = nullptr) {
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

#include "./../templates/queue.tpp"

}  // namespace s21

#endif  // SRC_HEADERS_S21_QUEUE_H_
