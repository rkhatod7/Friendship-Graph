  #ifndef FRIEND_NETWORK_H
#define FRIEND_NETWORK_H
#include "Node.h"
#include "FriendNode.h"
#include <string>

using namespace std;

class FriendNetwork {
 public:
  FriendNode *friendGraph;
  
  FriendNetwork();
  int insertPerson(string name);
  void addFriend(int key, string fri);
  int findPerson(string name);
  int hash(string name);
  void printNetwork();
  string retrieveFriends(int key);

 private:
  int TABLE_SIZE;
};

#endif
