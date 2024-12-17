# include <stdio.h>
# include <stdlib.h>
#include <math.h>

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

double euclidian_dis(double *vec1, double *vec2, int dim){
    double sum, pair_sub;
    int i;
    sum = 0;
    for(i = 0; i < dim; i++){
        pair_sub = vec2[i]-vec1[i];
        sum += pair_sub*pair_sub;
    }
    return sqrt(sum);
}
void closest_centroid(double **centroid_matrix, int num_of_clusters, double *vector, int dim){
    int i;
    double curr_min_dis = euclidian_dis(vector,centroid_matrix[0], dim);
    double curr_dis = curr_min_dis;
    vector[dim] = (double)0;
    for(i = 0; i < num_of_clusters; i++){
        curr_dis = euclidian_dis(vector,centroid_matrix[i], dim);
        if(curr_dis < curr_min_dis){
            curr_min_dis = curr_dis;
            vector[dim] = (double)i;
        }
    }
}
int num_of_dim(struct vector *curr){
    int i = 0;
    struct cord *c = curr -> cords;
    while(c != NULL){
        i += 1;
        c = c -> next;
    }
    return i;
}
int num_of_vec(struct vector *curr){
    int i = 0;
    struct vector *c = curr;
    while(c->next != NULL){
        i += 1;
        c = c -> next;
    }
    return i;
}
double** input_to_matrix(int rows, int cols, struct vector *curr_vec){
    int i;
    int j;
    int k;
    double *p;
    double **a;
    struct cord *curr_cord = curr_vec->cords;
    p = calloc(rows * (cols+1), sizeof(double));
    a = calloc(rows, sizeof(double *));
    for (i = 0; i < rows; i++){
        a[i] = p + i * (cols+1);
    }

    for (k = 0; k < rows; k++){
        for(j = 0; j <= cols; j ++){
            if(j == cols){
                a[k][j] = 0;
            }
            else{
                a[k][j] = curr_cord->value;
                curr_cord = curr_cord->next;
            }   
        }
        curr_vec = curr_vec->next;
        if(k < rows-1){
            curr_cord = curr_vec->cords;
        }
    }
    return a;
}
double** init_centroids(int num_of_clusters, int dim, double **matrix, int num_of_vec, int first){
    int i,j,k,s;
    double *p;
    int *b;
    double **a;
    b = calloc(num_of_clusters, sizeof(int));
    p = calloc(num_of_clusters * dim, sizeof(double));
    a = calloc(num_of_clusters, sizeof(double *));
    for (i = 0; i < num_of_clusters; i++){
        a[i] = p + i * dim;
    }
    for (k = 0; k < num_of_clusters; k++){
        for(j = 0; j < dim; j ++){
                a[k][j] = 0;
        }
    }
    k = 0;
    j = 0;

    if(first == 1){
        for (k = 0; k < num_of_clusters; k++){
            for(j = 0; j < dim; j ++){
                    a[k][j] = matrix[k][j];
            }
        }
    }
    else{
        for (k = 0; k < num_of_vec; k++){
            s = matrix[k][dim];
            b[s] ++;
            for(j = 0; j < dim; j ++){
                a[s][j] += matrix[k][j];
            }
        }

        for (k = 0; k < num_of_clusters; k++){
            for(j = 0; j < dim; j ++){
                    a[k][j] = a[k][j]/b[k];
            }
        }
    }
    free(b);
    return a;
}


void print_matrix(double** matrix, int rows, int cols) {
    int i,j;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            if(j == cols - 1){
                printf("%.4f", matrix[i][j]);
            }
            else{
                printf("%.4f,", matrix[i][j]);
            }
        }
        printf("\n");
    }
}

double calc_eps(double **cent_mat1, double **cent_mat2, int num_of_cluster, int dim){
    double *eps_ans = calloc(num_of_cluster, sizeof(double)), max;
    int i;
    for(i = 0; i < num_of_cluster; i++){
        eps_ans[i] = euclidian_dis(cent_mat1[i],cent_mat2[i],dim);
    }
    i = 0;
    max = eps_ans[0];
    for (i = 1; i < num_of_cluster; i++) {
        if (eps_ans[i] > max) {
            max = eps_ans[i];
        }
    }
    return max;
}
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
            free(tempChord);
        }
        currentVector = currentVector->next;
        free(tempVector);
    }
}

int main(int argc, char **argv){
    double **vec_matrix, **centroids_matrix, **old_centroids_matrix;
    char c;
    int k,s;
    struct vector *head_vec, *curr_vec, *next_vec;
    struct cord *head_cord, *curr_cord, *next_cord;
    int i, j, rows = 0, cols = 0, iter_max = 200, iter_count = 0, num_of_clusters;
    double n, eps = 0.002;;
    
    
    head_cord = malloc(sizeof(struct cord));
    curr_cord = head_cord;
    curr_cord->next = NULL;

    head_vec = malloc(sizeof(struct vector));
    curr_vec = head_vec;
    curr_vec->next = NULL;


    while (scanf("%lf%c", &n, &c) == 2){
        if (c == '\n')
        {
            curr_cord->value = n;
            curr_vec->cords = head_cord;
            curr_vec->next = malloc(sizeof(struct vector));
            curr_vec = curr_vec->next;
            curr_vec->next = NULL;
            head_cord = malloc(sizeof(struct cord));
            curr_cord = head_cord;
            curr_cord->next = NULL;
            continue;
        }
        curr_cord->value = n;
        curr_cord->next = malloc(sizeof(struct cord));
        curr_cord = curr_cord->next;
        curr_cord->next = NULL;
    }
    cols = num_of_dim(head_vec);
    rows = num_of_vec(head_vec);
    num_of_clusters = atoi(argv[1]);
    if(argc == 3){
        iter_max = atoi(argv[2]);
        if(iter_max >= 1000 || iter_max <= 1){
            printf("Invalid maximum iteration!\n");
            exit(1);
        }
    }
    if(num_of_clusters >= rows || num_of_clusters <= 1){
        printf("Invalid number of clusters!\n");
        exit(1);
    }
    
    vec_matrix = input_to_matrix(rows, cols, head_vec);
    freeVectors(head_vec);
    centroids_matrix = init_centroids(num_of_clusters, cols, vec_matrix, rows, iter_count + 1);
    while(eps >= 0.001 && iter_count < iter_max){
        for(i = 0; i < rows; i++){
            closest_centroid(centroids_matrix, num_of_clusters, vec_matrix[i], cols);
        }
        if(iter_count != 0){
            free(old_centroids_matrix[0]);
            free(old_centroids_matrix);
        }
        old_centroids_matrix = centroids_matrix;
        centroids_matrix = init_centroids(num_of_clusters, cols, vec_matrix, rows, 0);
        eps = calc_eps(old_centroids_matrix, centroids_matrix, num_of_clusters, cols);
        iter_count++;
    }
    print_matrix(centroids_matrix, num_of_clusters, cols);
    free(centroids_matrix[0]);
    free(centroids_matrix);
    (void)argv; 
    (void)i;
    (void)s;
    (void)k;
    (void)j;
    (void)rows;
    (void)cols;
    (void)next_vec;
    (void)next_cord;
    return 0;
}