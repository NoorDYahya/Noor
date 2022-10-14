#include "tests.h"
#include <string.h>

#define K_1 3

#define K_2 2
#define K_3 -1
#define K_4 29
#define K_5 -3

// See full documentation in header file
int test_encode_non_cyclic_lower_case_positive_k()
{
    char in[] = "abc";
    char out[] = "def";
    encode(in, K_1);
    return strcmp(in, out) != 0;
}

// See full documentation in header file
int test_encode_cyclic_lower_case_special_char_positive_k()
{
    char in[] = "zc#@w";
    char out[] = "cf#@c";
    encode(in, K_2);
    return strcmp(in, out) != 0;
}

// See full documentation in header file
int test_encode_non_cyclic_lower_case_special_char_negative_k()
{
    char in[] = "fg!h";
    char out[] = "ef!g";
    encode(in, K_3);
    return strcmp(in, out) != 0;
}

// See full documentation in header file
int test_encode_cyclic_lower_case_negative_k()
{
    char in[] = "abc";
    char out[] = "xyz";
    encode(in, K_5);
    return strcmp(in, out) != 0;
}

// See full documentation in header file
int test_encode_cyclic_upper_case_positive_k()
{
    char in[] = "ABC";
    char out[] = "DEF";
    encode(in, K_4);
    return strcmp(in, out) != 0;
}
// See full documentation in header file
int test_decode_non_cyclic_lower_case_positive_k()
{
    char in[] = "de#f";
    char out[] = "ab#c";
    decode(in, K_1);
    return strcmp(in, out) != 0;
}
// See full documentation in header file
int test_decode_cyclic_lower_case_special_char_positive_k()
{
    char in[] = "ab!c";
    char out[] = "yz!a";
    decode(in, K_2);
    return strcmp(in, out) != 0;
}
// See full documentation in header file
int test_decode_non_cyclic_lower_case_special_char_negative_k()
{
    char in[] = "efg";
    char out[] = "fgh";
    decode(in, K_3);
    return strcmp(in, out) != 0;
}

// See full documentation in header file
int test_decode_cyclic_lower_case_negative_k()
{
    char in[] = "xyz";
    char out[] = "abc";
    decode(in, K_5);
    return strcmp(in, out) != 0;
}

// See full documentation in header file
int test_decode_cyclic_upper_case_positive_k()
{
    char in[] = "ABC";
    char out[] = "XYZ";
    decode(in, K_4);
    return strcmp(in, out) != 0;
}

