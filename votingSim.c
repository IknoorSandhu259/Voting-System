#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
    int votes;
} Candidate;

int main() {
    int numCandidates;
    int i, choice;
    FILE *file;

    printf("Enter number of candidates: ");
    scanf("%d", &numCandidates);

    Candidate *candidates = malloc(numCandidates * sizeof(Candidate));
    if (candidates == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    for (i = 0; i < numCandidates; i++) {
        printf("Enter name for candidate %d: ", i + 1);
        scanf("%s", candidates[i].name);
        candidates[i].votes = 0;
    }

    printf("\nVoting begins (enter -1 to stop)\n");

    while (1) {
        printf("Vote for candidate (1-%d): ", numCandidates);
        scanf("%d", &choice);

        if (choice == -1) {
            break;
        }

        if (choice < 1 || choice > numCandidates) {
            printf("Invalid vote.\n");
        } else {
            candidates[choice - 1].votes++;
        }
    }

    file = fopen("votes.txt", "w");
    if (file == NULL) {
        printf("Could not open file.\n");
        free(candidates);
        return 1;
    }

    for (i = 0; i < numCandidates; i++) {
        fprintf(file, "%s: %d votes\n", candidates[i].name, candidates[i].votes);
    }

    fclose(file);

    printf("\nResults saved to votes.txt\n");

    free(candidates);
    return 0;
}