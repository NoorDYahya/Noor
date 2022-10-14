#ifndef EX2_REPO_SORTBUSLINES_H
#define EX2_REPO_SORTBUSLINES_H
// write only between #define EX2_REPO_SORTBUSLINES_H and #endif
// EX2_REPO_SORTBUSLINES_H
/**
 * TODO add documentation
 *
 *
 */
typedef struct BusLine
{
    int line_number, distance, duration;
} BusLine;

/**
 * TODO add documentation
 */
void bubble_sort(BusLine *start, BusLine *end);

/**
 * TODO add documentation
 */
void quick_sort(BusLine *start, BusLine *end);

/**
 * TODO add documentation
 */

// write only between #define EX2_REPO_SORTBUSLINES_H and #endif
// EX2_REPO_SORTBUSLINES_H
#endif //EX2_REPO_SORTBUSLINES_H

