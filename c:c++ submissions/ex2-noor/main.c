#include "sort_bus_lines.h"
#include "test_bus_lines.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define ONE 1
#define TWO 2
#define MAX_NUM_OF_LINES 60
#define MAX_NUM_LINE 999
#define MAX_DIST 1000
#define MAX_DURATION 100
#define MIN_DURATION 10


int input_correctness(int line, int distance, int duration)
{

    if (line < 1 || line > MAX_NUM_LINE)
    {
        printf("ERROR: line should be an integer between 1 and 999\n");
        return 0;
    }
    if (distance < 0 || distance > MAX_DIST)
    {
        printf("ERROR: distance should be an integer between 0 and 1000\n");
        return 0;
    }
    if (duration < MIN_DURATION || duration > MAX_DURATION)
    {
        printf("ERROR: duration should be an integer between 10 and 100\n");
        return 0;
    }
    return 1;
}


int cli_correctness(int argc, char *argv[])
{
    if (argc != TWO)
    {
        printf("USAGE: number of argument is not correct\n");
        return 1;
    }
    if (strcmp(argv[ONE], "bubble") != 0 && strcmp(argv[ONE], "test") != 0 &&
        strcmp
                (argv[ONE], "quick") != 0)
    {
        printf("USAGE: the given operating mode is not available \n");
        return 1;
    }
    return 0;
}

int get_num_lines()
{
    int num_of_lines;
    char buff[MAX_NUM_OF_LINES];
    printf("Enter number of lines. Then enter\n");

    if (fgets(buff, MAX_NUM_OF_LINES, stdin) != NULL)
    {
        if (sscanf(buff, "%d", &num_of_lines) != EOF)
        {
            while (num_of_lines <= 0)
            {
                printf("ERROR: number of line should be positive\n");
                printf("Enter number of lines. Then enter\n");
                fgets(buff, MAX_NUM_OF_LINES, stdin);
                sscanf(buff, "%d", &num_of_lines);
            }
            return num_of_lines;
        }
        return 0;
    }
    return 0;
}

int store_lines_data(BusLine *bus_arr, int num_of_lines)
{

    int i = 0;
    while (i < num_of_lines)
    {

        char buff[MAX_NUM_OF_LINES];
        int line, distance, duration;
        printf("Enter line info. Then enter\n");
        if (fgets(buff, MAX_NUM_OF_LINES, stdin) != NULL)
        {
            if (sscanf(buff, "%d,%d,%d", &line, &distance, &duration) != EOF)
            {
                while (input_correctness(line, distance, duration) == 0)
                {
                    printf("Enter line info. Then enter\n");
                    if (fgets(buff, MAX_NUM_OF_LINES, stdin) != NULL)
                    {
                        if (sscanf(buff, "%d,%d,%d", &line, &distance,
                                   &duration) != EOF)
                        {

                        }
                    }
                }
                bus_arr[i].line_number = line;
                bus_arr[i].distance = distance;
                bus_arr[i].duration = duration;
                i++;
            }

        }

    }
    return 0;

}

int test_mode(char key[], BusLine *bus_arr, BusLine *copy_bus, int
num_of_lines)
{
    if (strcmp(key, "bubble") == 0)
    {
        if (is_sorted_by_distance(bus_arr, bus_arr + num_of_lines))
        {
            printf("TEST 1 PASSED: the lines are sorted by distance\n");

        }
        if (is_sorted_by_distance(bus_arr, bus_arr + num_of_lines) == 0)
        {
            printf("TEST 1 FAILED: the lines aren't sorted byy distance\n");
            return 1;
        }
        if (is_equal(bus_arr, bus_arr + num_of_lines, copy_bus,
                     copy_bus + num_of_lines))
        {
            printf("TEST 2 PASSED: lines are still the same after sorting\n");

        }
        if (is_equal(bus_arr, bus_arr + num_of_lines, copy_bus,
                     copy_bus + num_of_lines) == 0)
        {

            printf("TEST 2 FAILED: lines are not the same after sorting\n");
            return 1;
        }
    }
    if (strcmp(key, "quick") == 0)
    {
        if (is_sorted_by_duration(bus_arr, bus_arr + num_of_lines))
        {
            printf("TEST 3 PASSED: the lines are sorted by duration\n");

        }
        if (is_sorted_by_duration(bus_arr, bus_arr + num_of_lines) == 0)
        {
            printf("TEST 3 FAILED: the lines aren't sorted by duration\n");
            return 1;
        }
        if (is_equal(bus_arr, bus_arr + num_of_lines, copy_bus,
                     copy_bus + num_of_lines))
        {
            printf("TEST 4 PASSED: lines are still the same after sorting\n");

        }
        if (is_equal(bus_arr, bus_arr + num_of_lines, copy_bus,
                     copy_bus + num_of_lines) == 0)
        {

            printf("TEST 4 FAILED: lines are not the same after sorting\n");
            return 1;
        }
    }
    return 0;
}


void handle_mode(char *argv[], BusLine *bus_arr, int
num_of_lines)
{
    if (strcmp(argv[ONE], "bubble") == 0)
    {
        bubble_sort(bus_arr, bus_arr + num_of_lines);

    }
    if ((strcmp(argv[ONE], "quick") == 0))
    {
        quick_sort(bus_arr, bus_arr + num_of_lines);
    }
    for (int i = 0; i < num_of_lines; i++)
    {
        printf("%d,%d,%d\n", bus_arr[i].line_number, bus_arr[i].distance,
               bus_arr[i].duration);
    }
}

int handle_test(char *argv[], BusLine *bus_arr, BusLine *copy_bus, int
num_of_lines)
{
    if (strcmp(argv[ONE], "test") == 0)
    {
        bubble_sort(bus_arr, bus_arr + num_of_lines);
        if (test_mode("bubble", bus_arr, copy_bus, num_of_lines))
        {
            return 1;
        }
        quick_sort(bus_arr, bus_arr + num_of_lines);
        if (test_mode("quick", bus_arr, copy_bus, num_of_lines))
        {
            return 1;
        }
    }
    return 0;
}

void free_arr(int a, BusLine *bus_arr, BusLine *copy_bus)
{
    if (a == 1)
    {
        free(bus_arr);
        bus_arr = NULL;
    } else
    {
        free(bus_arr);
        free(copy_bus);
        bus_arr = NULL;
        copy_bus = NULL;
    }
}

int main(int argc, char *argv[])
{

    if (cli_correctness(argc, argv) != 0)
    {
        return EXIT_FAILURE;
    }
    int num_of_lines = get_num_lines();
    if (num_of_lines == 0)
    {

        return EXIT_FAILURE;
    }
    BusLine *bus_arr = malloc(sizeof(BusLine) * num_of_lines);
    if (bus_arr == NULL)
    {
        return EXIT_FAILURE;
    }
    store_lines_data(bus_arr, num_of_lines);
    BusLine *copy_bus = malloc(sizeof(BusLine) * num_of_lines);
    if (copy_bus == NULL)
    {
        free_arr(1, bus_arr, copy_bus);
        return EXIT_FAILURE;
    }
    if (memcpy(copy_bus, bus_arr, num_of_lines * sizeof(copy_bus)) == NULL)
    {
        free_arr(0, bus_arr, copy_bus);
        return EXIT_FAILURE;
    }
    if (strcmp(argv[ONE], "bubble") == 0 || strcmp(argv[ONE], "quick") == 0)
    {
        handle_mode(argv, bus_arr, num_of_lines);
    }
    if (strcmp(argv[ONE], "test") == 0)
    {
        if (handle_test(argv, bus_arr, copy_bus, num_of_lines))
        {
            free_arr(0, bus_arr, copy_bus);
            return EXIT_FAILURE;
        }
    }
    free_arr(0, bus_arr, copy_bus);

    return EXIT_SUCCESS;

}
