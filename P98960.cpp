#include <iostream>
using namespace std;


char toUpperCase(char c)
{
    return c - 32;
}

char toLowerCase(char c)
{
    return c + 32;
}


int main() {
    char c;
    cin >> c;
    (c > 96) ? cout << toUpperCase(c) : cout << toLowerCase(c);
    cout << endl;
    return 0;
}