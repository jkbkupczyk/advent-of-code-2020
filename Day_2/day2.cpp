#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct PassPolicy {
	int minChars;
	int maxChars;
	char letter;
	std::string pass;
};

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

int numberOfValid(std::vector<PassPolicy> vector) {

	int count = 0;

	for (int i = 0; i < vector.size(); i++) {
		if (validate(vector[i])) {
			count++;
		}
	}

	return count;
}

int main() {

	std::vector<PassPolicy> passwords = populateVector("input.txt");

	std::cout << "Valid passwords: " << numberOfValid(passwords) << std::endl;

	return 0;
}