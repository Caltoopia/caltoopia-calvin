//
//  actors-coder.c
//  Calvin
//
//  Created by Per Persson on 2014-03-24.
//
//

#include "actors-coder.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* ========================================================================= */

#define DEBUG_BUFFER_SIZE 1024

typedef struct ActorDebugCoder {
    ActorCoder baseCoder;
    char *storage;
    int writepos;
} ActorDebugCoder;

static void debug_encode(ActorCoder *this, void *value_ref, const char *key, const char *type)
{
    ActorDebugCoder *coder = (ActorDebugCoder *)this;
    char *dst = &coder->storage[coder->writepos];
    size_t limit = DEBUG_BUFFER_SIZE - coder->writepos - 1;
    if (limit > 0) {
        int written = snprintf(dst, limit, "Encoding %s @ %s\n", type, key);
        if (written > 0) {
            coder->writepos += written;
        }
    }
}

static void debug_decode(ActorCoder *this, void *value_ref, const char *key, const char *type)
{
    ActorDebugCoder *coder = (ActorDebugCoder *)this;
    char *dst = &coder->storage[coder->writepos];
    size_t limit = DEBUG_BUFFER_SIZE - coder->writepos - 1;
    if (limit > 0) {
        int written = snprintf(dst, limit, "Decoding %s @ %s\n", type, key);
        if (written > 0) {
            coder->writepos += written;
        }
    }
}

static const char *debug_string_rep(ActorCoder *this)
{
    ActorDebugCoder *coder = (ActorDebugCoder *)this;

    return coder->storage;
}


ActorCoder *newDebugCoder(void)
{
    ActorDebugCoder *coder = malloc(sizeof(ActorDebugCoder));
    
    coder->storage = calloc(DEBUG_BUFFER_SIZE, sizeof(char));
    coder->writepos = 0;
 
    coder->baseCoder.decode = debug_decode;
    coder->baseCoder.encode = debug_encode;
    coder->baseCoder._description = debug_string_rep;
    
    return (ActorCoder *)coder;
}

/* ========================================================================= */

void destroyCoder(ActorCoder *coder)
{
    // free(coder);
}
