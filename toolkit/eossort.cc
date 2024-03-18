#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <bits/stdc++.h>
#include <TString.h>

int macro(std::string inputname) {
  std::cout<<std::endl;
  std::ifstream getdata(inputname.c_str());
  std::string line;
  std::map<float, std::string> dirs;
  std::vector<float> v;
  while (!getdata.eof()) {
    std::getline(getdata, line);
    std::stringstream ss(line);
    std::string temp, name, unit; float size;
    ss >> temp >> temp >> temp >> temp
       >> size >> unit
       >> temp >> temp >> temp
       >> name;
    if (unit != "T") continue;
    dirs[size] = Form("%.1f%s  %s", size, unit.c_str(), name.c_str());
    v.push_back(size);
  }
  std::sort(v.begin(), v.end(), std::greater<int>());
  for (auto i : v) {
    std::cout<<dirs[i]<<std::endl;
  }
  return 0;
}

int main(int argc, char* argv[]) {
  if (argc == 2)
    return macro(argv[1]);
  return 1;
}
