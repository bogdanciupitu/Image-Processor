#include <stdio.h>
#include <stdlib.h>
#include "imageprocessing.h"
#include "bmp.h"

int main(int argc, char **argv) {
    if (argc < 3) {
        printf("Usage: ./check <task_number> <output_file>\n");
        return 1;
    }

    int task = atoi(argv[1]);
    char *output_file = argv[2];
    
    char image_path[100];
    int N, M;
    int x, y, h, w;
    int rows, cols, new_R, new_G, new_B;
    int filter_size;
    float **filter;

	char image_path2[100];
	int N2, M2;
	int ***image2;
	
    scanf("%s %d %d", image_path, &N, &M);

    // Allocate memory for the image
    int ***image = (int ***)malloc(N * sizeof(int **));
    for (int i = 0; i < N; i++) {
        image[i] = (int **)malloc(M * sizeof(int *));
        for (int j = 0; j < M; j++) {
            image[i][j] = (int *)malloc(3 * sizeof(int));
        }
    }

    // Read the image
    read_from_bmp(image, N, M, image_path);

    // Apply the transformation based on the task number
    switch (task) {
        case 1:
            image = flip_horizontal(image, N, M);
            break;
        case 2:
            image = rotate_left(image, N, M);
            int aux = N;
            N = M;
            M = aux;
            break;
        case 3:
            scanf("%d %d %d %d", &x, &y, &w, &h);
            image = crop(image, N, M, x, y, h, w);
            N = h;
            M = w;
            break;
        case 4:
            scanf("%d %d %d %d %d", &rows, &cols, &new_R, &new_G, &new_B);
            image = extend(image, N, M, rows, cols, new_R, new_G, new_B);
            N = N + 2 * rows;
            M = M + 2 * cols;
            break;
        case 5:
            scanf("%s %d %d", image_path2, &N2, &M2);
            image2 = (int ***)malloc(N2 * sizeof(int **));
            for (int i = 0; i < N2; i++) {
                image2[i] = (int **)malloc(M2 * sizeof(int *));
                for (int j = 0; j < M2; j++) {
                    image2[i][j] = (int *)malloc(3 * sizeof(int));
                }
            }

            read_from_bmp(image2, N2, M2, image_path2);
            scanf("%d %d", &x, &y);

            image = paste(image, N, M, image2, N2, M2, x, y);
            for (int i = 0; i < N2; i++) {
                for (int j = 0; j < M2; j++) {
                    free(image2[i][j]);
                }
                free(image2[i]);
            }
            free(image2);
            break;
        case 6:
            scanf("%d", &filter_size);
            filter = (float **)malloc(filter_size * sizeof(float *));
            for (int i = 0; i < filter_size; i++) {
                filter[i] = (float *)malloc(filter_size * sizeof(float));
                for (int j = 0; j < filter_size; j++) {
                    scanf("%f", &filter[i][j]);
                }
            }
            image = apply_filter(image, N, M, filter, filter_size);
            break;
        default:
            printf("Invalid task number.\n");
            return 1;
    }

    // Save the transformed image
    write_to_bmp(image, N, M, output_file);

    // Free memory
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            free(image[i][j]);
        }
        free(image[i]);
    }
    free(image);

    return 0;
}
