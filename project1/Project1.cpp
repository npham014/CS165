#include "../hashlib2plus/trunk/src/hashlibpp.h"
#include <string>
#include <sstream>
#include <iostream>
//note: to compile:  g++ -I../hashlib2plus/trunk/src/ -std=c++11 ../hashlib2plus/trunk/src/hl_md5wrapper.cpp ../hashlib2plus/trunk/src/hl_md5.cpp Project1.cpp
std::string convertHash(std::string hash, int length);
std::string appInt(std::string pass, int length);


int main(int argc, char** argv) {
	std::string salt = "hfT7jp2q";

	std::string password = "zhgnnd"; //For testing hash, this will be replaced with a random password later	

	std::string altSum = password + salt + password;
	
	//TODO: Merge in password generator

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
	std::cout << "intermediate0 after hashing: " << myWrapper->getHashFromString(interm0) << std::endl << std::endl;
	std::string intermi, intermiprehash;
	/*for(unsigned int i = 0; i <= 999; i++) // intermediate1000 loop, incomplete
	{
		if(i%2) intermiprehash += password;
		else 
		{
			if(i == 0)
			
		}
	}*/
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
