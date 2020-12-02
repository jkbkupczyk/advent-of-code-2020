#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::vector<int> populateVector(std::string fileName) {

	std::ifstream file;

	std::vector<int> data;
	int temp;

	file.open(fileName);

	if (file.good()) {
		while (file >> temp) {
			data.push_back(temp);
		}

		file.close();
	}

	return data;
}

// Find the two entries that sum to 2020
int find2Entries(std::vector<int> data, int sum) {

	for (int i = 0; i < data.size(); i++) {
		for (int j = i + 1; j < data.size() - 1; j++) {
			if (data[i] + data[j] == sum) {
				return data[i] * data[j];
			}
		}
	}

	return 0;
}

// Find the three entries that sum to 2020
int find3Entries(std::vector<int> data, int sum) {

	for (int i = 0; i < data.size(); i++) {
		for (int j = i + 1; j < data.size(); j++) {
			for (int k = j + 1; k < data.size(); k++) {
				if (data[i] + data[j] + data[k] == sum) {
					return data[i] * data[j] * data[k];
				}
			}
		}
	}

	return 0;
}

int main()
{
	std::vector<int> entries = populateVector("input.txt");

	std::cout << "2 entries: " << find2Entries(entries, 2020) << std::endl;
	std::cout << "3 entries: " << find3Entries(entries, 2020) << std::endl;
	
	return 0;
}