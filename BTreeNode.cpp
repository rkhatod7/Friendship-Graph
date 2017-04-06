#include "BTreeNode.h"

BTreeNode::BTreeNode() {
  dataRecord = new Profile[5];
  childPointer = new BTreeNode*[6];
  this -> leaf = false;
  next = NULL;
  count = 0;
}

BTreeNode::BTreeNode(bool leaf) {
  dataRecord = new Profile[5];
  childPointer = new BTreeNode*[6];
  this -> leaf = leaf;
  next = NULL;
  count = 0;
}

BTreeNode::~BTreeNode() {
  delete [] dataRecord;
  delete [] childPointer;
  leaf = false;
  count = -1;
}
