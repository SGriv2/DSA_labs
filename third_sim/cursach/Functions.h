#ifndef FUNCTIOM_H
#define FUNCTION_H

#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

struct Dataset {
	double X[4];
	int y;
};

void ReadData(Dataset* d, int n);
void randperm(Dataset* matrix, int size);

#endif 