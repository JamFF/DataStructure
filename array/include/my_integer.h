//
// Created by FF on 2021/2/23.
//

#ifndef DATASTRUCTURE_MY_INTEGER_H
#define DATASTRUCTURE_MY_INTEGER_H

// 将年龄的类型int封装成Integer
typedef struct Integer {
    int retainCount;
    int value;
} Integer;

Integer *newInteger(int value);

int getIntegerValue(Integer *ins);

#endif //DATASTRUCTURE_MY_INTEGER_H
