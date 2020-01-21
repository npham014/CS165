#include "../hashlib2plus/trunk/src/hashlibpp.h"
#include <string>
#include <sstream>
#include <iostream>
//note: to compile:  g++ -I../hashlib2plus/trunk/src/ -std=c++11 ../hashlib2plus/trunk/src/hl_md5wrapper.cpp ../hashlib2plus/trunk/src/hl_md5.cpp Project1.cpp
std::string convertHash(std::string hash, int length);
std::string appInt(std::string pass, int length);
std::string print64(std::string base, unsigned char inc[], int incsize);
std::string inc(std::string s);

std::string gpassword = "aaaaaa";
std::string salt = "hfT7jp2q";
std::string hashTarget = "wPwz7GC6xLt9eQZ9eJkaq";
bool cracked = false;
int main(int argc, char** argv) {

while(gpassword != "zzzzzz" && !cracked) {
	for(int trunc = 1; trunc < 7; trunc++) {

		std::string altSum = password + salt + password;
	
		std::string password = gpassword.substr(0, trunc);		

		hashwrapper *myWrapper = new md5wrapper();
	
		myWrapper->test();
		std::cout << "altsum before hashing: " << altSum << std::endl;
		altSum = myWrapper->getHashFromString(altSum);
		std::cout << "altsum after hashing: ";
		std::cout << altSum << std::endl;
		

		std::string interm0 = password + "$1$" + salt;
		interm0 += convertHash((altSum), password.length());
		std::cout << interm0 << std::endl;
		interm0 += appInt(password, password.length());
		std::cout << "intermediate0 before hashing: " <<  interm0 << std::endl;
		interm0 = myWrapper->getHashFromString(interm0);
		std::cout << "intermediate0 after hashing: " << interm0 << std::endl << std::endl;
		std::string intermi;
		intermi = interm0;
		for(unsigned long int i = 0; i <= 999; i++) // intermediate1000 loop, incomplete
		{	unsigned long int j = i;
			std::string intermiprehash;
			intermi = convertHash(intermi, 16);
			intermiprehash += (j%2) == 0 ? intermi : password;
			if((j%3) > 0) intermiprehash += salt;
			if((j%7) > 0) intermiprehash += password;
			intermiprehash += (j%2) == 0 ? password : intermi;
			intermi = myWrapper->getHashFromString(intermiprehash);
		}
		std::cout << "intermediate1000: " << intermi << std::endl;
		std::string s = convertHash(intermi, 16);
		std::cout << "s: " << s << "\ns size: " << s.size() <<  std::endl;

		std::string y; y += s.at(11);y += s.at(4); y+= s.at(10); y+= s.at(5);
		y += s.at(3); y+= s.at(9); y+= s.at(15); y+= s.at(2); y+= s.at(8); y+= s.at(14); y+= s.at(1); y+= s.at(7); y+= s.at(13); y+= s.at(0); y+= s.at(6); y+= s.at(12);
		unsigned char x[22];
		unsigned char j = 0;
		//x[j++] = y.at(y.size()-1) & 0x3f;
       		for(unsigned char i = 15; i > 0; i--)
	        {
			x[j] = (y.at(i) & 0x3f); j++;
	                x[j] = ((y.at(i)&0xc0) >> 6) + ((y.at(i-1) & 0x0f) << 2); j++;
			i--;
			x[j] = ((y.at(i)&0xf0) >> 4) + ((y.at(i-1) & 0x03) << 4); j++;
			i--;
			x[j] = ((y.at(i)&0xfc) >> 2);j++;
	        }
		x[20] = (y.at(0) & 0x3f);
		x[21] = (y.at(0)>>6);
	

		std::string base64 = "./0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
		std::cout << "base64 size: " << base64.size() << std::endl;
		std::cout << "last 6 bits: " << base64.at((char)(s.at(s.size()-1 ) >> 2 )) << "\nfirst six bits: " << base64.at((char)(s.at(0) & 0x3f)) << std::endl;
		std::cout << "first 3 characters: " << (int)(x[0]) << " " << (int)(x[1]) << " " << (int)(x[2]) << std::endl;
		std::cout << base64.at(x[0]) << base64.at(x[1]) << base64.at(x[2]) << std::endl;
		std::cout << "final string: ";
		for(unsigned char i = 0; i < 22; i++)
		{
			std::cout << base64.at(x[i]);
		}
		std::cout << std::endl;
		std::cout << base64.at(x[21]) <<  std::endl;
		delete myWrapper;
	}// end for
password = inc(gpassword);
}// end while
	return 0;
}

std::string convertHash(std::string hash, int length) {
	unsigned int x;
	std::string temp;
	for(int i = 0; i < 32; i+=2 ) {
		x = std::stoul(hash.substr(i,2), nullptr, 16);
		std::cout << x << std::endl;
		temp.push_back(static_cast<char>(x));
	}
	std::string output;
	for(int j = 0; j < length; j++) {
		output.push_back(temp.at(j));
	}
	std::cout << "convHash output: " << output << std::endl;
	return output;
}

std::string appInt(std::string pass, int length) {
	std::string output;
	std::string temp = pass;
	while((length > 0)) {
		if(length % 2) {
			output+='\0';
		}
		else {
			output+= pass.at(0);
		}
		
		length = length >> 1;
	}
	/*for(int i = 0; i < length; i+=2)
	{
		output.push_back(std::stoul(temp.substr(i,2), nullptr, 16));
	}*/
	std::cout << "appInt output: " << output << std::endl;
	return output;
}
std::string print64(std::string base, unsigned char inc[], int incsize)
{
  for(unsigned char i = 0; i < incsize; i++)
  {	if(inc[i] > 63) std::cout << "\n" << (int)inc[i] << std::endl;
	else  std::cout << base.at(inc[i]);
  }
}

std::string inc(std::string s)
{ std::string b = s;
  if(b[0] == 'z')
  {
    b[0] = 'a';
    if(b[1] == 'z')
    {
      b[1] = 'a';
      if(b[2] == 'z')
      {
	b[2] = 'a';
	if(b[3] == 'z') {
		b[3] = 'a';
		if(b[4] == 'z') {
			b[4] == 'a';
			b[5] += 1;
		}
		else b[4] += 1;
	}
	else b[3] += 1;
      }
      else b[2] += 1;
    }
    else b[1] += 1;
  }
  else
    b[0] += 1;
  return b;
}

	/*unsigned char x[22];
	x[0] = s.at(0) & 0x3f;
	//x[0] = x << 6;
	unsigned char j = 1;
     	for(unsigned int i = 0; i < 16; i++)
	{
		x[j] += (s.at(i) >> 6) + (s.at(i+1) << 2);
  	     	//x[j] = x << 6;
	}*/

	/*unsigned char x[16];
	for(unsigned char i = 0; i < 16; i++)
	{
		x[i] = (s.at(i)) & 0x3f;
	}*/
	/*unsigned long int x = s.at(s.size()-1) & 0x3f;
	x << 6;
	for(unsigned char i = 15; i >0; i--)
	{
		
	}*/
