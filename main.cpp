#include <iostream>
#include "merge_sort.hpp"

int main()
{
    std::size_t arr[] {2 ,4 ,9, 12, 8, 3, 6, 87, 91, 133, 64};
    mergeSort(arr, 0, sizeof(arr) / sizeof(arr[0]));
    arrPrint(arr, sizeof(arr) / sizeof(arr[0]));
    return 0;
}