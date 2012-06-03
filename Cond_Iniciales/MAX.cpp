#include <iostream>
#include <algorithm>
using namespace std;
int main () 
{
  cout << "max(3,4)==" << max(3,4) << endl;
  cout << "max(4,3)==" << max(4,3) << endl;
  cout << "max('b','d')==" << max('b','d') << endl;
  cout << "max(3.14,2.72)==" << max(3.14,2.72) << endl;
  return 0;
}
