# include <stdio.h>
# include <stdlib.h>

void print_matrix(double** matrix, int rows, int cols) {
    int i,j;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            if(j == cols - 1){
                printf("%.0f", matrix[i][j]);
            }
            else{
                printf("%.0f,", matrix[i][j]);
            }
        }
        printf("\n");
    }
}


int main(){
    int i,rows, cols;
    double *p;
    double **a;
    rows = 100;
    cols = 100;
    p = calloc(rows * cols, sizeof(double));
    if(p == NULL){
        free(p);
        exit(1);
    }
    a = calloc(rows, sizeof(double *));
    if (a == NULL){
        free(a);
        exit(1);
    }
    for (i = 0; i < rows; i++){
        a[i] = p + i * cols;
    }
    a[5][5] = 101.69695;
    printf("\n%f\n", a[5][5]);
    print_matrix(a, 10, 10);
    free(a[0]);
    free(a);
}