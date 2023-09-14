#include <iostream>
using namespace std;



void printSuccessors(int a, int b)
{
    while (a <= b) (a < b) ? cout << a++ << "," : cout << a++;
    cout << endl;
}

int main() {
    
    int a, b;
    cin >> a >> b;
    printSuccessors(a, b);
    return 0;
}
