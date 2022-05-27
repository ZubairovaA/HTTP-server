#include <iostream>
#include <unistd.h>
#include <string.h>
#include <sstream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <set>
#include <map>
#include "translate.h"
#include "tree.h"

enum RequestState
{
  UNKNOWN_METHOD,
  EMPTY_REQUEST,
  WRONG_REQUEST, 
  CORRECT
};

class ServerAnswer
{
public:
  ServerAnswer()
  {
    FillHeaders();
    FillMethods();
  }
  void HandleRequest(int sock);
  void FillMethods();
  void FillHeaders();
  RequestState GetRequestState();
  std::string ParseHTTP(char* buf, int size);
private:
  std::set<std::string> methods;
  std::map<std::string, std::string> headers;
  std::vector<std::string> requestFilds;
  RequestState state = CORRECT;
  Translate translation;
  Tree Obj;
};
