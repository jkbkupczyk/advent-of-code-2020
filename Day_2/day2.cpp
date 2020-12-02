#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// Struct that represent input
struct PassPolicy {
	int minChars;
	int maxChars;
	char letter;
	std::string pass;
};

// Mapping input to struct
std::vector<PassPolicy> populateVector(std::string fileName){

	std::ifstream file;

	std::vector<PassPolicy> data;
	int min, max;
	char letter, delimeters[] = { '-', ':' };
	std::string pass;

	file.open(fileName);

	if (file.good()) {
		while (file >> min >> delimeters[0] >> max >> letter >> delimeters[1] >> pass) {
			PassPolicy passPolicy;
			
			passPolicy.minChars = min;
			passPolicy.maxChars = max;
			passPolicy.letter = letter;
			passPolicy.pass = pass;

			data.push_back(passPolicy);
		}

		file.close();
	}

	return data;	
}

// Task 1
bool validate(PassPolicy passPolicy) {

	int count = 0;

	for (int i = 0; i < passPolicy.pass.size(); i++) {
		if (passPolicy.pass.at(i) == passPolicy.letter) {
			count++;
		}
	}

	if (count >= passPolicy.minChars && count <= passPolicy.maxChars) {
		return true;
	}

	return false;
}

// Task 2
bool validate2(PassPolicy passPolicy) {
	int min = passPolicy.minChars - 1,
		max = passPolicy.maxChars - 1;

	if ((passPolicy.pass.at(min) == passPolicy.letter || passPolicy.pass.at(max) == passPolicy.letter) 
		&& passPolicy.pass.at(min) != passPolicy.pass.at(max)) {
		return true;
	}

	return false;	
}

// Return number of passwords that met specific criteria
int numberOfValid(std::vector<PassPolicy> vector, bool(*validator)(PassPolicy)) {

	int count = 0;

	for (int i = 0; i < vector.size(); i++) {
		if (validator(vector[i])) {
			count++;
		}
	}

	return count;
}

int main() {

	std::vector<PassPolicy> passwords = populateVector("input.txt");

	std::cout << "1. Valid passwords (1st criteria): " << numberOfValid(passwords, validate) << std::endl;
	std::cout << "2. Valid passwords (2nd criteria): " << numberOfValid(passwords, validate2) << std::endl;

	return 0;
}