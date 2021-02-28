//
// Created by FF on 2021/2/23.
//

#include <iostream>
#include <cstdlib>
#include <cassert>
#include "my_array.h"
#include "object.h"
#include "people.h"

using namespace std;

// 分配capacity个AnyObject指针大小的内存
static AnyObject *allocMemoryByCapacity(int capacity) {
    return static_cast<AnyObject *>(malloc(capacity * sizeof(AnyObject)));
}

// 释放People
static void destroyPeople(People *pPeople) {
    if (pPeople == nullptr) {
        return;
    }
    OBJRELEASE(pPeople->age);
    OBJRELEASE(pPeople->name);
    OBJRELEASE(pPeople);
}

/**
 * 数组扩容
 * @param array
 */
static void expandArray(Array *array) {
    // 容量翻倍
    array->capacity *= 2;
    cout << "需要扩容 capacity = " << array->capacity << endl;
    AnyObject *oldValue = array->value;
    // 由于capacity增加，重新开辟一块大内存
    array->value = allocMemoryByCapacity(array->capacity);
    // 将老数据，拷贝到新的内存上
    memcpy(array->value, oldValue, array->length * sizeof(AnyObject));
    // 循环释放老的People内存（包括里面的name和age）
    for (int i = 0; i < array->length; ++i) {
        auto *pPeople = reinterpret_cast<People *>(oldValue);
        // 这里直接free，不要用OBJRELEASE，因为retainCount已经copy到新的内存上，这里操作retainCount没有意义
        if (pPeople != nullptr) {
            if (pPeople->name != nullptr) {
                free(pPeople->name);
                pPeople->name = nullptr;
            }
            if (pPeople->age != nullptr) {
                free(pPeople->age);
                pPeople->age = nullptr;
            }
            free(pPeople);
            pPeople = nullptr;
        }
    }
    // 最后释放People的二级指针
    free(oldValue);
    oldValue = nullptr;
}

// 初始化数组
Array *newArray() {
    auto *pArray = static_cast<Array *>(malloc(sizeof(Array)));
    pArray->length = 0;
    pArray->capacity = 32;// 初始设置为32
    pArray->value = allocMemoryByCapacity(pArray->capacity);// 二级指针
    return pArray;
}

// 增加元素
void addElement(Array *array, AnyObject value) {
    if (array->length >= array->capacity) {
        expandArray(array);
    }

    // 在value创建时计数+1了，这里增加也模拟计数+1
    OBJRETAIN(value);
    array->value[array->length] = value;
    array->length++;
}

// 删除元素
Array *removeIndexAt(Array *array, int index) {
    assert(index >= 0 && index < array->length);  // 断言，防止越界
    destroyPeople(reinterpret_cast<People *>(getValueIndexAt(array, index)));
    for (int i = index; i < array->length - 1; ++i) {
        array->value[i] = array->value[i + 1];
    }
    array->length--;
    return array;
}

// 在指定位置增加元素
Array *insertIndexAt(Array *array, AnyObject value, int index) {
    if (array->length >= array->capacity) {
        expandArray(array);
    }
    // 将元素后移
    for (int i = array->length; i > index - 1; --i) {
        array->value[i] = array->value[i - 1];
    }
    // 插入指定位置
    array->value[index] = value;
    // 在value创建时计数+1了，这里增加也模拟计数+1
    OBJRETAIN(value);
    array->length++;
    return array;
}

// 获取某个位置的元素
AnyObject getValueIndexAt(Array *array, int index) {
    assert(index >= 0 && index < array->length);
    return array->value[index];
}

// 获取数组元素个数
int getArrayLength(Array *array) {
    return array->length;
}

// 释放数组内存
void destroyArray(Array *array) {
    // 内部的name和age都是结构体还没被销毁，需要for循环释放
    for (int i = 0; i < array->length; ++i) {
        destroyPeople(reinterpret_cast<People *>(array->value[i]));
    }
    free(array->value);
    array->value = nullptr;
    free(array);
    array = nullptr;
    cout << "数组已销毁释放" << endl;
}

// 打印Array内容
void printArray(Array *array) {
    for (int i = 0; i < array->length; i++) {
        cout << "位置：" << i << "，";
        cout << "姓名：" << getStringValue(getName(reinterpret_cast<People *>(getValueIndexAt(array, i)))) << "，";
        cout << "年龄：" << getIntegerValue(getAge(reinterpret_cast<People *>( getValueIndexAt(array, i)))) << endl;
    }
}

int main() {
    Array *arr = newArray();

    cout << "初始化10个People" << endl;
    People *p0 = newPeople(newString("A"), newInteger(20));
    People *p1 = newPeople(newString("B"), newInteger(16));
    People *p2 = newPeople(newString("C"), newInteger(17));
    People *p3 = newPeople(newString("D"), newInteger(14));
    People *p4 = newPeople(newString("E"), newInteger(22));
    People *p5 = newPeople(newString("F"), newInteger(18));
    People *p6 = newPeople(newString("G"), newInteger(25));
    People *p7 = newPeople(newString("H"), newInteger(11));
    People *p8 = newPeople(newString("I"), newInteger(19));
    People *p9 = newPeople(newString("J"), newInteger(22));

    cout << "\n增加10个People元素" << endl;
    // 设计思想类似于继承，Array中设计为Object指针类型，添加的是People指针类型，都是指针类型，占用同样大小内存
    // 这种设计的前提是，结构体中都有相同字段，retainCount，所以可以强转后取出进行操作，而不出现问题
    addElement(arr, (Object *) p0);
    addElement(arr, (Object *) p1);
    addElement(arr, (Object *) p2);
    addElement(arr, (Object *) p3);
    addElement(arr, (Object *) p4);
    addElement(arr, (Object *) p5);
    addElement(arr, (Object *) p6);
    addElement(arr, (Object *) p7);
    addElement(arr, (Object *) p8);
    addElement(arr, (Object *) p9);

    // 释放内存，newPeople和addElement，操作两次，计数器增为2，这里模拟释放1次，保证后面回收
    cout << "\n释放 p0-p9" << endl;
    OBJRELEASE(p0);
    OBJRELEASE(p1);
    OBJRELEASE(p2);
    OBJRELEASE(p3);
    OBJRELEASE(p4);
    OBJRELEASE(p5);
    OBJRELEASE(p6);
    OBJRELEASE(p7);
    OBJRELEASE(p8);
    OBJRELEASE(p9);

    cout << "\n查看数组全部元素" << endl;
    printArray(arr);

    // 删除第数组中元素
    cout << "\n删除位置2处的元素" << endl;
    removeIndexAt(arr, 2);
    printArray(arr);

    cout << "\n在位置4处插入新元素" << endl;
    People *p10 = newPeople(newString("NEW"), newInteger(23));
    insertIndexAt(arr, (Object *) p10, 4);
    printArray(arr);

    // 释放内存，newPeople和addElement，操作两次，计数器增为2，这里模拟释放1次，保证后面回收
    cout << "\n释放 p10" << endl;
    OBJRELEASE((Object *) p10);

    int index = 4;
    cout << "\n查找位置" << index << "处的元素，";
    cout << "位置：" << index << "，";
    cout << "姓名：" << getStringValue(getName(reinterpret_cast<People *>( getValueIndexAt(arr, index)))) << "，";
    cout << "年龄：" << getIntegerValue(getAge(reinterpret_cast<People *>(getValueIndexAt(arr, index)))) << "\n" << endl;

    cout << "销毁数组" << endl;
    destroyArray(arr);
}