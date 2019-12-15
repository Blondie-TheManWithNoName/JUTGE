#include <iostream>
#include <queue>
#include <sstream>

using namespace std;


int main() {

	queue<int> q;
	queue<int> qaux;
	int n, sum = 0; 
	unsigned int i;
	string str;
	while (getline(cin, str)) {

		istringstream ss(str);
		while (ss >> n)
		{
			q.push(n);
		}

		while(not q.empty())
		{
		//	cout << "sum: " << sum << "  |  fron(): " << q.front() << endl;
			if (sum >= q.front())
				qaux.push(q.front());
			sum += q.front();
			q.pop();
		}
		i = qaux.size();
		while (not qaux.empty())
		{
			if (i == qaux.size())
				cout << qaux.front();
			else
				cout << " " << qaux.front();
			qaux.pop();
		}
		cout << endl;
		sum = 0;
	}
}
