#ifndef MERGE
#define MERGE
#include <iostream>
#include <future>

typedef std::size_t big_n;
typedef std::future<void> future;
void merge(big_n *arr, big_n L, big_n M, big_n R);
void mergeSort(big_n *arr, big_n L, big_n R);
void arrPrint(big_n *arr, big_n size);
#endif