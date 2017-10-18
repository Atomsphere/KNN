#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <math.h>
using namespace std;


struct Iris {
	double dim[4];
	int label;
	vector<double> sim;
};


vector<Iris> initializeTest() {
	vector<Iris> vec;
	Iris temp;
	temp.dim[0] = 4.9;
	temp.dim[1] = 3.0;
	temp.dim[2] = 1.4;
	temp.dim[3] = .2;
	vec.push_back(temp);

	temp.dim[0] = 4.9;
	temp.dim[1] = 2.4;
	temp.dim[2] = 3.3;
	temp.dim[3] = 1.0;
	vec.push_back(temp);

	temp.dim[0] = 4.9;
	temp.dim[1] = 2.5;
	temp.dim[2] = 4.5;
	temp.dim[3] = 1.7;
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
			cout << vec[i].dim[j] << " ";
		}
		cout << vec[i].label << endl;
	}
}

string name(int lab) {
	switch (lab) {
	case 1:
		return "Iris-setosa";
	case 2:
		return "Iris-versicolor";
	default:
		return "Iris-virginica";
	}
}

void printResults(vector<Iris> vec, int mapping[5], Iris test, int count) {
	int total1 = 0;
	int total2 = 0;
	int total3 = 0;
	if(count == 1)
		cout << "For " << count << " neighbor using test data: ";
	else
		cout << "For " << count << " neighbors using test data: ";
	for (int i = 0; i < 4; ++i) {
		cout << test.dim[i];
		if (i != 3)
			cout << ", ";
	}
	cout << endl;

	if (count == 1) {
		cout << "closest neighbor:\n";
		for (int i = 0; i < 4; ++i) {
			cout << mapping[0];
			cout << vec[mapping[0]].dim[i] << ", ";
		}
		cout << name(vec[mapping[0]].label) << endl;
		cout << "Prediction: "
			<< name(vec[mapping[0]].label);
	}
	else {
		cout << "closest neighbors:\n";
		for (int j = 0; j < count; ++j) {
			for (int i = 0; i < 4; ++i) {
				cout << vec[mapping[j]].dim[i] << ", ";
			}
			cout << name(vec[mapping[j]].label) << endl;
			if (vec[mapping[j]].label == 1)
				total1++;
			else if (vec[mapping[j]].label == 2)
				total2++;
			else if (vec[mapping[j]].label == 3)
				total3++;
		}
		cout << "Prediction: ";
		if (total1 >= total2 && total1 >= total3)
			cout << name(1);
		else if (total2 >= total1 && total2 >= total3)
			cout << name(2);
		else
			cout << name(3);
	}

}




//************************************
//normalization: Normalizes values so that they use feature scaling
//as described here https://en.wikipedia.org/wiki/Feature_scaling
//*********************************
vector<Iris> normalization(vector<Iris> vec) {
	for (int i = 0; i < vec.size(); ++i) {
		vec[i].dim[0] = (vec[i].dim[0] - 4.3) / 3.6;
		vec[i].dim[1] = (vec[i].dim[1] - 2) / 2.4;
		vec[i].dim[2] = (vec[i].dim[2] - 1) / 5.9;
		vec[i].dim[3] = (vec[i].dim[3] - .1) / 2.4;
	}
	return vec;
}

//
void similiarity(vector<Iris> &vec, vector<Iris> test) {
	double temp;
	for (int i = 0; i < vec.size(); ++i) {
		for (int j = 0; j < test.size(); ++j) {
			temp = 0;
			for (int k = 0; k < 4; ++k) {
				temp += pow(vec[i].dim[k] - test[j].dim[k], 2);
			}
			vec[i].sim.push_back(sqrt(temp));
		}
	}
}

void nearest(vector<Iris> vec, int near[5], int index) {
	double temp;
	bool flag;

	for (int i = 0; i < 5; ++i) {
		temp = DBL_MAX;
		for (int j = 0; j < vec.size(); ++j) {
			flag = true;
			for (int k = 0; k < 5; ++k) {
				if (near[k] == j)
					flag = false;
			}
			if (flag) {
				if (vec[j].sim[index] < temp) {
					temp = vec[j].sim[index];
					near[i] = j;
				}
			}
		}
	}
}

int main() {

	vector<Iris> data;
	vector<Iris> nData;
	vector<Iris> test = initializeTest();
	vector<Iris> nTest = normalization(test);
	ifstream inFile;
	int near1[5];
	int near2[5];
	int near3[5];

	fill_n(near1, 5, -1);
	fill_n(near2, 5, -1);
	fill_n(near3, 5, -1);


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
			temp.dim[i] = stod(temp1);
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
	similiarity(nData, nTest);
	
	nearest(nData, near1, 0);
	nearest(nData, near2, 1);
	nearest(nData, near3, 2);
	
	printResults(data, near1, test[0], 1);
	cout << endl << endl;
	printResults(data, near2, test[1], 1);
	cout << endl << endl;
	printResults(data, near3, test[2], 1);
	cout << endl << endl;
	
	printResults(data, near1, test[0], 3);
	cout << endl << endl;
	printResults(data, near2, test[1], 3);
	cout << endl << endl;
	printResults(data, near3, test[2], 3);
	cout << endl << endl;

	printResults(data, near1, test[0], 5);
	cout << endl << endl;
	printResults(data, near2, test[1], 5);
	cout << endl << endl;
	printResults(data, near3, test[2], 5);
	cout << endl << endl;
	
	//print(data);
	//print(nData);



	return 0;
}