#include "translate.h"
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include "tree.h"

void Translate::ABC_Init()
{
  Translate::Eng = { {'a',".-"}, {'b',"-..."}, {'c', "-.-."}, {'d',"-.."}, {'e', "."},
                     {'f', "..-."}, {'g', "--."}, {'h',"...."}, {'i',".."}, {'j',".---"},
                     {'k',"-.-"},{'l',".-.."}, {'m',"--"}, {'n',"-."}, {'o',"---"},
                     {'p',".--."}, {'q', "--.-"}, {'r',".-."}, {'s',"..."}, {'t',"-"},
                     {'u',"..-"}, {'v',"...-"}, {'w',".--"}, {'x',"-..-"}, {'y',"-.--"}, {'z',"--.."} };
}

std::string Translate::Morze(std::string& S, Tree* Obj)
{
  std::string cur = "", S1 = "";
  char res = char();
  for (int i = 0; i < S.size(); i++)
  {
    try 
    {
      if (S[i] != '.' && S[i] != '-' && S[i] != ' ')     //if there are wrong elements in the text
      {
        throw std::invalid_argument("The original text is in English");
      }
    }
    catch (std::invalid_argument& e)
    {
      throw e;
    }
    if (S[i] != ' ')      //next letter marker
    {
      cur += S[i];
    }
    else
    {
      (Obj->Check(cur, 0, res));      //finding the correct English letter
       S1 += res;
       cur = "";
       if (S[i + 1] == ' ')           //two spaces mark next word
       {
         S1 += ' ';
         i++;
       }
    }
  }
  if(cur!=" "&& cur!="")              //checking the last letter
  {
    (Obj->Check(cur, 0, res));
    S1 += res;
  }
  return S1;

}

std::string Translate::English(std::string& S2)
{
std::string SR ="";
    for (int i = 0; i <S2.size(); i++)          //not translated characters
    {
        if ((S2[i] != ' ') && (S2[i] != '.') && (S2[i] != ',') && (S2[i] != '!') && (S2[i] != '?') && (!(S2[i] >= 'a' && S2[i] <= 'z')))
        {
            continue;
        }

        if (S2[i] >= 'a' && S2[i] <= 'z')
        {
            SR+= Eng[(int)S2[i]- 97].second;     //finding the correct Morze letter
            SR+=" ";
        }
        else
        {
            SR += S2[i];      //adding space
        }
    }

    return SR;
}

