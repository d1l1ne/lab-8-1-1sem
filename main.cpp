#include <iostream> 
#include <fstream>
#include <string>

using namespace std;

int posRows(const int(&array)[5][5], int rows, int columns);
void outArray(const int(&array)[5][5], int rows, int columns, string path);
string delSymbol(string str, char symbol);
string selPath();
const int nrows(5), ncolumns(5);

int main() {

	string out_path = selPath();
	int array[5][5];
	ofstream out(out_path);
	string inputed;

	if (out.is_open()) {

		for (int i = 0; i < nrows; i++) {
			for (int k = 0; k < ncolumns; k++) {

				cout << "Row " << i + 1 << " column " << k + 1 << ": ";
				cin >> inputed;
				cout << endl;

				if ((inputed.find('.') != inputed.npos) || (inputed.find(',') != inputed.npos)) {

					cout << "Value must be integer" << endl;
					k--;
					continue;

				}

				try {

					array[i][k] = stoi(inputed);

				}
				catch (exception) {

					cout << "Invalid value" << endl;
					k--;
					continue;

				}

			}
		}
		out.close();
		outArray(array, 5, 5, out_path);
		ofstream out(out_path, ios::app);
		cout << "Rows with unique numbers: " << posRows(array, 5, 5) << endl;
		out << "Rows with unique numbers: " << posRows(array, 5, 5) << endl;

	}
	else {

		cout << "Can't create output file" << endl;

	}
	

	system("pause");
	return 0;

}

int posRows(const int(&array)[5][5], int rows, int columns) {

	int* temparray = new int[columns];
	int result(0);
	bool state(true);

	for (int i = 0; i < rows; i++) {
		for (int k = 0; k < columns; k++) {

			temparray[k] = array[i][k];

			if (k == columns - 1) {

				for (int q = 0; q < columns; q++) {

					for (int j = 0; j < columns; j++) {

						if ((temparray[q] == temparray[j]) && (q != j)) {

							state = false;
							break;

						}
						if (!state)break;

					}

				}

			}
		}
		if (state) {

			result++;
		}
		else {
			state = true;
		}
	}

	return result;
}

void outArray(const int(&array)[5][5], int rows, int columns, string path) {

	ofstream out(path.c_str(), ios::app);
	for (int s = 0; s < rows; s++) {
		for (int d = 0; d < columns; d++) {

			cout << array[s][d] << " ";
			out << array[s][d] << " ";

		}
		cout << endl;
		out << endl;
	}
	out.close();

}
string delSymbol(string str, char symbol) {

	int length = str.length();
	string newstr;

	for (int k = 0; k < length; k++) {

		if (str[k] != symbol) {
			newstr.append(1, str[k]);
		}

	}

	return newstr;
}

string selPath() {

	string ipath;
	while (true) {

		cout << "Enter path to the file:" << endl;
		cin >> ipath;
		cout << endl;

		int n = ipath.length();
		for (int i = 0; i < n; i++) {

			if (ipath[i] == '\\') {
				ipath[i] = '/';
			}

		}
		ipath = delSymbol(ipath, '\"');
		ipath = delSymbol(ipath, ' ');


		int n1 = ipath.length();
		if (n1 < 4 || (ipath[n1 - 1] != 't' && ipath[n1 - 2] != 'x' && ipath[n1 - 3] != 't' && ipath[n1 - 4] != '.')) {
			cout << "File must be .txt" << endl;
		}
		else {
			break;
		}

	}


	return ipath;
}