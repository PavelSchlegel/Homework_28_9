#include <iostream>
#include <mutex>
#include "merge_sort.hpp"

typedef std::size_t max_i;

//код из юнита
void merge(max_i *arr, max_i L, max_i M, max_i R)
{
   max_i nl = M - L + 1;
   max_i nr = R - M;

   // создаем временные массивы
   max_i left[nl], right[nr];

   // копируем данные во временные массивы
   for (max_i i = 0; i < nl; i++)
       left[i] = arr[L + i];
   for (max_i j = 0; j < nr; j++)
       right[j] = arr[M + 1 + j];

   max_i i = 0, j = 0;
   max_i k = L;  // начало левой части

   while (i < nl && j < nr) {
       // записываем минимальные элементы обратно во входной массив
       if (left[i] <= right[j]) {
           arr[k] = left[i];
           i++;
       }
       else {
           arr[k] = right[j];
           j++;
       }
       k++;
   }
   // записываем оставшиеся элементы левой части
   while (i < nl) {
       arr[k] = left[i];
       i++;
       k++;
   }
   // записываем оставшиеся элементы правой части
   while (j < nr) {
       arr[k] = right[j];
       j++;
       k++;
   }
}

void mergeSort(max_i *arr, max_i L, max_i R)
{
    if (L >= R) {
        return; //выход из рекурсии
    }
    max_i M = (L + R - 1) / 2;
    mergeSort(arr, L, M);
    mergeSort(arr, M + 1, R);
    merge(arr, L, M, R);
}

void print(max_i* arr, max_i size)
{
    max_i str = 0;
    for (max_i i = 0; i < size; ++i) {
        std::cout << arr[i] << " ";
        ++str;
        if (str == 10) {
            std::cout << std::endl;
            str = 0;
        }
    }
}