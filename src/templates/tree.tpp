/**
 * @file tree.tpp
 * @authors karstarl (https://edu.21-school.ru/profile/karstarl)
 * @authors shericen (https://edu.21-school.ru/profile/shericen)
 * @brief Template for the RB tree container.
 * @version 1.0
 * @date 2024-12-08
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "./../headers/tree.h"

using namespace s21;

/**
 * @brief Default constructor a tree without nodes.
 *
 * @details
 * This constructor defines the type of tree elements (unique, non-unique)
 *
 * @param[in] type Type of tree elements (unique/non-unique).
 */
template <typename K, typename M>
tree<K, M>::tree(Uniq type) noexcept : type_{type} {}

/**
 * @brief Constructs a tree with a single node.
 *
 * @details
 * This constructor initializes the tree with a single node containing the given
 * key and value.
 *
 * @param[in] pair The pair of key/value for node.
 * @param[in] type Type of tree elements (unique/non-unique).
 */
template <typename K, typename M>
tree<K, M>::tree(const value_type &pair, Uniq type) : type_{type} {
  sentinel_ = new Node{value_type{}};
  insert(pair);
}

/**
 * @brief Constructs a tree with elements from an initializer list.
 *
 * @details
 * This constructor initializes the tree with elements from the given
 * initializer list. It creates a new sentinel node and then inserts all
 * elements from the list into the tree.
 *
 * @param[in] items The initializer list of key-val pairs insert into the tree.
 * @param[in] type Type of tree elements (unique/non-unique).
 */
template <typename K, typename M>
tree<K, M>::tree(std::initializer_list<value_type> const &items, Uniq type)
    : type_{type} {
  sentinel_ = new Node{value_type{}};

  for (auto pair : items) {
    insert(pair);
  }
}

/**
 * @brief Copy constructor for the red-black tree.
 *
 * @details
 * This constructor creates a new tree by copying the elements from another
 * tree. It initializes the sentinel node and then inserts all elements from the
 * source tree.
 *
 * @param[in] t The tree to copy from.
 */
template <typename K, typename M>
tree<K, M>::tree(const tree &t) : type_{t.type_} {
  sentinel_ = new Node{value_type{}};

  copyTree(t.root_);
}

/**
 * @brief Move constructor for the red-black tree.
 *
 * @details
 * This constructor creates a new tree by moving the elements from another tree.
 * It takes ownership of the root and sentinel nodes from the source tree,
 * leaving the source tree in a valid but unspecified state.
 *
 * @param[in] t The tree to move from.
 */
template <typename K, typename M>
tree<K, M>::tree(tree &&t)
    : root_{std::exchange(t.root_, nullptr)},
      sentinel_{std::exchange(t.sentinel_, nullptr)},
      size_{std::exchange(t.size_, 0)},
      type_{t.type_} {}

/**
 * @brief Move assignment operator for the red-black tree.
 *
 * @details
 * This operator moves the elements from another tree to the current tree.
 * It first cleans up the current tree and then moves the elements from the
 * source tree.
 *
 * @param[in] t The tree to move from.
 * @return tree<K, M>& - reference to the assigned tree.
 */
template <typename K, typename M>
tree<K, M> &tree<K, M>::operator=(tree &&t) {
  if (this != &t) {
    cleanTree(root_);
    delete sentinel_;
    // new (this) tree{t};
    new (this) tree{std::move(t)};
  }

  return *this;
}

/**
 * @brief Copy assignment operator for the red-black tree.
 *
 * @details
 * This operator copies the elements from another tree to the current tree.
 * It first cleans up the current tree and then copies the elements from the
 * source tree.
 *
 * @param[in] t The tree to copy from.
 * @return tree<K, M>& - reference to the assigned tree.
 */
template <typename K, typename M>
tree<K, M> &tree<K, M>::operator=(const tree &t) {
  if (this != &t) {
    cleanTree(root_);
    delete sentinel_;

    new (this) tree{t};
  }

  return *this;
}

/**
 * @brief Destructor.
 *
 * @details
 * Destroys the tree and frees allocated memory.
 */
template <typename K, typename M>
tree<K, M>::~tree() {
  if (root_) {
    cleanTree(root_);
  }

  if (sentinel_) {
    delete sentinel_;
  }
}

// TREE METHODS
/**
 * @brief Returns an iterator to the beginning of the tree.
 *
 * @return iterator - an iterator to the beginning of the tree.
 */
template <typename K, typename M>
auto tree<K, M>::begin() const noexcept -> iterator {
  return iterator{findMin(root_), root_, sentinel_};
}

/**
 * @brief Returns an iterator to the end of the tree.
 *
 * @return iterator - an iterator to the end of the tree.
 */
template <typename K, typename M>
auto tree<K, M>::end() const noexcept -> iterator {
  return iterator{sentinel_, root_, findMax(root_)};
}

/**
 * @brief Returns an iterator to the beginning of the tree.
 *
 * @return iterator - an iterator to the beginning of the tree.
 */
template <typename K, typename M>
auto tree<K, M>::cbegin() const noexcept -> const_iterator {
  return const_iterator{findMin(root_), root_, sentinel_};
}

/**
 * @brief Returns an iterator to the end of the tree.
 *
 * @return iterator - an iterator to the end of the tree.
 */
template <typename K, typename M>
auto tree<K, M>::cend() const noexcept -> const_iterator {
  return const_iterator{sentinel_, root_, findMax(root_)};
}

////TREE BASE METHODS

/**
 * @brief Returns the number of elements in the tree.
 *
 * @details
 * This method returns the number of elements currently stored in the red-black
 * tree.
 *
 * @return size_type - the number of elements in the tree.
 */
template <typename K, typename M>
auto tree<K, M>::size() const noexcept -> size_type {
  return size_;
}

/**
 * @brief Returns the maximum number of elements the tree can hold.
 *
 * @return size_type - the maximum number of elements.
 */
template <typename K, typename M>
auto tree<K, M>::max_size() const noexcept -> size_type {
  return std::numeric_limits<size_type>::max() / sizeof(Node) / 2;
}

/**
 * @brief Performs a left rotation at the given node.
 *
 * @param[in] old_root The node at which to perform the rotation.
 */
template <typename K, typename M>
void tree<K, M>::rotateLeft(Node *old_root) noexcept {
  Node *new_root = old_root->right;

  if (new_root->left) {
    new_root->left->parent = old_root;
  }

  old_root->right = new_root->left;
  new_root->left = old_root;

  if (!old_root->parent) {
    root_ = new_root;
  } else if (old_root == old_root->parent->left) {
    old_root->parent->left = new_root;
  } else {
    old_root->parent->right = new_root;
  }

  new_root->parent = std::exchange(old_root->parent, new_root);
}

/**
 * @brief Performs a right rotation at the given node.
 *
 * @param[in] old_root The node at which to perform the rotation.
 */
template <typename K, typename M>
void tree<K, M>::rotateRight(Node *old_root) noexcept {
  Node *new_root = old_root->left;

  if (new_root->right) {
    new_root->right->parent = old_root;
  }

  old_root->left = new_root->right;
  new_root->right = old_root;

  if (!old_root->parent) {
    root_ = new_root;
  } else if (old_root == old_root->parent->left) {
    old_root->parent->left = new_root;
  } else {
    old_root->parent->right = new_root;
  }

  new_root->parent = std::exchange(old_root->parent, new_root);
}

/**
 * @brief Swaps the colors of the given node and its children.
 *
 * @param[in] node The node at which to swap colors.
 */
template <typename K, typename M>
void tree<K, M>::swapColors(Node *node) noexcept {
  if (node == nullptr || node->left == nullptr || node->right == nullptr) {
    return;
  }

  if (node->left->color == kRED && node->right->color == kRED) {
    node->left->color = node->right->color = kBLACK;
    node->color = kRED;

    if (node->parent && node->parent != root_) {
      swapColors(node->parent);
    }
  }

  if (root_) {
    root_->color = kBLACK;
  }
}

/**
 * @brief Finds the node with the maximum key in the tree.
 *
 * @param[in] node The root node of the tree.
 * @return Node* - the node with the maximum key.
 */
template <typename K, typename M>
auto tree<K, M>::findMax(Node *node) noexcept -> Node * {
  while (node && node->right) {
    node = node->right;
  }

  return node;
}

/**
 * @brief Finds the node with the minimum key in the tree.
 *
 * @param[in] node The node from which to start searching for the minimum key.
 * @return Node* - the node with the minimum key.
 */
template <typename K, typename M>
auto tree<K, M>::findMin(Node *node) noexcept -> Node * {
  while (node && node->left) {
    node = node->left;
  }

  return node;
}

/**
 * @brief Finds the node with the given key.
 *
 * @param[in] node The root node of the tree.
 * @param[in] key The key to search for.
 * @return Node* - the node with the given key, or nullptr if the key is not
 * found.
 */
template <typename K, typename M>
auto tree<K, M>::findNode(Node *node, const key_type &key) const noexcept
    -> Node * {
  if (!node) {
    return nullptr;
  }

  if (node->pair->first > key) {
    return findNode(node->left, key);
  } else if (node->pair->first < key) {
    return findNode(node->right, key);
  } else {
    return node;
  }
}

/**
 * @brief Searches for a value associated with a given key.
 *
 * @param[in] key The key to search for.
 * @return value_type - pointer to pair associated with the key, or a
 * nullptr if the key is not found.
 */
template <typename K, typename M>
auto tree<K, M>::find(const key_type &key) const -> iterator {
  Node *find = findNode(root_, key);

  return (find) ? iterator{find, root_, sentinel_} : end();
}

// BALANCING TREE

/**
 * @brief Balances the tree after inserting a new node.
 *
 * @param[in] node The newly inserted node.
 */
template <typename K, typename M>
void tree<K, M>::balancingTree(Node *node) noexcept {
  while (node->parent && node->parent->color == kRED) {
    Node *parent = node->parent;
    Node *grandpar = parent->parent;
    Node *uncle = (parent == grandpar->left) ? grandpar->right : grandpar->left;

    if (uncle && uncle->color == kRED) {
      parent->color = kBLACK;
      uncle->color = kBLACK;
      grandpar->color = kRED;
      node = grandpar;
    } else {
      if (node == parent->right && parent == grandpar->left) {
        rotateLeft(parent);
        node = parent;
        parent = node->parent;
      } else if (node == parent->left && parent == grandpar->right) {
        rotateRight(parent);
        node = parent;
        parent = node->parent;
      }

      parent->color = kBLACK;
      grandpar->color = kRED;

      if (parent == grandpar->left) {
        rotateRight(grandpar);
      } else {
        rotateLeft(grandpar);
      }
    }
  }
}

/**
 * @brief Inserts a node into the red-black tree.
 *
 * @details
 * This method inserts a given node into the red-black tree, maintaining the
 * red-black tree properties. If the node is inserted successfully, it may
 * require rebalancing the tree to maintain its properties.
 *
 * @param[in] insert The node to insert.
 * @param[in,out] node A reference to the node pointer where the new node will
 * be inserted.
 * @param[in] parent The parent of the new node.
 */
template <typename K, typename M>
void tree<K, M>::insertNode(Node *insert, Node *&node, Node *parent) {
  if (!node) {
    insert->color = kRED;
    insert->parent = parent;
    insert->left = insert->right = nullptr;

    ++size_;
    node = insert;

    if (node->parent && node->parent->color == kRED) {
      balancingTree(node);
    }
  } else {
    if (insert->pair->first < node->pair->first) {
      insertNode(insert, node->left, node);
    } else {
      insertNode(insert, node->right, node);
    }
  }

  if (root_) {
    root_->color = kBLACK;
  }
}

/**
 * @brief Inserts a new node with the given key and value into the tree.
 *
 * @param[in] pair The pair of key/value for node.
 */
template <typename K, typename M>
auto tree<K, M>::insert(const value_type &pair) -> iterator {
  if (type_ == kUNIQUE && findNode(root_, pair.first)) {
    return end();
  }

  if (!sentinel_) {
    sentinel_ = new Node{value_type{}};
  }

  Node *node_pos = new Node{pair, kRED};
  insertNode(node_pos, root_);

  return iterator{node_pos, root_, sentinel_};
}

/**
 * @brief Inserts a new element into the tree, constructed in place.
 *
 * @details
 * This method constructs a new element directly in the tree using the provided
 * arguments, and inserts it into the tree.
 *
 * @tparam Args The types of the arguments to forward to the constructor of the
 * element.
 * @param args The arguments to forward to the constructor of the element.
 * @return A pair consisting of an iterator to the inserted element (or to the
 * element that prevented the insertion) and a bool denoting whether the
 * insertion took place.
 */
template <typename K, typename M>
auto tree<K, M>::emplace(K key, M val) -> std::pair<iterator, bool> {
  Node *new_node = new Node{value_type{key, val}};

  if (type_ == kUNIQUE && findNode(root_, new_node->pair->first)) {
    delete new_node;
    return {end(), false};
  }

  if (!sentinel_) {
    sentinel_ = new Node{value_type{}};
  }

  insertNode(new_node, root_);

  return {iterator{new_node, root_, sentinel_}, true};
}

// NODES DELETION

/**
 * @brief Handles the case where the node to delete has a red parent and a black
 * brother with a red left child.
 *
 * @param[in,out] node The node to delete.
 */
template <typename K, typename M>
void tree<K, M>::redParBlackSonRedLeft(Node *&node) noexcept {
  Node *parent = node->parent;
  Node *brother = (parent->left == node) ? parent->right : parent->left;
  bool is_left = (parent->left == node) ? true : false;

  removeConnect(node);
  (is_left) ? rotateLeft(brother->parent) : rotateRight(brother->parent);
  swapColors(brother);
}

/**
 * @brief Handles the case where the node to delete has a red parent and a black
 * brother with a red right child.
 *
 * @param[in,out] node The node to delete.
 */
template <typename K, typename M>
void tree<K, M>::redParBlackSonRedRight(Node *&node) noexcept {
  Node *parent = node->parent;
  Node *brother = (parent->left == node) ? parent->right : parent->left;
  bool is_left = (parent->left == node) ? true : false;

  removeConnect(node);
  (is_left) ? rotateRight(brother) : rotateLeft(brother);
  std::swap(brother->color, brother->parent->color);
  (is_left) ? rotateLeft(parent) : rotateRight(parent);
  swapColors(parent->parent);
}

/**
 * @brief Handles the case where the node to delete has a black parent and a red
 * brother with a black right child.
 *
 * @param[in,out] node The node to delete.
 */
template <typename K, typename M>
void tree<K, M>::blackParRedSonBlackRight(Node *&node) noexcept {
  Node *parent = node->parent;
  bool is_left = (parent->left == node) ? true : false;
  Node *brother = (parent->left == node) ? parent->right : parent->left;
  Node *grandson = (is_left) ? brother->left : brother->right;

  std::swap(brother->color, grandson->color);
  removeConnect(node);
  (is_left) ? rotateLeft(parent) : rotateRight(parent);
}

/**
 * @brief Handles the case where the node to delete has a black parent and a red
 * brother with a black right child and a red left child.
 *
 * @param[in,out] node The node to delete.
 */
template <typename K, typename M>
void tree<K, M>::blackParRedBrosBlackRightRedLeft(Node *&node) noexcept {
  Node *parent = node->parent;
  Node *brother = (parent->left == node) ? parent->right : parent->left;

  removeConnect(node);
  rotateLeft(brother->parent);
  std::swap(brother->color, parent->color);
  rotateLeft(parent);
  swapColors(parent->parent);
}

/**
 * @brief Fix to a double black violation.
 *
 * @param[in,out] node The node with the double black violation.
 */
template <typename K, typename M>
void tree<K, M>::fixDoubleBlack(Node *&node) noexcept {
  if (node == root_) {
    return;
  }

  Node *parent = node->parent;
  Node *brother = (parent->left == node) ? parent->right : parent->left;

  if (brother->color == kRED) {
    parent->color = kRED;
    brother->color = kBLACK;

    (brother == parent->left) ? rotateRight(parent) : rotateLeft(parent);
    fixDoubleBlack(node);
  } else {
    if ((brother->left && brother->left->color == kBLACK) &&
        (brother->right && brother->right->color == kBLACK)) {
      brother->color = kRED;
      if (parent->color == kBLACK) {
        fixDoubleBlack(parent);
      } else {
        parent->color = kBLACK;
      }
    } else {
      if (brother == parent->left) {
        if (brother->left && brother->left->color == kRED) {
          brother->left->color = std::exchange(brother->color, parent->color);
          rotateRight(parent);
        } else {
          if (brother->right && brother->right->color == kRED) {
            brother->right->color = parent->color;
            rotateLeft(brother);
            rotateRight(parent);
          }
        }
      } else {
        if (brother->right && brother->right->color == kRED) {
          brother->right->color = std::exchange(brother->color, parent->color);
          rotateLeft(parent);
        } else {
          if (brother->left && brother->left->color == kRED) {
            brother->left->color = parent->color;
            rotateRight(brother);
            rotateLeft(parent);
          }
        }
      }
      parent->color = kBLACK;
    }
  }
}

/**
 * @brief Handles the case where the node to delete has a black parent and a
 * black brother with no children.
 *
 * @param[in,out] node The node to delete.
 */
template <typename K, typename M>
void tree<K, M>::blackParBlackBrosBlackAll(Node *&node) noexcept {
  Node *parent = node->parent;
  Node *brother = (parent->left == node) ? parent->right : parent->left;

  brother->color = kRED;
  removeConnect(node);

  if (parent->color == kBLACK) {
    fixDoubleBlack(parent);
  } else {
    parent->color = kBLACK;
  }
}

/**
 * @brief Handles the case where the node to delete has a black parent and a
 * black brother with a red right grandchild.
 *
 * @param[in,out] node The node to delete.
 */
template <typename K, typename M>
void tree<K, M>::blackParBlackBrosRedRightGran(Node *&node) noexcept {
  Node *parent = node->parent;
  Node *brother = (parent->left == node) ? parent->right : parent->left;
  bool is_left = (parent->left == node) ? true : false;

  removeConnect(node);
  (is_left) ? rotateRight(brother) : rotateLeft(brother);
  std::swap(brother->color, brother->parent->color);
  (is_left) ? rotateLeft(parent) : rotateRight(parent);
  brother->color = kBLACK;
}

/**
 * @brief Handles the case where the node to delete has a black parent and a
 * black brother with a red left child or all grandchildren.
 *
 * @param[in,out] node The node to delete.
 */
template <typename K, typename M>
void tree<K, M>::blackParBlackBrosRedLeftOrAllGran(Node *&node) noexcept {
  Node *parent = node->parent;
  bool is_left = (parent->left == node) ? true : false;

  removeConnect(node);
  if (is_left) {
    rotateLeft(parent);
    if (parent->parent && parent->parent->right) {
      parent->parent->right->color = kBLACK;
    } else if (root_ == parent) {
      root_->right->color = kBLACK;
    }
  } else {
    rotateRight(parent);
    if (parent->parent && parent->parent->left) {
      parent->parent->left->color = kBLACK;
    } else if (root_ == parent) {
      root_->left->color = kBLACK;
    }
  }
}

/**
 * @brief Deletes a black node with no children.
 *
 * @param[in,out] node The node to delete.
 */
template <typename K, typename M>
void tree<K, M>::deleteBlackNoChild(Node *&node) noexcept {
  if (!node->parent) {
    return;
  }

  Node *parent = node->parent;
  Node *brother = (parent->left == node) ? parent->right : parent->left;
  bool is_left = (parent->left == node) ? true : false;

  if (brother && parent->color == kRED && brother->color == kBLACK) {
    if (!brother->left && !brother->right) {
      std::swap(brother->color, parent->color);
      removeConnect(node);
    } else if ((is_left && brother->right && brother->right->color == kRED) ||
               (!is_left && brother->left && brother->left->color == kRED)) {
      redParBlackSonRedLeft(node);
    } else if ((is_left && brother->left && brother->left->color == kRED) ||
               (!is_left && brother->right && brother->right->color == kRED)) {
      redParBlackSonRedRight(node);
    }
  } else if (brother && parent->color == kBLACK && brother->color == kBLACK) {
    if (!brother->left && !brother->right) {
      blackParBlackBrosBlackAll(node);
    } else if ((is_left && !brother->right && brother->left) ||
               (!is_left && !brother->left && brother->right)) {
      blackParBlackBrosRedRightGran(node);
    } else {
      blackParBlackBrosRedLeftOrAllGran(node);
    }
  } else if (brother && node->parent->color == kBLACK &&
             brother->color == kRED) {
    if ((is_left && brother->left && brother->left->color == kBLACK) ||
        (!is_left && brother->right && brother->right->color == kBLACK)) {
      Node *grgrson = (is_left) ? brother->left->right : brother->right->left;
      if (grgrson && grgrson->color == kRED) {
        blackParRedBrosBlackRightRedLeft(node);
      } else {
        blackParRedSonBlackRight(node);
      }
    }
  }
}

/**
 * @brief Deletes a node with one child from the red-black tree.
 *
 * @details
 * This method handles the deletion of a node that has exactly one child. It
 * swaps the values of the node to be deleted with its child, and then removes
 * the child node. This ensures that the tree properties are maintained.
 *
 * @param[in,out] node The node to delete. It must have exactly one child.
 * @param[in,out] child The child of the node to delete.
 * @return Node* - a pointer to the node that was actually deleted.
 */
template <typename K, typename M>
auto tree<K, M>::deleteOneChild(Node *&node, Node *&child) noexcept -> Node * {
  Node *ch = child;

  value_type node_copy{*node->pair};

  delete node->pair;
  node->pair = new value_type{*child->pair};
  delete child->pair;
  child->pair = new value_type{node_copy};

  child = nullptr;

  return ch;
}

/**
 * @brief Deletes a node with two children from the red-black tree.
 *
 * @details
 * This method handles the deletion of a node that has two children. It finds
 * the in-order successor or predecessor of the node to be deleted, swaps the
 * values, and then deletes the successor or predecessor node. The method
 * handles different cases based on the color of the node and the number of its
 * children.
 *
 * @param[in,out] node The node to delete. It must have two children.
 * @return Node* - a pointer to the node that was actually deleted.
 */
template <typename K, typename M>
auto tree<K, M>::deleteTwoChild(Node *&node) noexcept -> Node * {
  Node *swap = findMax(node->left);
  Node *to_del{swap};

  if (!(swap && !(swap->left && swap->right))) {
    swap = findMin(node->right);
  }

  value_type swap_copy{*swap->pair};

  delete swap->pair;
  swap->pair = new value_type{*node->pair};
  delete node->pair;
  node->pair = new value_type{swap_copy};

  if (!swap->left && !swap->right) {
    if (swap->color == kRED) {
      removeConnect(swap);
    } else {
      deleteBlackNoChild(swap);
    }
  } else if (!swap->left && swap->right) {
    to_del = deleteOneChild(swap, swap->right);
  } else if (swap->left && !swap->right) {
    to_del = deleteOneChild(swap, swap->left);
  }

  return to_del;
}

/**
 * @brief Removes parents connect with given node.
 *
 * @param[in,out] node Node to break connection with.
 */
template <typename K, typename M>
void tree<K, M>::removeConnect(Node *node) noexcept {
  if (node->parent) {
    if (node->parent->left == node) {
      node->parent->left = nullptr;
    } else {
      node->parent->right = nullptr;
    }
  }
}

/**
 * @brief Extracts a node from the red-black tree.
 *
 * @details
 * This method extracts a given node from the red-black tree, maintaining the
 * red-black tree properties. The method handles different cases based on the
 * color of the node and the number of its children.
 *
 * @param[in] node The node to extract.
 * @return Node* - a pointer to the node that was extracted.
 */
template <typename K, typename M>
auto tree<K, M>::extractNode(Node *node) noexcept -> Node * {
  if (!node) {
    return nullptr;
  }

  Node *to_del{node};

  if (node->color == kRED) {
    if (!node->left && !node->right) {
      removeConnect(node);
    } else if (node->left && node->right) {
      to_del = deleteTwoChild(node);
    }
  } else {
    if (!node->left && !node->right) {
      deleteBlackNoChild(node);
    } else if (!node->left && node->right) {
      to_del = deleteOneChild(node, node->right);
    } else if (node->left && !node->right) {
      to_del = deleteOneChild(node, node->left);
    } else {
      to_del = deleteTwoChild(node);
    }
  }

  --size_;

  return to_del;
}

/**
 * @brief Merges another red-black tree into the current tree.
 *
 * @details
 * This method merges the elements of another red-black tree into the current
 * tree. It iterates through the other tree and inserts each unique element into
 * the current tree. If an element already exists in the current tree, it is not
 * inserted again.
 *
 * @param[in,out] other The tree to merge into the current tree.
 */
template <typename K, typename M>
void tree<K, M>::merge(tree &other) {
  if (type_ == kUNIQUE) {
    auto it = other.begin();

    while (it != other.end()) {
      if (!findNode(root_, (*it).first)) {
        Node *extracted = other.extractNode(findNode(other.root_, (*it).first));

        if (extracted == other.root_) {
          other.root_ = nullptr;
          delete other.sentinel_;
          other.sentinel_ = nullptr;
          it = other.end();
        } else {
          it = other.begin();
        }

        insertNode(extracted, root_);
      } else {
        ++it;
      }
    }
  } else {
    while (other.size_) {
      insertNode(other.extractNode(findMin(other.root_)), root_);
    }

    other.root_ = nullptr;
    delete other.sentinel_;
    other.sentinel_ = nullptr;
  }
}

/**
 * @brief Cleans the tree by deleting all nodes.
 */
template <typename K, typename M>
void tree<K, M>::clear() noexcept {
  if (root_) {
    cleanTree(root_);
  }

  if (sentinel_) {
    delete sentinel_;
    sentinel_ = nullptr;
  }
}

/**
 * @brief Removes the node with the given key from the tree.
 *
 * @param[in] key The key of the node to remove.
 * @return iterator - an iterator to the next node after the erased node, or
 * end() if the erased node was the last node.
 */
template <typename K, typename M>
auto tree<K, M>::erase(const key_type &key) noexcept -> iterator {
  Node *node = findNode(root_, key);
  iterator it = (node) ? ++iterator{node, root_, sentinel_} : end();

  if (node) {
    delete extractNode(node);

    if (!size_) {
      root_ = nullptr;
    }
  }

  return it;
}

/**
 * @brief Erases the node pointed to by the constant iterator.
 *
 * @details
 * This method erases the node pointed to by the constant iterator. It uses the
 * key of the node to find and remove it from the tree.
 *
 * @param[in] it The constant iterator pointing to the node to be erased.
 * @return iterator - an iterator to the next node after the erased node, or
 * end() if the erased node was the last node.
 */
template <typename K, typename M>
auto tree<K, M>::erase(const_iterator it) noexcept -> iterator {
  return erase((*it).first);
}

/**
 * @brief Erases the elements in the specified range.
 *
 * @details
 * This method removes the elements in the range [first, last) from the tree.
 *
 * @param[in] first The position of the first element to erase.
 * @param[in] last The position following the last element to erase.
 * @return iterator - an iterator to the element following the last erased
 * element, or end() if the last erased element was the last element.
 * @throws std::range_error if the range is invalid.
 */
template <typename K, typename M>
auto tree<K, M>::erase(const_iterator first, const_iterator last) -> iterator {
  if (first == last) {
    return first.toIterator();
  } else if (first == begin() && last == end()) {
    clear();
    return end();
  }

  bool has_first{};
  bool has_last{(last == cend()) ? true : false};

  for (auto i = cbegin(); i != cend() && !(has_first && has_last); ++i) {
    if (first == i) {
      if (!has_last || last == cend()) {
        has_first = true;
      }
    } else if (last == i && has_first) {
      has_last = true;
    }
  }

  if (!has_first || !has_last) {
    throw std::range_error("map::erase() - invalid map range");
  }

  key_type first_key = (*first).first;

  iterator ret_it;

  if (last == end()) {
    ret_it = --find((*first).first);

    for (auto it = cbegin(); it != cend(); ++it) {
      auto current = (*it).first;

      if (current >= first_key) {
        erase(current);
        it = cbegin();
      }
    }
  } else {
    key_type last_key = (*last).first;
    ret_it = --find(last_key);

    for (auto it = cbegin(); it != cend(); ++it) {
      auto current = (*it).first;

      if (current >= first_key && current < last_key) {
        erase(current);
        it = cbegin();
      }
    }
  }

  return ret_it;
}

/**
 * @brief Cleans the tree by deleting all nodes.
 *
 * @param[in,out] node The root node of the tree.
 */
template <typename K, typename M>
void tree<K, M>::cleanTree(Node *&node) noexcept {
  if (node) {
    cleanTree(node->left);
    cleanTree(node->right);

    delete node;
    node = nullptr;
    --size_;
  }
}

// COPYING TREE

/**
 * @brief Copies the nodes from another red-black tree.
 *
 * @details
 * This method recursively copies all the nodes from another red-black tree into
 * the current tree. It inserts each node's key-value pair into the current
 * tree, ensuring that the tree properties are maintained.
 *
 * @param[in] node The root node of the tree to copy from.
 */
template <typename K, typename M>
void tree<K, M>::copyTree(Node *node) {
  if (node) {
    insert(*node->pair);

    copyTree(node->left);
    copyTree(node->right);
  }
}

// PRINTING

/**
 * @brief Prints the nodes of the tree in a structured format.
 *
 * @param[in] node The root node of the tree.
 * @param[in] indent The indentation level for printing (used for formatting).
 * @param[in] last Whether the node is the last child of its parent.
 * @return std::string - a string representation of the tree structure.
 */
template <typename K, typename M>
std::string tree<K, M>::printNodes(const Node *node, int indent,
                                   bool last) const noexcept {
  std::string str{};

  if (node) {
    str = std::string(indent, ' ');
    if (last) {
      str += "R---";
    } else {
      str += "L---";
    }
    str += (node->color == kRED ? "{R:" : "{B:");

    int reserve = 50;
    char *char_str = new char[reserve]{};

    std::snprintf(char_str, reserve, "%d", node->pair->first);
    str += std::string(char_str);
    str += "}\n";

    if (char_str) {
      delete[] char_str;
    }

    str += printNodes(node->left, indent + 4, false);
    str += printNodes(node->right, indent + 4, true);
  }

  return str;
}

/**
 * @brief Returns a string representation of the tree structure.
 *
 * @return std::string - a string representation of the tree structure.
 */
template <typename K, typename M>
std::string tree<K, M>::structure() const noexcept {
  return printNodes(root_);
}

// TREE ITERATOR CONSTRUCTORS

/**
 * @brief Constructs a tree iterator.
 *
 * @param[in] node The node to which the iterator points.
 * @param[in] root The root node of the tree.
 * @param[in] sentinel The sentinel node of the tree.
 */
template <typename K, typename M>
tree<K, M>::iterator::TreeIterator(Node *node, Node *root,
                                   Node *sentinel) noexcept
    : TreeConstIterator(node, root, sentinel) {}

/**
 * @brief Copy constructor for the tree iterator.
 *
 * @param[in] other The iterator to copy from.
 */
template <typename K, typename M>
tree<K, M>::iterator::TreeIterator(const iterator &other) noexcept
    : TreeConstIterator(other.ptr_, other.first_, other.last_) {}

// TREE ITERATOR OPERATORS

/**
 * @brief Assignment operator for the tree iterator.
 *
 * @param[in] other The iterator to assign from.
 * @return iterator& - reference to the assigned iterator.
 */
template <typename K, typename M>
auto tree<K, M>::iterator::operator=(const iterator &other) noexcept
    -> iterator & {
  // TreeConstIterator(other.ptr_, other.first_, other.last_)
  // setFields(other);
  this->ptr_ = other.ptr_;
  this->first_ = other.first_;
  this->last_ = other.last_;

  return *this;
}

/**
 * @brief Pre-decrement operator for the tree iterator.
 *
 * @return iterator& - reference to the decremented iterator.
 */
template <typename K, typename M>
auto tree<K, M>::iterator::operator--() noexcept -> iterator & {
  Node *max_node = findMax(this->first_);

  if (this->last_ == max_node) {
    std::swap(this->ptr_, this->last_);
  } else if (this->ptr_) {
    if (this->ptr_->left) {
      this->ptr_ = findMax(this->ptr_->left);
    } else {
      if (this->ptr_ != findMin(this->first_)) {
        Node *parent = this->ptr_->parent;

        while (parent && this->ptr_ == parent->left) {
          this->ptr_ = parent;
          parent = parent->parent;
        }

        this->ptr_ = parent;
      }
    }
  }

  return *this;
}

/**
 * @brief Pre-increment operator for the tree iterator.
 *
 * @return iterator& - reference to the incremented iterator.
 */
template <typename K, typename M>
auto tree<K, M>::iterator::operator++() noexcept -> iterator & {
  Node *max_node = findMax(this->first_);

  if (this->ptr_ == max_node) {
    std::swap(this->ptr_, this->last_);
  } else if (this->ptr_ && this->last_ != max_node) {
    if (this->ptr_->right) {
      this->ptr_ = findMin(this->ptr_->right);
    } else {
      Node *parent = this->ptr_->parent;

      while (parent && this->ptr_ == parent->right) {
        this->ptr_ = parent;
        parent = parent->parent;
      }

      this->ptr_ = parent;
    }
  }

  return *this;
}

/**
 * @brief Increments the iterator and returns the original position.
 *
 * @return An `iterator` representing the original position of the iterator
 * before the increment.
 */
template <typename K, typename M>
auto tree<K, M>::iterator::operator++(int) noexcept -> iterator {
  iterator copy{*this};

  ++*this;

  return copy;
}

/**
 * @brief Decrements the iterator and returns the original position.
 *
 * @return An `iterator` representing the original position of the iterator
 * before the decrement.
 */
template <typename K, typename M>
auto tree<K, M>::iterator::operator--(int) noexcept -> iterator {
  iterator copy{*this};

  --*this;

  return copy;
}

/**
 * @brief Addition operator for the tree iterator.
 *
 * @param[in] shift The number of positions to shift.
 * @return iterator - before the shift.
 */
template <typename K, typename M>
auto tree<K, M>::iterator::operator+(size_type shift) const noexcept
    -> iterator {
  iterator copy{*this};

  for (size_type i = 0; i < shift; ++i) {
    ++copy;
  }

  return copy;
}

/**
 * @brief Subtraction operator for the tree iterator.
 *
 * @param[in] shift The number of positions to shift.
 * @return iterator - before the shift.
 */
template <typename K, typename M>
auto tree<K, M>::iterator::operator-(size_type shift) const noexcept
    -> iterator {
  iterator copy{*this};

  for (size_type i = 0; i < shift; ++i) {
    --copy;
  }

  return copy;
}

/**
 * @brief Advances the iterator by a specified number of positions.
 *
 * @param[in] shift The number of positions to advance the iterator.
 */
template <typename K, typename M>
void tree<K, M>::iterator::operator+=(size_type shift) noexcept {
  for (size_type i = 0; i < shift; ++i) {
    ++*this;
  }
}

/**
 * @brief Moves the iterator back by a specified number of positions.
 *
 * @param[in] shift The number of positions to move the iterator backward.
 */
template <typename K, typename M>
void tree<K, M>::iterator::operator-=(size_type shift) noexcept {
  for (size_type i = 0; i < shift; ++i) {
    --*this;
  }
}

/**
 * @brief Equality comparison operator for the tree iterator.
 *
 * @param[in] other The iterator to compare with.
 * @return true if the iterators are equal, false otherwise.
 */
template <typename K, typename M>
bool tree<K, M>::iterator::operator==(iterator other) const noexcept {
  return (this->ptr_ == other.ptr_ && this->first_ == other.first_ &&
          this->last_ == other.last_)
             ? true
             : false;
}

/**
 * @brief Inequality comparison operator for the tree iterator.
 *
 * @param[in] other The iterator to compare with.
 * @return true if the iterators are not equal, false otherwise.
 */
template <typename K, typename M>
bool tree<K, M>::iterator::operator!=(iterator other) const noexcept {
  return (this->ptr_ != other.ptr_ || this->first_ != other.first_ ||
          this->last_ != other.last_)
             ? true
             : false;
}

/**
 * @brief Arrow operator for the tree iterator.
 *
 * @return value_type & - reference to pair in current node.
 */
template <typename K, typename M>
std::pair<const K, M &> tree<K, M>::iterator::operator*() noexcept {
  return std::pair<const K, M &>{this->ptr_->pair->first,
                                 this->ptr_->pair->second};
}

// TREE CONST ITERATOR CONSTRUCTORS

/**
 * @brief Constructs a tree const_iterator.
 *
 * @param[in] node The node to which the const_iterator points.
 * @param[in] root The root node of the tree.
 * @param[in] sentinel The sentinel node of the tree.
 */
template <typename K, typename M>
tree<K, M>::const_iterator::TreeConstIterator(Node *node, Node *root,
                                              Node *sentinel) noexcept
    : ptr_{node}, first_{root}, last_{sentinel} {}

/**
 * @brief Copy constructor for the tree const_iterator.
 *
 * @param[in] other The const_iterator to copy from.
 */
template <typename K, typename M>
tree<K, M>::const_iterator::TreeConstIterator(
    const const_iterator &other) noexcept
    : ptr_{other.ptr_}, first_{other.first_}, last_{other.last_} {}

/**
 * @brief Converts the constant iterator to a regular iterator.
 *
 * @details
 * This method converts a constant iterator to a regular iterator. This is
 * useful when you need to perform operations that modify the elements of the
 * tree, which are not allowed with a constant iterator. The returned iterator
 * will point to the same element as the constant iterator.
 *
 * @return iterator - A regular iterator initialized with the same position and
 * range as the constant iterator.
 */
template <typename K, typename M>
auto tree<K, M>::const_iterator::toIterator() const noexcept -> iterator {
  return iterator{ptr_, first_, last_};
}

// TREE CONST ITERATOR OPERATORS

/**
 * @brief Assignment operator for the tree const_iterator.
 *
 * @param[in] other The const_iterator to assign from.
 * @return const_iterator& - reference to the assigned const_iterator.
 */
template <typename K, typename M>
auto tree<K, M>::const_iterator::operator=(const const_iterator &other) noexcept
    -> const_iterator & {
  ptr_ = other.ptr_;
  first_ = other.first_;
  last_ = other.last_;

  return *this;
}

/**
 * @brief Pre-decrement operator for the tree const_iterator.
 *
 * @return const_iterator& - reference to the decremented const_iterator.
 */
template <typename K, typename M>
auto tree<K, M>::const_iterator::operator--() noexcept -> const_iterator & {
  Node *max_node = findMax(first_);

  if (last_ == max_node) {
    std::swap(ptr_, last_);
  } else if (ptr_) {
    if (ptr_->left) {
      ptr_ = findMax(ptr_->left);
    } else {
      if (ptr_ != findMin(first_)) {
        Node *parent = ptr_->parent;

        while (parent && ptr_ == parent->left) {
          ptr_ = parent;
          parent = parent->parent;
        }

        ptr_ = parent;
      }
    }
  }

  return *this;
}

/**
 * @brief Pre-increment operator for the tree const_iterator.
 *
 * @return const_iterator& - reference to the incremented const_iterator.
 */
template <typename K, typename M>
auto tree<K, M>::const_iterator::operator++() noexcept -> const_iterator & {
  Node *max_node = findMax(first_);

  if (ptr_ == max_node) {
    std::swap(ptr_, last_);
  } else if (ptr_ && last_ != max_node) {
    if (ptr_->right) {
      ptr_ = findMin(ptr_->right);
    } else {
      Node *parent = ptr_->parent;

      while (parent && ptr_ == parent->right) {
        ptr_ = parent;
        parent = parent->parent;
      }

      ptr_ = parent;
    }
  }

  return *this;
}

/**
 * @brief Increments the constant iterator and returns the original position.
 *
 * @return A `const_iterator` representing the original position of the
 * iterator before the increment.
 */
template <typename K, typename M>
auto tree<K, M>::const_iterator::operator++(int) noexcept -> const_iterator {
  const_iterator copy{*this};

  ++*this;

  return copy;
}

/**
 * @brief Decrements the constant iterator and returns the original position.
 *
 * @return A `const_iterator` representing the original position of the
 * iterator before the decrementation.
 */
template <typename K, typename M>
auto tree<K, M>::const_iterator::operator--(int) noexcept -> const_iterator {
  const_iterator copy{*this};

  --*this;

  return copy;
}

/**
 * @brief Increments the constant iterator by a shift value and returns the
 * original position.
 *
 * @param[in] shift The number of positions to shift.
 * @return A `const_iterator` representing the original position of the
 * iterator before the incrementation.
 */
template <typename K, typename M>
auto tree<K, M>::const_iterator::operator+(size_type shift) const noexcept
    -> const_iterator {
  const_iterator copy{*this};

  for (size_type i = 0; i < shift; ++i) {
    ++copy;
  }

  return copy;
}

/**
 * @brief Decrements the constant iterator by a shift value and returns the
 * original position.
 *
 * @param[in] shift The number of positions to shift.
 * @return A `const_iterator` representing the original position of the
 * iterator before the decrementation.
 */
template <typename K, typename M>
auto tree<K, M>::const_iterator::operator-(size_type shift) const noexcept
    -> const_iterator {
  const_iterator copy{*this};

  for (size_type i = 0; i < shift; ++i) {
    --copy;
  }

  return copy;
}

/**
 * @brief Moves the const_iterator forward by a specified number of positions.
 *
 * @param[in] shift The number of positions to move the const_iterator backward.
 */
template <typename K, typename M>
void tree<K, M>::const_iterator::operator+=(size_type shift) noexcept {
  for (size_type i = 0; i < shift; ++i) {
    ++*this;
  }
}

/**
 * @brief Moves the const_iterator back by a specified number of positions.
 *
 * @param[in] shift The number of positions to advance the const_iterator.
 */
template <typename K, typename M>
void tree<K, M>::const_iterator::operator-=(size_type shift) noexcept {
  for (size_type i = 0; i < shift; ++i) {
    --*this;
  }
}

/**
 * @brief Equality comparison operator for the tree const_iterator.
 *
 * @param[in] other The const_iterator to compare with.
 * @return true if the const_iterators are equal, false otherwise.
 */
template <typename K, typename M>
bool tree<K, M>::const_iterator::operator==(
    const_iterator other) const noexcept {
  return (ptr_ == other.ptr_ && first_ == other.first_ && last_ == other.last_)
             ? true
             : false;
}

/**
 * @brief Inequality comparison operator for the tree const_iterator.
 *
 * @param[in] other The const_iterator to compare with.
 * @return true if the const_iterators are not equal, false otherwise.
 */
template <typename K, typename M>
bool tree<K, M>::const_iterator::operator!=(
    const_iterator other) const noexcept {
  return (ptr_ != other.ptr_ || first_ != other.first_ || last_ != other.last_)
             ? true
             : false;
}

/**
 * @brief Arrow operator for the tree iterator.
 *
 * @return value_type & - reference to pair in current node.
 */
template <typename K, typename M>
auto tree<K, M>::const_iterator::operator*() const noexcept
    -> const value_type {
  return *ptr_->pair;
}