// serztop
#ifndef CAL_COMMON_SERZ__TOP
#define CAL_COMMON_SERZ__TOP
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "actors-rts.h"
#include "natives.h"
#define TRUE 1
#define FALSE 0
#define TYPE_DIRECT
typedef struct {
  int32_t len;
  int32_t sz[4];
} __arrayArg;
static inline __arrayArg maxArraySz(__arrayArg* targetSz, __arrayArg* exprSz, int shift) {
    __arrayArg ret;
    if(shift==0) {
        return *exprSz;
    }
    ret.len = targetSz->len;
    memcpy(ret.sz,targetSz->sz,sizeof(int32_t)*4);
    for(int i=0;i<exprSz->len;i++) {
        if(targetSz->sz[i+shift]<exprSz->sz[i])
            ret.sz[i+shift] = exprSz->sz[i];
    }
    return ret;
}
typedef struct {
  union {
  char* p;
  char* (*pp);
  };
  union { struct {
    uint16_t flags;
    uint16_t dim;
  }; uint32_t flags_dim;};
  int32_t sz[4];
} __array4char;
#define TYPE char
#include "__arrayCopy.h"
typedef struct {
  union {
  int8_t* p;
  int8_t* (*pp);
  };
  union { struct {
    uint16_t flags;
    uint16_t dim;
  }; uint32_t flags_dim;};
  int32_t sz[4];
} __array4int8_t;
#define TYPE int8_t
#include "__arrayCopy.h"
typedef struct {
  union {
  uint8_t* p;
  uint8_t* (*pp);
  };
  union { struct {
    uint16_t flags;
    uint16_t dim;
  }; uint32_t flags_dim;};
  int32_t sz[4];
} __array4uint8_t;
#define TYPE uint8_t
#include "__arrayCopy.h"
typedef struct {
  union {
  int16_t* p;
  int16_t* (*pp);
  };
  union { struct {
    uint16_t flags;
    uint16_t dim;
  }; uint32_t flags_dim;};
  int32_t sz[4];
} __array4int16_t;
#define TYPE int16_t
#include "__arrayCopy.h"
typedef struct {
  union {
  uint16_t* p;
  uint16_t* (*pp);
  };
  union { struct {
    uint16_t flags;
    uint16_t dim;
  }; uint32_t flags_dim;};
  int32_t sz[4];
} __array4uint16_t;
#define TYPE uint16_t
#include "__arrayCopy.h"
typedef struct {
  union {
  int32_t* p;
  int32_t* (*pp);
  };
  union { struct {
    uint16_t flags;
    uint16_t dim;
  }; uint32_t flags_dim;};
  int32_t sz[4];
} __array4int32_t;
#define TYPE int32_t
#include "__arrayCopy.h"
typedef struct {
  union {
  uint32_t* p;
  uint32_t* (*pp);
  };
  union { struct {
    uint16_t flags;
    uint16_t dim;
  }; uint32_t flags_dim;};
  int32_t sz[4];
} __array4uint32_t;
#define TYPE uint32_t
#include "__arrayCopy.h"
typedef struct {
  union {
  double* p;
  double* (*pp);
  };
  union { struct {
    uint16_t flags;
    uint16_t dim;
  }; uint32_t flags_dim;};
  int32_t sz[4];
} __array4double;
#define TYPE double
#include "__arrayCopy.h"
typedef struct {
  union {
  void* p;
  void* (*pp);
  };
  union { struct {
    uint16_t flags;
    uint16_t dim;
  }; uint32_t flags_dim;};
  int32_t sz[4];
} __array4void;
#define TYPE void
#include "__arrayCopy.h"
typedef struct {
  union {
  bool_t* p;
  bool_t* (*pp);
  };
  union { struct {
    uint16_t flags;
    uint16_t dim;
  }; uint32_t flags_dim;};
  int32_t sz[4];
} __array4bool_t;
#define TYPE bool_t
#include "__arrayCopy.h"
#undef TYPE_DIRECT
typedef struct T1_s T1_t;
typedef struct T2_s T2_t;
typedef struct {
  union {
    T1_t* p;
    T1_t* (*pp);
  };
  union { struct {
    uint16_t flags;
    uint16_t dim;
  }; uint32_t flags_dim;};
  int32_t sz[4];
} __array4T1_t;
int freeStructT1_t(T1_t * src, int top);
int copyStructT1_t(T1_t ** dst, T1_t * src);
int constructT1___A(T1_t ** dst, int32_t a, int32_t b);
int constructT1___B(T1_t ** dst, int32_t a, int32_t c);
char* serializeStructT1_t(T1_t * src, char* dstbuf);
char* deserializeStructT1_t(T1_t ** dst, char* srcbuf);
long sizeStructT1_t(T1_t * src);
#define TYPE T1_t
#include "__arrayCopy.h"
typedef struct {
  union {
    T2_t* p;
    T2_t* (*pp);
  };
  union { struct {
    uint16_t flags;
    uint16_t dim;
  }; uint32_t flags_dim;};
  int32_t sz[4];
} __array4T2_t;
int freeStructT2_t(T2_t * src, int top);
int copyStructT2_t(T2_t ** dst, T2_t * src);
int constructT2___A(T2_t ** dst, T1_t* a, __array4int32_t b);
int constructT2___B(T2_t ** dst, int32_t a, T1_t* c);
char* serializeStructT2_t(T2_t * src, char* dstbuf);
char* deserializeStructT2_t(T2_t ** dst, char* srcbuf);
long sizeStructT2_t(T2_t * src);
#define TYPE T2_t
#include "__arrayCopy.h"
enum T1_tags {
  T1___none=0,
  T1___A,
  T1___B
};

struct T1_s {
  uint32_t flags;
  enum T1_tags tag;
  union {
    struct {
      int32_t a;
      int32_t b;
    } A;
    struct {
      int32_t a;
      int32_t c;
    } B;
  } members;
};
enum T2_tags {
  T2___none=0,
  T2___A,
  T2___B
};

struct T2_s {
  uint32_t flags;
  enum T2_tags tag;
  union {
    struct {
      T1_t* a;
      __array4int32_t b;
    } A;
    struct {
      int32_t a;
      T1_t* c;
    } B;
  } members;
};
#endif