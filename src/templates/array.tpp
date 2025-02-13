/**
 * @file array.tpp
 * @author elmatree (https://edu.21-school.ru/profile/elmatree)
 * @brief Template for the array container.
 * @version 1.0
 * @date 2024-12-08
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "./../headers/s21_array.h"

using namespace s21;

// Constructors/assignment operators/destructor

/**
 * @brief Creates an array of the given size.
 *
 * @details
 * This constructor creates an array of length N
 * and initializes it with the minimum values ​​of type.
 *
 */
template <typename T, std::size_t N>
array<T, N>::array() : _elems(new T[N]) {
  std::fill_n(_elems, N, value_type());
}

/**
 * @brief Constructs an array with elements from an initializer list.
 *
 * @details
 * This constructor initializes the array with elements from the given
 * initializer list. It creates a new array and inserts all elements from the
 * list into the array.
 *
 * @param[in] items The initializer list of values to insert into the array.
 */
template <typename T, std::size_t N>
array<T, N>::array(std::initializer_list<value_type> const &items)
    : _elems(new T[N]) {
  std::copy(items.begin(), items.end(), _elems);
}

/**
 * @brief Copy constructor for the array.
 *
 * @details
 * This constructor creates a new array by copying the elements from another
 * array. It initializes the _elems with the elements from the source array.
 *
 * @param[in] a The array to copy from.
 */
template <typename T, std::size_t N>
array<T, N>::array(const array &a) : _elems(new T[N]) {
  std::copy(a._elems, a._elems + N, _elems);
}

/**
 * @brief Move constructor for the array.
 *
 * @details
 * This constructor creates a new array by moving the elements from another
 * array. It takes ownership of the elems from the source array, leaving the
 * source array in a valid but unspecified state.
 *
 * @param[in] a The array to move from.
 */
template <typename T, std::size_t N>
array<T, N>::array(array &&a) : _elems(new T[N]) {
  std::move(a._elems, a._elems + N, _elems);
}

/**
 * @brief Copy assignment operator for the array.
 *
 * @details
 * This operator copies the elements from another array to the current array.
 * It first cleans up the current array and then copies the elements from the
 * source array.
 *
 * @param[in] a The array to copy from.
 * @return array<T, N>& - reference to the assigned array.
 */
template <typename T, std::size_t N>
array<T, N> array<T, N>::operator=(const array &a) {
  if (this != &a) std::copy(a._elems, a._elems + N, _elems);
  return *this;
}

/**
 * @brief Move assignment operator for the array.
 *
 * @details
 * This operator moves the elements from another array to the current array.
 * It first swap the elements from the source array
 * and then cleans up the another array
 *
 * @param[in] a The array to move from.
 * @return array<T, N>& - reference to the assigned array.
 */
template <typename T, std::size_t N>
array<T, N> &array<T, N>::operator=(array &&a) {
  std::move(a._elems, a._elems + N, _elems);
  return *this;
}

/**
 * @brief Destructor.
 *
 * @details
 * Destroys the array and frees allocated memory.
 */
template <typename T, std::size_t N>
array<T, N>::~array() {
  delete[] _elems;
}

// Array Element access

/**
 * @brief Access a specified element with bounds checking.
 *
 * @details
 * This method returns a reference to the element
 * that is located in the value specified in the argument.
 *
 * @param[in] pos Position of the searched element.
 * @return reference - to element of the array.
 */
template <typename T, std::size_t N>
typename array<T, N>::reference array<T, N>::at(size_type pos) {
  if (pos >= N)
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
 * @return reference - to element of the array.
 */
template <typename T, std::size_t N>
typename array<T, N>::reference array<T, N>::operator[](size_type pos) {
  if (pos >= size())
    throw std::out_of_range("index must be less than or equal to size");
  return *(this->_elems + pos);
}

/**
 * @brief Access the first element.
 *
 * @details
 * This method returns a constant reference
 * to the first element in the array
 *
 * @return const_reference - to the first element of the array.
 */
template <typename T, std::size_t N>
typename array<T, N>::const_reference array<T, N>::front() const {
  if (N == 0) throw std::out_of_range("Verctor empty");
  return *cbegin();
}

/**
 * @brief Access the last element.
 *
 * @details
 * This method returns a constant reference
 * to the last element in the array
 *
 * @return const_reference - to the last element of the array.
 */
template <typename T, std::size_t N>
typename array<T, N>::const_reference array<T, N>::back() const {
  if (N == 0) throw std::out_of_range("Verctor empty");
  return *(cend() - 1);
}

/**
 * @brief Direct access to the underlying array.
 *
 * @details
 * This method returns a direct pointer to the array.
 *
 * @return iterator - pointer to the array.
 */
template <typename T, std::size_t N>
typename array<T, N>::iterator array<T, N>::data() noexcept {
  return _elems;
}

/**
 * @brief Direct const access to the underlying array.
 *
 * @details
 * This method returns a direct const pointer to the array.
 *
 * @return const_iterator - pointer to the array.
 */
template <typename T, std::size_t N>
typename array<T, N>::const_iterator array<T, N>::data() const noexcept {
  return _elems;
}

// Array Iterators

/**
 * @brief Returns an iterator to the beginning.
 *
 * @details
 * This method returns an iterator to the first element of the array.
 *
 * @return iterator - an iterator to the beginning of the array.
 */
template <typename T, std::size_t N>
typename array<T, N>::iterator array<T, N>::begin() noexcept {
  return iterator(data());
}

/**
 * @brief Returns an iterator to the end.
 *
 * @details
 * This method returns an iterator to the element following the last element
 * of the array.
 *
 * @return iterator - an iterator to the end of the array.
 */
template <typename T, std::size_t N>
typename array<T, N>::iterator array<T, N>::end() noexcept {
  return iterator(data() + N);
}

/**
 * @brief Returns a const iterator to the beginning of the array.
 *
 * @details
 * This method returns a const iterator to the first element of the array.
 *
 * @return const_iterator - a const iterator to the beginning of the array.
 */
template <typename T, std::size_t N>
typename array<T, N>::const_iterator array<T, N>::cbegin() const noexcept {
  return const_iterator(data());
}

/**
 * @brief Returns a const iterator to the end of the array.
 *
 * @details
 * This method returns a const iterator to the element following the last
 * element of the array.
 *
 * @return const_iterator - a const iterator to the end of the array.
 */
template <typename T, std::size_t N>
typename array<T, N>::const_iterator array<T, N>::cend() const noexcept {
  return const_iterator(data() + N);
}

// Array Capacity

/**
 * @brief checks whether the container is empty.
 *
 * @details
 * This method returns true if the array contains no elements, and false
 * otherwise.
 *
 * @return bool - true if the array is empty, false otherwise.
 */
template <typename T, std::size_t N>
bool array<T, N>::empty() const noexcept {
  return size() == 0;
}

/**
 * @brief Returns the number of elements.
 *
 * @details
 * This method returns the number of elements currently stored in the array.
 *
 * @return size_type - the number of elements in the array.
 */
template <typename T, std::size_t N>
typename array<T, N>::size_type array<T, N>::size() const noexcept {
  return N;
}

/**
 * @brief Returns the maximum number of elements the array can hold.
 *
 * @return size_type - the maximum number of elements.
 */
template <typename T, std::size_t N>
typename array<T, N>::size_type array<T, N>::max_size() const noexcept {
  return N;
}

// Array Modifiers

/**
 * @brief Swaps the contents.
 *
 * @details
 * After the call to this method, the elements in this container are those which
 * were in other before the call, and the elements of other are those which were
 * in this.
 *
 */
template <typename T, std::size_t N>
void array<T, N>::swap(array &other) {
  std::swap_ranges(begin(), end(), other.begin());
}

/**
 * @brief Assigns the given value to all elements in the container.
 *
 * @details
 * This method sets value as the value for all the elements in the array object.
 *
 */
template <typename T, std::size_t N>
void array<T, N>::fill(const_reference value) {
  std::fill_n(begin(), size(), value);
}