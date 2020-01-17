#include <hashlibpp.h>
#include <string>
#include <sstream>
#include <iostream>
//note: to compile:  g++ -Ihashlib2plus/trunk/src/ -std=c++11 hashlib2plus/trunk/src/hl_md5wrapper.cpp hashlib2plus/trunk/src/hl_md5.cpp test.cpp
std::string convertHash(std::string hash, int length);
std::string appInt(std::string pass, int length);

int main(int argc, char** argv) {
	
	std::string salt = "hfT7jp2q";

	std::string password = "zhgnnd"; //For testing hash, this will be replaced with a random password later	

	std::string altSum = password + salt + password;
	
	//TODO: Merge in password generator

	hashwrapper *myWrapper = new md5wrapper();
	
	myWrapper->test();
	altSum = myWrapper->getHashFromString(altSum);
	std::cout << altSum << std::endl;
		

	std::string interm0 = password + "$1$" + salt;
	interm0 += convertHash(myWrapper->getHashFromString(altSum), password.length());
	std::cout << interm0 << std::endl;
	interm0 += appInt(password, password.length());
	std::cout << interm0 << std::endl;
	delete myWrapper;

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
	return output;
}

std::string appInt(std::string pass, int length) {
	std::string output;
	while(length > 0) {
		if(length % 2) {
			output.push_back('\0');
		}
		else {
			output.push_back(pass.at(pass.length() - 1));
		}
		
		length = length >> 1;
	}
	return output;
}
