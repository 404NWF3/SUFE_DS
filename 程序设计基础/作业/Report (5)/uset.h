#pragma once
// 集合库头文件
#ifndef USET_H
#include "uset.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#define USET_H
#define INITSETSIZE 64

struct uset {
	int* elem;
	int card;
};

void newSet(uset** set);

void deleteSet(uset** set);

void addElem(int* elem, uset* set);

void remElem(int* elem, uset* set);

// display the number of elements and all the elements
void displaySet(uset* pset);

bool contains(int* elem, uset* pset);

int findPos(int* elem, uset* pset);
#endif
