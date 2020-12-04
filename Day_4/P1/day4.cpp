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
	bool cid; // CID is not required in validation
};

// Map input to vector of strings
std::vector<std::string> populateVector(std::string fileName) {
	
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
bool validate(PassReq* o) {
	if (o->byr && o->iyr && o->eyr && o->hgt && o->hcl && o->ecl && o->pid){
		return true;
	}

	return false;
}

// Count number of passports that meet specific criteria
int countValid(std::vector<std::string> data) {
	int count = 0;
	PassReq* req = new PassReq();

	for (int i = 0; i < data.size(); i++) {
		if (data[i] == "\0") {
			if (validate(req)) {
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
			if (data[i].find("byr") != std::string::npos) req->byr = 1;
			if (data[i].find("iyr") != std::string::npos) req->iyr = 1;
			if (data[i].find("eyr") != std::string::npos) req->eyr = 1;
			if (data[i].find("hgt") != std::string::npos) req->hgt = 1;
			if (data[i].find("hcl") != std::string::npos) req->hcl = 1;
			if (data[i].find("ecl") != std::string::npos) req->ecl = 1;
			if (data[i].find("pid") != std::string::npos) req->pid = 1;
		}
	}

	if (validate(req)) {
		count++;
	}

	return count;
}

int main() {

	std::vector<std::string> data = populateVector("input.txt");

	std::cout << "1. Number of valid: " << countValid(data) << std::endl;
}