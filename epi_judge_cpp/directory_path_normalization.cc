#include <string>
#include <vector>
#include <sstream>

#include "test_framework/generic_test.h"
using std::string;
using std::vector;
using std::stringstream;
string ShortestEquivalentPath(const string& path) {
  if(path.empty()){
    throw std::invalid_argument("Not a valid path");
  }

  vector<string> directory;
  stringstream ss(path);
  string token;
  const char delimeter = '/';

  if(path.front() == '/'){
    directory.emplace_back("/");
  }

  while(getline(ss, token, delimeter)){
    if(token == ".."){
      if(directory.empty() || directory.back() == ".."){
        directory.emplace_back(token);
      }else{
        if(directory.back() == "/"){
          throw std::invalid_argument("Not a valid path");
        }
        directory.pop_back();
      }
    }else if(token != "." && !token.empty()){
      directory.emplace_back(token);
    }
  }

  string pathname = "";
  if(!directory.empty()){
    pathname += directory.front();
    for(int i = 1; i < directory.size(); i++){
      if(i == 1 && pathname == "/"){
        pathname += directory[i];
      }else{
        pathname += '/' + directory[i];
      }
    }
  }

  return pathname;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"path"};
  return GenericTestMain(args, "directory_path_normalization.cc",
                         "directory_path_normalization.tsv",
                         &ShortestEquivalentPath, DefaultComparator{},
                         param_names);
}
