/**
 * @file stack.tpp
 * @author elmatree (https://edu.21-school.ru/profile/elmatree)
 * @brief Template for the stack container.
 * @version 1.0
 * @date 2024-12-08
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "../headers/s21_stack.h"

using namespace s21;

// Constructors/assignment operators/destructor

/**
 * @brief Creates an entity stack.
 *
 * @details
 * Creates a stack entity of size 0
 * and with nullptr pointers for the head of the stack
 *
 */
template <typename T>
stack<T>::stack() {
  Size = 0;
  head = nullptr;
}

/**
 * @brief Constructs a stack with elements from an initializer list.
 *
 * @details
 * This constructor initializes the stack with elements from the given
 * initializer list. It creates a new stack and inserts all elements from the
 * list into the list.
 *
 * @param[in] items The initializer list of values to insert into the stack.
 */
template <typename T>
stack<T>::stack(std::initializer_list<T> const &items) : stack() {
  for (auto i : items) {
    push(i);
  }
}

/**
 * @brief Copy constructor for the stack.
 *
 * @details
 * This constructor creates a new stack by copying the elements from another
 * stack.
 *
 * @param[in] s The stack to copy from.
 */
template <typename T>
stack<T>::stack(const stack &s) : stack() {
  *this = s;
}

/**
 * @brief Move constructor for the stack.
 *
 * @details
 * This constructor creates a new stack by moving the elements from another
 * stack. It takes ownership of the elems from the source stack, leaving the
 * source stack in a valid but unspecified state.
 *
 * @param[in] s The stack to move from.
 */
template <typename T>
stack<T>::stack(stack &&s) : stack() {
  if (this != &s) {
    head = s.head;
    Size = s.Size;
    s.head = nullptr;
    s.Size = 0;
  }
}

/**
 * @brief Destructor for the stack.
 *
 * @details
 * Destroys the stack and frees allocated memory.
 *
 */
template <typename T>
inline stack<T>::~stack() {
  int i = size();
  while (i >= 0) {
    pop();
    --i;
  }
  Size = 0;
}

/**
 * @brief Copy assignment operator for the stack.
 *
 * @details
 * This operator copies the elements from another stack to the current stack.
 * It first cleans up the this stack and then copies the elements from the
 * source stack.
 *
 * @param[in] s The stack to copy from.
 * @return stack<T>& - reference to the assigned stack.
 */
template <typename T>
stack<T> &stack<T>::operator=(const stack &s) {
  if (this != &s) {
    while (!empty()) {
      pop();
    }
    stack<T> temp;
    Node<T> *current = s.head;
    while (current) {
      temp.push(current->data);
      current = current->pNext;
    }
    current = temp.head;
    while (current) {
      push(current->data);
      current = current->pNext;
    }
    Size = s.Size;
  }
  return *this;
}

/**
 * @brief Move assignment operator for the stack.
 *
 * @details
 * This operator moves the elements from another stack to the current stack.
 *
 * @param[in] l The stack to move from.
 * @return stack<T>& - reference to the assigned stack.
 */
template <typename T>
stack<T> &stack<T>::operator=(stack &&l) {
  if (this != &l) {
    stack<T> tmp(std::move(l));
    *this = tmp;
  }
  return *this;
}

// Stack Element access

/**
 * @brief Accesses the top element.
 *
 * @details
 * This method returns a constant reference
 * to the top node in the stack.
 *
 * @return const_reference - to the top node of the stack.
 */
template <typename T>
typename stack<T>::const_reference stack<T>::top() const {
  return this->head->data;
}

// Stack Capacity

/**
 * @brief Checks whether the container is empty.
 *
 * @details
 * This method returns true if the stack contains no elements, and false
 * otherwise.
 *
 * @return bool - true if the stack is empty, false otherwise.
 */
template <typename T>
bool stack<T>::empty() const {
  return this->Size == 0;
}

/**
 * @brief Returns the number of elements.
 *
 * @details
 * This method returns the number of elements currently stored in the stack.
 *
 * @return size_type - the number of elements in the stack.
 */
template <typename T>
typename stack<T>::size_type stack<T>::size() const {
  return Size;
}

// List Modifiers

/**
 * @brief Inserts an element at the top.
 *
 * @details
 * Inserts a new element at the top of the stack.
 * The content of val is copied to the inserted element.
 *
 * @param[in] value value to be copied to the inserted element.
 *
 */
template <typename T>
void stack<T>::push(const_reference value) {
  Node<T> *current = this->head;
  head = new Node<T>(value, current);
  ++Size;
}

/**
 * @brief Removes the top element.
 *
 * @details
 * Removes the top element in the stack container, effectively reducing its
 * size by one.
 *
 */
template <typename T>
void stack<T>::pop() {
  if (this->Size > 0) {
    Node<T> *temp = head;
    head = temp->pNext;
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
 * @param[in] other Another list container of the same type as this (i.e., with
 * the same template parameter T).
 *
 */
template <typename T>
void stack<T>::swap(stack &other) noexcept {
  stack<T> temp(*this);
  *this = other;
  other = temp;
}

/**
 * @brief Appends new elements to the end of the container.
 *
 * @details
 * This method constructs a new elements directly in the stack using the
 * provided arguments, and inserts it into the stack. This can be more efficient
 * than inserting an already constructed element, as it avoids unnecessary
 * copying or moving. The method ensures that the stack properties are
 * maintained after the insertion.
 *
 * @tparam Args The types of the arguments to forward to the constructor of the
 * element.
 * @param args The arguments to forward to the constructor of the element.
 */
template <typename T>
template <typename... Args>
void s21::stack<T>::insert_many_back(Args &&...args) {
  ([&] { this->push(args); }(), ...);
}
