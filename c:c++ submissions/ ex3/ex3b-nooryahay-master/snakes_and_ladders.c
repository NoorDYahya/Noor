#include <string.h> // For strlen(), strcmp(), strcpy()
#include "markov_chain.h"
#define MAX(X, Y) (((X) < (Y)) ? (Y) : (X))

#define EMPTY -1
#define BOARD_SIZE 100
#define MAX_GENERATION_LENGTH 60
#define TWO 2
#define TEN 10
#define DICE_MAX 6
#define NUM_OF_TRANSITIONS 20




/**
 * represents the transitions by ladders and snakes in the game
 * each tuple (x,y) represents a ladder from x to if x<y or a snake otherwise
 */

const int transitions[][2] = {{13, 4},
                              {85, 17},
                              {95, 67},
                              {97, 58},
                              {66, 89},
                              {87, 31},
                              {57, 83},
                              {91, 25},
                              {28, 50},
                              {35, 11},
                              {8,  30},
                              {41, 62},
                              {81, 43},
                              {69, 32},
                              {20, 39},
                              {33, 70},
                              {79, 99},
                              {23, 76},
                              {15, 47},
                              {61, 14}};

/**
 * struct represents a Cell in the game board
 */
typedef struct Cell {
    int number; // Cell number 1-100
    int ladder_to;  // ladder_to represents
    // the jump of the ladder in case there is one from this square
    int snake_to;  // snake_to represents
    // the jump of the snake in case there is one from this square
    //both ladder_to and snake_to should be -1 if the Cell doesn't have them
} Cell;

static void print (void* word)
{
    int *new_word =word;
    if(*new_word == 1)
    {
        printf("[%d]",*new_word);

    }
    else if (*new_word == BOARD_SIZE)
    {
        printf(" -> [%d]",*new_word);

    }
    else
    {
        printf(" -> [%d]",*new_word);
    }
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
    const int* p1 = lhs;
    const int* p2 = rhs;
    return (*p1 - *p2);
}
static bool is_last (void* elem)
{
    int*cell = elem;

    if (*cell == BOARD_SIZE)
    {
        return true;
    }
    return false;
}

/** Error handler **/
static int handle_error(char *error_msg, MarkovChain **database)
{
    printf("%s", error_msg);
    if (database != NULL)
    {
        free_markov_chain(database);
    }
    return EXIT_FAILURE;
}


static int create_board(Cell *cells[BOARD_SIZE])
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        cells[i] = malloc(sizeof(Cell));
        if (cells[i] == NULL)
        {
            for (int j = 0; j < i; j++) {
                free(cells[j]);
            }
            handle_error(ALLOCATION_ERROR_MASSAGE,NULL);
            return EXIT_FAILURE;
        }
        *(cells[i]) = (Cell) {i + 1, EMPTY, EMPTY};
    }

    for (int i = 0; i < NUM_OF_TRANSITIONS; i++)
    {
        int from = transitions[i][0];
        int to = transitions[i][1];
        if (from < to)
        {
            cells[from - 1]->ladder_to = to;
        }
        else
        {
            cells[from - 1]->snake_to = to;
        }
    }
    return EXIT_SUCCESS;
}

/**
 * fills database
 * @param markov_chain
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */

static int fill_database(MarkovChain *markov_chain)
{
    Cell* cells[BOARD_SIZE];
    if(create_board(cells) == EXIT_FAILURE)
    {
        return EXIT_FAILURE;
    }
    MarkovNode *from_node = NULL, *to_node = NULL;
    size_t index_to;
    for (size_t i = 0; i < BOARD_SIZE; i++)
    {
        add_to_database(markov_chain, cells[i]);
    }
    for (size_t i = 0; i < BOARD_SIZE; i++)
    {
        from_node = get_node_from_database(markov_chain,cells[i])->data;

        if (cells[i]->snake_to != EMPTY || cells[i]->ladder_to != EMPTY)
        {
            index_to = MAX(cells[i]->snake_to,cells[i]->ladder_to) - 1;
            to_node = get_node_from_database(markov_chain, cells[index_to])
                    ->data;
            add_node_to_counter_list(from_node, to_node, markov_chain);
        }
        else
        {
            for (int j = 1; j <= DICE_MAX; j++)
            {
                index_to = ((Cell*) (from_node->data))->number + j - 1;
                if (index_to >= BOARD_SIZE)
                {
                    break;
                }
                to_node = get_node_from_database(markov_chain, cells[index_to])
                        ->data;
                add_node_to_counter_list(from_node, to_node, markov_chain);
            }
        }
    }
    for (size_t i = 0; i < BOARD_SIZE; i++)
    {
        free(cells[i]);
    }
    return EXIT_SUCCESS;
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
static int check_args(int argc, char *argv[])
{
    if (argc!=3)
    {
        return 1;
    }
    else{
        int num_walks = strtol(argv[TWO],NULL,TEN);
        if(num_walks<0)
        {
            return 1;
        }
    }
    return 0;
}

static int print_walks(char *argv[], MarkovChain *markov_chain,
                       int max_length)
{
    int num_walks = strtol(argv[TWO], NULL, TEN);
    int i = 1;
    while (num_walks != 0)
    {
        printf("Random Walk %d: ", i);
        MarkovNode *first_node = markov_chain->database->first->data;
        generate_random_sequence(markov_chain, first_node, max_length);
        num_walks--;
        i++;
    }
    return 0;
}
/**
 * @param argc num of arguments
 * @param argv 1) Seed
 *             2) Number of sentences to generate
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
int main(int argc, char *argv[])
{
    handle_seed(argv);
    int res = check_args(argc,argv);
    if(res)
    {
        return EXIT_FAILURE;
    }
    MarkovChain *dataset = initial_chain();
    if (dataset == NULL)
    {
        return EXIT_FAILURE;
    }
    int result = fill_database(dataset);
    if(result == EXIT_FAILURE)
    {
        free_markov_chain(&dataset);
        return EXIT_FAILURE;
    }
    print_walks(argv,dataset,  MAX_GENERATION_LENGTH);
    return 0;
}