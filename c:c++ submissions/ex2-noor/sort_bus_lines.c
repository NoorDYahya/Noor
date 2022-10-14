#include "sort_bus_lines.h"
#include "stdlib.h"
#include "stdio.h"


void swap(BusLine *xp, BusLine *yp)
{
    BusLine temp = *yp;
    *yp = *xp;
    *xp = temp;
}

BusLine *partition(BusLine *start, BusLine *end)
{

    int pivot = (end)->duration; // pivot
    int len = end - start;
    int i = -1;
    for (int j = 0; j < len; j++)
    {
        // If current element is smaller than the pivot
        if ((start + j)->duration <= pivot)
        {
            i++; // increment index of smaller element
            swap(start + i, start + j);
        }
    }
    swap(start + i + 1, end);
    return start + i + 1;
}

void quick_sort(BusLine *start, BusLine *end)
{

    if (start < end - 1)
    {
        /* pi is partitioning index, arr[p] is now
        at right place */
        BusLine *pi = partition(start, end - 1);

        // Separately sort elements before
        // partition and after partition
        quick_sort(start, pi - 1);
        quick_sort(pi, end - 1);
    }
}

void bubble_sort(BusLine *start, BusLine *end)
{

    int n = end - start;
    for (int i = 0; i < n; i++)
    {

        // Last i elements are already in place
        for (int j = i + 1; j < n; j++)
        {
            if (((start + j)->distance) < (start + i)->distance)
            {
                swap(start + j, start + i);
            }
        }
    }
}

