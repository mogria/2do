#ifndef _ARRAY_H
#define _ARRAY_H


// allocate memory for an 1 dimensional array
#define ALLOC1(type, varname, size)  do { \
  varname = calloc((size), sizeof(type)); \
} while(0)

// allocate memory for an 2 dimensional array
#define ALLOC2(type, varname, size1, size2)  do { \
  ALLOC1(type*, varname, size1); \
  int y; \
  for(y = 0; y < size1; y++) { \
    ALLOC1(type, varname[y], size2); \
  } \
} while(0)

// grab an part of an 1 dimensional array
#define PART1(dest, source, offset) do {\
  dest = &source[offset]; \
} while(0)

// grab an part of an 2 dimensional array
#define PART2(type, dest, dest_size1, src, offset1, offset2) do {\
  int i; \
  ALLOC1(type*, dest, dest_size1); \
  for(i = 0; i < dest_size1; i++) { \
    PART1(dest[i], src[i + offset1], offset2); \
  } \
} while(0)

// free memory of 1 dimensional array
#define FREE1(varname)  do { \
  free(varname); \
} while(0)

// free memory of 2 dimensional array
#define FREE2(varname, size) do { \
  int y = 0; \
  for(y = 0; y < size; y++) { \
    FREE1(varname[y]); \
  } \
  FREE1(varname); \
} while(0)
 
#endif /* _ARRAY_H */
