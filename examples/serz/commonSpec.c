// serztop
#include "commonSpec.h"
/*NOT USED dprint_trace2*/
int freeStructT1_t (T1_t * src, int top) {
  if(src==NULL) return FALSE;
  switch(src->tag) {
  case T1___A:
    break;
  case T1___B:
    break;
  default:
    break;
  }
  if(top && (src->flags&0x1)==0x1) {
    free(src);
  }
  return TRUE;
}

int copyStructT1_t (T1_t ** dst, T1_t * src) {
  if((src->flags&0x3)==0x3) {
    if(*dst!=NULL) {
      freeStructT1_t(*dst,TRUE);
    }
    *dst = src;
    return TRUE;
  }
  int flags;
  if(*dst==NULL) {
    *dst = calloc(sizeof(**dst),1);
    flags = 0x1;
  } else {
    flags = (*dst)->flags;
  }
  memcpy(*dst,src,sizeof(**dst));
  (*dst)->flags = flags;
  switch(src->tag) {
  case T1___A:
    break;
  case T1___B:
    break;
  default:
    break;
  }
  return TRUE;
}

int constructT1___A(T1_t ** dst, int32_t a, int32_t b) {
  if(*dst==NULL) {
    *dst = calloc(sizeof(**dst),1);
  }
  (*dst)->flags = 0x1;
  (*dst)->tag = T1___A;
  (*dst)->members.A.a = a;
  (*dst)->members.A.b = b;
  return TRUE;
}

int constructT1___B(T1_t ** dst, int32_t a, int32_t c) {
  if(*dst==NULL) {
    *dst = calloc(sizeof(**dst),1);
  }
  (*dst)->flags = 0x1;
  (*dst)->tag = T1___B;
  (*dst)->members.B.a = a;
  (*dst)->members.B.c = c;
  return TRUE;
}

char * serializeStructT1_t(T1_t * src, char* dstbuf) {
  char * p = dstbuf;
  *(enum T1_tags*)p = src->tag;
  p = (char*)((enum T1_tags*)p + 1);
  switch(src->tag) {
  case T1___A:
    *(int32_t*)p = src->members.A.a;
    p = (char*)((int32_t*)p + 1);
    *(int32_t*)p = src->members.A.b;
    p = (char*)((int32_t*)p + 1);
    break;
  case T1___B:
    *(int32_t*)p = src->members.B.a;
    p = (char*)((int32_t*)p + 1);
    *(int32_t*)p = src->members.B.c;
    p = (char*)((int32_t*)p + 1);
    break;
  default:
    break;
  }
  return p;
}

char * deserializeStructT1_t(T1_t ** dst, char* srcbuf) {
  char * p = srcbuf;
  *dst = calloc(sizeof(**dst),1);
  (*dst)->flags = 0x1;
  (*dst)->tag = *(enum T1_tags*) p;
  p = (char*)((enum T1_tags*)p + 1);
  switch((*dst)->tag) {
  case T1___A:
    (*dst)->members.A.a = *(int32_t*)p;
    p = (char*)((int32_t*)p + 1);
    (*dst)->members.A.b = *(int32_t*)p;
    p = (char*)((int32_t*)p + 1);
    break;
  case T1___B:
    (*dst)->members.B.a = *(int32_t*)p;
    p = (char*)((int32_t*)p + 1);
    (*dst)->members.B.c = *(int32_t*)p;
    p = (char*)((int32_t*)p + 1);
    break;
  default:
    break;
  }
  return p;
}

long sizeStructT1_t(T1_t * src) {
  long ret = 0;
  ret += sizeof(enum T1_tags);
  switch(src->tag) {
  case T1___A:
    ret += sizeof(src->members.A.a);
    ret += sizeof(src->members.A.b);
    break;
  case T1___B:
    ret += sizeof(src->members.B.a);
    ret += sizeof(src->members.B.c);
    break;
  default:
    break;
  }
  return ret;
}

int freeStructT2_t (T2_t * src, int top) {
  if(src==NULL) return FALSE;
  switch(src->tag) {
  case T2___A:
    freeStructT1_t(src->members.A.a, TRUE);
    freeint32_t(&src->members.A.b, TRUE);
    break;
  case T2___B:
    freeStructT1_t(src->members.B.c, TRUE);
    break;
  default:
    break;
  }
  if(top && (src->flags&0x1)==0x1) {
    free(src);
  }
  return TRUE;
}

int copyStructT2_t (T2_t ** dst, T2_t * src) {
  if((src->flags&0x3)==0x3) {
    if(*dst!=NULL) {
      freeStructT2_t(*dst,TRUE);
    }
    *dst = src;
    return TRUE;
  }
  int flags;
  if(*dst==NULL) {
    *dst = calloc(sizeof(**dst),1);
    flags = 0x1;
  } else {
    flags = (*dst)->flags;
  }
  memcpy(*dst,src,sizeof(**dst));
  (*dst)->flags = flags;
  switch(src->tag) {
  case T2___A:
    (*dst)->members.A.b.flags = 0x0;
    copyint32_t(&(*dst)->members.A.b, &src->members.A.b, (__arrayArg){0,{}}, (__arrayArg){0,{}}, (__arrayArg){src->members.A.b.dim,{src->members.A.b.sz[0],src->members.A.b.sz[1],src->members.A.b.sz[2],src->members.A.b.sz[3]}});
    break;
  case T2___B:
    break;
  default:
    break;
  }
  return TRUE;
}

int constructT2___A(T2_t ** dst, T1_t* a, __array4int32_t b) {
  if(*dst==NULL) {
    *dst = calloc(sizeof(**dst),1);
  }
  (*dst)->flags = 0x1;
  (*dst)->tag = T2___A;
  copyStructT1_t(&(*dst)->members.A.a, a);
  copyint32_t(&(*dst)->members.A.b, &b, (__arrayArg){0,{}}, (__arrayArg){0,{}}, (__arrayArg){b.dim,{b.sz[0],b.sz[1],b.sz[2],b.sz[3]}});
  return TRUE;
}

int constructT2___B(T2_t ** dst, int32_t a, T1_t* c) {
  if(*dst==NULL) {
    *dst = calloc(sizeof(**dst),1);
  }
  (*dst)->flags = 0x1;
  (*dst)->tag = T2___B;
  (*dst)->members.B.a = a;
  copyStructT1_t(&(*dst)->members.B.c, c);
  return TRUE;
}

char * serializeStructT2_t(T2_t * src, char* dstbuf) {
  char * p = dstbuf;
  *(enum T2_tags*)p = src->tag;
  p = (char*)((enum T2_tags*)p + 1);
  switch(src->tag) {
  case T2___A:
    p = serializeStructT1_t(src->members.A.a, p);
    p = serializeEachint32_t(&src->members.A.b, p);
    break;
  case T2___B:
    *(int32_t*)p = src->members.B.a;
    p = (char*)((int32_t*)p + 1);
    p = serializeStructT1_t(src->members.B.c, p);
    break;
  default:
    break;
  }
  return p;
}

char * deserializeStructT2_t(T2_t ** dst, char* srcbuf) {
  char * p = srcbuf;
  *dst = calloc(sizeof(**dst),1);
  (*dst)->flags = 0x1;
  (*dst)->tag = *(enum T2_tags*) p;
  p = (char*)((enum T2_tags*)p + 1);
  switch((*dst)->tag) {
  case T2___A:
    p = deserializeStructT1_t(&(*dst)->members.A.a, p);
    p = deserializeEachint32_t(&(*dst)->members.A.b, p);
    break;
  case T2___B:
    (*dst)->members.B.a = *(int32_t*)p;
    p = (char*)((int32_t*)p + 1);
    p = deserializeStructT1_t(&(*dst)->members.B.c, p);
    break;
  default:
    break;
  }
  return p;
}

long sizeStructT2_t(T2_t * src) {
  long ret = 0;
  ret += sizeof(enum T2_tags);
  switch(src->tag) {
  case T2___A:
    ret += sizeStructT1_t(src->members.A.a);
    ret += sizeEachint32_t(&src->members.A.b);
    break;
  case T2___B:
    ret += sizeof(src->members.B.a);
    ret += sizeStructT1_t(src->members.B.c);
    break;
  default:
    break;
  }
  return ret;
}

/*NOT USED dprint2*/
/*NOT USED dprint*/
/*NOT USED printInt*/
/*NOT USED dprint1*/
/*NOT USED println*/
/*NOT USED dprintc*/
/*NOT USED dprint_trace*/
/*NOT USED printStr*/
/*NOT USED dprint_trace3*/
/*NOT USED dprint_trace1*/
/*NOT USED dprint3*/