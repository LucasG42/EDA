#ifndef TREE_H
#define TREE_H
#include <sstream>
#include <string>

struct Node;

class Tree {
public:
  Tree();
  Tree(std::string serial);
  void inorder(); // percurso em ordem simetrica
  void bshow();   // exibe a arvore de forma amigavel
  int size();
  int height();
  bool identical(Tree *t);
  Tree *clone();
  int sum_keys();
  int min_key();
  int total_internal_nodes();
  int um_filho();
  void delete_leaves();
  void delete_leaves_with_value(int key);
  int count_leaves();
  int size_iterativo();
  std::string find_path(int value);
  ~Tree();

private:
  Node *_root;
  Node *_clear(Node *root);
  void _inorder(Node *node);
  void _bshow(Node *node, std::string heranca);
  void _serializeTree(std::stringstream &ss, Node **node);
  int _size(Node *node);
  int _height(Node *node);
  int _sum_keys(Node *node);
  int _min_key(Node *node);
  int _total_internal_nodes(Node *node);
  int _um_filho(Node *node);
  bool _identical(Node *nd1, Node *nd2);
  Node *_clone(Node *node);
  Node *_delete_leaves(Node *node);
  Node *_delete_leaves_with_value(int key, Node *node);
  int _count_leaves(Node *node);
  int _size_iterativo(Node *node);
  std::string _find_path(Node *node, int value);
};

#endif