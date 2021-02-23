//
// Created by FF on 2021/2/23.
//
#include <cstdlib>
#include "my_string.h"
#include "object.h"

String *newString(char *value) {
    auto *pString = static_cast<String *>(malloc(sizeof(String)));
    pString->retainCount = 0;// TODO 新增retainCount的初始化
    pString->value = value;
//    objectRetain(reinterpret_cast<Object *>(pString));
    OBJRETAIN(pString);// 这样不会校验，省略了强转
    return pString;
}

char *getStringValue(String *ins) {
    return ins->value;
}