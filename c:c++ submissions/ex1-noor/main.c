
#include "cipher.h"
#include "tests.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>



#define ROW_SIZE 1024
#define ONE 1
#define TWO 2
#define  THREE 3
#define  FOUR 4
#define TEN 10
#define FIVE 5
#define MAX_LENGTH 1024

int int_float(const char num[])
{
    int i = 0;
    while (num[i++] != '\0')
    {
        if (num[i] == '.')    // decimal point is present
        {
            return 1;

        }
    }
    return 0;
}

int is_digit(const char num[])
{
    int j = 0;
    if (strtol(num, NULL, TEN) < 0)
    {
        return 0;
    }
    while (num[j] != '\0')
    {
        if (isdigit(num[j]) != 0)
        {
            j++;
        } else
        {
            return 1;
        }

    }
    return 0;
}

int check_argc_correctness(int argc, char *argv[])
{
    if ((argc != FIVE) && (argc != TWO))
    {

        fprintf(stderr, "The program receives 1 or 4 arguments only.\n");
        return EXIT_FAILURE;

    }
    if ((argc == TWO) & (strcmp(argv[ONE], "test") != 0))
    {
        fprintf(stderr, "Usage: cipher test\n");
        return EXIT_FAILURE;
    }
    if (argc == FIVE)
    {

        if ((strcmp(argv[ONE], "encode") != 0) && (strcmp(argv[ONE],
                                                          "decode") != 0))
        {
            fprintf(stderr, "The given command is invalid.\n");
            return EXIT_FAILURE;

        }
        if (is_digit(argv[TWO]) != 0)
        {
            fprintf(stderr, "The given shift value is invalid.\n");
            return EXIT_FAILURE;
        }
        if (int_float(argv[TWO]))
        {
            fprintf(stderr, "The given shift value is invalid.\n");
            return EXIT_FAILURE;
        }

    }
    return 0;
}

int check_file(FILE *in_file, FILE *out_file)
{
    if (in_file == NULL || out_file == NULL)
    {
        fprintf(stderr, "The given file is invalid.\n");
        return EXIT_FAILURE;
    }
    return 0;
}

void treat_argv2(char *argv[], FILE *out_file, char word[])
{

    long k = strtol(argv[TWO], NULL, TEN);
    if (strcmp(argv[ONE], "encode") == 0)
    {
        encode(word, k);
        fprintf(out_file, "%s", word);
    }
    if (strcmp(argv[ONE], "decode") == 0)
    {
        decode(word, k);
        fprintf(out_file, "%s", word);
    }

}

int treat_test()
{
    if (test_encode_cyclic_lower_case_negative_k() != 0)
    {
        return EXIT_FAILURE;
    }
    if (test_decode_cyclic_lower_case_negative_k() != 0)
    {
        return EXIT_FAILURE;
    }
    if (test_encode_cyclic_lower_case_special_char_positive_k() != 0)
    {
        return EXIT_FAILURE;
    }
    if (test_encode_cyclic_upper_case_positive_k() != 0)
    {
        return EXIT_FAILURE;
    }
    if (test_encode_non_cyclic_lower_case_positive_k() != 0)
    {
        return EXIT_FAILURE;
    }
    if (test_encode_non_cyclic_lower_case_special_char_negative_k() != 0)
    {
        return EXIT_FAILURE;
    }
    if (test_decode_cyclic_lower_case_special_char_positive_k() != 0)
    {
        return EXIT_FAILURE;
    }
    if (test_decode_cyclic_upper_case_positive_k() != 0)
    {
        return EXIT_FAILURE;
    }
    if (test_decode_non_cyclic_lower_case_positive_k() != 0)
    {
        return EXIT_FAILURE;
    }
    if (test_decode_non_cyclic_lower_case_special_char_negative_k() != 0)
    {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}


int main(int argc, char *argv[])
{
    char buffer[MAX_LENGTH];
    if (check_argc_correctness(argc, argv))
    {
        return EXIT_FAILURE;
    }
    if (strcmp(argv[ONE], "test") == 0)
    {
        treat_test();
        return EXIT_SUCCESS;
    }
    FILE *in_file = fopen(argv[THREE], "r");
    FILE *out_file = fopen(argv[FOUR], "w+");
    if (check_file(in_file, out_file) == 0)
    {
        while (fgets(buffer, MAX_LENGTH, in_file) != NULL)
        {
            if (strcmp(argv[ONE], "decode") == 0 || strcmp(argv[ONE],
                                                           "encode") == 0)
            {
                treat_argv2(argv, out_file, buffer);
            }
        }
        fclose(in_file);
        fclose(out_file);
        return EXIT_SUCCESS;

    }
    return EXIT_FAILURE;

}
