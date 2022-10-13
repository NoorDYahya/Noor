#include "test_bus_lines.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int is_sorted_by_distance(BusLine *start, BusLine *end)
{

    while (start != end - 1)
    {
//        printf("%d\n",start->distance);

        if (start->distance > (start + 1)->distance)
        {
            return 0;
        }
        start++;

    }
    return 1;
}

int is_sorted_by_duration(BusLine *start, BusLine *end)
{
    while (start != end - 1)
    {
        if (start->duration > (start + 1)->duration)
        {
            return 0;
        }
        start++;

    }
    return 1;
}


int is_equal(BusLine *start_sorted,
             BusLine *end_sorted, BusLine *start_original,
             BusLine *end_original)
{

    int len = end_original - start_original;
    int score = 0;
    while (start_original != end_original)
    {
        while(start_sorted != end_sorted)
        {
            if (start_original->line_number == (start_sorted)->line_number)
            {
                score +=1;

            }
            start_sorted++;

        }
        start_original++;


    }
    if (score != len)
    {
        return 0;
    }
    return 1;
}

