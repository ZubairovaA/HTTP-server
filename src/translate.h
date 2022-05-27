#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include "tree.h"

class Translate
{
private:
  std::vector<std::pair <char, const char*> > Eng;      //English letters

public:
  std::string Morze(std::string& S, Tree* Obj);  //translate from Morze
  std::string English(std::string& S2);          //translate from English
  void ABC_Init();                                       //filling the Eng
  std::string Work(std::string& S, Tree* Obj)    //translation
  {
    std::string result = "";
    try
    {
      result = Morze(S, Obj);
      return result;
    }
    catch (std::invalid_argument& e)
    {
      std::cout << e.what();
      result = English(S);
      return result;
    }
  }
  Translate() { ABC_Init(); };
};
