//
// Created by FF on 2021/2/23.
//
#include <cstdlib>
#include "my_integer.h"
#include "object.h"

Integer *newInteger(int value) {
    auto *pInteger = static_cast<Integer *>(malloc(sizeof(Integer)));
    pInteger->retainCount = 0;// 新增retainCount的初始化，
    pInteger->value = value;
//    objectRetain(reinterpret_cast<Object *>(pInteger));
    OBJRETAIN(pInteger);// 这样不会校验，省略了强转
    return pInteger;
}

int getIntegerValue(Integer *ins) {
    return ins->value;
}