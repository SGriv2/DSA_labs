#include "Functions.h"

void ReadData(Dataset* d, int n) {
	string filename = "input.dat";
	ifstream reading(filename);

	d = new Dataset[n];
	if (reading) {
		for (int i = 0; i < n; i++) {
			reading >> d[i].y;

			for (int j = 0; j < 4; j++) {
				reading >> d[i].X[j];;
			}
		}
	}
	else {
		cout << "Не удалось открыть файл" << filename << endl;
	}
	reading.close();
}

void randperm(Dataset* matrix, int size) {
	random_shuffle(matrix, matrix + size);
}