  #include "FriendNetwork.h"
#include <string>
#include <iostream>

using namespace std;

FriendNetwork::FriendNetwork() {
  TABLE_SIZE = 211;
  friendGraph = new FriendNode[TABLE_SIZE];
}

int FriendNetwork::insertPerson(string name) {
  int key = hash(name);
  while (friendGraph[key].name != "") {
    key++;
    if (key == TABLE_SIZE) {
      key = 0;
    }
  }
  friendGraph[key].name = name;
  return key;
}

void FriendNetwork::addFriend(int key, string fri) {
  if (friendGraph[key].next == NULL) {
    friendGraph[key].next = new FriendNode();
    friendGraph[key].next -> name = fri;
  }
  else {
    FriendNode *finder = friendGraph[key].next;
    while(finder -> next != NULL) {
      finder = finder -> next;
    }
    finder -> next = new FriendNode();
    finder -> next -> name = fri;
  }
}

int FriendNetwork::findPerson(string name) {
  int key = hash(name);
  while(friendGraph[key].name != name && 
	friendGraph[key].name != "") {
    key++;
    if (key == TABLE_SIZE) {
      key = 0;
    }
  }
  if (friendGraph[key].name != name) {
    key = -1;
  }
  return key;
}

int FriendNetwork::hash(string name) {
  int hash = 0;
  for (int i = 0; i < name.length(); i++) {
    hash = (hash * 101 + name[i]) % TABLE_SIZE;
  }
  return hash;
}

void FriendNetwork::printNetwork() {
  cout << "All available users:" << endl;
  for (int i = 0; i < TABLE_SIZE; i++) {
    cout << i << ": ";
    if (friendGraph[i].name == "") {
      cout << "NULL" << endl;
    }
    else {
      cout << friendGraph[i].name;
      FriendNode *finder = friendGraph[i].next;
      while (finder != NULL) {
	cout << ", " << finder -> name;
	finder = finder -> next;
      }
      cout << endl;
    }
  }
}

string FriendNetwork::retrieveFriends(int key) {
  string friends = "";
  FriendNode *finder = friendGraph[key].next;
  while (finder != NULL) {
    friends += finder -> name;
    if (finder -> next != NULL) {
      friends += ",";
    }
    finder = finder -> next;
  }
  return friends;
}
