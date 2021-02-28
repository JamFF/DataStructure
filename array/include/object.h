//
// Created by FF on 2021/2/23.
//

#ifndef DATASTRUCTURE_OBJECT_H
#define DATASTRUCTURE_OBJECT_H

#include "my_integer.h"

// 定义Object结构体
typedef struct Object {
    // 内存计数器
    int retainCount;
} Object;

// 宏定义方法，宏函数，方便书写。这样也可以减少IDE进行指针的类型检查，可传入任意指针类型
#define OBJRETAIN(obj) objectRetain((Object*)obj)
#define OBJRELEASE(obj) objectRelease((Object*)obj)
#define GETRETAINCOUNT(obj) getRetainCount((Object*)obj)

void objectRetain(Object *obj);

void objectRelease(Object *obj);

int getRetainCount(Object *obj);

#endif //DATASTRUCTURE_OBJECT_H
