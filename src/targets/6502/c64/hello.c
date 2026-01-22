#include <stdio.h>

void doCount(int max) {
  for (int c = 0; c < max; c++) {
    printf("%d\t", c);
  }

  printf("\r\n");
}

int main(void) {
  int max;

  printf("Max value: ");
  scanf("%d", &max);

  doCount(max);

  printf("One more hello! max: %d\r\n", max);

  return 0;
}
