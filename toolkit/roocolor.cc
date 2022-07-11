#include <TColor.h>
#include <iostream>
#include <string>
#include <map>

namespace xjjc
{
  bool str_contains(std::string str1, std::string str2) { return str1.find(str2) != std::string::npos; }
  bool str_startsby(std::string str1, std::string str2) { return str1.find_first_of(str2) == 0; }
  std::string str_eraseall(std::string strs, std::string sub)
  {
    std::string result(strs);
    std::string str(strs);
    size_t pos = str.find(sub, 0);
    size_t thispos = 0;
    while(pos != std::string::npos)
      {
        result.replace(pos + thispos, sub.size(), "");
        thispos -= sub.size();
        pos = str.find(sub, pos+1);
      }
    return result;
  }
}

std::map<std::string, int> precolor = {
  {"kWhite", 0},   
  {"kBlack", 1},   
  {"kGray", 920},
  {"kRed", 632}, 
  {"kGreen", 416}, 
  {"kBlue", 600}, 
  {"kYellow", 400}, 
  {"kMagenta", 616}, 
  {"kCyan", 432},
  {"kOrange", 800}, 
  {"kSpring", 820}, 
  {"kTeal", 840}, 
  {"kAzure", 860}, 
  {"kViolet", 880}, 
  {"kPink", 900}
};

int main(int argc, char* argv[])
{
  std::string cc = "kBlack";
  if(argc > 1) cc = std::string(argv[1]);
  int icol = 0;
  for(auto& pre : precolor)
    {
      if(xjjc::str_contains(cc, pre.first))
        {
          icol = pre.second;
          int offset = atoi(xjjc::str_eraseall(cc, pre.first).c_str());
          icol += offset;
          break;
        }
    }
  std::cout<<cc<<" => "<<icol<<std::endl;
  return 0;
}
