#include "server_answer.h"

void ServerAnswer::HandleRequest(int sock)
{
  const int max_client_buffer_size = 1024;
  char buf[max_client_buffer_size];

  int result = recv(sock, buf, max_client_buffer_size, 0);

  std::stringstream response; 
  std::stringstream response_body; 

  if (result == 0) 
  {
   printf("connection closed...\n");
  }
  else if (result > 0) 
  {
    buf[result] = '\0';
    printf("Recieved new request\n");
    std::string request_body = ParseHTTP(buf, result);
    if(request_body == "")
    {
      printf(" Empty string ");
    }
    std::string answer = translation.Work(request_body, &Obj);

    response_body << "Morze - English Translator\n"
    << "Enter " << request_body << "\n"
    << "Translation is " << answer << "\n";

    response << "HTTP/1.1 200 OK\r\n"
    << "Version: HTTP/1.1\r\n"
    << "Content-Type: text/html; charset=utf-8\r\n"
    << "Content-Length: " << response_body.str().length()
    << "\r\n\r\n"
    << response_body.str();
    result = send(sock, response.str().c_str(), response.str().length(), 0);
  }
}

void ServerAnswer::FillHeaders()
{
  ServerAnswer::headers.insert({ "Content-Type" ,"text/html" });
}

void ServerAnswer::FillMethods()
{
  ServerAnswer::methods.insert("GET");
}

RequestState ServerAnswer::GetRequestState()
{
  return state;
}

std::string ServerAnswer::ParseHTTP(char* buf, int size)
{
  std::stringstream requestStream(buf);
  std::string requestString = requestStream.str();
  std::string currentString = "";
  std::string delimiter = "\r\n";
  size_t currPos = 0, emptyStr = requestString.find("\r\n\r\n");
  while (currPos < emptyStr)
  {
    currentString.clear();
    size_t pos = requestString.find_first_of(delimiter, currPos);
    currentString = requestString.substr(currPos, pos - currPos);
    currPos = (pos + 2);
    requestFilds.push_back(currentString);
  }

  std::string method = requestFilds[0].substr(0, requestFilds[0].find(" "));
  if (methods.find(method) == methods.end())
  {
    state = UNKNOWN_METHOD;
    return "";
  }
  std::map<std::string, std::string>::iterator iter;
  for (size_t index = 1; index < requestFilds.size(); index++)
  {
    std::string header = requestFilds[index].substr(0, requestFilds[index].find(":"));
    if ((iter = headers.find(header)) != headers.end())
    {
      if (requestFilds[index].find(iter->second) == std::string::npos)
      {
        state = WRONG_REQUEST;
        return "";
      }
    }
  }
  std::string body = requestString.substr(emptyStr + 6, requestString.size() - (emptyStr + 4));
  return body;
}
