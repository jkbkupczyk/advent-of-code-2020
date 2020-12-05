#include <iostream>
#include <fstream>
#include <vector>
#include <string>

// Passport requirements
struct PassReq {
	bool byr;
	bool iyr;
	bool eyr;
	bool hgt;
	bool hcl;
	bool ecl;
	bool pid;
};

// Map input to vector of strings
std::vector<std::string> populateVector(const std::string &fileName) {
	
	std::ifstream file;

	std::vector<std::string> data;
	std::string line;

	file.open(fileName);

	if (file.good()) {

		while (getline(file, line)) {
			data.push_back(line);
		}
	}

	return data;
}

// Check if passport have all required data
bool validatePassport(PassReq* o) {
	if (o->byr && o->iyr && o->eyr && o->hgt && o->hcl && o->ecl && o->pid){
		return true;
	}

	return false;
}

bool validateNumber(int date, int num1, int num2) {

	if (date >= num1 && date <= num2) {
		return true;
	}

	return false;
}

bool validateColor(std::string color) {

	std::vector<std::string> colors = { "amb", "blu", "brn", "gry", "grn", "hzl", "oth" };

	for (size_t i = 0; i < colors.size(); i++) {
		if (color.find(colors[i]) != std::string::npos) {
			return true;
		}
	}

	return false;
}

bool isHex(std::string str) {

	if (str.size() == 6 && str.find_first_not_of("0123456789abcdef") == std::string::npos) {
		return true;
	}

	return false;
}

bool isNumber(std::string str) {
	return str.find_first_not_of("0123456789") == std::string::npos;
}

// Count number of passports that meet specific criteria
int countValid(std::vector<std::string> data) {
	int count = 0;
	PassReq* req = new PassReq();

	for (size_t i = 0; i < data.size(); i++) {
		if (data[i] == "\0") {
			if (validatePassport(req)) {
				count++;
			}

			req->byr = 0;
			req->iyr = 0;
			req->eyr = 0;
			req->hgt = 0;
			req->hcl = 0;
			req->ecl = 0;
			req->pid = 0;
		}
		else {
			if (data[i].find("byr") != std::string::npos) {
				int byr = stoi(data[i].substr(data[i].find("byr") + 4, 4));

				if (validateNumber(byr, 1920, 2002)){
					req->byr = 1;
				}
			}

			if (data[i].find("iyr") != std::string::npos) {
				int iyr = stoi(data[i].substr(data[i].find("iyr") + 4, 4));

				if (validateNumber(iyr, 2010, 2020)) {
					req->iyr = 1;
				}
			}

			if (data[i].find("eyr") != std::string::npos) {
				int eyr = stoi(data[i].substr(data[i].find("eyr") + 4, 4));

				if (validateNumber(eyr, 2020, 2030)) {
					req->eyr = 1;
				}
			}

			if (data[i].find("hgt") != std::string::npos) {
				std::string hgt = data[i].substr(data[i].find("hgt") + 4, 5);

				// Split on spaces
				std::string splitted = hgt.substr(0, hgt.find(" "));

				if (hgt.find("cm") != std::string::npos) {
					if (validateNumber(stoi(hgt.substr(0 ,3)), 150, 193)) {
						req->hgt = 1;
					}
				} else if (hgt.find("in") != std::string::npos) {
					if (validateNumber(stoi(hgt.substr(0, 2)), 59, 76)) {
						req->hgt = 1;
					}
				}
			}

			if (data[i].find("hcl") != std::string::npos) {
				std::string hcl = data[i].substr(data[i].find("hcl") + 4, 7);

				std::string hex = hcl.substr(hcl.find("#") + 1, 7);

				// Split on spaces
				std::string splitted = hex.substr(0, hex.find(" "));

				if (isHex(splitted)) {
					req->hcl = 1;
				}
			}

			if (data[i].find("ecl") != std::string::npos) {
				std::string ecl = data[i].substr(data[i].find("ecl") + 4, 3);

				// Split on spaces
				std::string splitted = ecl.substr(0, ecl.find(" "));

				if (validateColor(ecl)) {
					req->ecl = 1;
				}
			}

			if (data[i].find("pid") != std::string::npos) {
				std::string pid = data[i].substr(data[i].find("pid") + 4, 9);

				// Split on spaces
				std::string splitted = pid.substr(0, pid.find(" "));

				if (splitted.size() == 9) {
					req->pid = 1;
				}

			}
		}
	}

	if (validatePassport(req)) {
		count++;
	}

	return count - 2;
}

int main() {

	std::vector<std::string> data = populateVector("input.txt");

	std::cout << "2. Number of valid passports: " << countValid(data) << std::endl;
}