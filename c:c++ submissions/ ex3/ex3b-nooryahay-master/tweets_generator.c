#include <stdio.h>
#include <string.h>
#include "markov_chain.h"
#include <assert.h>
#define MAX_LEN_LINE 1000000
#define FIVE 5
#define FOUR 4
#define THREE 3
#define TWO 2
#define ONE 1
#define FILE_INDEX 3
#define TEN 10
#define MAX_LEN_TWEET 20


static void print (void* word)
{
    char * new_word =word;
    printf("%s ",new_word);
}
static void* copy ( void *p)
{
    char* dest = malloc(sizeof(dest));
    if(dest == NULL)
    {
        return NULL;
    }
    char* source = p;
    return strcpy(dest ,source);
}
static int compare( void *lhs ,  void* rhs)
{
    const char *const * p1 = lhs;
    const char *const * p2 = rhs;
    return strcmp (*p1, *p2);
}
static bool is_last (void* elem)
{
    char*word = elem;
    int len = strlen(word);
    if (word[len - 1] == '.')
    {
        return true;
    }
    return false;
}
static FILE *check_args_file(int argc, char *argv[])
{
    if ((argc != FIVE) && (argc != FOUR))
    {

        printf("Usage: The program can receives 3 or 4 arguments only.\n");
        return NULL;

    }
    if (argv[FILE_INDEX] == NULL)
    {
        fprintf(stdout, "Error: The given file is invalid.\n");
        return NULL;
    }
    FILE *in_file = fopen(argv[FILE_INDEX], "r");
    if (in_file == NULL)
    {
        fprintf(stdout, "Error: The given file cannot be opened.\n");
        return NULL;
    }
    return in_file;
}

static int fill_data_with_num_to_read(FILE *fp, int words_to_read, MarkovChain
*markov_chain)
{
    char buffer[MAX_LEN_LINE];
    char *token;
    Node *prev = NULL;
    while ((fgets(buffer, MAX_LEN_LINE, fp)) != NULL &&
           markov_chain->database->size != words_to_read)
    {
        token = strtok(buffer, " \n");
        while (token != NULL && markov_chain->database->size != words_to_read)
        {
            if (markov_chain->database->size == 0)
            {
                prev = NULL;

            }
            Node *res = add_to_database(markov_chain, token);
            if (res == NULL)
            {
                return 1;
            }
            if (prev != NULL)
            {
                if (markov_chain->is_last(prev->data->data))
                {
                    prev->data->length_counter_list = 0;
                    prev->data->counter_list = NULL;
                } else
                {
                    bool cur = add_node_to_counter_list(
                            prev->data,res->data,markov_chain);
                    if (!cur)
                    {
                        return 1;
                    }
                }
            }
            prev = res;
            token = strtok(NULL, " \n");
        }
    }
    return 0;
}
static int words(int argc, char *argv[])
{

    char buffer[MAX_LEN_LINE];
    char *token;
    FILE *in_file = check_args_file(argc, argv);
    int count =0;
    while ((fgets(buffer, MAX_LEN_LINE, in_file)) != NULL )
    {
        token = strtok(buffer, " \n");
        while (token != NULL)
        {
            token = strtok(NULL, " \n");
            count++;
        }
    }
    fclose(in_file);
    return count;

}

static int fill_database(FILE *fp, int words_to_read, MarkovChain
*markov_chain ,int argc, char *argv[])
{
    if (words_to_read)
    {
        return fill_data_with_num_to_read(fp, words_to_read, markov_chain);
    }
    else
    {
        int c = words(argc,argv);
        return fill_data_with_num_to_read(fp, c, markov_chain);
    }
}


static void handle_seed(char *argv[])
{
    int unsigned seed;
    seed = strtol(argv[1], NULL, TEN);
    srand(seed);
}

static MarkovChain *initial_chain()
{
    MarkovChain *dataset = malloc(sizeof(MarkovChain));
    if (dataset == NULL)
    {
        printf("Allocation failure: can not allocate memory\n");
        return NULL;
    }
    dataset->print_func = print;
    dataset->comp_func = compare;
    dataset->copy_func = copy;
    dataset->free_data = free;
    dataset->is_last = is_last;

    dataset->database = malloc(sizeof(LinkedList));
    if (dataset->database == NULL)
    {
        printf("Allocation failure: can not allocate memory\n");
        free(dataset);
        return NULL;
    }
    dataset->database->first = NULL;
    dataset->database->last = NULL;
    dataset->database->size = 0;
    return dataset;
}


static int store_data(FILE *in_file, MarkovChain *dataset, char *argv[], int
argc)
{
    int unsigned words_to_read = 0;
    if (argc == FIVE)
    {
        words_to_read = strtol(argv[FOUR], NULL, TEN);
    }
    int res = fill_database(in_file, (int) words_to_read,
                            dataset, argc, argv);
    if (res)
    {
        printf("Allocation failure: can not allocate memory\n");
        free_markov_chain(&dataset);
        return 1;
    }
    return 0;
}

static int print_tweets(char *argv[], MarkovChain *markov_chain,
                        int max_length)
{
    int num_tweets = strtol(argv[TWO], NULL, TEN);
    int i = 1;
    while (num_tweets != 0)
    {
        printf("Tweet %d: ", i);
        MarkovNode *first_node = get_first_random_node(markov_chain);
        generate_random_sequence(markov_chain, first_node, max_length);
        num_tweets--;
        i++;
    }
    return 0;
}
int main(int argc, char *argv[])
{
    handle_seed(argv);
    MarkovChain *dataset = initial_chain();
    if (dataset == NULL)
    {
        return EXIT_FAILURE;
    }
    FILE *in_file = check_args_file(argc, argv);
    if (in_file == NULL)
    {

        return EXIT_FAILURE;

    }
    int result = store_data(in_file, dataset, argv, argc);
    if (result)
    {
        fclose(in_file);
        free_markov_chain(&dataset);
        return EXIT_FAILURE;
    }
    fclose(in_file);
    print_tweets(argv, dataset,  MAX_LEN_TWEET);
    return 0;
}
