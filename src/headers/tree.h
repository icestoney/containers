/**
 * @file tree.h
 * @authors karstarl (https://edu.21-school.ru/profile/karstarl)
 * @authors shericen (https://edu.21-school.ru/profile/shericen)
 * @brief Header for the RB tree container.
 * @version 1.0
 * @date 2024-12-08
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef SRC_HEADERS_S21_TREE_H_
#define SRC_HEADERS_S21_TREE_H_

#include <algorithm>         // for exchange()
#include <initializer_list>  // for init_list type
#include <limits>            // for max()
#include <string>            // for string type

/// @brief Namespace for working with containers
namespace s21 {

/**
 * @brief A red-black tree container template class.
 *
 * @details
 * This template class tree provides a red-black tree similar to
 * std::map in the C++ Standard Library. It manages a balanced binary search
 * tree of elements of type K and M, supporting various
 * operations including iteration, element access, and size management.
 *
 * @tparam K The type of keys stored in the tree.
 * @tparam M The type of values stored in the tree.
 */
template <typename K, typename M>
class tree {
 public:
  // Container types

  class TreeIterator;
  class TreeConstIterator;
  enum Uniq { kUNIQUE, kNON_UNIQUE };

  // Type aliases

  using key_type = K;             ///< Type of first template (nodes key)
  using mapped_type = M;          ///< Type of second template (nodes value)
  using iterator = TreeIterator;  ///< For read/write elements
  using const_iterator = TreeConstIterator;  ///< For read elements
  using value_type = std::pair<K, M>;        ///< Key-map pair
  using size_type = std::size_t;

  // Constructors/destructor

  explicit tree(Uniq type = kUNIQUE) noexcept;
  explicit tree(const value_type &pair, Uniq type = kUNIQUE);
  tree(std::initializer_list<value_type> const &items, Uniq type = kUNIQUE);
  tree(const tree &t);
  tree(tree &&t);
  tree &operator=(tree &&t);
  tree &operator=(const tree &t);
  ~tree();

  // Tree Iterators

  iterator begin() const noexcept;
  iterator end() const noexcept;
  const_iterator cbegin() const noexcept;
  const_iterator cend() const noexcept;

  // Working with tree

  iterator find(const key_type &key) const;
  iterator insert(const value_type &pair);
  iterator erase(const key_type &key) noexcept;
  iterator erase(const_iterator it) noexcept;
  iterator erase(const_iterator first, const_iterator last);
  size_type size() const noexcept;
  size_type max_size() const noexcept;
  void merge(tree &other);
  void clear() noexcept;
  std::string structure() const noexcept;

  // template <typename... Args>
  std::pair<iterator, bool> emplace(K key, M val);

 private:
  // Container types

  struct Node;
  enum Colors { kRED, kBLACK };

  // Fields

  Node *root_{};      ///< Root of tree
  Node *sentinel_{};  ///< Dummy element
  size_type size_{};  ///< Size of tree
  Uniq type_{};       ///< Determines whether to allow duplicates

  // Add/remove nodes

  void insertNode(Node *insert, Node *&node, Node *parent = nullptr);
  Node *extractNode(Node *node) noexcept;
  void cleanTree(Node *&node) noexcept;
  void removeConnect(Node *node) noexcept;
  void copyTree(Node *node);

  // Tree balancing

  void balancingTree(Node *node) noexcept;
  void fixDoubleBlack(Node *&node) noexcept;
  void rotateLeft(Node *old_root) noexcept;
  void rotateRight(Node *old_root) noexcept;
  void swapColors(Node *node) noexcept;

  // Tree searching

  Node *findNode(Node *node, const key_type &key) const noexcept;
  static Node *findMax(Node *node) noexcept;
  static Node *findMin(Node *node) noexcept;

  // Cases of node removal

  Node *deleteTwoChild(Node *&node) noexcept;
  Node *deleteOneChild(Node *&node, Node *&child) noexcept;
  void deleteBlackNoChild(Node *&node) noexcept;

  // Black no child node removal cases

  void redParBlackSonRedLeft(Node *&node) noexcept;
  void redParBlackSonRedRight(Node *&node) noexcept;
  void blackParRedSonBlackRight(Node *&node) noexcept;
  void blackParRedBrosBlackRightRedLeft(Node *&node) noexcept;
  void blackParBlackBrosBlackAll(Node *&node) noexcept;
  void blackParBlackBrosRedRightGran(Node *&node) noexcept;
  void blackParBlackBrosRedLeftOrAllGran(Node *&node) noexcept;

  // Printing

  std::string printNodes(const Node *node, int indent = 0,
                         bool last = true) const noexcept;
};

template <typename K, typename M>
class tree<K, M>::TreeConstIterator {
 public:
  // Constructors

  TreeConstIterator() noexcept = default;
  TreeConstIterator(Node *node, Node *root, Node *sentinel) noexcept;
  TreeConstIterator(const const_iterator &other) noexcept;

  // Operators

  const_iterator &operator=(const const_iterator &other) noexcept;
  const_iterator &operator--() noexcept;
  const_iterator &operator++() noexcept;
  const_iterator operator--(int) noexcept;
  const_iterator operator++(int) noexcept;
  const_iterator operator+(size_type shift) const noexcept;
  const_iterator operator-(size_type shift) const noexcept;
  void operator+=(size_type shift) noexcept;
  void operator-=(size_type shift) noexcept;
  bool operator==(const_iterator other) const noexcept;
  bool operator!=(const_iterator other) const noexcept;
  const value_type operator*() const noexcept;
  iterator toIterator() const noexcept;

 protected:
  // Fields

  Node *ptr_{};    ///< Pointer to the current node
  Node *first_{};  ///< Pointer to the lowest node
  Node *last_{};   ///< Pointer to a dummy node
};

template <typename K, typename M>
class tree<K, M>::TreeIterator : public TreeConstIterator {
 public:
  // Constructors

  TreeIterator() noexcept = default;
  TreeIterator(Node *node, Node *root, Node *sentinel) noexcept;
  TreeIterator(const iterator &other) noexcept;

  // Operators

  iterator &operator=(const iterator &other) noexcept;
  iterator &operator--() noexcept;
  iterator &operator++() noexcept;
  iterator operator--(int) noexcept;
  iterator operator++(int) noexcept;
  iterator operator+(size_type shift) const noexcept;
  iterator operator-(size_type shift) const noexcept;
  void operator+=(size_type shift) noexcept;
  void operator-=(size_type shift) noexcept;
  bool operator==(iterator other) const noexcept;
  bool operator!=(iterator other) const noexcept;
  std::pair<const key_type, mapped_type &> operator*() noexcept;

  /**
   * @brief Converts the current iterator to a constant iterator.
   *
   * @details
   * This conversion operator allows you to obtain a `const_iterator` from
   * the current iterator. This is useful when you need to access elements
   * in the container without modifying them. The returned `const_iterator`
   * provides read-only access to the elements.
   *
   * @return A `const_iterator` initialized with the same position and range
   *         as the current iterator.
   */
  // operator const_iterator() const noexcept {
  //   return const_iterator{};
  // }
};

/**
 * @brief A node in the red-black tree.
 *
 * @details
 * This class represents a node in the red-black tree. It contains the key,
 * value, color, parent, left child, and right child of the node.
 *
 * @tparam K The type of keys stored in the tree.
 * @tparam M The type of values stored in the tree.
 */
template <typename K, typename M>
struct tree<K, M>::Node {
 public:
  value_type *pair;  ///< Node key
  Colors color;      ///< Color of node (red/black)
  Node *parent;      ///< Parent of this node
  Node *left{};      ///< Left son of this node
  Node *right{};     ///< Right son of this node

  /**
   * @brief Constructs a new node.
   *
   * @param[in] k The key of the node.
   * @param[in] v The value of the node.
   * @param[in] c The color of the node.
   * @param[in] p The parent of the node.
   */
  Node(const value_type &pair_, Colors color_ = kRED, Node *parent_ = 0)
      : pair{new value_type{pair_}}, color{color_}, parent{parent_} {}

  /**
   * @brief Destructor. Destroys nodes pair.
   */
  ~Node() { delete pair; }
};

#include "./../templates/tree.tpp"

}  // namespace s21

#endif