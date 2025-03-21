# include <stdio.h>
# include <stdlib.h>
struct cord
{
    double value;
    struct cord *next;
};
struct vector
{
    struct vector *next;
    struct cord *cords;
};



void freeVectors(struct vector *firstVector) {
    struct vector *tempVector;
    struct cord *currentChord, *tempChord;
    struct vector *currentVector = firstVector;
    while (currentVector != NULL) {
        tempVector = currentVector;
        currentChord = currentVector->cords;
        while (currentChord != NULL) {
            tempChord = currentChord;
            currentChord = currentChord->next;
            // free(tempChord->next);
            // free(&tempChord->value);
            free(tempChord);
        }
        currentVector = currentVector->next;
        // free(tempVector->cords);
        // free(tempVector->next);
        free(tempVector);
    }
}


int main(int argc, char **argv){
    struct vector *head_vec, *curr_vec, *next_vec;
    struct cord *head_cord, *curr_cord, *next_cord;
    int i, j, rows = 0, cols;
    double n;
    char c;

    head_cord = malloc(sizeof(struct cord));
    curr_cord = head_cord;
    curr_cord->next = NULL;

    head_vec = malloc(sizeof(struct vector));
    curr_vec = head_vec;
    curr_vec->next = NULL;

    while (scanf("%lf%c", &n, &c) == 2)
    {
        if (c == '\n' || c=='\r')
        {
            curr_cord->value = n;
            curr_vec->cords = head_cord;
            curr_vec->next = malloc(sizeof(struct vector));
            curr_vec = curr_vec->next;
            curr_vec->next = NULL;
            head_cord = malloc(sizeof(struct cord));
            curr_vec->cords = head_cord;
            curr_cord = head_cord;
            curr_cord->next = NULL;
            continue;
        }
        curr_cord->value = n;
        curr_cord->next = malloc(sizeof(struct cord));
        curr_cord = curr_cord->next;
        curr_cord->next = NULL;
   
    }
    // free(curr_vec);
    // free(head_cord);


    printf("\n%f\n", head_vec->cords->value);

    freeVectors(head_vec);
    exit(1);
    return 0;

}