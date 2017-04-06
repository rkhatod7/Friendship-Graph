#ifndef B_TREE_NETWORK_H
#define B_TREE_NETWORK_H

#include "Profile.h"
#include "BTreeNode.h"
#include <string>

using namespace std;

class BTreeNetwork {
 public:
  BTreeNode *root;
  
  BTreeNetwork();
  void insert(Profile *person, BTreeNode *&pointer);
  void split(BTreeNode *&pointer);
  void sort(BTreeNode *pointer);
  void swap(Profile &person1, Profile &person2);
  void add(Profile &person1, Profile &person2);
  BTreeNode* traversalParent(Profile *person, BTreeNode *&pointer);
  BTreeNode* traversal(Profile *person, BTreeNode *&pointer);
  BTreeNode* traversalLeaf(Profile *person, BTreeNode *&pointer);
  BTreeNode* search(string name, BTreeNode *&pointer);
  void linkNetwork(BTreeNode *&pointer);
  bool checkNetwork(BTreeNode *&pointer);
  string range(string lowerBound, string upperBound, BTreeNode *&pointer);
  bool checkBounds(string lowerBound, string upperBound, string name);
};

#endif
