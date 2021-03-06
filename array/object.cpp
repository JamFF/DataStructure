//
// Created by FF on 2021/2/23.
//
#include <iostream>
#include "object.h"

using namespace std;

// 使用一次，计数+1
void objectRetain(Object *obj) {
    obj->retainCount++;
    cout << obj << "，retain计数+1 = " << obj->retainCount << endl;
}

// 释放一次，计数-1
void objectRelease(Object *obj) {
    if (obj == nullptr) {
        return;
    }
    obj->retainCount--;
    cout << obj << "，retain计数-1 = " << obj->retainCount << endl;
    if (obj->retainCount <= 0) {
        cout << obj << "，free obj" << endl;
        free(obj);
        obj = nullptr;
    }
}

int getRetainCount(Object *obj) {
    return obj->retainCount;
}