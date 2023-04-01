#include "../includes/Tree.h"
#include <climits>
#include <iostream>
#include <sstream>
#include <stack>
#include <string>

struct Node {
  int key;
  Node *left;
  Node *right;

  Node(int k, Node *l = nullptr, Node *r = nullptr) {
    this->key = k;
    this->left = l;
    this->right = r;
  }
};

Tree::Tree() { _root = nullptr; }

Tree::Tree(std::string serial) {
  _root = nullptr;
  std::stringstream ss(serial);
  _serializeTree(ss, &_root);
}

Tree::~Tree() { _root = _clear(_root); }

void Tree::_serializeTree(std::stringstream &ss, Node **node) {
  std::string value;
  ss >> value;
  if (value == "#") // filho == nullptr
    return;
  int key = std::stoi(value);
  *node = new Node(key);
  _serializeTree(ss, &((*node)->left));
  _serializeTree(ss, &((*node)->right));
}

Node *Tree::_clear(Node *node) {
  if (node != nullptr) {
    node->left = _clear(node->left);
    node->right = _clear(node->right);
    delete node;
  }
  return nullptr;
}

void Tree::inorder() {
  _inorder(_root);
  std::cout << std::endl;
}

void Tree::_inorder(Node *node) {
  if (node != nullptr) {
    _inorder(node->left);
    std::cout << node->key << " ";
    _inorder(node->right);
  }
}

void Tree::bshow() { _bshow(_root, ""); }

void Tree::_bshow(Node *node, std::string heranca) {
  if (node != nullptr && (node->left != nullptr || node->right != nullptr))
    _bshow(node->right, heranca + "r");
  for (int i = 0; i < (int)heranca.size() - 1; i++)
    std::cout << (heranca[i] != heranca[i + 1] ? "│   " : "    ");
  if (heranca != "")
    std::cout << (heranca.back() == 'r' ? "┌───" : "└───");
  if (node == nullptr) {
    std::cout << "#" << std::endl;
    return;
  }
  std::cout << node->key << std::endl;
  if (node != nullptr && (node->left != nullptr || node->right != nullptr))
    _bshow(node->left, heranca + "l");
}

bool Tree::identical(Tree *t) { return _identical(t->_root, _root); }

bool Tree::_identical(Node *nd1, Node *nd2) {
  if (nd1 != nullptr && nd2 != nullptr) {
    return (nd1->key == nd2->key) && _identical(nd1->left, nd2->left) ==
                                         _identical(nd1->right, nd2->right);
  }
  return false;
}

Tree *Tree::clone() {
  Tree *tClone = new Tree;
  tClone->_root = _clone(_root);
  return tClone;
}

Node *Tree::_clone(Node *node) {
  if (node != nullptr) {
    Node *copy = new Node(node->key);
    copy->left = _clone(node->left);
    copy->right = _clone(node->right);
    return copy;
  }
  return nullptr;
}

int Tree::size() { return _size(_root); }

int Tree::_size(Node *node) {
  if (node == nullptr) {
    return 0;
  }
  return 1 + _size(node->left) + _size(node->right);
}

int Tree::height() { return _height(_root); }

int Tree::_height(Node *node) {
  if (node == nullptr) {
    return 0;
  }
  return 1 + std::max(_height(node->right), _height(node->left));
}
int Tree::sum_keys() { return _sum_keys(_root); }

int Tree::_sum_keys(Node *node) {
  if (node != nullptr) {
    return node->key + _sum_keys(node->left) + _sum_keys(node->right);
  }
  return 0;
}

// Para fazer essa funcao, suponha que as arvores dos testes nunca serao vazias,
// assim, sempre havera um menor valor de chave a ser retornado
int Tree::min_key() { return _min_key(_root); }

// Supoe que o ponteiro recebido sempre eh diferente de nullptr
int Tree::_min_key(Node *node) {
  if (node != nullptr) {
    return std::min(std::min(_min_key(node->left), _min_key(node->right)),
                    node->key);
  }
  return INT_MAX;
}

int Tree::total_internal_nodes() { // TODO
  return _total_internal_nodes(_root);
}

int Tree::_total_internal_nodes(Node *node) { // TODO
  if (node != nullptr) {
    if (node->left != nullptr || node->right != nullptr) {
      return 1 + _total_internal_nodes(node->left) +
             _total_internal_nodes(node->right);
    }
  }
  return 0;
}

int Tree::um_filho() { return _um_filho(_root); }

int Tree::_um_filho(Node *node) {
  if (node != nullptr) {
    if ((node->left == nullptr && node->right != nullptr) ||
        (node->left != nullptr && node->right == nullptr)) {
      return 1 + _um_filho(node->left) + _um_filho(node->right);
    }
    return 0 + _um_filho(node->left) + _um_filho(node->right);
  }
  return 0;
}

int Tree::count_leaves() { return _count_leaves(_root); }

int Tree::_count_leaves(Node *node) {
  if (node != nullptr) {
    if (node->left == nullptr && node->right == nullptr) {
      return 1;
    } else {
      return _count_leaves(node->left) + _count_leaves(node->right);
    }
  } else {
    return 0;
  }
}

void Tree::delete_leaves() { _delete_leaves(_root); }

Node *Tree::_delete_leaves(Node *node) {
  if (node != nullptr) {
    if (node->left == nullptr && node->right == nullptr) {
      delete node;
      return nullptr;
    } else {
      if (node->left != nullptr) {
        node->left = _delete_leaves(node->left);
      }
      if (node->right != nullptr) {
        node->right = _delete_leaves(node->right);
      }
    }
  }
  return node;
}

void Tree::delete_leaves_with_value(int key) {
  _delete_leaves_with_value(key, _root);
}

Node *Tree::_delete_leaves_with_value(int key, Node *node) {
  if (node != nullptr) {
    if (node->left == nullptr && node->right == nullptr && node->key == key) {
      delete node;
      return nullptr;
    } else {
      if (node->left != nullptr) {
        node->left = _delete_leaves_with_value(key, node->left);
      }
      if (node->right != nullptr) {
        node->right = _delete_leaves_with_value(key, node->right);
      }
    }
  }
  return node;
}

int Tree::size_iterativo() { return _size_iterativo(_root); }

int Tree::_size_iterativo(Node *node) {
  int size = 0;
  if (node == nullptr) {
    return size;
  }

  std::stack<Node *> nos;
  nos.push(node);

  while (nos.empty() == false) {
    node = nos.top();
    nos.pop();
    size++;
    if (node->right != nullptr) {
      nos.push(node->right);
    }

    if (node->left != nullptr) {
      nos.push(node->left);
    }
  }

  return size;
}

std::string Tree::find_path(int value) {
  std::string result = _find_path(_root, value);
  std::stringstream ss(result);
  std::string tmp;
  while (ss >> tmp) {
    if (tmp.find("x") != std::string::npos) {
      return tmp;
    }
  }

  return "!";
}

std::string Tree::_find_path(Node *node, int value) {
  if (node != nullptr) {
    if (node->key == value) {
      return "x ";
    } else {
      return "l" + _find_path(node->left, value) + "r" +
             _find_path(node->right, value);
    }
  }
  return " ";
  // para resolver essa questão pensei em separar a string com espaço ao chegar
  // em um nó nulo. e pesquisar recursivametnte marcando o "galho" com l ou r,
  // assim ao quebrar o stringstream eu teria todas as ramificações da arvore, e
  // poderia escolhe a que me retornou o x. caso não encontre x na string eu
  // retorno ! assim como especificado na questão.
}