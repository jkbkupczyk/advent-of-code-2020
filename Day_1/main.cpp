#include <iostream>
#include <fstream>

int populate(string filename){

    ifstream file;
    int num, next;

    file.open(filename);

    if(file.good()){

        while(file >> num){
            std::cout << num << std::endl;
        }

        file.close();
    }

    return 0;
}

int main()
{
    populate("input.txt");

    return 0;
}
