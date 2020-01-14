#include <iostream>

#include <string>

using namespace std;
string inc(string s);

int main()
{
  string base = "aaaa";

  while(base != "zzzz") {cout << base << endl; base = inc(base);}
  return 0;
}

string inc(string s)
{ string b = s;
  if(b[0] == 'z')
  {
    b[0] = 'a';
    if(b[1] == 'z')
    {
      b[1] = 'a';
      if(b[2] == 'z')
      {
	b[2] = 'a';
	b[3] += 1;
      }
      else b[2] +=1;
    }
    else b[1] += 1;
  }
  else
    b[0] += 1;
  return b;
}
