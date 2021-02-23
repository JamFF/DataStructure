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
static AnyObject *allocMemoryByCapacity(Array *arr) {
    return static_cast<AnyObject *>(malloc(sizeof(AnyObject) * arr->capacity));
}

// TODO 我增加的释放People的方法，是否有必要
static void destroyPeople(People *pPeople) {
    OBJRELEASE(pPeople->age);
    OBJRELEASE(pPeople->name);
    OBJRELEASE(pPeople);
}

Array *newArray() {
    auto *pArray = static_cast<Array *>(malloc(sizeof(Array)));
    pArray->length = 0;
    pArray->capacity = 32;// 初始设置为32
    pArray->value = allocMemoryByCapacity(pArray);// 二级指针
    return pArray;
}

// 增加元素
void addElement(Array *array, AnyObject value) {
    if (array->length >= array->capacity) {
        // 扩容
        array->capacity *= 2;
        AnyObject *oldValue = array->value;
        // TODO 参数1和参数2是同块内存地址吧？不会修改了capacity的值，value也跟着变动吧？
        memcpy(array->value, oldValue, array->length * sizeof(AnyObject));
        // TODO 释放也有问题，oldValue里面的name和age都是结构体也需要释放
        free(oldValue);
    }
    // TODO 我的扩容思路，如下，打开注释查看：
//    if (array->length >= array->capacity) {
//        // 扩容
//        array->capacity *= 2;
//        AnyObject *oldValue = array->value;
//        // 由于capacity翻倍了，重新开辟一块内存
//        array->value = allocMemoryByCapacity(array);
//        // 将老数据，拷贝到新的内存上
//        memcpy(array->value, oldValue, array->length * sizeof(AnyObject));
//        // 循环释放老的People内存（包括里面的name和age）
//        for (int i = 0; i < array->length; ++i) {
//            destroyPeople(reinterpret_cast<People *>(oldValue));
//        }
//        // 最后释放People的二级内存
//        free(oldValue);
//    }

    // TODO 在value创建时计数+1了，add时也要计数+1吗？
    OBJRETAIN(value);
    array->value[array->length] = value;
    array->length++;
}

// 删除元素
Array *removeIndexAt(Array *array, int index) {
    assert(index >= 0 && index < array->length);  // 断言，防止越界
    // TODO 这里释放不彻底吧，应该用我的destroyPeople方法
//    OBJRELEASE(getValueIndexAt(array, index));
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
        // 扩容
        array->capacity *= 2;
        AnyObject *oldValue = array->value;
        memcpy(array->value, oldValue, array->length * sizeof(AnyObject));
        free(oldValue);
    }
    // 将元素后移
    for (int i = array->length; i > index - 1; --i) {
        array->value[i] = array->value[i - 1];
    }
    // 插入指定位置
    array->value[index] = value;
    OBJRETAIN(value);
    array->length++;
}

// 获取某个元素
AnyObject getValueIndexAt(Array *array, int index) {
    assert(index >= 0 && index < array->length);
    return array->value[index];
}

// 获取数组元素个数
int getArrayLength(Array *array) {
    return array->length;
}

void destroyArray(Array *array) {
    // TODO 内部的name和age都是结构体还没被销毁，是不是需要for循环释放
    for (int i = 0; i < array->length; ++i) {
        destroyPeople(reinterpret_cast<People *>(array->value[i]));
    }
    free(array->value);
    free(array);
    cout << "数组被销毁" << endl;
}

void printArray(Array *array) {
    for (int i = 0; i < array->length; i++) {
        cout << "位置：" << i << "，";
        cout << "姓名：" << getStringValue(getName(reinterpret_cast<People *>(getValueIndexAt(array, i)))) << "，";
        cout << "年龄：" << getIntegerValue(getAge(reinterpret_cast<People *>( getValueIndexAt(array, i)))) << endl;
    }
}

int main() {
    Array *arr = newArray();

    cout << "初始化11个People" << endl;
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
    // TODO 设计思想是什么，添加的元素是People指针类型，Array中设计为Object的指针类型？
    // TODO 这种设计的前提是，机构体中第一个字段都是int，并且都为内存计数器吗？
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

    // TODO 为什么要释放内存？是因为newPeople和addElement时，计数器增为2，这里统一减1，保证后面回收吗？
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

    // TODO 为什么要释放内存？是因为newPeople和insertIndexAt时，计数器增为2，这里统一减1，保证后面回收吗？
    cout << "\n释放 p10" << endl;
    OBJRELEASE((Object *) p10);

    int index = 4;
    cout << "\n查找位置" << index << "处的元素";
    cout << "位置：" << index << "，";
    cout << "姓名：" << getStringValue(getName(reinterpret_cast<People *>( getValueIndexAt(arr, index)))) << "，";
    cout << "年龄：" << getIntegerValue(getAge(reinterpret_cast<People *>(getValueIndexAt(arr, index)))) << "\n" << endl;

    cout << "销毁数组" << endl;
    destroyArray(arr);
}