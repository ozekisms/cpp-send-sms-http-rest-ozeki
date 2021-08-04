#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>

using namespace std;

class uuidGenerator {
public:
	string uuid(void) {
		vector<char> numbers = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
		vector<char> characters = { 'a','b','c','d','e','f', 'g','h','i','j','k',
			'l','m','n','o','p', 'q','r','s','t','u','v','w','x','y','z' };
		vector<char> uuid = { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
		' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 
		' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 
		' ', ' ', ' ', ' ', ' ', ' ',};
		for (int i = 0; i < 36; i++) {
			int random = (rand() % 4);
			if (random == 1) {
				int randomNumber = rand() % numbers.size();
				uuid[i] = numbers[randomNumber];
			}
			else {
				int randomCharacter = rand() % characters.size();
				uuid[i] = characters[randomCharacter];
			}
		}
		uuid[8] = '-';
		uuid[13] = '-';
		uuid[18] = '-';
		uuid[23] = '-';
		string uuid_string = "";
		for (int i = 0; i < 36; i++) {
			uuid_string += uuid[i];
		}
		return uuid_string;
	}
};