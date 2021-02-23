//
// Created by FF on 2021/2/23.
//

#ifndef DATASTRUCTURE_MY_ARRAY_H
#define DATASTRUCTURE_MY_ARRAY_H

#include "object.h"

// 将Object*类型定义为简单的别名AnyObject
typedef Object *AnyObject;

typedef struct Array {
    int length;// 数组元素个数
    int capacity;// 数组容量
    AnyObject *value;// 二级指针
} Array;

Array *newArray();

// 增加数组元素
void addElement(Array *array, AnyObject value);

// 删除
Array *removeIndexAt(Array *array, int index);

// 插入
Array *insertIndexAt(Array *array, AnyObject value, int index);

// 查找
AnyObject getValueIndexAt(Array *array, int index);

// 获取数组长度
int getArrayLength(Array *array);

// 销毁
void destroyArray(Array *array);

// 打印
void printArray(Array *array);

#endif //DATASTRUCTURE_MY_ARRAY_H
