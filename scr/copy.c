#include "copy.h"

void copy(int * first_arr, int * second_arr, int size_other_arr, int start_index_first_arr, int start_index_second_arr)
{
    for (;start_index_second_arr < size_other_arr; start_index_second_arr++)
    {
        first_arr[start_index_first_arr] = second_arr[start_index_second_arr];
        ++start_index_first_arr;
    }
}
