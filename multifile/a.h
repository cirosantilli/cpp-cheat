#ifndef A_H
#define A_H

// The standard way to share a function across multiple files.
// Must declare, not define it on the header so that all files see it.
void a();

// BAD idea: will define the function multiple times if this is included twice.
//void a() {};

// BAD idea: if included twice will give multiple definition error.
//int aHInt = 0;

static int aHStaticInt = 0;

extern int externInt;

#ifdef DEF
  int def;
#endif

#endif
