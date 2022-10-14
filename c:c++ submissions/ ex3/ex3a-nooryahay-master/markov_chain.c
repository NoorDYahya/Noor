
#include "markov_chain.h"
#include <string.h>
#include <assert.h>
#define WORD_MAX_LEN 100

/**
* Get random number between 0 and max_number [0, max_number).
* @param max_number maximal number to return (not including)
* @return Random number
*/
int get_random_number(int max_number)
{
    return rand() % max_number;
}

int is_end_with_dot(char *word)
{
    int len = strlen(word);
    if (word[len - 1] == '.')
    {
        return 1;
    }
    return 0;

}

MarkovNode *get_first_random_node(MarkovChain *markov_chain)
{

    int max_num = markov_chain->database->size;
    int random_num = get_random_number(max_num);
    Node *current = markov_chain->database->first;
    int i = 0;
    while (i != random_num)
    {
        current = current->next;
        i++;
    }
    while (is_end_with_dot(current->data->data) != 0)
    {
        int j = 0;
        current = markov_chain->database->first;
        int random_num_2 = get_random_number(max_num);
        while (j != random_num_2)
        {
            current = current->next;
            j++;
        }
    }
    return current->data;
}

MarkovNode *get_next_random_node(MarkovNode *state_struct_ptr)
{
    int max_num = 0;
    int k = 0;
    int counter_1 = state_struct_ptr->length_counter_list;
    NextNodeCounter *temp = state_struct_ptr->counter_list;
    while (counter_1 != k)
    {


        max_num += temp[k].frequency;
        k++;
    }
    int random_num = get_random_number (max_num);
    int count = 0;
    MarkovNode *result = NULL;
    for (int i = 0; i < state_struct_ptr->length_counter_list; i++)
    {
        for (int j = 0;
             j < state_struct_ptr->counter_list[i].frequency; j++)
        {
            if (count == random_num)
            {
                result = state_struct_ptr->counter_list[i].markov_node;
                return result;

            }
            count++;
        }
    }
    return result;

}
void generate_random_sequence(MarkovChain *markov_chain, MarkovNode *
first_node, int max_length)
{
    if (first_node == NULL)
    {
        first_node = get_first_random_node(markov_chain);
    }
    MarkovNode *temp = first_node;

    printf("%s ", temp->data);
    temp = get_next_random_node(temp);
    while ((max_length - 2) != 0 && (is_end_with_dot(temp->data) != 1))
    {

        printf("%s ", temp->data);
        temp = get_next_random_node(temp);
        max_length--;
    }
    printf("%s\n", temp->data);
}

void free_markov_chain(MarkovChain **ptr_chain)
{

    Node *current = (*ptr_chain)->database->first;
    Node *next;
    while (current != NULL)
    {
        if(current->data->counter_list != NULL)
        {
            free(current->data->counter_list);
        }
        free(current->data->data);
        free (current->data);
        next = current;
        current = current->next;
        free (next);
    }

    /* deref head_ref to affect the real head back
       in the caller. */
    (*ptr_chain)->database->first = NULL;
    (*ptr_chain)->database->last = NULL;
    (*ptr_chain)->database->size= 0;
    free((*ptr_chain)->database);
    free(*ptr_chain);
}
bool add_node_to_counter_list(MarkovNode *first_node, MarkovNode *second_node)
{
    int len = first_node->length_counter_list;
    for (int i = 0; i < len; i++)
    {
        if (strcmp(first_node->counter_list[i].markov_node->data,
                   second_node->data) == 0)
        {
            first_node->counter_list[i].frequency++;

            return true;
        }
    }
    NextNodeCounter *temp;
    if(first_node->counter_list == NULL)
    {
        temp  = malloc (sizeof (NextNodeCounter));
    }
    else{
        temp = realloc(first_node->counter_list,
                       (first_node->length_counter_list + 1) * sizeof
                               (NextNodeCounter));
    }
    if (temp == NULL)
    {
        return false;
    }
    first_node->counter_list = temp;
    first_node->counter_list[len].markov_node = malloc(sizeof(MarkovNode));
    if (first_node->counter_list[len].markov_node == NULL)
    {

        return false;
    }
    first_node->counter_list[len].markov_node = second_node;
    first_node->counter_list[len].frequency =1;
    first_node->length_counter_list++;
    return true;
}

Node *get_node_from_database(MarkovChain *markov_chain, char *data_ptr)
{
    int i = 0;
    Node *curent = markov_chain->database->first;
    while (i != markov_chain->database->size)
    {
        if (strcmp(curent->data->data, data_ptr) == 0)
        {
            return curent;
        }
        curent = curent->next;
        i++;
    }
    return NULL;
}


Node *add_to_database(MarkovChain *markov_chain, char *data_ptr)
{
    Node *result = get_node_from_database(markov_chain, data_ptr);
    if (result != NULL)
    {
        return result;
    }

    Node *new_node = malloc(sizeof(Node));
    if (new_node == NULL)
    {
        return NULL;
    }
    new_node->data = malloc(sizeof(MarkovNode));
    if (new_node->data == NULL)
    {
        return NULL;
    }
    new_node->data->data = malloc(sizeof(char) * WORD_MAX_LEN);
    if (new_node->data->data == NULL)
    {
        return NULL;
    }
    strcpy(new_node->data->data, data_ptr);
    new_node->next = NULL;
    new_node->data->counter_list = NULL;
    new_node->data->length_counter_list = 0;

    /*If the Linked List is empty, then make the new node as head */
    if ((markov_chain->database->first) == NULL)
    {
        (markov_chain->database->first) = new_node;
        markov_chain->database->last = new_node;
        markov_chain->database->size++;
        return (markov_chain->database->first);
    }
    /* Change the next of last node */
    Node *temp = markov_chain->database->last;
    temp->next = new_node;
    markov_chain->database->last = temp->next;
    markov_chain->database->last->next = NULL;
    markov_chain->database->size++;
    return new_node;
}
