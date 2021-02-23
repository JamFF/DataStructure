//
// Created by FF on 2021/2/23.
//

#ifndef DATASTRUCTURE_MY_STRING_H
#define DATASTRUCTURE_MY_STRING_H

// 将char* 字符串类型 封装成String
typedef struct String {
    int retainCount;
    char *value;
} String;

String *newString(char *value);

char *getStringValue(String *ins);

#endif //DATASTRUCTURE_MY_STRING_H
