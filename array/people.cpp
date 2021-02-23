//
// Created by FF on 2021/2/23.
//
#include <cstdlib>
#include "people.h"
#include "object.h"

People *newPeople(String *name, Integer *age) {
    auto *pPeople = static_cast<People *>(malloc(sizeof(People)));
    pPeople->retainCount = 0;// TODO 新增retainCount的初始化
    pPeople->age = age;
    pPeople->name = name;
//    objectRetain(reinterpret_cast<Object *>(pPeople));
    OBJRETAIN(pPeople);// 这样不会校验，省略了强转
    return pPeople;
}

String *getName(People *people) {
    return people->name;
}

Integer *getAge(People *people) {
    return people->age;
}