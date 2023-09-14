#include <iostream>
#include <vector>
using namespace std;


void mostra(vector<double> v)
{
  for (unsigned int i = 0; i < v.size(); ++i)
    cout << " " << v[i];
  cout << endl;
}



vector<double> ordenar(vector<double> v1, vector<double> v2)
{
  unsigned int c1 = 0, c2 = 0;
  vector<double> v(v1.size() + v2.size());

//  mostra(v1);
//  mostra(v2);
  for (unsigned int i = 0; i < v.size(); ++i)
  {
    if (c1 >= v1.size() and c2 < v2.size())
    {
      v[i] = v2[c2];
      ++c2; 
    }
    else if (c2 >= v2.size() and c1 < v1.size())
    {
      v[i] = v1[c1];
      ++c1; 
    }
    else if (v1[c1] < v2[c2] and c1 < v1.size())
    {
      v[i] = v1[c1];
      ++c1;
    }
    else if (v1[c1] > v2[c2] and c2 < v2.size())
    {
      v[i] = v2[c2];
      ++c2; 
    }
  }  
  return v;
}

void ordena_per_fusio(vector<double>& v)
{

  vector<double> v2(v.size()/2);
  int size = v.size();
  unsigned  int n = size/2;
  if (v.size()%2 != 0) ++n;
  vector<double> v1(n);

  for (unsigned int i = 0; i < n; ++i)
  {
    if (i < v2.size()) v2[v2.size() - i - 1] = v[size - i - 1];
    v1[i] = v[i];
  }
  if (v1.size() > 1)
     ordena_per_fusio(v1);

  if (v2.size() > 1)
     ordena_per_fusio(v2);

  v = ordenar(v1, v2);

}

int main() {
    int n;
    while (cin >> n) {
        vector<double> v(n);
        for (int i=0; i<n; ++i) {
            cin >> v[i];
        }
        ordena_per_fusio(v);
        for (int i=0; i<n; ++i) {
            cout << " " << v[i];
        }
        cout << endl;
    }
}
