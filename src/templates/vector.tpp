/**
 * @file vector.tpp
 * @author elmatree (https://edu.21-school.ru/profile/elmatree)
 * @brief Template for the vector container.
 * @version 1.0
 * @date 2024-12-08
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "../headers/s21_vector.h"

using namespace s21;

// Vector Member functions

/**
 * @brief Creates an entity vector.
 *
 * @details
 * Creates a vector entity of size 0
 * and with nullptr pointers for the array of the vector
 *
 */
template <typename T>
vector<T>::vector() : _array(nullptr), _size(0), _capacity(0) {}

/**
 * @brief Creates a vector of the given size.
 *
 * @details
 * This constructor creates a vector of length n
 * and initializes it with 0.
 *
 * @param[in] n Vector size.
 */
template <typename T>
vector<T>::vector(size_type n)
    : _array(new value_type[n]), _size(n), _capacity(n) {
  std::fill_n(_array, n, value_type());
}

/**
 * @brief Constructs a vector with elements from an initializer list.
 *
 * @details
 * This constructor initializes the vector with elements from the given
 * initializer list. It creates a new vector and inserts all elements from the
 * list into the list.
 *
 * @param[in] items The initializer list of values to insert into the vector.
 */
template <typename T>
vector<T>::vector(std::initializer_list<value_type> const &items)
    : vector(items.size()) {
  std::copy(items.begin(), items.end(), _array);
}

/**
 * @brief Copy constructor for the vector.
 *
 * @details
 * This constructor creates a new vector of size 'v' and copies the values
 * ​​in 'v' into it.
 *
 * @param[in] v The vector to copy from.
 */
template <typename T>
vector<T>::vector(const vector &v) : vector(v._capacity) {
  for (size_type i = 0; i < v._capacity; ++i) _array[i] = v._array[i];
}

/**
 * @brief Move constructor for the vector.
 *
 * @details
 * This constructor creates a new vector by moving the elements from another
 * vector. It takes ownership of the elems from the source vector, leaving the
 * source vector in a valid but unspecified state.
 *
 * @param[in] v The vector to move from.
 */
template <typename T>
vector<T>::vector(vector &&v) {
  this->swap(v);
  v._array = nullptr;
  v._size = 0;
  v._capacity = 0;
}

/**
 * @brief Move assignment operator for the vector.
 *
 * @details
 * This operator moves the elements from another vector to the current vector.
 * It first swap the elements from the source vector
 * and then cleans up the another vector
 *
 * @param[in] v The vector to move from.
 * @return vector<T>& - reference to the assigned vector.
 */
template <typename T>
vector<T> &vector<T>::operator=(vector &&v) {
  if (this != &v) {
    this->swap(v);

    delete[] v._array;
    v._array = nullptr;
    v._size = 0;
    v._capacity = 0;
  }
  return *this;
}

/**
 * @brief Destructor.
 *
 * @details
 * Destroys the array and frees allocated memory.
 */
template <typename T>
vector<T>::~vector() {
  delete[] _array;
  _size = 0;
  _capacity = 0;
}

// Vector Element access

/**
 * @brief Access a specified element with bounds checking.
 *
 * @details
 * This method returns a reference to the element
 * that is located in the value specified in the argument.
 *
 * @param[in] pos Position of the searched element.
 * @return reference - to element of the vector.
 */
template <typename T>
typename vector<T>::reference vector<T>::at(size_type pos) {
  if (pos >= this->_size)
    throw std::out_of_range("'pos' must be less than or equal to size");
  return (*this)[pos];
}

/**
 * @brief Access a specified element.
 *
 * @details
 * This method returns a reference to the element
 * that is located in the value specified in the argument.
 *
 * @param[in] pos Position of the searched element.
 * @return reference - to element of the vector.
 */
template <typename T>
typename vector<T>::reference vector<T>::operator[](size_type pos) {
  if (pos >= this->_size)
    throw std::out_of_range("index must be less than or equal to size");
  return *(this->_array + pos);
}

/**
 * @brief Const access a specified element.
 *
 * @details
 * This method returns a const reference to the element
 * that is located in the value specified in the argument.
 *
 * @param[in] pos Position of the searched element.
 * @return const_reference - to element of the vector.
 */
template <typename T>
typename vector<T>::const_reference vector<T>::operator[](
    const size_type pos) const {
  if (pos >= this->_size)
    throw std::out_of_range("index must be less than or equal to size");
  return *(this->_array + pos);
}

/**
 * @brief Access the first element.
 *
 * @details
 * This method returns a constant reference
 * to the first element in the vector.
 *
 * @return const_reference - to the first element of the vector.
 */
template <typename T>
typename vector<T>::const_reference vector<T>::front() const {
  if (_size == 0) throw std::out_of_range("Verctor empty");
  return _array[0];
}

/**
 * @brief Access the last element.
 *
 * @details
 * This method returns a constant reference
 * to the last element in the vector.
 *
 * @return const_reference - to the last element of the vector.
 */
template <typename T>
typename vector<T>::const_reference vector<T>::back() const {
  if (_size == 0) throw std::out_of_range("Verctor empty");
  return _array[_size - 1];
}

/**
 * @brief Direct access to the underlying vector.
 *
 * @details
 * This method returns a direct pointer to the vector.
 *
 * @return iterator - pointer to the vector.
 */
template <typename T>
typename vector<T>::value_type *vector<T>::data() noexcept {
  return _array;
}

// Vector Iterators

/**
 * @brief Returns an iterator to the beginning.
 *
 * @details
 * This method returns an iterator to the first element of the vector.
 *
 * @return iterator - an iterator to the beginning of the vector.
 */
template <typename T>
typename vector<T>::iterator vector<T>::begin() noexcept {
  return iterator(_array);
}

/**
 * @brief Returns an iterator to the end.
 *
 * @details
 * This method returns an iterator to the element following the last element
 * of the vector.
 *
 * @return iterator - an iterator to the end of the vector.
 */
template <typename T>
typename vector<T>::iterator vector<T>::end() noexcept {
  return iterator(_array + _size);
}

/**
 * @brief Returns a const iterator to the beginning of the vector.
 *
 * @details
 * This method returns a const iterator to the first element of the vector.
 *
 * @return const_iterator - a const iterator to the beginning of the vector.
 */
template <typename T>
typename vector<T>::const_iterator vector<T>::cbegin() const noexcept {
  return const_iterator(_array);
}

/**
 * @brief Returns a const iterator to the end of the vector.
 *
 * @details
 * This method returns a const iterator to the element following the last
 * element of the vector.
 *
 * @return const_iterator - a const iterator to the end of the vector.
 */
template <typename T>
typename vector<T>::const_iterator vector<T>::cend() const noexcept {
  return const_iterator(_array + _size);
}

// Vector Capacity

/**
 * @brief checks whether the container is empty.
 *
 * @details
 * This method returns true if the array contains no elements, and false
 * otherwise.
 *
 * @return bool - true if the vector is empty, false otherwise.
 */
template <typename T>
bool vector<T>::empty() const noexcept {
  return _size == 0;
}

/**
 * @brief Returns the number of elements.
 *
 * @details
 * This method returns the number of elements currently stored in the vector.
 *
 * @return size_type - the number of elements in the vector.
 */
template <typename T>
typename vector<T>::size_type vector<T>::size() const noexcept {
  return _size;
}

/**
 * @brief Returns the maximum number of elements the array can hold.
 *
 * @details
 * Returns the maximum number of elements the container is able
 * to hold due to system or library implementation limitation
 *
 * @return size_type - the maximum number of elements.
 */
template <typename T>
typename vector<T>::size_type vector<T>::max_size() const noexcept {
  return std::size_t(__PTRDIFF_MAX__) / sizeof(T);
}

/**
 * @brief Allocate storage of size elements and copies current array elements to
 * a newely allocated array.
 *
 * @details
 * Increase the capacity of the vector (the total number of elements that the
 * vector can hold without requiring reallocation) to a value that's greater or
 * equal to 'size'. If 'size' is greater than the current capacity(), new
 * storage is allocated, otherwise the function does nothing.
 *
 * @param[in] size New vector size.
 *
 */
template <typename T>
void vector<T>::reserve(size_type size) {
  if (this->_capacity < size) {
    T *new_arr = new T[size];
    for (size_type i = 0; i < this->_size; ++i) new_arr[i] = this->_array[i];
    if (this->_array) delete[] this->_array;
    this->_array = new_arr;
    this->_capacity = size;
  }
}

/**
 * @brief Areturns the number of elements that can be held in currently
 * allocated storage.
 *
 * @return Size_t capacity.
 *
 */
template <typename T>
typename vector<T>::size_type vector<T>::capacity() {
  return _capacity;
}

/**
 * @brief Reduces memory usage by freeing unused memory.
 *
 * @details
 * It is a non-binding request to reduce capacity() to size()
 *
 */
template <typename T>
void vector<T>::shrink_to_fit() {
  if (_capacity != _size) {
    T *new_arr = new T[_size];
    for (size_type i = 0; i < _size; ++i) new_arr[i] = _array[i];
    if (_array) delete[] _array;
    _array = new_arr;
    _capacity = _size;
  }
}

// Vector Modifiers

/**
 * @brief Clears the contents.
 *
 * @details
 * Erases all elements from the container. After this call, size() returns zero.
 *
 */
template <typename T>
void vector<T>::clear() noexcept {
  _size = 0;
  _capacity = 0;
}

/**
 * @brief Inserts elements at the specified location in the container.
 *
 * @details
 * Inserts element into concrete pos and returns the iterator that points to the
 * new element.
 * If after the operation the new size() is greater than old capacity() a
 * reallocation takes place.
 *
 * @param[in] pos iterator before which the content will be inserted (pos may be
 * the end() iterator).
 * @param[in] value element value to insert.
 *
 * @return Iterator pointing to the inserted value.
 */
template <typename T>
typename vector<T>::iterator vector<T>::insert(iterator pos,
                                               const_reference value) {
  iterator new_pos;
  if (pos == end()) {
    push_back(value);
    new_pos = --end();
  } else {
    if (_capacity == _size) _capacity = (_capacity) ? _capacity * 2 : 1;
    T *new_arr = new T[_capacity];
    int pos_in_new = 0;
    for (size_type i = 0; i < _size; ++i) {
      if (_array[i] == *pos) {
        new_arr[pos_in_new] = value;
        new_arr[++pos_in_new] = *pos;
        pos_in_new++;
      } else {
        new_arr[pos_in_new] = _array[i];
        pos_in_new++;
      }
    }
    value_type index = pos - begin();
    if (_array) delete[] _array;
    _array = new_arr;
    _size = _size + 1;
    new_pos = begin() + index;
  }
  return new_pos;
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
void vector<T>::erase(iterator pos) {
  size_type index = pos - begin();
  while (index < _size - 1) {
    _array[index] = *++pos;
    ++index;
  }
  --_size;
}

/**
 * @brief Adds an element to the end.
 *
 * @details
 * Adds a new element at the end of the vector container, after its current last
 * element. The content of val is copied (or moved) to the new element.
 * If after the operation the new size() is greater than old capacity() a
 * reallocation takes place.
 *
 * @param[in] value value to be copied (or moved) to the new element.
 *
 */
template <typename T>
void vector<T>::push_back(const_reference value) {
  if (_capacity == _size) {
    _capacity = (_capacity) ? _capacity * 2 : 1;
    T *new_arr = new T[_capacity];
    for (size_type i = 0; i < _size; ++i) new_arr[i] = _array[i];
    if (_array) delete[] _array;
    _array = new_arr;
  }
  _array[_size] = value;
  ++_size;
}

/**
 * @brief Removes the last element.
 *
 * @details
 * Removes the last element of the container.
 * Calling pop_back on an empty container results in undefined behavior.
 *
 */
template <typename T>
void vector<T>::pop_back() {
  if (_size > 0) _size -= 1;
}

/**
 * @brief Swaps the contents.
 *
 * @details
 * After the call to this method, the elements in this container are those which
 * were in other before the call, and the elements of other are those which were
 * in this.
 *
 */
template <typename T>
void vector<T>::swap(vector &other) {
  std::swap(_array, other._array);
  std::swap(_size, other._size);
  std::swap(_capacity, other._capacity);
}

/**
 * @brief Inserts new elements into the container directly before pos.
 *
 * @details
 * This method constructs a new elements directly in the vector using the
 * provided arguments, and inserts it into the vector. This can be more
 * efficient than inserting an already constructed element, as it avoids
 * unnecessary copying or moving. The method ensures that the vector properties
 * are maintained after the insertion.
 *
 * @tparam Args The types of the arguments to forward to the constructor of the
 * element.
 * @param[in] pos iterator before which the content will be inserted (pos may be
 * the end() iterator).
 * @param args The arguments to forward to the constructor of the element.
 *
 * @return An iterator pointing to the first element in the argument vector.
 */
template <typename T>
template <typename... Args>
typename s21::vector<T>::iterator s21::vector<T>::insert_many(
    const_iterator pos, Args &&...args) {
  iterator position = pos.it_const_cast();
  ([&] { position = this->insert(position, args) + 1; }(), ...);
  return position;
}

/**
 * @brief Appends new elements to the end of the container.
 *
 * @details
 * This method constructs a new elements directly in the vector using the
 * provided arguments, and inserts it into the vector. This can be more
 * efficient than inserting an already constructed element, as it avoids
 * unnecessary copying or moving. The method ensures that the vector properties
 * are maintained after the insertion.
 *
 * @tparam Args The types of the arguments to forward to the constructor of the
 * element.
 * @param args The arguments to forward to the constructor of the element.
 */
template <typename T>
template <typename... Args>
void s21::vector<T>::insert_many_back(Args &&...args) {
  // реализация через Lambda expressions
  ([&] { this->push_back(args); }(), ...);
}

// VectorIterator

/**
 * @brief Creates an entity vector iterator.
 *
 */
template <typename T>
inline vector<T>::VectorIterator::VectorIterator() : m_ptr(nullptr) {}

/**
 * @brief Constructs a vector iterator.
 *
 * @param[in] other The other iterator to value.
 */
template <typename T>
inline vector<T>::VectorIterator::VectorIterator(pointer other)
    : m_ptr(other) {}

/**
 * @brief Convert to VectorConstIterator.
 *
 * @return const_iterator
 */
template <typename T>
inline typename vector<T>::iterator vector<T>::VectorIterator::it_const_cast()
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
inline typename vector<T>::VectorIterator::reference
vector<T>::VectorIterator::operator*() const noexcept {
  return *m_ptr;
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
inline typename vector<T>::VectorIterator::pointer
vector<T>::VectorIterator::operator->() const noexcept {
  return m_ptr;
}

/**
 * @brief Pre-increment operator for the vector iterator.
 *
 * @return iterator& - reference to the incremented iterator.
 */
template <typename T>
inline typename vector<T>::iterator &
vector<T>::VectorIterator::operator++() noexcept {
  ++m_ptr;
  return *this;
}

/**
 * @brief Increments the iterator and returns the original position.
 *
 * @return An `iterator` representing the original position of the iterator
 * before the increment.
 */
template <typename T>
inline typename vector<T>::iterator vector<T>::VectorIterator::operator++(
    int) noexcept {
  return iterator(m_ptr++);
}

/**
 * @brief Pre-decrement operator for the vector iterator.
 *
 * @return iterator& - reference to the decremented iterator.
 */
template <typename T>
inline typename vector<T>::iterator &
vector<T>::VectorIterator::operator--() noexcept {
  --m_ptr;
  return *this;
}

/**
 * @brief Decrements the iterator and returns the original position.
 *
 * @return An `iterator` representing the original position of the iterator
 * before the decrement.
 */
template <typename T>
inline typename vector<T>::iterator vector<T>::VectorIterator::operator--(
    int) noexcept {
  return iterator(m_ptr--);
}

/**
 * @brief Advances the iterator by a specified number of positions.
 *
 * @param[in] n The number of positions to advance the iterator.
 */
template <typename T>
inline typename vector<T>::iterator &vector<T>::VectorIterator::operator+=(
    value_type n) noexcept {
  m_ptr += n;
  return *this;
}

/**
 * @brief Addition operator for the vector iterator.
 *
 * @param[in] n The number of positions to shift.
 * @return iterator - before the shift.
 */
template <typename T>
inline typename vector<T>::iterator vector<T>::VectorIterator::operator+(
    value_type n) const noexcept {
  return iterator(m_ptr + n);
}

/**
 * @brief Moves the iterator back by a specified number of positions.
 *
 * @param[in] n The number of positions to move the iterator backward.
 */
template <typename T>
inline typename vector<T>::iterator &vector<T>::VectorIterator::operator-=(
    value_type n) noexcept {
  m_ptr -= n;
  return *this;
}

/**
 * @brief Subtraction operator for the vector iterator.
 *
 * @param[in] n The number of positions to shift.
 * @return iterator - before the shift.
 */
template <typename T>
inline typename vector<T>::iterator vector<T>::VectorIterator::operator-(
    value_type n) const noexcept {
  return iterator(m_ptr - n);
}

/**
 * @brief Difference between iteratorsю
 *
 * @param[in] other Subtractive iterator.
 * @return the number of positions between this and other iterators
 */
template <typename T>
inline typename vector<T>::difference_type vector<T>::VectorIterator::operator-(
    const iterator &other) noexcept {
  return m_ptr - other.m_ptr;
}

/**
 * @brief Iterator comparison 'less'.
 *
 * @details
 * One iterator is smaller than another if it points to an element closer to the
 * beginning
 *
 * @param[in] other Comparable iterator.
 * @return bool - true if this iterator less than other, false otherwise.
 */
template <typename T>
inline bool vector<T>::VectorIterator::operator<(
    const iterator &other) noexcept {
  return other.m_ptr - this->m_ptr > 0;
}

/**
 * @brief Iterator comparison 'larg'.
 *
 * @details
 * One iterator is larger than another if it points to an element that is closer
 * to the end
 *
 * @param[in] other Comparable iterator.
 * @return bool - true if this iterator is greater than the other, false
 * otherwise.
 */
template <typename T>
inline bool vector<T>::VectorIterator::operator>(
    const iterator &other) noexcept {
  return other.m_ptr < this->m_ptr;
}

/**
 * @brief Iterator comparison 'less or equals'.
 *
 * @details
 * One iterator is smaller than another if it points to an element closer to the
 * beginning
 *
 * @param[in] other Comparable iterator.
 * @return bool - true if this iterator less or equals than other, false
 * otherwise.
 */
template <typename T>
inline bool vector<T>::VectorIterator::operator<=(
    const iterator &other) noexcept {
  return !(this->m_ptr > other.m_ptr);
}

/**
 * @brief Iterator comparison 'larg or equals'.
 *
 * @details
 * One iterator is larger than another if it points to an element that is closer
 * to the end
 *
 * @param[in] other Comparable iterator.
 * @return bool - true if this iterator is greater or equals than the other,
 * false otherwise.
 */
template <typename T>
inline bool vector<T>::VectorIterator::operator>=(
    const iterator &other) noexcept {
  return !(this->m_ptr < other.m_ptr);
}

// VectorConstIterator

/**
 * @brief Creates an entity vector const iterator.
 *
 */
template <typename T>
inline vector<T>::VectorConstIterator::VectorConstIterator() : m_ptr(nullptr) {}

/**
 * @brief Constructs a const vector iterator.
 *
 * @param[in] other The other const iterator to value.
 */
template <typename T>
inline vector<T>::VectorConstIterator::VectorConstIterator(const_pointer other)
    : m_ptr(other) {}

/**
 * @brief Convert to VectorIterator.
 *
 * @return iterator
 */
template <typename T>
inline typename vector<T>::iterator
vector<T>::VectorConstIterator::it_const_cast() const noexcept {
  return iterator(const_cast<T *>(m_ptr));
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
inline typename vector<T>::VectorConstIterator::const_reference
vector<T>::VectorConstIterator::operator*() const noexcept {
  return *m_ptr;
}

/**
 * @brief operator '->'
 *
 * @details
 * Get the value it points to.
 *
 * @return const pointer to value
 */
template <typename T>
inline typename vector<T>::VectorConstIterator::pointer
vector<T>::VectorConstIterator::operator->() const noexcept {
  return m_ptr;
}

/**
 * @brief Pre-increment operator for the vector iterator.
 *
 * @return iterator& - reference to the incremented iterator.
 */
template <typename T>
inline typename vector<T>::const_iterator &
vector<T>::VectorConstIterator::operator++() noexcept {
  ++m_ptr;
  return *this;
}

/**
 * @brief Increments the iterator and returns the original position.
 *
 * @return An `iterator` representing the original position of the iterator
 * before the increment.
 */
template <typename T>
inline typename vector<T>::const_iterator
vector<T>::VectorConstIterator::operator++(int) noexcept {
  return const_iterator(m_ptr++);
}

/**
 * @brief Pre-decrement operator for the vector iterator.
 *
 * @return iterator& - reference to the decremented iterator.
 */
template <typename T>
inline typename vector<T>::const_iterator &
vector<T>::VectorConstIterator::operator--() noexcept {
  --m_ptr;
  return *this;
}

/**
 * @brief Decrements the iterator and returns the original position.
 *
 * @return An `iterator` representing the original position of the iterator
 * before the decrement.
 */
template <typename T>
inline typename vector<T>::const_iterator
vector<T>::VectorConstIterator::operator--(int) noexcept {
  return const_iterator(m_ptr--);
}

/**
 * @brief Advances the iterator by a specified number of positions.
 *
 * @param[in] n The number of positions to advance the iterator.
 */
template <typename T>
inline typename vector<T>::const_iterator &
vector<T>::VectorConstIterator::operator+=(value_type n) noexcept {
  m_ptr += n;
  return *this;
}

/**
 * @brief Addition operator for the vector iterator.
 *
 * @param[in] n The number of positions to shift.
 * @return iterator - before the shift.
 */
template <typename T>
inline typename vector<T>::const_iterator
vector<T>::VectorConstIterator::operator+(value_type n) const noexcept {
  return const_iterator(m_ptr + n);
}

/**
 * @brief Moves the iterator back by a specified number of positions.
 *
 * @param[in] n The number of positions to move the iterator backward.
 */
template <typename T>
inline typename vector<T>::const_iterator &
vector<T>::VectorConstIterator::operator-=(value_type n) noexcept {
  m_ptr -= n;
  return *this;
}

/**
 * @brief Subtraction operator for the vector const iterator.
 *
 * @param[in] n The number of positions to shift.
 * @return iterator - before the shift.
 */
template <typename T>
inline typename vector<T>::const_iterator
vector<T>::VectorConstIterator::operator-(value_type n) const noexcept {
  return const_iterator(m_ptr - n);
}

/**
 * @brief Difference between const iterators.
 *
 * @param[in] other Subtractive const iterator.
 * @return the number of positions between this and other iterators
 */
template <typename T>
inline typename vector<T>::difference_type
vector<T>::VectorConstIterator::operator-(
    const const_iterator &other) noexcept {
  return m_ptr - other.m_ptr;
}

/**
 * @brief Iterator comparison 'less'.
 *
 * @details
 * One iterator is smaller than another if it points to an element closer to the
 * beginning
 *
 * @param[in] other Comparable iterator.
 * @return bool - true if this iterator less than other, false otherwise.
 */
template <typename T>
inline bool vector<T>::VectorConstIterator::operator<(
    const const_iterator &other) noexcept {
  return other.m_ptr - this->m_ptr > 0;
}

/**
 * @brief Iterator comparison 'larg'.
 *
 * @details
 * One iterator is larger than another if it points to an element that is closer
 * to the end
 *
 * @param[in] other Comparable iterator.
 * @return bool - true if this iterator is greater than the other, false
 * otherwise.
 */
template <typename T>
inline bool vector<T>::VectorConstIterator::operator>(
    const const_iterator &other) noexcept {
  return other.m_ptr < this->m_ptr;
}

/**
 * @brief Iterator comparison 'less or equals'.
 *
 * @details
 * One iterator is smaller than another if it points to an element closer to the
 * beginning
 *
 * @param[in] other Comparable iterator.
 * @return bool - true if this iterator less or equals than other, false
 * otherwise.
 */
template <typename T>
inline bool vector<T>::VectorConstIterator::operator<=(
    const const_iterator &other) noexcept {
  return !(this->m_ptr > other.m_ptr);
}

/**
 * @brief Iterator comparison 'larg or equals'.
 *
 * @details
 * One iterator is larger than another if it points to an element that is closer
 * to the end
 *
 * @param[in] other Comparable iterator.
 * @return bool - true if this iterator is greater or equals than the other,
 * false otherwise.
 */
template <typename T>
inline bool vector<T>::VectorConstIterator::operator>=(
    const const_iterator &other) noexcept {
  return !(this->m_ptr < other.m_ptr);
}
