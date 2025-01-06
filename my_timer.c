#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <my_timer.h>

static struct timeval ti;

void initTimer(void) {
  gettimeofday(&ti, (struct timezone*) 0);
}

double getElapsedTime(void) {
  struct timeval t;
  double diff;
  gettimeofday(&t, (struct timezone*) 0);
  diff = (t.tv_sec - ti.tv_sec) * 1000000
    + (t.tv_usec - ti.tv_usec);
  return diff/1000000.;
}
