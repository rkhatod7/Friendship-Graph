/*
 * Main.cpp
 *
 *  Created on: Feb 11, 2016
 *  Modified on March 4, 2016
 *      Authors: Radhika Khatod, Drew Taylor
 */

#include "ProfileData.h"
#include "FriendNetwork.h"
#include "BTreeNetwork.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

vector<string> split(string str, char delimiter)
{
  vector<string> internal;
  stringstream ss(str);       // turn the string into a stream.                                                                                                                             
  string tok;

  while(getline(ss, tok, delimiter))
    {
      internal.push_back(tok);
    }

  return internal;
}

int main ()
{
  ProfileData profiles;
  FriendNetwork friendList;
  BTreeNetwork tree;

  profiles.createFile();
  ifstream f;
  f.open("Generated.txt", ios::in);
  if(!f) cerr << "File not found" << endl;
  else {
    string line;
    while(std::getline(f, line)) {
      vector<string> words = split(line, ',');
      int key = friendList.insertPerson(words[0]);
      profiles.insertProfile(key, words[0], words[1], words[2]);
      Profile *profile = new Profile(key, words[0]);
      tree.insert(profile, tree.root);
      for (int i = 3; i < words.size(); i++) {
	friendList.addFriend(key, words[i]);
      }
    }
  }
  cout << "                           #####\n";
  cout << "                       #######\n";
  cout << "            ######    ########       #####\n";
  cout << "        #####################  #############\n";
  cout << "    ######################--#####################\n";
  cout << "  ####         ######################          #####\n";
  cout <<  "##          ####      #############              ###\n";
  cout << "#          ####          ############               ##\n";
  cout << "          ###              $$$$$$ ####                 #\n";
  cout << "         ##                $$$$$$   ###\n";
  cout << "         #                 $$$$$$    ##\n";
  cout << "                           $$$$$$    ##\n";
  cout << "                           $$$$$$     #\n";
  cout << "                           $$$$$$\n";
  cout << "                           $$$$$$\n";
  cout << "                           $$$$$$\n";
  cout << "                           $$$$$$\n";
  cout << "                           $$$$$$\n";
  cout << "                           $$$$$$\n";
  cout << "                           $$$$$$\n";
  cout << "                           $$$$$$\n";
  cout << "                           $$$$$$\n";
  cout << "                           $$$$$$\n";
  cout << "                           $$$$$$\n";
  cout << "                           $$$$$$\n";


  cout << "       WELCOME TO THE         \n";
  cout << "**************************\n";
  cout << "╔╦╗┌─┐┬    ╔═╗┬  ┌─┐┬ ┬┌─┐\n ║║├┤ │    ╠═╝│  ├─┤└┬┘├─┤\n═╩╝└─┘┴─┘  ╩  ┴─┘┴ ┴ ┴ ┴ ┴\n"\
    ;
  cout << "**************************\n";
  cout << "          SOCIETY         \n";
  /*
  for (int i = 0; i < 211; i++) {
    string entireProfile = "";
    entireProfile += profiles.retrieveProfile(i);
    entireProfile += friendList.retrieveFriends(i);
    if (entireProfile != "") {
      cout << entireProfile << endl;
    }
    }*/
  try
    {
      
      while(true) {
	cout << "Type one of the following options to continue:\n> Insert\n> AddFriend\n> ListFriendsInfo\n> ListInfo\n> PrintAll\n";
	string x;
        getline(cin, x);
	string* argument = new string[5];
	int index = 0;
	string value = "";
	for (int i = 0; i < x.length(); i++) {
	  if (index == 3) {
	    if (x[i] == '"') {
	      for (int j = i+1; j < x.length()-1; j++) {
		value += x[j];
	      }
	    }
	  }
	  else {
	    if (x[i] != ' ') {
	      value += x[i];
	    }
	    else {
	      argument[index] = value;
	      value = "";
	      index++;
	    }
	  }
	  if (i == x.length() - 1) {
	    argument[index] = value;
	    value = "";
	    index++;
	  }
	}
	
	if(argument[0] == "INSERT" || argument[0] == "insert" || argument[0] == "Insert") {
	  int key2 = friendList.insertPerson(argument[1]);
	  profiles.insertProfile(key2, argument[1], argument[2], argument[3]);
	  Profile *profile2 = new Profile(key2, argument[1]);
	  tree.insert(profile2, tree.root);
	}
	
	if(argument[0] == "ADDFRIEND" || argument[0] == "addfriend" || argument[0] == "AddFriend") {
	  if (friendList.findPerson(argument[1]) != -1 && friendList.findPerson(argument[2]) != -1) {
	    friendList.addFriend(friendList.findPerson(argument[1]), argument[2]);
	    friendList.addFriend(friendList.findPerson(argument[2]), argument[1]);
	  }
	}
	
	//lists name, age, and occupation of friends of some user                                                                                                            
	if(argument[0] == "ListFriendsInfo" || argument[0] == "list friends info" || argument[0] == "List friends info") {
	  if (friendList.findPerson(argument[1]) != -1) {
	    string friendArray = friendList.retrieveFriends(friendList.findPerson(argument[1]));
	    string friendProfile;
	    for (int i = 0; i < friendArray.length(); i++) {
	      if (friendArray[i] != ',') {
		friendProfile += friendArray[i];
	      }
	      else {
		cout << profiles.retrieveProfile(friendList.findPerson(friendProfile)) << endl;
		friendProfile = "";
	      }
	    }
	  }
	}
	
	//List all users' information with names e.g. Alice <= name <= Bob, ListInfo lowerBound upperBound,                                                                      
	//where lowerBound and upperBound are names that may or may not be in the system                                                                                         
	
	if(argument[0] == "ListInfo" || argument[0] == "list info") {
	  string keys =  tree.range(argument[1], argument[2], tree.root);
	  string aKey;
	  for (int i = 0; i < keys.length(); i++) {
	    if (keys[i] != ',') {
	      aKey += keys[i];
	    }
	    else {
	      cout << profiles.retrieveProfile(atoi(aKey.c_str())) << endl;
	      aKey = "";
	    }
	  }
	}
	
	if(argument[0] == "PrintAll" || argument[0] == "print all" || argument[0] == "Print all") {
	  for (int i = 0; i < 211; i++) {
	    string entireProfile = "";
	    entireProfile += profiles.retrieveProfile(i);
	    string check = friendList.retrieveFriends(i);
	    if (check != "") {
	      entireProfile += ",";
	    }
	    entireProfile += check;
	    if (entireProfile != "") {
	      cout << entireProfile << endl;
	    }
	  }
	}	
      }
    }
  catch(exception& ex) {
    //    cerr < ex.what() << endl;
  }
  return 0;
}
