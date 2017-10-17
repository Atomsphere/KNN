#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;


struct Iris {
	double dimensions[4];
	int label;
	vector<double> similarity;
};


vector<Iris> initializeTest() {
	vector<Iris> vec;
	Iris temp;
	temp.dimensions[0] = 4.9;
	temp.dimensions[1] = 3.0;
	temp.dimensions[2] = 1.4;
	temp.dimensions[3] = .2;
	vec.push_back(temp);

	temp.dimensions[0] = 4.9;
	temp.dimensions[1] = 2.4;
	temp.dimensions[2] = 3.3;
	temp.dimensions[3] = 1.0;
	vec.push_back(temp);

	temp.dimensions[0] = 4.9;
	temp.dimensions[1] = 2.5;
	temp.dimensions[2] = 4.5;
	temp.dimensions[3] = 1.7;
	vec.push_back(temp);

	return vec;
}

//*******************************************
//print: test function-> prints the data vector
//after it has been filled
//*******************************************
void print(vector<Iris> vec) {
	for (int i = 0; i < vec.size(); ++i) {
		for (int j = 0; j < 4; ++j) {
			cout << vec[i].dimensions[j] << " ";
		}
		cout << vec[i].label << endl;
	}
}

//************************************
//normalization: Normalizes values so that they use feature scaling
//as described here https://en.wikipedia.org/wiki/Feature_scaling
//*********************************
vector<Iris> normalization(vector<Iris> vec) {
	for (int i = 0; i < vec.size(); ++i) {
		vec[i].dimensions[0] = (vec[i].dimensions[0] - 4.3) / 3.6;
		vec[i].dimensions[1] = (vec[i].dimensions[1] - 2) / 2.4;
		vec[i].dimensions[2] = (vec[i].dimensions[2] - 1) / 5.9;
		vec[i].dimensions[3] = (vec[i].dimensions[3] - .1) / 2.4;
	}
	return vec;
}

//
void similiarity(vector<Iris> vec, vector<Iris> test) {


}

int main() {

	vector<Iris> data;
	vector<Iris> nData;
	vector<Iris> test = initializeTest();
	vector<Iris> nTest = normalization(test);
	ifstream inFile;



	inFile.open("iris.txt");

	string line;
	//istringstream iss;
	size_t found;
	string::size_type sz;

	if (!inFile) {
		cout << "Unable to open file iris.txt";
		exit(1);
	}

	while (getline(inFile, line)) {
		Iris temp;
		found = 0;
		string temp1;
		string temp2;
		if (line.empty()) {
			break;
		}

		istringstream iss(line);
		
		for (int i = 0; i < 4; ++i) {

			getline(iss, temp1, ',');
			temp.dimensions[i] = stod(temp1);
		}
		getline(iss, temp2);
		if (temp2 == "Iris-setosa")
			temp.label = 1;
		else if (temp2 == "Iris-versicolor")
			temp.label = 2;
		else if (temp2 == "Iris-virginica")
			temp.label = 3;

		data.push_back(temp);
	}

	inFile.close();
	nData = normalization(data);
	print(data);
	print(nData);



	return 0;
}