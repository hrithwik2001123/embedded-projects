#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>
//#include <sys/time.h>
//#include <sys/times.h>

// Define missing error codes if not defined
#ifndef ECHILD
#define ECHILD 10
#endif

#ifndef ENOENT
#define ENOENT 2
#endif

#ifndef EMLINK
#define EMLINK 31
#endif

#ifndef EAGAIN
#define EAGAIN 11
#endif
