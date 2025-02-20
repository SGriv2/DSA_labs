#include <iostream>
#include "Functions.h"
#include <chrono>
#include <clocale>

int main() {
    setlocale(LC_CTYPE, "rus");

    Dataset* dataset = new Dataset[0];
	int n = 150;
	ReadData(dataset, n);

    //cout << dataset[0].y << " " << dataset[0].X[0] << endl;

    srand(unsigned(time(NULL)));
    randperm(dataset, n);

    //cout << dataset[0].y << " " << dataset[0].X[0] << endl;

    int Nd = 150; //размер обучающей БД
    int INPUT_DIM = 4; // число входных сигналов
    int OUT_DIM = 3; // число выходных сигналов(второй слой)
    int H_DIM = 10; // число скрытых нейронов(первый слой)

    double** W1 = new double* [INPUT_DIM]; // массив весов между входом и первым слоем
    double* b1 = new double[H_DIM]; // смещение
    for (int i = 0; i < INPUT_DIM; i++) {
        W1[i] = new double[H_DIM]; // второе число число скрытых нейронов
    }

    double** W2 = new double*[H_DIM]; // слой соединияющий скрытый слой и выход
    double* b2 = new double[OUT_DIM]; // смещение
    for (int i = 0; i < H_DIM; i++) {
        W2[i] = new double[OUT_DIM];
    }

    int a = 0, b = 1;
    for(int i = 0; i < H_DIM; i++) {
        b1[i] = (double(rand()) * (b - a) / RAND_MAX + a);
        for(int j = 0; j < INPUT_DIM; j++) {
            W1[j][i] = (double(rand()) * (b - a) / RAND_MAX + a);
        }
    }

    cout << b1[0] << " " << b1[1] << " " << b1[2] << " " << endl;

    delete(W1);
    delete(W2);
    delete(b2);
    delete(b1);
    delete(dataset);


    return 0;
}