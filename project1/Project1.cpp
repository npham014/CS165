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
		//if(intermi == ff202f2e9b6ac6e495570536fc89fd2a)
	}
	std::cout << "intermediate1000: " << intermi << std::endl;
	std::string s = "";
	unsigned char x[22] = {0};
	for(unsigned int i = 0; i < intermi.size(); i++)
	{
		unsigned char temp = intermi.at(i);
		x[i] = temp & 0x3f;
	}
	std::string base64 = "./0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	std::cout << base64.at(x[11]) << base64.at(x[4]) << base64.at(x[10]) << base64.at(x[5]) << base64.at(x[3]) << base64.at(x[9]) << base64.at(x[15]) << base64.at(x[2]) << base64.at(x[8]) << base64.at(x[14]) << base64.at(x[1]) << base64.at(x[7]) << base64.at(x[13]) << base64.at(x[0]) << base64.at(x[6]) << base64.at(x[12]) << std::endl;
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
