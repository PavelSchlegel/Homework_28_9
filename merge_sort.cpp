#include <iostream>
#include "merge_sort.hpp"

typedef std::size_t big_n;
typedef std::future<void> future;
void merge(big_n *arr, big_n L, big_n M, big_n R)
{
   big_n nl = M - L + 1;
   big_n nr = R - M;

   // создаем временные массивы
   big_n left[nl], right[nr];

   // копируем данные во временные массивы
   for (big_n i = 0; i < nl; i++)
       left[i] = arr[L + i];
   for (big_n j = 0; j < nr; j++)
       right[j] = arr[M + 1 + j];

   big_n i = 0, j = 0;
   big_n k = L;  // начало левой части

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

void mergeSort(big_n *arr, big_n L, big_n R)
{
    if (L >= R) {
        return; //выход из рекурсии
    }

    big_n M = (L + R - 1) / 2;
    future A = std::async(std::launch::async, mergeSort, arr, L, M);
    A.wait();
    // mergeSort(arr, L, M);
    future B = std::async(std::launch::async, mergeSort, arr, M + 1, R);
    B.wait();
    // mergeSort(arr, M + 1, R);
    future C = std::async(std::launch::async, merge, arr, L, M, R);
    C.wait();
    // merge(arr, L, M, R);
}

void arrPrint(big_n *arr, big_n size)
{
    for (big_n i = 0; i < size; ++i) {
        if (arr[i] > arr[i + 1]) {
            std::cout << "Array is unsorted!" << std::endl;
        }
        std::cout << arr[i] << " ";
    }
}