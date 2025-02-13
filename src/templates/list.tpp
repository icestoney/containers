/**
 * @file list.tpp
 * @author elmatree (https://edu.21-school.ru/profile/elmatree)
 * @brief Template for the list container.
 * @version 1.0
 * @date 2024-12-08
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "../headers/s21_list.h"

using namespace s21;

// Constructors/assignment operators/destructor

/**
 * @brief Creates an entity list.
 *
 * @details
 * Creates a list entity of size 0
 * and with nullptr pointers for the head and tail of the list
 *
 */
template <typename T>
list<T>::list() {
  Size = 0;
  head = nullptr;
  tail = nullptr;
}

/**
 * @brief Creates a list of the given size.
 *
 * @details
 * This constructor creates a list of length N
 * and initializes it with 0.
 *
 * @param[in] n List size.
 */
template <typename T>
list<T>::list(size_type n) : list() {
  while (n > 0) {
    push_front(0);
    --n;
  }
}

/**
 * @brief Constructs a list with elements from an initializer list.
 *
 * @details
 * This constructor initializes the list with elements from the given
 * initializer list. It creates a new list and inserts all elements from the
 * list into the list.
 *
 * @param[in] items The initializer list of values to insert into the list.
 */
template <typename T>
list<T>::list(std::initializer_list<T> const &items) : list() {
  for (auto i : items) {
    push_back(i);
  }
}

/**
 * @brief Copy constructor for the list.
 *
 * @details
 * This constructor creates a new list by copying the elements from another
 * list.
 *
 * @param[in] l The list to copy from.
 */
template <typename T>
list<T>::list(const list &l) : list() {
  Node<T> *tmp = l.head;
  while (tmp) {
    push_back(tmp->data);
    tmp = tmp->pNext;
  }
}

/**
 * @brief Move constructor for the list.
 *
 * @details
 * This constructor creates a new list by moving the elements from another
 * list. It takes ownership of the elems from the source list, leaving the
 * source list in a valid but unspecified state.
 *
 * @param[in] l The list to move from.
 */
template <typename T>
list<T>::list(list &&l) : list() {
  if (this != &l) {
    head = l.head;
    tail = l.tail;
    Size = l.Size;
    l.head = nullptr;
    l.tail = nullptr;
    l.Size = 0;
  }
}

/**
 * @brief Destructor for the list.
 *
 * @details
 * Destroys the list and frees allocated memory.
 *
 */
template <typename T>
inline list<T>::~list() {
  clear();
}

/**
 * @brief Copy assignment operator for the list.
 *
 * @details
 * This operator copies the elements from another list to the current list.
 * It first cleans up the this list and then copies the elements from the
 * source list.
 *
 * @param[in] l The list to copy from.
 * @return list<T>& - reference to the assigned list.
 */
template <typename T>
list<T> &list<T>::operator=(const list &l) {
  if (this != &l) {
    while (!empty()) {
      pop_front();
    }
    Node<T> *current = l.head;
    while (current) {
      push_back(current->data);
      current = current->pNext;
    }
    Size = l.size();
  }
  return *this;
}

/**
 * @brief Move assignment operator for the list.
 *
 * @details
 * This operator moves the elements from another list to the current list.
 *
 * @param[in] l The list to move from.
 * @return list<T>& - reference to the assigned list.
 */
template <typename T>
list<T> &list<T>::operator=(list &&l) {
  if (this != &l) {
    list<T> tmp(std::move(l));
    *this = tmp;
  }
  return *this;
}

// List Element access

/**
 * @brief Access to the first node.
 *
 * @details
 * This method returns a constant reference
 * to the first node in the list.
 *
 * @return const_reference - to the first node of the list.
 */
template <typename T>
typename list<T>::const_reference list<T>::front() const {
  return this->head->data;
}

/**
 * @brief Access to the last node.
 *
 * @details
 * This method returns a constant reference
 * to the last node in the list.
 *
 * @return const_reference - to the last node of the list.
 */
template <typename T>
typename list<T>::const_reference list<T>::back() const {
  return this->tail->data;
}

// List Iterators

/**
 * @brief Returns an iterator to the beginning.
 *
 * @details
 * This method creates an iterator from a node pointing to the head of the list.
 *
 * @return iterator - an iterator to the first node of the list.
 */
template <typename T>
typename list<T>::iterator list<T>::begin() noexcept {
  return iterator(this->head);
}

/**
 * @brief Returns an iterator to the end.
 *
 * @details
 * Returns an iterator to the element following the last element of the list.
 * This element acts as a placeholder; attempting to access it results in
 * undefined behavior.
 *
 * @return iterator - an iterator to the element following the last element.
 */
template <typename T>
typename list<T>::iterator list<T>::end() noexcept {
  return this->head ? iterator(this->tail->pNext, this->tail) : begin();
}

/**
 * @brief Returns a const iterator to the beginning.
 *
 * @details
 * This method creates a const iterator from a node pointing to the head of the
 * list.
 *
 * @return iterator - a const iterator to the first node of the list.
 */
template <typename T>
typename list<T>::const_iterator list<T>::cbegin() const noexcept {
  return const_iterator(this->head);
}

/**
 * @brief Returns a const iterator to the end.
 *
 * @details
 * Returns an iterator to the element following the last element of the list.
 * This element acts as a placeholder; attempting to access it results in
 * undefined behavior.
 *
 * @return iterator - a const iterator to the element following the last
 * element.
 */
template <typename T>
typename list<T>::const_iterator list<T>::cend() const noexcept {
  return const_iterator(this->tail->pNext, this->tail);
}

// List Capacity

/**
 * @brief Checks whether the container is empty.
 *
 * @details
 * This method returns true if the list contains no elements, and false
 * otherwise.
 *
 * @return bool - true if the list is empty, false otherwise.
 */
template <typename T>
bool list<T>::empty() const noexcept {
  return this->Size == 0;
}

/**
 * @brief Returns the number of elements.
 *
 * @details
 * This method returns the number of elements currently stored in the list.
 *
 * @return size_type - the number of elements in the list.
 */
template <typename T>
typename list<T>::size_type list<T>::size() const noexcept {
  return Size;
}

/**
 * @brief Returns the maximum number of elements the list can hold.
 *
 * @details
 * Returns the maximum number of elements the container is able
 * to hold due to system or library implementation limitation
 *
 * @return size_type - the maximum number of elements.
 */
template <typename T>
typename list<T>::size_type list<T>::max_size() const noexcept {
  return std::size_t(__PTRDIFF_MAX__) / sizeof(Node<T>);
}

// List Modifiers

/**
 * @brief Clears the contents.
 *
 * @details
 * The method clears the contents of the container
 *
 */
template <typename T>
void list<T>::clear() {
  int i = size();
  while (i >= 0) {
    pop_front();
    --i;
  }
}

/**
 * @brief Inserts elements at the specified location in the container.
 *
 * @details
 * Inserts element into concrete pos and returns the iterator that points to the
 * new element.
 *
 * @param[in] pos iterator before which the content will be inserted (pos may be
 * the end() iterator).
 * @param[in] value element value to insert.
 *
 * @return Iterator that points to the new element.
 */
template <typename T>
typename list<T>::iterator list<T>::insert(iterator pos,
                                           const_reference value) {
  if (pos == this->begin()) {
    this->push_front(value);
    pos = this->begin();
  } else if (pos == end()) {
    this->push_back(value);
    pos = --this->end();
  } else {
    Node<T> *current = pos.get();
    Node<T> *newNode = new Node(value, current, current->pPrev);
    current->pPrev->pNext = newNode;
    current->pPrev = newNode;
    ++Size;
    pos.set(newNode);
  }
  return pos;
}

/**
 * @brief Erases element at pos
 *
 * @details
 * References and iterators to the erased elements are invalidated.
 * The iterator pos must be valid and dereferenceable.
 * Thus the end() iterator (which is valid, but is not dereferenceable) cannot
 * be used as a value for pos.
 *
 * @param[in] pos iterator to the element to remove.
 *
 */
template <typename T>
void list<T>::erase(iterator pos) {
  if (pos == this->begin()) {
    this->pop_front();
  } else if (pos.get() == this->tail) {
    this->pop_back();
  } else {
    Node<T> *temp = pos.get();
    temp->pPrev->pNext = temp->pNext;
    temp->pNext->pPrev = temp->pPrev;
    delete temp;
    --this->Size;
  }
}

/**
 * @brief Adds an element to the end.
 *
 * @details
 * Adds a new element at the end of the list container, after its current last
 * element. The content of val is copied (or moved) to the new element.
 *
 * @param[in] value value to be copied (or moved) to the new element.
 *
 */
template <typename T>
void list<T>::push_back(const_reference value) {
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
 * @brief removes the last element.
 *
 * @details
 * Removes the last element in the list container, effectively reducing the
 * container size by one.
 *
 */
template <typename T>
void list<T>::pop_back() {
  Node<T> *temp = tail;
  tail = temp->pPrev;
  tail->pNext = nullptr;
  delete temp;
  --Size;
}

/**
 * @brief Adds an element to the head.
 *
 * @details
 * Inserts a new element at the beginning of the list, right before its current
 * first element. The content of val is copied (or moved) to the inserted
 * element.
 *
 * @param[in] value value to be copied (or moved) to the inserted element.
 *
 */
template <typename T>
void list<T>::push_front(const_reference value) {
  Node<T> *current = this->head;
  head = new Node(value, head);
  if (tail == nullptr) {
    tail = head;
  } else {
    current->pPrev = head;
  }
  ++Size;
}

/**
 * @brief Removes the first element.
 *
 * @details
 * Removes the first element in the list container, effectively reducing its
 * size by one.
 *
 */
template <typename T>
void list<T>::pop_front() {
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
 * Exchanges the content of the container by the content of other, which is
 * another list of the same type. Sizes may differ.
 *
 * After the call to this member function, the elements in this container are
 * those which were in other before the call, and the elements of other are
 * those which were in this.
 *
 * @param[in] other Another list container of the same type as this (i.e., with
 * the same template parameter T).
 *
 */
template <typename T>
void list<T>::swap(list &other) {
  list<T> temp(*this);
  *this = other;
  other = temp;
}

/**
 * @brief Merges two sorted lists.
 *
 * @details
 * Merges other into the list by transferring all of its elements at their
 * respective ordered positions into the container (both containers shall
 * already be ordered).
 *
 * This effectively removes all the elements in other (which becomes empty), and
 * inserts them into their ordered position within container (which expands in
 * size by the number of elements transferred).
 *
 * @param[in] other Another list container of the same type as this (i.e., with
 * the same template parameter T).
 *
 */
template <typename T>
void list<T>::merge(list &other) {
  if (this != &other) {
    iterator first_this = this->begin();
    iterator first_other = other.begin();
    iterator last_this = this->end();
    iterator last_other = other.end();
    while (first_this != last_this && first_other != last_other) {
      if (*first_other <= *first_this) {
        this->insert(first_this, *first_other);
        ++first_other;
      } else {
        ++first_this;
      }
    }
    while (first_other != last_other) {
      this->push_back(*first_other);
      ++first_other;
    }
  }
  other.clear();
}

/**
 * @brief Transfers elements from list other starting from pos.
 *
 * @details
 * No elements are copied or moved, only the internal pointers of the list nodes
 * are re-pointed.
 *
 * Transfers all elements from other into *this. The elements are inserted
 * before the element pointed to by pos. The container other becomes empty after
 * the operation.
 *
 * @param[in] pos position within the container where the elements of other are
 * inserted.
 * @param[in] other Another list container of the same type as this (i.e., with
 * the same template parameter T).
 *
 */
template <typename T>
void list<T>::splice(const_iterator pos, list &other) {
  iterator p = pos.it_const_cast();
  list<T>::Node<T> *node_tmp = p.get();
  if (this != &other && other.head != nullptr) {
    if (this->head == nullptr) {
      this->head = other.head;
      this->tail = other.tail;
    } else if (p == this->begin()) {
      this->head = other.head;
      other.tail->pNext = node_tmp;
      node_tmp->pPrev = other.tail;
    } else if (p == this->end()) {
      other.head->pPrev = this->tail;
      this->tail->pNext = other.head;
      this->tail = other.tail;
    } else {
      Node<T> *current = node_tmp;
      current->pPrev->pNext = other.head;
      other.head->pPrev = current->pPrev;
      other.tail->pNext = current;
    }
  }
  this->Size += other.Size;
  other.head = nullptr;
  other.tail = nullptr;
  other.Size = 0;
}

/**
 * @brief Reverses the order of the elements.
 *
 * @details
 * Reverses the order of the elements in the list container.
 *
 */
template <typename T>
void list<T>::reverse() {
  if (this->Size > 1) {
    Node<T> *current = this->head;
    for (size_type i = 0; i < this->size(); ++i) {
      std::swap(current->pNext, current->pPrev);
      current = current->pPrev;
    }
    std::swap(this->head, this->tail);
  }
}

/**
 * @brief Removes consecutive duplicate elements.
 *
 * @details
 * Removes all but the first element from every consecutive group of equal
 * elements in the container. Notice that an element is only removed from the
 * list container if it compares equal to the element immediately preceding it.
 * Thus, this function is especially useful for sorted lists.
 *
 */
template <typename T>
void list<T>::unique() {
  iterator first = this->begin();
  iterator last = --this->end();
  if (first != last) {
    list<T> tmp;
    tmp.push_back(*first);
    iterator next = first;
    while (++next != last) {
      if (*first != *next) {
        tmp.push_back(*next);
      }
      first = next;
    }
    if (*first != *next) {
      tmp.push_back(*next);
    }
    *this = tmp;
  }
}

/**
 * @brief Sorts the elements.
 *
 * @details
 * Sorts the elements in the list, altering their position within the container.
 * The sorting is performed by applying an algorithm merg sort
 *
 */
template <typename T>
void list<T>::sort() {
  s21::list<T> tmp;
  if (this->Size > 1) {
    this->half_divide(tmp);
    if (this->Size > 1) {
      this->sort();
    }
    if (tmp.Size > 1) {
      tmp.sort();
    }
    this->merge(tmp);
  }
}

/**
 * @brief Dividing a list in half.
 *
 * @details
 * Sorting Helper Function
 * The method divides this list into half. The first half is written to tmp, the
 * second is left in this
 *
 * @param[in] tmp Another list container of the same type as this (i.e., with
 * the same template parameter T).
 */
template <typename T>
void list<T>::half_divide(list &tmp) {
  int middle = this->Size / 2;
  iterator it = this->begin();
  std::advance(it, middle);
  Node<T> *node_tmp = it.get();
  tmp.head = this->head;
  tmp.tail = node_tmp->pPrev;
  tmp.tail->pNext = nullptr;
  node_tmp->pPrev = nullptr;
  this->head = it.get();
  tmp.Size = middle;
  this->Size = this->Size - middle;
}

/**
 * @brief Inserts new elements into the container directly before pos.
 *
 * @details
 * This method constructs a new elements directly in the list using the provided
 * arguments, and inserts it into the list. This can be more efficient than
 * inserting an already constructed element, as it avoids unnecessary copying or
 * moving. The method ensures that the list properties are maintained after the
 * insertion.
 *
 * @tparam Args The types of the arguments to forward to the constructor of the
 * element.
 * @param[in] pos iterator before which the content will be inserted (pos may be
 * the end() iterator).
 * @param args The arguments to forward to the constructor of the element.
 *
 * @return An iterator pointing to the first element in the argument list.
 */
template <typename T>
template <typename... Args>
typename s21::list<T>::iterator s21::list<T>::insert_many(const_iterator pos,
                                                          Args &&...args) {
  iterator position = pos.it_const_cast();
  ([&] { this->insert(position, args); }(), ...);
  return position;
}

/**
 * @brief Appends new elements to the end of the container.
 *
 * @details
 * This method constructs a new elements directly in the list using the provided
 * arguments, and inserts it into the list. This can be more efficient than
 * inserting an already constructed element, as it avoids unnecessary copying or
 * moving. The method ensures that the list properties are maintained after the
 * insertion.
 *
 * @tparam Args The types of the arguments to forward to the constructor of the
 * element.
 * @param args The arguments to forward to the constructor of the element.
 */
template <typename T>
template <typename... Args>
void s21::list<T>::insert_many_back(Args &&...args) {
  ([&] { this->push_back(args); }(), ...);
}

/**
 * @brief Appends new elements to the top of the container.
 *
 * @details
 * This method constructs a new elements directly in the list using the provided
 * arguments, and inserts it into the list. This can be more efficient than
 * inserting an already constructed element, as it avoids unnecessary copying or
 * moving. The method ensures that the list properties are maintained after the
 * insertion.
 *
 * @tparam Args The types of the arguments to forward to the constructor of the
 * element.
 * @param args The arguments to forward to the constructor of the element.
 */
template <typename T>
template <typename... Args>
void list<T>::insert_many_front(Args &&...args) {
  if (sizeof...(args) > 0) {
    s21::list<T> tmp = {std::forward<Args>(args)...};
    this->splice(cbegin(), tmp);
  }
}

// ListIterator

/**
 * @brief Creates an entity list iterator.
 *
 */
template <typename T>
inline list<T>::ListIterator::ListIterator() noexcept : m_ptr(), last_node() {}

/**
 * @brief Constructs a list iterator.
 *
 * @param[in] node The node to which the iterator points.
 */
template <typename T>
inline list<T>::ListIterator::ListIterator(list<T>::Node<T> *node) noexcept
    : m_ptr(node), last_node(node) {}

/**
 * @brief Constructs a list iterator.
 *
 * @param[in] node The node to which the iterator points.
 * @param[in] last The last node in the list (required for end() to work
 * correctly).
 */
template <typename T>
inline list<T>::ListIterator::ListIterator(list<T>::Node<T> *node,
                                           list<T>::Node<T> *last) noexcept
    : m_ptr(node), last_node(last) {}

/**
 * @brief Convert to ListConstIterator.
 *
 * @return const_iterator
 */
template <typename T>
typename list<T>::iterator list<T>::ListIterator::it_const_cast()
    const noexcept {
  return *this;
}

/**
 * @brief operator '*'
 *
 * @details
 * Get the value it points to.
 *
 * @return reference to value
 */
template <typename T>
typename list<T>::ListIterator::reference list<T>::ListIterator::operator*()
    const noexcept {
  return m_ptr->data;
}

/**
 * @brief operator '->'
 *
 * @details
 * Get the value it points to.
 *
 * @return pointer to value
 */
template <typename T>
typename list<T>::ListIterator::pointer list<T>::ListIterator::operator->()
    const noexcept {
  return m_ptr->data;
}

/**
 * @brief Getter.
 *
 * @details
 * Get a pointer to the node pointed to by the iterator.
 *
 * @return pointer to list<T>::Node<T>.
 */
template <typename T>
typename list<T>::Node<T> *list<T>::ListIterator::get() {
  return m_ptr;
}

/**
 * @brief Setter.
 *
 * @details
 * Set the iterator pointer to the other node.
 *
 * @param[in] other pointer to list<T>::Node<T>.
 */
template <typename T>
void list<T>::ListIterator::set(list<T>::Node<T> *other) {
  this->m_ptr = other;
}

/**
 * @brief Pre-increment operator for the list iterator.
 *
 * @return iterator& - reference to the incremented iterator.
 */
template <typename T>
typename list<T>::iterator &list<T>::ListIterator::operator++() noexcept {
  m_ptr = m_ptr->pNext;
  return *this;
}

/**
 * @brief Increments the iterator and returns the original position.
 *
 * @return An `iterator` representing the original position of the iterator
 * before the increment.
 */
template <typename T>
typename list<T>::iterator list<T>::ListIterator::operator++(int) noexcept {
  iterator tmp = *this;
  m_ptr = m_ptr->pNext;
  return tmp;
}

/**
 * @brief Pre-decrement operator for the list iterator.
 *
 * @return iterator& - reference to the decremented iterator.
 */
template <typename T>
typename list<T>::iterator &list<T>::ListIterator::operator--() noexcept {
  m_ptr ? m_ptr = m_ptr->pPrev : m_ptr = last_node;
  return *this;
}

/**
 * @brief Decrements the iterator and returns the original position.
 *
 * @return An `iterator` representing the original position of the iterator
 * before the decrement.
 */
template <typename T>
typename list<T>::iterator list<T>::ListIterator::operator--(int) noexcept {
  iterator tmp = *this;
  m_ptr ? m_ptr = tmp.m_ptr->pPrev : m_ptr = tmp.last_node;
  return tmp;
}

// ListConstIterator

/**
 * @brief Creates an entity list const iterator.
 *
 */
template <typename T>
inline list<T>::ListConstIterator::ListConstIterator() noexcept
    : m_ptr(), last_node() {}

/**
 * @brief Constructs a list const iterator.
 *
 * @param[in] node The node to which the iterator points.
 */
template <typename T>
inline list<T>::ListConstIterator::ListConstIterator(
    const list<T>::Node<T> *node) noexcept
    : m_ptr(node), last_node(node) {}

/**
 * @brief Constructs a list const iterator.
 *
 * @param[in] node The node to which the iterator points.
 * @param[in] last The last node in the list (required for end() to work
 * correctly).
 */
template <typename T>
inline list<T>::ListConstIterator::ListConstIterator(
    const list<T>::Node<T> *node, const list<T>::Node<T> *last) noexcept
    : m_ptr(node), last_node(last) {}

/**
 * @brief Copy constructor for the list const iterator.
 *
 * @param[in] other The iterator to copy from.
 */
template <typename T>
inline list<T>::ListConstIterator::ListConstIterator(
    const iterator &other) noexcept
    : m_ptr(other.m_ptr), last_node(other.m_ptr) {}

/**
 * @brief Convert to ListIterator.
 *
 * @return iterator
 */
template <typename T>
typename list<T>::iterator list<T>::ListConstIterator::it_const_cast()
    const noexcept {
  return iterator(const_cast<list<T>::Node<T> *>(m_ptr));
}

/**
 * @brief operator '*'
 *
 * @details
 * Get the value it points to.
 *
 * @return const reference to value
 */
template <typename T>
typename list<T>::const_reference list<T>::ListConstIterator::operator*()
    const {
  return m_ptr->data;
}

/**
 * @brief operator '->'
 *
 * @details
 * Get the value it points to.
 *
 * @return pointer to value
 */
template <typename T>
typename list<T>::ListConstIterator::pointer
list<T>::ListConstIterator::operator->() {
  return m_ptr;
}

/**
 * @brief Pre-increment operator for the list iterator.
 *
 * @return const iterator& - reference to the incremented const iterator.
 */
template <typename T>
typename list<T>::const_iterator &
list<T>::ListConstIterator::operator++() noexcept {
  m_ptr = m_ptr->pNext;
  return *this;
}

/**
 * @brief Increments the iterator and returns the original position.
 *
 * @return An `const_iterator` representing the original position of the
 * iterator before the increment.
 */
template <typename T>
typename list<T>::const_iterator list<T>::ListConstIterator::operator++(
    int) noexcept {
  const_iterator tmp = *this;
  m_ptr = m_ptr->pNext;
  return tmp;
}

/**
 * @brief Pre-decrement operator for the list iterator.
 *
 * @return const iterator& - reference to the decremented const iterator.
 */
template <typename T>
typename list<T>::const_iterator &
list<T>::ListConstIterator::operator--() noexcept {
  m_ptr ? m_ptr = m_ptr->pPrev : m_ptr = last_node;
  return *this;
}

/**
 * @brief Decrements the iterator and returns the original position.
 *
 * @return An `const_iterator` representing the original position of the
 * iterator before the decrement.
 */
template <typename T>
typename list<T>::const_iterator list<T>::ListConstIterator::operator--(
    int) noexcept {
  const_iterator tmp = *this;
  m_ptr ? m_ptr = tmp.m_ptr->pPrev : m_ptr = tmp.last_node;
  return tmp;
}
