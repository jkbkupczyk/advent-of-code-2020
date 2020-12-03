#include <iostream>
#include <fstream>
#include <vector>
#include <string>

// Mapping input into vector of strings
std::vector<std::string> populateVector(std::string fileName) {

	std::ifstream file;

	std::vector<std::string> data;
	std::string line;

	file.open(fileName);

	if (file.good()) {
		while (file >> line) {
			data.push_back(line);
		}

		file.close();
	}

	return data;
}

//
int countTrees(std::vector<std::string> data, int stepX, int stepY) {
	int count = 0, x = 0;

	for (int y = 0; y < data.size(); y += stepY) {
		if (x >= data[y].length()) {
			x -= data[y].length();
		}

		if (data[y].at(x) == '#') {
			count++;
		}

		x += stepX;
	}

	return count;
}

// Number of trees encountered on each slope
uint32_t encounteredTrees(std::vector<std::string> data) {
	return countTrees(data, 1, 1)
		*countTrees(data, 3, 1)
		*countTrees(data, 5, 1)
		*countTrees(data, 7, 1)
		*countTrees(data, 1, 2);
}

int main() {

	std::vector<std::string> data = populateVector("input.txt");

	std::cout << "1. Count trees: " << countTrees(data, 3, 1) << std::endl;
	std::cout << "2. Count trees in diff slopes: " << encounteredTrees(data) << std::endl;

	return 0;
}