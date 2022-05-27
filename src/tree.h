#pragma once
#include <iostream>
#include <string>
#include <stdexcept>

class Tree      //the Morze letters' Tree
{ 
private:
  class Node 
  {
  public:
    std::pair<std::string, char>pr;     // first- Morze letter, second- English letter
    Node* Left = nullptr;
    Node* Right = nullptr;

    Node()
    {
      pr.first = "";
      pr.second = char();
    };  
    Node(std::pair<std::string, char>pr1) : pr(pr1), Left(nullptr), Right(nullptr) {};
  };

  Node* node = new Node();

public:
  Node* Insert(Node* tree, std::pair<std::string, char> pr1, int i);    //add new nodes
  void Find(Node* Tree, std::string value, int i, char& res);       // find the English letter by the Morze one
  void Free(Node* tree);                                        //remove all the nodes
  Node* Insert();                                               // adding all the letters in the constructor
  void Check(std::string value, int i, char& res);

  Tree() { Insert();}
  ~Tree() { Free(this->node); }
};


