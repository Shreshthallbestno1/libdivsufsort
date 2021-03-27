/*
 * Code modified from documentation of libdivsufsort:
 * Example Usage
 * https://github.com/y-256/libdivsufsort
 */


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include <divsufsort.h>

int main() {
  //build a random input string of length 150 million
  srand(time(NULL));
  char *Text = malloc(150000000*sizeof(char));
  for( int i = 0; i < 150000000; ++i){
    Text[i] = '0' + rand()%72; // starting on '0', ending on '}'
  }
  int n = strlen(Text);

  // allocate
  int *SA = (int *)malloc(n * sizeof(int));

  // sort
  divsufsort((unsigned char *)Text, SA, n);

  printf("SA built successfully\n");

  // deallocate
  free(SA);

  return 0;
}
