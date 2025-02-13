/**
 * @file queue.tpp
 * @author elmatree (https://edu.21-school.ru/profile/elmatree)
 * @brief Template for the queue container.
 * @version 1.0
 * @date 2024-12-08
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "../headers/s21_queue.h"

using namespace s21;

// Constructors/assignment operators/destructor

/**
 * @brief Creates an entity queue.
 *
 * @details
 * Creates a queue entity of size 0
 * and with nullptr pointers for the head and tail of the queue
 *
 */
template <typename T>
queue<T>::queue() {
  Size = 0;
  head = nullptr;
  tail = nullptr;
}

/**
 * @brief Constructs a queue with elements from an initializer list.
 *
 * @details
 * This constructor initializes the queue with elements from the given
 * initializer list. It creates a new queue and inserts all elements from the
 * list into the queue.
 *
 * @param[in] items The initializer queue of values to insert into the list.
 */
template <typename T>
queue<T>::queue(std::initializer_list<T> const &items) : queue() {
  for (auto i : items) {
    push(i);
  }
}

/**
 * @brief Copy constructor for the queue.
 *
 * @details
 * This constructor creates a new queue by copying the elements from another
 * queue.
 *
 * @param[in] q The queue to copy from.
 */
template <typename T>
queue<T>::queue(const queue &q) : queue() {
  Node<T> *tmp = q.head;
  while (tmp) {
    push(tmp->data);
    tmp = tmp->pNext;
  }
}

/**
 * @brief Move constructor for the queue.
 *
 * @details
 * This constructor creates a new queue by moving the elements from another
 * queue. It takes ownership of the elems from the source queue, leaving the
 * source queue in a valid but unspecified state.
 *
 * @param[in] q The queue to move from.
 */
template <typename T>
queue<T>::queue(queue &&q) : queue() {
  if (this != &q) {
    head = q.head;
    tail = q.tail;
    Size = q.Size;
    q.head = nullptr;
    q.tail = nullptr;
    q.Size = 0;
  }
}

/**
 * @brief Destructor for the queue.
 *
 * @details
 * Destroys the queue and frees allocated memory.
 *
 */
template <typename T>
inline queue<T>::~queue() {
  clear();
}

/**
 * @brief Copy assignment operator for the queue.
 *
 * @details
 * This operator copies the elements from another queue to the current queue.
 * It first cleans up the this queue and then copies the elements from the
 * source queue.
 *
 * @param[in] q The queue to copy from.
 * @return queue<T>& - reference to the assigned queue.
 */
template <typename T>
queue<T> &queue<T>::operator=(const queue &q) {
  if (this != &q) {
    while (!empty()) {
      pop();
    }
    Node<T> *current = q.head;
    while (current) {
      push(current->data);
      current = current->pNext;
    }
    Size = q.Size;
  }
  return *this;
}

/**
 * @brief Move assignment operator for the queue.
 *
 * @details
 * This operator moves the elements from another queue to the current queue.
 *
 * @param[in] q The queue to move from.
 * @return queue<T>& - reference to the assigned queue.
 */
template <typename T>
queue<T> &queue<T>::operator=(queue &&q) {
  if (this != &q) {
    queue<T> tmp(std::move(q));
    *this = tmp;
  }
  return *this;
}

// Queue Element access

/**
 * @brief Access to the first node.
 *
 * @details
 * This method returns a constant reference
 * to the first node in the queue.
 *
 * @return const_reference - to the first node of the queue.
 */
template <typename T>
typename queue<T>::const_reference queue<T>::front() const {
  return this->head->data;
}

/**
 * @brief Access to the last node.
 *
 * @details
 * This method returns a constant reference
 * to the last node in the queue.
 *
 * @return const_reference - to the last node of the queue.
 */
template <typename T>
typename queue<T>::const_reference queue<T>::back() const {
  return this->tail->data;
}

// Queue Capacity

/**
 * @brief Checks whether the container is empty.
 *
 * @details
 * This method returns true if the queue contains no elements, and false
 * otherwise.
 *
 * @return bool - true if the queue is empty, false otherwise.
 */
template <typename T>
bool queue<T>::empty() const {
  return this->Size == 0 ? true : false;
}

/**
 * @brief Returns the number of elements.
 *
 * @details
 * This method returns the number of elements currently stored in the queue.
 *
 * @return size_type - the number of elements in the queue.
 */
template <typename T>
typename queue<T>::size_type queue<T>::size() const {
  return Size;
}

// Queue Modifiers

/**
 * @brief Clears the contents.
 *
 * @details
 * The method clears the contents of the container
 *
 */
template <typename T>
void queue<T>::clear() {
  int i = size();
  while (i >= 0) {
    pop();
    --i;
  }
}

/**
 * @brief Adds an element to the end.
 *
 * @details
 * Adds a new element at the end of the queue container, after its current last
 * element. The content of val is copied (or moved) to the new element.
 *
 * @param[in] value value to be copied (or moved) to the new element.
 *
 */
template <typename T>
void queue<T>::push(const_reference value) {
  Node<T> *current = this->tail;
  tail = new Node<T>(value, nullptr, tail);
  if (head == nullptr) {
    head = tail;
  } else {
    current->pNext = tail;
  }
  ++Size;
}

/**
 * @brief Removes the first element.
 *
 * @details
 * Removes the first element in the queue container, effectively reducing its
 * size by one.
 *
 */
template <typename T>
void queue<T>::pop() {
  if (this->Size > 0) {
    Node<T> *temp = head;
    head = temp->pNext;
    if (head == nullptr) {
      tail = head;
    } else {
      head->pPrev = nullptr;
    }
    delete temp;
    --Size;
  }
}

/**
 * @brief Swaps the contents.
 *
 * @details
 * Exchanges the contents of the container adaptor (*this) by those of other.
 * Sizes may differ.
 *
 * @param[in] other Another queue container adaptor of the same type (i.e.,
 * instantiated with the same template parameters, T and Container).
 *
 */
template <typename T>
void queue<T>::swap(queue &other) noexcept {
  queue<T> temp(*this);
  *this = other;
  other = temp;
}

/**
 * @brief Appends new elements to the end of the container.
 *
 * @details
 * This method constructs a new elements directly in the queue using the
 * provided arguments, and inserts it into the queue. This can be more efficient
 * than inserting an already constructed element, as it avoids unnecessary
 * copying or moving. The method ensures that the queue properties are
 * maintained after the insertion.
 *
 * @tparam Args The types of the arguments to forward to the constructor of the
 * element.
 * @param args The arguments to forward to the constructor of the element.
 */
template <typename T>
template <typename... Args>
void queue<T>::insert_many_back(Args &&...args) {
  ([&] { this->push(args); }(), ...);
}