#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define LINE_SIZE 10

struct array {
  char **element;
  ssize_t size;
} typedef array;

int part1(array *array) {
  int rotation_amount = 50;
  int total = 0;
  for (int i = 0; i < array->size; i++) {
    char *line = array->element[i];
    int direction = line[0] == 'L' ? -1 : 1;
    int rotation = atoi(array->element[i] + 1);

    rotation_amount += rotation * direction;
    rotation_amount %= 100;
    if (rotation_amount == 0) {
      total++;
    }
  }

  return total;
}

int part2(array *array) {
  int current_rotation = 50;
  int prev = current_rotation;
  int total = 0;
  for (int i = 0; i < array->size; i++) {
    char *line = array->element[i];
    int direction = line[0] == 'L' ? -1 : 1;
    int rotation = atoi(array->element[i] + 1);

    assert(rotation != 0);

    int rotation_left = rotation;
    while (rotation_left > 0) {
      current_rotation += 1 * direction;

      if (current_rotation % 100 == 0) {
        total++;
        current_rotation = 0;
      }

      rotation_left--;
    }

    if (current_rotation < 0) {
      current_rotation = (current_rotation % 100) + 100;
    } else if (current_rotation > 100) {
      current_rotation = (current_rotation % 100) - 100;
    }

    printf("rotation: %d, current_rotation: %d, prev: %d, total: %d\n",
           rotation * direction, current_rotation, prev, total);
    prev = current_rotation;
  }

  return total;
}

int main(int argc, char *argv[]) {
  printf("Hello World!\n");
  if (argc < 2) {
    printf("Argc is too low (%d)\n", argc);
    return EXIT_FAILURE;
  }
  FILE *data = fopen(argv[1], "r");

  if (!data) {
    printf("Failed to open %s\n", argv[1]);
    return EXIT_FAILURE;
  }
  char line[LINE_SIZE];
  int line_amount = 5000;

  array array;
  array.element = malloc(line_amount * sizeof(char *));

  int true_line_amount = 0;
  while (fgets(line, LINE_SIZE, data) != NULL) {
    array.element[true_line_amount] = (char *)malloc(sizeof(line));
    strcpy(array.element[true_line_amount], line);
    true_line_amount++;
  }

  array.size = true_line_amount;

  printf("Running AOC with %zd lines \n", array.size);
  printf("Result part1: %d\n", part1(&array));
  printf("Result part2: %d\n", part2(&array));

  for (int i = 0; i < line_amount; i++) {
    free(array.element[i]);
  }
  free(array.element);

  fclose(data);

  return EXIT_SUCCESS;
}
