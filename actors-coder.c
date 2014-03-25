//
//  actors-coder.c
//  Calvin
//
//  Created by Per Persson on 2014-03-24.
//
//

#include "actors-coder.h"
#include <stdio.h>


typedef struct ActorDebugCoder {
    ActorCoder baseCoder;
    char *storage;
} ActorDebugCoder;


static void debug_encode(void *value_ref, const char *key, const char *type)
{
    fprintf(stderr, "Encoding %s @ %s\n", type, key);
}

static void debug_decode(void *value_ref, const char *key, const char *type)
{
    fprintf(stderr, "Decoding %s @ %s\n", type, key);
}

static const char *string_rep(void)
{
    return "No string rep for debugCoder";
}


ActorCoder *newDebugCoder(void)
{
    ActorDebugCoder *coder = malloc(sizeof(ActorDebugCoder));
    coder->storage = NULL;
    ActorCoder *baseCoder = (ActorCoder *)coder;
    baseCoder->encode = debug_encode;
    baseCoder->decode = debug_decode;
    baseCoder->string_rep = string_rep;
    
    return (ActorCoder *)coder;
}

void destroyCoder(ActorCoder *coder)
{
    // free(coder);
}
