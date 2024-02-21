#include <stdio.h>
#include <stdlib.h>
#include "imageprocessing.h"
#define limitamare 255
#define limitamica 0

int ***flip_horizontal(int ***image, int N, int M) {
    int i = 0, j = 0, k = 0, aux = 0;
    for (i = 0; i < N; i++) {
        for (j = 0; j < M / 2; j ++) {
            for (k = 0; k < 3; k++) {
                aux = image[i][j][k];
                image[i][j][k] = image[i][M - 1 - j][k];
                image[i][M - 1 - j][k] = aux;
            }
        }
    }
    return image;
}

int ***rotate_left(int ***image, int N, int M) {
    int i = 0, j = 0, k = 0;
    int ***rotated_image = (int ***)malloc(M * sizeof(int **));
    for (i = 0; i < M; i++) {
        rotated_image[i] = (int **)malloc(N * sizeof(int *));
        for (j = 0; j < N; j++) {
            rotated_image[i][j] = (int *)malloc(3 * sizeof(int));
            for (k = 0; k < 3; k++) {
                rotated_image[i][j][k] = image[j][M - i - 1][k];
            }
        }
    }
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            free(image[i][j]);
        }
        free(image[i]);
    }
    free(image);
    return rotated_image;
}

int ***crop(int ***image, int N, int M, int x, int y, int h, int w) {
    int ***cropped_image = (int ***)malloc(h * sizeof(int **));
    for (int i = 0; i < h; i++) {
        cropped_image[i] = (int **)malloc(w * sizeof(int *));
        for (int j = 0; j < w; j++) {
            cropped_image[i][j] = (int *)malloc(3 * sizeof(int));
            for (int k = 0; k < 3; k++) {
                cropped_image[i][j][k] = image[i + y][j + x][k];
            }
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            free(image[i][j]);
        }
        free(image[i]);
    }
    free(image);
    return cropped_image;
}

int ***extend(int ***image, int N, int M, int rows, int cols, int new_R, int new_G, int new_B) {
    int i = 0, j = 0, k = 0;
    int rows_N = 2 * rows + N;
    int cols_M = 2 * cols + M;
    int ***extended_image = (int ***)malloc(rows_N * sizeof(int **));
    for (i = 0; i < rows_N; i++) {
        extended_image[i] = (int **)malloc(cols_M * sizeof(int *));
        for (j = 0; j < cols_M; j++) {
            extended_image[i][j] = (int *)malloc(3 * sizeof(int));
            extended_image[i][j][0] = new_R;
            extended_image[i][j][1] = new_G;
            extended_image[i][j][2] = new_B;
        }
    }
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            for (k = 0; k < 3; k++) {
                extended_image[i + rows][j + cols][k] = image[i][j][k];
            }
        }
    }
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            free(image[i][j]);
        }
        free(image[i]);
    }
    free(image);
    return extended_image;
}

int ***paste(int ***image_dst, int N_dst, int M_dst, int *** image_src, int N_src, int M_src, int x, int y) {
    int i = 0, j = 0, k = 0;
    for (i = 0; i < N_src; i++) {
        for (j = 0; j < M_src; j++) {
            for (k = 0; k < 3; k++) {
                if (y + i < N_dst && x + j < M_dst) {
                    image_dst[y + i][x + j][k] = image_src[i][j][k];
                }
            }
        }
    }
    return image_dst;
}

int ***apply_filter(int ***image, int N, int M, float **filter, int filter_size) {
    int i = 0, j = 0, k = 0, a = 0, b = 0 , x = 0, y = 0;
    float s = 0.0f;
    int ***filtered_image = (int ***) malloc(N * sizeof(int **));
    for (i = 0; i < N; i++) {
        filtered_image[i] = (int **) malloc(M * sizeof(int *));
        for (j = 0; j < M; j++) {
            filtered_image[i][j] = (int *) malloc(3 * sizeof(int));
        }
    }
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            for (k = 0; k < 3; k++) {
                s = 0.0f;
                for (a = 0; a < filter_size; a++) {
                    for (b = 0; b < filter_size; b++) {
                        x = i - filter_size / 2 + a;
                        y = j - filter_size / 2 + b;
                        if (x >= 0 && y >=0 && x < N && y < M) {
                            s += (float)image[x][y][k] * filter[a][b];
                        }
                    }
                }
                filtered_image[i][j][k] = (int)s;
                if (filtered_image[i][j][k] > limitamare) {
                    filtered_image[i][j][k] = limitamare;
                }
                if (filtered_image[i][j][k] < limitamica) {
                    filtered_image[i][j][k] = limitamica;
                }
            }
        }
    }
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            free(image[i][j]);
        }
        free(image[i]);
    }
    free(image);
    return filtered_image;
}
