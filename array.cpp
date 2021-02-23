#include <iostream>
#include <memory.h>
#include "print_utils.h"

using namespace std;

typedef struct array {
    int size;// 数组元素数量
    int array[10];// 数组长度
} MyArray;

void insertElement(MyArray *myArray, int element, int index) {
    if (index < 0 || index > myArray->size) {
        cout << "超出数组实际元素范围" << endl;
        return;
    }
    for (int i = myArray->size; i > index - 1; --i) {
        myArray->array[i] = myArray->array[i - 1];
    }
    myArray->array[index] = element;
    myArray->size++;
    printArray(myArray->array, 10);
}

void deleteElement(MyArray *myArray, int index) {
    if (index < 0 || index >= myArray->size) {
        cout << "超出数组实际元素范围" << endl;
        return;
    }
    for (int i = index; i < myArray->size - 1; ++i) {
        myArray->array[i] = myArray->array[i + 1];
    }
    myArray->size--;
    myArray->array[myArray->size] = 0;
    printArray(myArray->array, 10);
}

int main() {
    auto *pMyArray = static_cast<MyArray *>(malloc(sizeof(MyArray)));/**/
    // 初始化结构体
    pMyArray->size = 0;
    memset(pMyArray->array, 0, sizeof(pMyArray->array));
    printArray(pMyArray->array, 10);

    insertElement(pMyArray, 3, 3);
    insertElement(pMyArray, 3, 0);
    insertElement(pMyArray, 7, 1);
    insertElement(pMyArray, 9, 2);
    insertElement(pMyArray, 5, 3);
    insertElement(pMyArray, 6, 1);

    deleteElement(pMyArray, 2);

    free(pMyArray);
    return 0;
}