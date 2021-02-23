//
// Created by FF on 2021/2/22.
//
#include <iostream>
#include "print_utils.h"

using namespace std;

void printArray(int *arr, int length) {
    for (int i = 0; i < length; ++i) {
        if (i == length - 1) {
            cout << arr[i] << endl;
        } else {
            cout << arr[i] << ",";
        }
    }
}