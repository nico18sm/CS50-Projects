#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 9

// Candidate structure with name and vote count
typedef struct
{
    string name;
    int votes;
    bool eliminated;
} candidate;

// Array of candidates
candidate candidates[MAX];

// Number of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter_index, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);
int preferences[MAX][100];

int main(int argc, string argv[])
{
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }

    // Initialize candidates
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    // Get number of voters
    voter_count = get_int("Number of voters: ");

    // Collect votes from voters
    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);
            if (!vote(i, j, name))  
            {
                printf("Invalid vote.\n");
            }
        }
    }

    // Run the election until we have a winner
    while (true)
    {
        // Tabulate the votes for the current round
        tabulate();

        // Print the winner if there is one
        if (print_winner())
        {
            break;
        }

        // Find the minimum number of votes
        int min = find_min();

        // Check for a tie
        if (is_tie(min))
        {
            printf("It's a tie!\n");
            break;
        }

        // Eliminate the candidate with the least votes
        eliminate(min);
    }

    return 0;
}

bool vote(int voter_index, int rank, string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            preferences[voter_index][rank] = i;  // Speichert den Index des Kandidaten in der Präferenzmatrix
            return true;
        }
    }
    return false;
}

void tabulate(void)
{
    // Setze die Stimmen jedes Kandidaten auf null zurück
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].votes = 0;
    }

    // Zähle die Stimmen basierend auf den Präferenzen
    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            int candidate_index = preferences[i][j];
            if (!candidates[candidate_index].eliminated)
            {
                candidates[candidate_index].votes++;
                break;  // Sobald der Kandidat gefunden wurde, zählen wir und brechen ab
            }
        }
    }
}

bool print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        // Check if the candidate has more than 50% of the votes
        if (candidates[i].votes > voter_count / 2)
        {
            printf("Winner: %s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}

int find_min(void)
{
    int min = voter_count;

    // Find the candidate with the minimum votes
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated && candidates[i].votes < min)
        {
            min = candidates[i].votes;
        }
    }
    return min;
}

bool is_tie(int min)
{
    // Check if all remaining candidates have the same number of votes
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated && candidates[i].votes != min)
        {
            return false;
        }
    }
    return true;
}

void eliminate(int min)
{
    // Eliminate candidates with the minimum number of votes
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }
}
