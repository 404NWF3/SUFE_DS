#include "uset.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#define INITSETSIZE 64

void newSet(uset** set);

void deleteSet(uset** set);

void addElem(int* elem, uset* set);

void remElem(int* elem, uset* set);

// display the number of elements and all the elements
void displaySet(uset* pset);

bool contains(int* elem, uset* pset);

int findPos(int* elem, uset* pset);

void newSet(uset** set) {
	*set = new uset;
	(*set)->elem = new int[INITSETSIZE];
	(*set)->card = 0;
}

void deleteSet(uset** set) {
	if (*set) {
		if ((*set)->elem != nullptr) {
			delete[](*set)->elem;
		}
		delete* set;
		*set = nullptr;
	}
}

int findPos(int* elem, uset* pset) {
	for (int i = 0; i < pset->card; i++) {
		if (pset->elem[i] == *elem) return i;
	}
	return -1;
}

bool contains(int* elem, uset* pset) {
	return findPos(elem, pset) != -1;
}

void addElem(int* elem, uset* set) {
	if (contains(elem, set)) return;

	if (set->card % INITSETSIZE == 0) {
		int newCapacity = set->card == 0 ? INITSETSIZE : set->card + 64;
		int* temp = new int[newCapacity];
		for (int i = 0; i < set->card; i++) {
			temp[i] = set->elem[i];
		}
		delete[]set->elem;
		set->elem = temp;
	}

	set->elem[set->card] = *elem;
	set->card++;
}

void remElem(int* elem, uset* set) {
	int pos = findPos(elem, set);
	if (pos != -1) {
		for (int i = pos; i < set->card - 1; i++) {
			set->elem[i] = set->elem[i + 1];
		}
		set->card--;
	}
	if ((set->card) % 64 == 0) {
		int* temp = new int[set->card];
		for (int i = 0; i < set->card; i++) {
			temp[i] = set->elem[i];
		}
		delete[]set->elem;
		set->elem = temp;
	}
}

void displaySet(uset* pset) {
	printf("{");
	if (pset->card != 0) {
		for (int i = 0; i < pset->card - 1; i++) {
			printf("%d, ", pset->elem[i]);
		}
		printf("%d", pset->elem[pset->card - 1]);
	}
	printf("}\n");
}
