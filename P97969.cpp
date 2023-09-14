#include <iostream>
#include <string>
using namespace std;



int checkAs(string s)
{
    int n = 0;
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == 'a') ++n;
    }

    return n;
}

int main() {
    
    string s;
    getline(cin, s);
    cout << checkAs(s) << endl;
    return 0;
}