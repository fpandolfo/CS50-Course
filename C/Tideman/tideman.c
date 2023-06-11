#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
// keep track over the graph
// return true if locked in the edge pointing from de candidate i to candidate j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner; // represent the candidate index winner of this pair
    int loser; // represent the cadidate index loser of this pair
}
pair;

// Array of strings, candidates
string candidates[MAX];

// store all of the pair where one candidate is preferred above another
// if there is a pair tie, dont add
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
int cmpfunc(const void *a, const void *b);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        // creating the array of candidates, by command line
        candidates[i] = argv[i + 1];
    }


    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    // first determine winner for each pair of candidates
    add_pairs();
    // sorte in decreasing strenght
    sort_pairs();
    // starting with strongest pair -- lock each pair to candidate graph, as long as no cycles
    lock_pairs();
    // source of graph
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // rank: which rank is being voted for => Rank 0, 1 or 2 - first 0 second and third
    // loop search by name => update "ranks" => indicar que tal eleitor tem tal candidato como sua preferencia - 0 first - 1 second - 2 third
    // return true if ok, return false if name dont match
    // ranks[i] represents the ith preference
    // differents names

    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }

    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // rank passed as argument
    // ranks[] ex: 3 | 0 | 4 | 1 | 2 => candidate 3 preferred over others - ranks[0]: candidate 3 == "any name"
    // called once per voter => takes ranks[i] => represents the iTH preference
    // update preferences[i][j] global matrix => number of voter that prefer candidate i than j
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // should add all pairs of candidates where one candidate is preferred to the pairs[]. A pair who are tied should not be added
    // vai comparar par por par, ver quem eh o preferido entre eles e adicionar na matriz
    // update the global pair_count to be the number of pairs of candidates ( between pairs[0] and pairs[pair_count - 1] )

    // use preferences[i][j] - voters who prefer candidate i over j
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count ++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count ++;
            }
        }
    }
}


/*Parameters
    base − This is the pointer to the first element of the array to be sorted.
    nitems − This is the number of elements in the array pointed by base.
    size − This is the size in bytes of each element in the array.
    compar − This is the function that compares two elements.*/

int cmpfunc(const void *a, const void *b)
{
    // decreasing --> ( *(pair*)b - *(pair*)a );
    pair *pairB = (pair *)b;
    pair *pairA = (pair *)a;
    return preferences[pairB -> winner][pairB -> loser] - preferences[pairA -> winner][pairA -> loser];
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // sort the pairs[] array in decreasing order of strenght of victory
    // strongest --> weak
    // by this we dont create a cycle, if the last one is going to form a cycle, we dont execute
    // difference between the winner and the looser => ex: 7-2 greater than 6-4

    qsort(pairs, pair_count, sizeof(pair), cmpfunc);

}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // create the locked graph in decreasing order -- edge would not create a cycle

    for (int k = 0; k < pair_count; k++)
    {
        for (int i = 0; i < candidate_count; i++)
        {
            for (int j = 0; j < candidate_count; j++)
            {
                if (pairs[k].winner == i && pairs[k].loser == j)
                {
                    locked[i][j] = true;
                }
            }
        }
    }

    return;
}

// Print the winner of the election
void print_winner(void)
{
    int rank;
    
    // print name of the candidate who is source of graph -- no arrows pointing towards
    for (int i = 0; i < candidate_count; i++)
    {
        rank = 0;
        for (int j = 0; j < candidate_count; j++)
        {   
            // se toda sua coluna for igual a false -- if all your column is false
            if (locked[j][i] == false)
            {
                rank ++;
            }
        }
        if (rank == candidate_count)
        {
            printf("%s\n", candidates[i]);
        }
    }
    return;
}

