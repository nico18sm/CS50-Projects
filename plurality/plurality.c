#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
} candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
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
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();

}

// Update vote totals given a new vote
bool vote(string name)
{
    for(int i = 0; i < candidate_count; i++){
        if(strcmp(name, candidates[i].name) == 0){
            candidates[i].votes += 1;
            return true; // Kandidat gefunden
        }
    }
   return false; // Kandidat nicht gefunden
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    //Bubble Sort implementierung
    for(int i = 0; i < (candidate_count - 1); i++)
    {
        for(int k = 0; k < (candidate_count - 1); k++)
        {
            if(candidates[k].votes > candidates[k + 1].votes)
            {
                 // Tausche Stimmen
                int temp = candidates[k].votes;
                candidates[k].votes = candidates[k + 1].votes;
                candidates[k + 1].votes = temp;

                // Tausche auch die Namen
                string temp_name = candidates[k].name;
                candidates[k].name = candidates[k + 1].name;
                candidates[k + 1].name = temp_name;
            }
        }
    }
    char *winners[MAX];
    int max_votes = candidates[candidate_count -1].votes;
    int winner_count = 0;

    for(int i = 0; i < candidate_count; i++){
        if(candidates[i].votes == max_votes){
            winners[winner_count] = candidates[i].name;
            winner_count++;
        }
    }

    for(int i = 0; i < winner_count; i++){
        printf("%s\n", winners[i]);
    }
    return;
}
