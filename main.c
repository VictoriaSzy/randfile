#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

int generate_random() {
  int x = open("/dev/random", O_RDONLY) ;
  int * y = malloc(sizeof(int)) ;
  read(x, y, 4) ;
  close(x) ;
  int n = *y ;
  free(y) ;
  return n ;
}

int main() {
  printf("Generating random numbers:\n") ;
  printf("***These will be the numbers in the first array called a\n") ;
  int * a = malloc(10 * sizeof(int)) ;
  int * b = malloc(10 * sizeof(int)) ;
  int x ;
  for (x = 0 ; x < 10 ; x++) {
    a[x] = generate_random() ;
    printf("random %d: %d\n", x, a[x]) ;
  }
  printf("\n\nWriting numbers to file...\n") ;
  int y = open("test.txt", O_WRONLY | O_CREAT, 0644);
  if (y == -1) printf("NOT GOOD. The file cannot be opened!!") ;
  if (write(y, a, 10 * sizeof(int)) == -1) printf("NOT GOOD. We can't write to the file!") ;
  close(y) ;
  printf("\nReading numbers from file...\n") ;
  y = open("test.txt", O_RDONLY) ;
  if (read(y, b, 10 * sizeof(int)) == -1) printf("NOT GOOD. We can't read the file!!") ;
  close(y) ;
  printf("\nVerification that written values were the same:\n") ;
  printf("Here are the values of the second array which come from the file:\n") ;
  for (x = 0 ; x < 10 ; x ++) {
    printf("index %d: %d\n", x, b[x]) ;
  }
}
