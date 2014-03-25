//
//  actors-coder.c
//  Calvin
//
//  Created by Per Persson on 2014-03-24.
//
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "actors-coder.h"
#include "cJSON.h"

/* ========================================================================= */

typedef struct ActorJSONCoder {
    ActorCoder baseCoder;
    cJSON *root;
    char *descr;
} ActorJSONCoder;

static void json_encode(ActorCoder *this, void *value_ref, const char *key, const char *type)
{
    ActorJSONCoder *coder = (ActorJSONCoder *)this;
    
    switch (type[0]) {
        case 's': // C string
            cJSON_AddItemToObject(coder->root, key, cJSON_CreateString(value_ref));
            break;
            
        default:
            fprintf(stderr, "Error: Unknown type specifier '%c' in type specifier\n", type[0]);
            break;
    }
}

static void json_decode(ActorCoder *this, void *value_ref, const char *key, const char *type)
{
    ActorJSONCoder *coder = (ActorJSONCoder *)this;
}

static const char *json_string_rep(ActorCoder *this)
{
    ActorJSONCoder *coder = (ActorJSONCoder *)this;
    free(coder->descr);
    coder->descr = cJSON_Print(coder->root);

    return coder->descr;
}


ActorCoder *newJSONCoder(void)
{
    ActorJSONCoder *coder = malloc(sizeof(ActorJSONCoder));
    
    coder->root = cJSON_CreateObject();
    // cJSON *item;
    // cJSON_AddItemToObject(coder->root, "header", item = cJSON_CreateObject());
	// cJSON_AddStringToObject(item, "key", "value");
    coder->descr = NULL;
    
    
    coder->baseCoder.encode = json_encode;
    coder->baseCoder.decode = json_decode;
    coder->baseCoder._description = json_string_rep;
    
    return (ActorCoder *)coder;
}



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
