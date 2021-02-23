//
// Created by FF on 2021/2/23.
//

#ifndef DATASTRUCTURE_PEOPLE_H
#define DATASTRUCTURE_PEOPLE_H

#include "my_string.h"
#include "my_integer.h"

typedef struct People {
    int retainCount;
    String *name;
    Integer *age;
} People;

People *newPeople(String *name, Integer *age);

String *getName(People *people);

Integer *getAge(People *people);

#endif //DATASTRUCTURE_PEOPLE_H
