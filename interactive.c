#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "imageprocessing.h"
#include "bmp.h"
#define H 100

int main() {
    int ****image = NULL;
    int N[H], M[H] , count = 0, i = 0, j = 0, index = 0, nr_filtre = 0;
    char command[3], path[H];
    int filter_size[H];
    int index_filter = -1;
    float ***filter = NULL;
    while (scanf("%s" , command)) {
        if (strcmp(command, "e") == 0) {
            break;
        }  else if (strcmp(command, "l") == 0) {
            count++;
            scanf("%d %d %s", &N[count - 1], &M[count - 1], path);
            image = (int ****)realloc(image, count * sizeof(int ***));
            image[count - 1] = (int ***)malloc(N[count - 1] * sizeof(int **));
            for (i = 0; i < N[count - 1]; i++) {
                image[count - 1][i] = (int **)malloc(M[count - 1] * sizeof(int *));
                for (j = 0; j < M[count - 1]; j++) {
                    image[count - 1][i][j] = (int *)malloc(3 * sizeof(int));
                }
            }
            read_from_bmp(image[count - 1], N[count - 1], M[count - 1], path);
        } else if (strcmp(command, "s") == 0) {
            char newpath[H];
            scanf("%d %s", &index, newpath);
            write_to_bmp(image[index], N[index], M[index], newpath);
        } else if (strcmp(command, "ah") == 0) {
            scanf("%d", &index);
            image[index] = flip_horizontal(image[index], N[index], M[index]);
        } else if (strcmp(command, "ar") == 0) {
            scanf("%d", &index);
            image[index] = rotate_left(image[index], N[index], M[index]);
            int aux = N[index];
            N[index] = M[index];
            M[index] = aux;
        } else if (strcmp(command, "ac") == 0) {
            int x = 0, y = 0, w = 0, h = 0;
            scanf("%d %d %d %d %d", &index, &x, &y, &w, &h);
            image[index] = crop(image[index], N[index], M[index], x, y , h, w);
            N[index] = h;
            M[index] = w;
        } else if (strcmp(command, "ae") == 0) {
            int rows = 0, cols = 0, R = 0, G = 0, B = 0;
            scanf("%d %d %d %d %d %d", &index, &rows, &cols, &R, &G, &B);
            image[index] = extend(image[index], N[index], M[index], rows, cols, R, G, B);
            N[index] = N[index] + 2 * rows;
            M[index] = M[index] + 2 * cols;
        } else if (strcmp(command, "ap") == 0) {
            int index_dst = 0, index_src = 0, x = 0, y = 0;
            scanf("%d %d %d %d", &index_dst, &index_src, &x, &y);
            image[index_dst] = paste(image[index_dst], N[index_dst], M[index_dst],
             image[index_src], N[index_src], M[index_src], x, y);
        } else if (strcmp(command, "cf") == 0) {
            nr_filtre++;
            scanf("%d", &filter_size[nr_filtre - 1]);
            filter = (float ***)realloc(filter, nr_filtre * sizeof(float **));
            filter[nr_filtre - 1] = (float **)malloc(filter_size[nr_filtre - 1] * sizeof(float *));
            for (i = 0; i < filter_size[nr_filtre - 1]; i++) {
                filter[nr_filtre - 1][i] = (float *)malloc(filter_size[nr_filtre - 1] * sizeof(float));
                for (j = 0; j < filter_size[nr_filtre - 1]; j++) {
                    scanf("%f", &filter[nr_filtre - 1][i][j]);
                }
            }
        } else if (strcmp(command, "af") == 0) {
            int index_img = 0;
            scanf("%d %d", &index_img, &index_filter);
            image[index_img] = apply_filter(image[index_img], N[index_img], M[index_img],
             filter[index_filter], filter_size[index_filter]);
        } else if (strcmp(command, "df") == 0) {
            int index_filter = 0;
            scanf("%d", &index_filter);
            for (i = 0; i < filter_size[index_filter]; i++) {
                free(filter[index_filter][i]);
            }
            free(filter[index_filter]);
            for (i = index_filter; i < nr_filtre - 1; i++) {
                filter[i] = filter[i + 1];
                filter_size[i] = filter_size[i + 1];
            }
            nr_filtre--;
        } else if (strcmp(command, "di") == 0) {
            int index_img = 0;
            scanf("%d", &index_img);
            for (i = 0; i < N[index_img]; i++) {
                for (j = 0; j < M[index_img]; j++) {
                    free(image[index_img][i][j]);
                }
                free(image[index_img][i]);
            }
            free(image[index_img]);
            for (i = index_img; i < count - 1; i++) {
                image[i] = image[i + 1];
                N[i] = N[i + 1];
                M[i] = M[i + 1];
            }
            count--;
        }
    }
    for (int k = 0; k < count; k++) {
        for (i = 0; i < N[k]; i++) {
            for (j = 0; j < M[k]; j++) {
                free(image[k][i][j]);
            }
            free(image[k][i]);
        }
        free(image[k]);
    }
    free(image);
    for (i = 0; i < nr_filtre; i++) {
        for (j = 0; j < filter_size[i]; j++) {
            free(filter[i][j]);
        }
        free(filter[i]);
    }
    free(filter);
    return 0;
}
