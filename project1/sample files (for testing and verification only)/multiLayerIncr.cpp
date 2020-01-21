#include <iostream>
#include <string>

using namespace std;

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




int main() {
string pass = "aaaa";
while(pass != "zzzz") {
	for(int trunc = 0; trunc < 5; trunc++) {
		cout << pass.substr(0, trunc) << ' ';

	}
	cout << endl;
	pass = inc(pass);
}
return 0;

}
