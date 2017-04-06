#include "BTreeNetwork.h"
#include <string>
#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

BTreeNetwork::BTreeNetwork() {
  root = NULL;
}  

void BTreeNetwork::insert(Profile *person, BTreeNode *&pointer) {
  if (pointer == NULL) {
    pointer = new BTreeNode(true);
    add(pointer -> dataRecord[0], *person);
    pointer -> count++;
  }
  else if (pointer -> leaf == true) {
    if (pointer -> count < 3) {
      add(pointer -> dataRecord[pointer -> count], *person);
      pointer -> count++;
      sort(pointer);
    }
    else if (pointer -> count == 3) {
      add(pointer -> dataRecord[pointer -> count], *person);
      pointer -> count++;
      sort(pointer);
      //begin split
      BTreeNode *temp = pointer;
      //create three new BTreeNodes
      pointer = new BTreeNode(false);
      pointer -> childPointer[0] = new BTreeNode(true);
      pointer -> childPointer[1] = new BTreeNode(true);
      //split original BTreeNode amongst children of new
      add(pointer -> childPointer[0] -> dataRecord[0], temp -> dataRecord[0]);
      add(pointer -> childPointer[0] -> dataRecord[1], temp -> dataRecord[1]);
      add(pointer -> childPointer[1] -> dataRecord[0], temp -> dataRecord[2]);
      add(pointer -> childPointer[1] -> dataRecord[1], temp -> dataRecord[3]);
      pointer -> childPointer[0] -> count = 2;
      pointer -> childPointer[1] -> count = 2;
      //assign key to root BTreeNode
      add(pointer -> dataRecord[0], temp -> dataRecord[2]);
      pointer -> count = 1;
      //delete old BTreeNode
      delete temp;
    }
  }
  else if (pointer -> leaf == false) {
    BTreeNode* traverser = traversal(person, pointer);
    BTreeNode* traverserLeaf = traversalLeaf(person, traverser);
    if (traverserLeaf -> count < 3) {
      add(traverserLeaf -> dataRecord[traverserLeaf -> count], *person);
      traverserLeaf -> count++;
      sort(traverserLeaf);
    }
    else if (traverserLeaf -> count == 3 && traverser -> count <= 4) {
      int location = 0;
      for (int i = 0; i < traverser -> count; i++) {
	int iterator = 0;
	if (traverser -> dataRecord[i].name != person -> name) {
	  while (int(traverser -> dataRecord[i].name[iterator]) ==
		 int(person -> name[iterator])) {
	    iterator++;
	  }
	  if (int(traverser -> dataRecord[i].name[iterator]) >
	      int(person -> name[iterator])) {
	    break;
	  }
	}
	location++;
      }
      BTreeNode *temp = new BTreeNode(false);
      for (int i = 0; i < traverser -> count; i++) {
	if (i < location) {
	  add(temp -> dataRecord[i], traverser -> dataRecord[i]);
	  temp -> childPointer[i] = traverser -> childPointer[i];
	}
	else {
	  add(temp -> dataRecord[i+1], traverser -> dataRecord[i]);
	  temp -> childPointer[i+2] = traverser -> childPointer[i+1];
	}
      }
      traverser -> count++;
      add(traverserLeaf -> dataRecord[traverserLeaf -> count], *person);
      traverserLeaf -> count++;
      sort(traverserLeaf);
      temp -> childPointer[location] = new BTreeNode(true);
      temp -> childPointer[location + 1] = new BTreeNode(true);
      add(temp -> childPointer[location] -> dataRecord[0], traverserLeaf -> dataRecord[0]);
      add(temp -> childPointer[location] -> dataRecord[1], traverserLeaf -> dataRecord[1]);
      add(temp -> childPointer[location + 1] -> dataRecord[0], traverserLeaf -> dataRecord[2]);
      add(temp -> childPointer[location + 1] -> dataRecord[1], traverserLeaf -> dataRecord[3]);
      temp -> childPointer[location] -> count = 2;
      temp -> childPointer[location + 1] -> count = 2;
      add(temp -> dataRecord[location], traverserLeaf -> dataRecord[2]);
      for (int i = 0; i <= traverser -> count; i++) {
	if (i != traverser -> count) {
	  add(traverser -> dataRecord[i], temp -> dataRecord[i]);
	};
	traverser -> childPointer[i] = temp -> childPointer[i];
      }
      split(root);
    }
  }
}
/*
    //splitting the first parent  
    if (traverser -> count == 5 && traverser -> childPointer[0] -> leaf == true) {
      BTreeNode *temporary = pointer;
      pointer = new BTreeNode(false);
      pointer -> childPointer[0] = new BTreeNode(false);
      pointer -> childPointer[1] = new BTreeNode(false);
      pointer -> childPointer[0] -> childPointer[0] = temporary -> childPointer[0];
      pointer -> childPointer[0] -> childPointer[1] = temporary -> childPointer[1];
      pointer -> childPointer[0] -> childPointer[2] = temporary -> childPointer[2];
      pointer -> childPointer[1] -> childPointer[0] = temporary -> childPointer[3];
      pointer -> childPointer[1] -> childPointer[1] = temporary -> childPointer[4];
      pointer -> childPointer[1] -> childPointer[2] = temporary -> childPointer[5];
      add(pointer -> childPointer[0] -> dataRecord[0], temporary -> dataRecord[0]);
      add(pointer -> childPointer[0] -> dataRecord[1], temporary -> dataRecord[1]);
      add(pointer -> childPointer[1] -> dataRecord[0], temporary -> dataRecord[3]);
      add(pointer -> childPointer[1] -> dataRecord[1], temporary -> dataRecord[4]);
      add(pointer -> dataRecord[0], temporary -> dataRecord[2]);
      pointer -> childPointer[0] -> count = 2;
      pointer -> childPointer[1] -> count = 2;
      pointer -> count = 1;
    }
    else if (traverser -> count == 5 ) {
    }
  }
  } */ 

void BTreeNetwork::split(BTreeNode *&pointer) {
  /*
  if (pointer -> childPointer[0] -> leaf == true) {
    return;
    }*/
  /*  for (int i = 0; i < pointer -> count; i++) {
    if (pointer -> childPointer[i] -> leaf == false) {
      split(pointer -> childPointer[i]);
    }
    }*/
  
  if (pointer == NULL || pointer -> leaf == true) {
    return;
  }

  for (int i = 0; i <= pointer -> count; i++) {
    split(pointer -> childPointer[i]);
  }
  
  for (int i = 0; i <= pointer -> count; i++) {
    if (pointer -> childPointer[i] -> count == 5 && pointer -> childPointer[i] -> leaf == false) {
      BTreeNode *temp = new BTreeNode(false);
      for (int j = 0; j < pointer -> count; j++) {
        if (j < i) {
          add(temp -> dataRecord[j], pointer -> dataRecord[j]);
          temp -> childPointer[j] = pointer -> childPointer[j];
        }
        else {
	  add(temp -> dataRecord[j+1], pointer -> dataRecord[j]);
          temp -> childPointer[j+2] = pointer -> childPointer[j+1];
        }
      }
      pointer -> count++;
      temp -> childPointer[i] = new BTreeNode(false);
      temp -> childPointer[i + 1] = new BTreeNode(false);
      temp -> childPointer[i] -> childPointer[0] = pointer -> childPointer[i] -> childPointer[0];
      temp -> childPointer[i] -> childPointer[1] = pointer -> childPointer[i] -> childPointer[1];
      temp -> childPointer[i] -> childPointer[2] = pointer -> childPointer[i] -> childPointer[2];
      temp -> childPointer[i+1] -> childPointer[0] = pointer -> childPointer[i] -> childPointer[3];
      temp -> childPointer[i+1] -> childPointer[1] = pointer -> childPointer[i] -> childPointer[4];
      temp -> childPointer[i+1] -> childPointer[2] = pointer -> childPointer[i] -> childPointer[5];
      add(temp -> childPointer[i] -> dataRecord[0], pointer -> childPointer[i] -> dataRecord[0]);
      add(temp -> childPointer[i] -> dataRecord[1], pointer -> childPointer[i] -> dataRecord[1]);
      add(temp -> childPointer[i + 1] -> dataRecord[0], pointer -> childPointer[i] -> dataRecord[3]);
      add(temp -> childPointer[i + 1] -> dataRecord[1], pointer -> childPointer[i] -> dataRecord[4]);
      temp -> childPointer[i] -> count = 2;
      temp -> childPointer[i + 1] -> count = 2;
      add(temp -> dataRecord[i], pointer -> childPointer[i] -> dataRecord[2]);
      for (int j = 0; j <= pointer -> count; j++) {
        if (j != pointer -> count) {
          add(pointer -> dataRecord[j], temp -> dataRecord[j]);
        }
        pointer -> childPointer[j] = temp -> childPointer[j];
      }
    }
  }
  if (root == pointer && pointer -> count == 5 && pointer -> leaf == false) {
    BTreeNode *temporary = pointer;                                               
    pointer = new BTreeNode(false);                                               
    pointer -> childPointer[0] = new BTreeNode(false);                            
    pointer -> childPointer[1] = new BTreeNode(false);                            
    pointer -> childPointer[0] -> childPointer[0] = temporary -> childPointer[0];
    pointer -> childPointer[0] -> childPointer[1] = temporary -> childPointer[1];
    pointer -> childPointer[0] -> childPointer[2] = temporary -> childPointer[2];
    pointer -> childPointer[1] -> childPointer[0] = temporary -> childPointer[3];
    pointer -> childPointer[1] -> childPointer[1] = temporary -> childPointer[4];
    pointer -> childPointer[1] -> childPointer[2] = temporary -> childPointer[5];
    add(pointer -> childPointer[0] -> dataRecord[0], temporary -> dataRecord[0]);
    add(pointer -> childPointer[0] -> dataRecord[1], temporary -> dataRecord[1]);
    add(pointer -> childPointer[1] -> dataRecord[0], temporary -> dataRecord[3]);
    add(pointer -> childPointer[1] -> dataRecord[1], temporary -> dataRecord[4]);
    add(pointer -> dataRecord[0], temporary -> dataRecord[2]);                    
    pointer -> childPointer[0] -> count = 2;                                      
    pointer -> childPointer[1] -> count = 2;                                      
    pointer -> count = 1;
    root = pointer;
  }
}

    
void BTreeNetwork::sort(BTreeNode *pointer) {
  for (int h = pointer -> count - 1; h > 0; h--) {
    for (int i = 0; i < h; i++) {
      int iterator = 0;
      while (int(pointer -> dataRecord[i].name[iterator]) ==
	     int(pointer -> dataRecord[i+1].name[iterator])) {
	iterator++;
      }
      if (int(pointer -> dataRecord[i].name[iterator]) >
	  int(pointer -> dataRecord[i+1].name[iterator])) {
	swap(pointer -> dataRecord[i], pointer -> dataRecord[i+1]);
      }
    }
  }
}
 
void BTreeNetwork::swap(Profile &person1, Profile &person2) {
  string tempName = person1.name;
  int tempKey = person1.key;
  person1.name = person2.name;
  person1.key = person2.key;
  person2.name = tempName;
  person2.key = tempKey;
}

void BTreeNetwork::add(Profile &person1, Profile &person2) {
  person1.name = person2.name;
  person1.key = person2.key;
}

BTreeNode* BTreeNetwork::traversalParent(Profile *person, BTreeNode *&pointer) {
  if (pointer -> childPointer[0] != NULL && 
      pointer -> childPointer[0] -> childPointer[0] != NULL &&
      pointer -> childPointer[0] -> childPointer[0] -> leaf == true) {
    return pointer;
  }
  BTreeNode *traverser =  pointer -> childPointer[0];
  for (int i = 0; i < pointer -> count; i++) {
    int iterator = 0;
    if (pointer -> dataRecord[i].name != person -> name) {
      while (int(pointer -> dataRecord[i].name[iterator]) ==
             int(person -> name[iterator])) {
        iterator++;
      }
      if (int(pointer -> dataRecord[i].name[iterator]) >
          int(person -> name[iterator])) {
        break;
      }
    }
    traverser = pointer -> childPointer[i+1];
  }
  return traversalParent(person, traverser);
}

BTreeNode* BTreeNetwork::traversal(Profile *person, BTreeNode *&pointer) {
  if (pointer -> childPointer[0] -> leaf == true) {
    return pointer;
  }
  BTreeNode *traverser =  pointer -> childPointer[0]; 
  for (int i = 0; i < pointer -> count; i++) {
    int iterator = 0;
    if (pointer -> dataRecord[i].name != person -> name) {
      while (int(pointer -> dataRecord[i].name[iterator]) ==
	     int(person -> name[iterator])) {
	iterator++;
      }
      if (int(pointer -> dataRecord[i].name[iterator]) >
	  int(person -> name[iterator])) {
	break;
      }
    }
    traverser = pointer -> childPointer[i+1];
  }
  return traversal(person, traverser);
}

BTreeNode* BTreeNetwork::traversalLeaf(Profile *person, BTreeNode *&pointer) {
  if (pointer -> leaf == true) {
    return pointer;
  }
  BTreeNode *traverser =  pointer -> childPointer[0];
  for (int i = 0; i < pointer -> count; i++) {
    int iterator = 0;
    if (pointer -> dataRecord[i].name != person -> name) {
      while (int(pointer -> dataRecord[i].name[iterator]) ==
	     int(person -> name[iterator])) {
	iterator++;
      }
      if (int(pointer -> dataRecord[i].name[iterator]) >
	  int(person -> name[iterator])) {
	break;
      }
    }
    traverser = pointer -> childPointer[i+1];
  }
  return traversalLeaf(person, traverser); 
}

BTreeNode* BTreeNetwork::search(string name, BTreeNode*& pointer) {
  if (pointer -> leaf == true) {
    return pointer;
  }
  BTreeNode *traverser =  pointer -> childPointer[0];
  for (int i = 0; i < pointer -> count; i++) {
    int iterator = 0;
    if (pointer -> dataRecord[i].name != name) {
      while (int(pointer -> dataRecord[i].name[iterator]) ==
             int(name[iterator])) {
	iterator++;
      }
      if (int(pointer -> dataRecord[i].name[iterator]) >
          int(name[iterator])) {
	break;
      }
    }
    traverser = pointer -> childPointer[i+1];
  }
  return search(name, traverser);
}

void BTreeNetwork::linkNetwork(BTreeNode*& pointer) {
}

bool BTreeNetwork::checkNetwork(BTreeNode*& pointer) {
  if (pointer -> leaf == false) {
    for (int i = 0; i <=  pointer -> count; i++) {
      if(checkNetwork(pointer -> childPointer[i])) {
	return true;
      }
    }
  }
  if (pointer -> leaf == true && pointer -> count == 4) {
    return true;
  }
  else if (pointer -> leaf == false && pointer -> count == 5) {
    return true;
  }
  return false;
}
    
string BTreeNetwork::range(string lowerBound, string upperBound, BTreeNode*& pointer) {
  string list = "";
  if (pointer -> leaf == true) {
    for (int i = 0; i < pointer -> count; i++) {
      if (checkBounds(lowerBound, upperBound, pointer -> dataRecord[i].name)) {
	list += to_string(pointer -> dataRecord[i].key);
	list += ",";
      }
    }
  }
  else {
    for (int i = 0; i <= pointer -> count; i++)  {
      list += range(lowerBound, upperBound, pointer -> childPointer[i]);
    }
  }
  return list;
  
}

bool BTreeNetwork::checkBounds(string lowerBound, string upperBound, string name) {
  if (lowerBound != name && upperBound != name) {
    int iterator = 0;
    while (int(lowerBound[iterator]) ==
	   int(name[iterator])) {
      iterator++;
    }
    if (int(lowerBound[iterator]) >
	int(name[iterator])) {
      return false;
    }
    iterator = 0;
    while (int(upperBound[iterator]) == 
	   int(name[iterator])) {
      iterator++;
    }
    if (int(upperBound[iterator]) < 
	int (name[iterator])) {
      return false;
    }
  }
  return true;
}
