#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "sort.h"
#include "team_generator.h"

bool goes_before(player x, player y){
    return x.id < y.id;
}

void swap(player a[], uint i, uint j) {
    player aux = a[i];
    a[i] = a[j];
    a[j] = aux;
}

bool array_is_sorted(player a[], uint length) {
    uint i = 1u;
    while (i < length && goes_before(a[i - 1u], a[i])) {
        i++;
    }
    return (i == length);
}

static uint partition(player a[], uint lft, uint rgt) {
	uint ppiv = lft;
	uint index_i = lft + 1;
	uint index_j = rgt;
	while (index_i <= index_j) {
		if (goes_before(a[index_i], a[ppiv])) {
			index_i++;
		} else if (goes_before(a[ppiv], a[index_j])) {
			index_j--;
		} else {
			swap(a, index_i, index_j);
			index_i++;
			index_j--;
		}
	}
	swap(a, ppiv, index_j);
	ppiv = index_j;
	return (ppiv);
}

static void quick_sort_rec(player a[], uint lft, uint rgt) {
    if (lft < rgt) {
        uint ppiv = partition(a, lft, rgt);
        quick_sort_rec(a, lft, (ppiv == 0u ? 0u : ppiv - 1));
        quick_sort_rec(a, ppiv + 1, rgt);
    }
}

void sort(player a[], uint length) {
    quick_sort_rec(a, 0, (length == 0) ? 0 : length - 1);
}

