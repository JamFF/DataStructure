#include <iostream>
#include "print_utils.h"

using namespace std;

/**
 * 选择排序
 */
void selectionSort() {
    cout << "-------------选择排序-------------\n";// 使用换行代替endl提高效率
    int arr[10] = {2, 5, 8, 1, 3, 4, 7, 9, 0, 6};
    int length = sizeof(arr) / sizeof(arr[0]);
    cout << "排序前：";
    printArray(arr, length);
    int tmp, min_pos, compare_count = 0, change_count = 0;
    for (int i = 0; i < length - 1; ++i) {
        min_pos = i;
        for (int j = i + 1; j < length; ++j) {
            if (arr[j] < arr[min_pos]) {
                min_pos = j;// 记录最小值的位置
            }
            compare_count++;// 比较大小的次数
        }
        if (i != min_pos) {
            tmp = arr[i];
            arr[i] = arr[min_pos];
            arr[min_pos] = tmp;
            change_count++;// 交换位置的次数
        }
    }
    cout << "排序后：";
    printArray(arr, length);
    cout << "比较了" << compare_count << "次，";
    cout << "交换了" << change_count << "次" << endl;
}

/**
 * 冒泡排序
 */
void bubbleSort() {
    cout << "-------------冒泡排序-------------\n";
    int tmp, compare_count = 0, change_count = 0;
    int arr[10] = {2, 5, 8, 1, 3, 4, 7, 9, 0, 6};
    int length = sizeof(arr) / sizeof(arr[0]);
    cout << "排序前：";
    printArray(arr, length);
    for (int i = 0; i < length - 1; ++i) {
        for (int j = 0; j < length - 1 - i; ++j) {
            if (arr[j] > arr[j + 1]) {
                tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
                change_count++;// 交换位置的次数
            }
            compare_count++;// 比较大小的次数
        }
    }
    cout << "排序后：";
    printArray(arr, length);
    cout << "比较了" << compare_count << "次，";
    cout << "交换了" << change_count << "次" << endl;
}

int main() {
    selectionSort();
    bubbleSort();
    return 0;
}
