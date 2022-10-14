#include "cipher.h"
#include <string.h>
#include <stdio.h>
#include "tests.h"

#define SIZEOF_LETTERS 27
#define S_Z_VALUE 122
#define S_A_VALUE 97
#define NUM_LETTERS 26
#define B_Z_VALUE 90
#define B_A_VALUE 65
/// IN THIS FILE, IMPLEMENT EVERY FUNCTION THAT'S DECLARED IN cipher.h.

char big_letters[SIZEOF_LETTERS] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                                    'I',
                                    'J', 'K', 'L',
                                    'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
                                    'U', 'V', 'W', 'X',
                                    'Y', 'Z'};
char small_letters[SIZEOF_LETTERS] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',
                                      'i',
                                      'j', 'k', 'l',
                                      'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
                                      'u', 'v', 'w', 'x',
                                      'y', 'z'};

char handle_small_letters_cases(int ch, int k, char val, char result)
{
    if (ch > 'z')
    {
        k = k - (S_Z_VALUE - val);
        k = k % NUM_LETTERS;
        result = small_letters[k - 1];

    }
    if (ch < 'a')
    {
        k = k - (val - S_A_VALUE);
        k = k % NUM_LETTERS;
        if (k == 0)
        {
            result = small_letters[0];
        } else
        {
            result = small_letters[NUM_LETTERS - k];
        }
    }
    return result;

}

char handle_big_letters_cases(int ch, int k, char val, char result)
{
    if (ch > 'Z')
    {  //any thing else
        k = k - (B_Z_VALUE - val);
        k = k % NUM_LETTERS;
        result = big_letters[k - 1];
    }
    if (ch < 'A')
    {

        k = k - (val - B_A_VALUE);
        k = k % NUM_LETTERS;
        if (k == 0)
        {
            result = big_letters[0];
        } else
        {
            result = big_letters[NUM_LETTERS - k];
        }
    }
    return result;
}
char big_letter(int ch , int k , char val ,char result){
    if (ch > 'Z')
    {  //any thing else
        return  handle_big_letters_cases(ch, k, val, result);
    } else
    {
        if (ch < 'A')
        {
            return handle_big_letters_cases(ch, (-1 * k), val, result);
        } else
        {
            return  ch;
        }
    }
}
char small_letter(int ch , int k , char val ,char result){
    if (ch > 'z')
    {
        return  handle_small_letters_cases(ch, k, val, result);
    } else
    {
        if (ch < 'a')
        {
            return  handle_small_letters_cases(ch, (-1 * k), val,
                                              result);
        } else
        {
            return  ch;
        }

    }
}
void encode(char s[], int k)
{
    int length = (int) strlen(s);

    for (int i = 0; i < length; i++)
    {
        int shift = k;
        char val = s[i];
        int ch = s[i];
        char result = 0;
        if (ch >= 'a' && ch <= 'z')
        { //small letters
            ch = ch + k;
            s[i] = small_letter(ch,k,val,result);
            k = shift;

        } else if (ch >= 'A' && ch <= 'Z')
        {
            ch = ch + k;

            s[i] = big_letter(ch,k,val,result);
            k = shift;

        } else
        {
            s[i] = s[i];
        }
    }
}
void decode(char s[], int k)
{
    k = k * (-1);
    encode(s, k);
}

