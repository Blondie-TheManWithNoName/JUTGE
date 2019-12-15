#include <iostream>
#include <queue>
#include <sstream>
#include <vector>
#include <string>

using namespace std;


int main() {
  string str;
  int cua;
  vector<queue<string> > v;
  queue<string> q;

  getline(cin, str);
  istringstream strs(str);
  strs >> cua;
  v.resize(cua);

  for (unsigned int i = 0; i < v.size(); ++i) {
      getline(cin, str);
      istringstream ss(str);
      while (ss >> str) {
        v[i].push(str);
      }
  }

  cout << "SORTIDES\n--------" << endl;
  while (getline(cin, str)) {
    istringstream ss(str);
    ss >> str;
    if (str == "SURT") {
      ss >> cua;
      if (cua > 0 and cua <= v.size() and not v[cua-1].empty()) {
        cout << v[cua-1].front() << endl;
        v[cua-1].pop();
      }
    }
    else if (str == "ENTRA") {
      ss >> str;
      ss >> cua;
      if (cua > 0 and cua <= v.size()) {
        v[cua-1].push(str);
      }
    }
  }

  cout << "\nCONTINGUTS FINALS\n-----------------" << endl;
  for (unsigned int i = 0; i < v.size(); ++i) {
      cout << "cua " << (i+1) << ":";
      while (not v[i].empty()) {
        cout << " " << v[i].front();
        v[i].pop();
      }
      cout << endl;
  }
}