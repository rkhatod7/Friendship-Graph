#ifndef B_TREE_NODE_H
#define B_TREE_NODE_H

#include "Profile.h"

class BTreeNode {
 public:
  Profile *dataRecord;
  BTreeNode **childPointer;
  bool leaf;
  int count;
  BTreeNode *next;

  BTreeNode();
  BTreeNode(bool leaf);
  ~BTreeNode();
};

#endif
