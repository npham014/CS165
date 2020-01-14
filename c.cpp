#include <iostream>
#include <fstream>

using namespace std;
string incstring(string, int);

int main(int argc, char **  argv)
{
  string s = "";
  while(s != "zzz")
  {
    s = incstring(s, 3);
    cout << s << endl;
  }
}

string incstring(string x, int mxsz)
{
  string s = x;
  if(mxsz == 0) return s;
  int i = 0;
  if(i >= s.size())
  {
    s+= "a";
    return s;
  }
  while(s[i] == 'z')
  {
    if(i+1 >= mxsz) { return s; }
    int j = 0;
    while(j <= i) 
    { 
      if(s[j] == 'z')
      {  s[j] = 'a';}
      j++;
    }
    if(i+1 >= s.size())
    {s+= "a"; return s;}
    
    i++;
  }
  s[i] += 1;
  return s;
}
