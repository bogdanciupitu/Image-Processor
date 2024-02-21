# Image-Processor

This project is a simple image processing library implemented in C. It provides several functions for manipulating 3D arrays, which are used to represent color images.

## Functions

- `flip_horizontal`: Flips an image horizontally.
- `rotate_left`: Rotates an image 90 degrees to the left.
- `crop`: Crops an image to a specified rectangle.
- `extend`: Extends the size of an image by adding a border of a specified color around it.
- `paste`: Pastes one image onto another at a specified location.
- `apply_filter`: Applies a convolutional filter to an image.

## Usage

Include `imageprocessing.h` in your C file. Then, call the functions as needed, passing in your image and any other required parameters.

## Makefile

The provided Makefile automates the build and run process of the project. It contains the following rules:

- `run-main`: Runs the `main` executable. If the executable does not exist, it compiles `main.c`, `imageprocessing.c`, and `bmp.c` into an executable named `main` before running it.
- `run-interactive`: Runs the `interactive` executable. If the executable does not exist, it compiles `interactive.c`, `imageprocessing.c`, and `bmp.c` into an executable named `interactive` before running it.
- `interactive`: Compiles `interactive.c`, `imageprocessing.c`, and `bmp.c` into an executable named `interactive`.
- `main`: Compiles `main.c`, `imageprocessing.c`, and `bmp.c` into an executable named `main`.
- `clean`: Removes the `main` and `interactive` executables.

To use this Makefile, you can run one of the following commands in a terminal:

```bash
make run-main
make run-interactive
make clean
```

## Interactive Mode

The `interactive.c` file provides an interactive mode for the image processing library. This mode allows you to load images, apply various transformations, and save the results.

The interactive mode supports the following commands:

- `l`: Load an image from a BMP file.
- `s`: Save an image to a BMP file.
- `ah`: Flip an image horizontally.
- `ar`: Rotate an image 90 degrees to the left.
- `ac`: Crop an image to a specified rectangle.
- `ae`: Extend the size of an image by adding a border of a specified color around it.
- `ap`: Paste one image onto another at a specified location.
- `cf`: Create a convolutional filter.
- `af`: Apply a convolutional filter to an image.
- `df`: Delete a convolutional filter.
- `di`: Delete an image.
- `e`: Exit the interactive mode.

To run the interactive mode, use the `run-interactive` rule in the Makefile:

```bash
make run-interactive
```

## Check16

The `check16.c` file is a test driver for the image processing library. It reads an image from a BMP file, applies a transformation based on a task number, and writes the transformed image to another BMP file.

The transformations are as follows:

- `1`: Flip the image horizontally.
- `2`: Rotate the image 90 degrees to the left.
- `3`: Crop the image to a specified rectangle.
- `4`: Extend the size of the image by adding a border of a specified color around it.
- `5`: Paste another image onto the image at a specified location.
- `6`: Apply a convolutional filter to the image.

The task number and output file name are passed as command-line arguments. The other parameters for the transformations are read from standard input.

To compile and run `check16.c`, use the following commands:

```bash
gcc -o check16 check16.c imageprocessing.c bmp.c -lm
./check16 <task_number> <output_file>
```

