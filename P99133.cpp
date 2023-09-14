#include <iostream>
#include <vector>
#include <string>
using namespace std;


string inverseString(string s)
{
    string newS = "";
    for (int i = s.length() - 1; i >= 0; i--) newS += s[i]; 
    
    return newS;
}

int main()
{
    int n;
    cin >> n;
    vector<string> stringVector;
    string s = "";
    for (int i = 0; i < n; i++) 
    {
        cin >> s;
        stringVector.push_back(s);
    }
    for (int i = stringVector.size() - 1; i >= 0; i--) cout << inverseString(stringVector[i]) << endl;

    return 0;
}