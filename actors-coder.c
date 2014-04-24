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

static CoderState *json_init(struct ActorCoder *this)
{
    ActorJSONCoder *coder = (ActorJSONCoder *)this;

    return (void *)(coder->root);
}

static CoderState *json_encode_struct(CoderState *state, const char *key)
{
    cJSON *object = cJSON_CreateObject();
    cJSON *cj_state = (cJSON *)state;
    
    if (cJSON_Array == cj_state->type) {
        cJSON_AddItemToArray(cj_state, object);
    } else {
        cJSON_AddItemToObject(cj_state, key, object);
    }

    return (void *)object;
}

static CoderState *json_encode_array(CoderState *state, const char *key)
{
    cJSON *object = cJSON_CreateArray();
    cJSON *cj_state = (cJSON *)state;
  
    if (cJSON_Array == cj_state->type) {
        cJSON_AddItemToArray(cj_state, object);
    } else {
        cJSON_AddItemToObject(cj_state, key, object);
    }
  
    return (void *)object;
}

static void json_encode(CoderState *state, const char *key, void *value_ref, const char *type)
{
    cJSON *cj_state = (cJSON *)state;
    
    // Parameter conversion
    cJSON *value = NULL;
    switch (type[0]) {
        case 's': // C string
            value = cJSON_CreateString(*(const char **)value_ref);
            break;
        case 'i': // C int
            value = cJSON_CreateNumber((double)*((int *)value_ref));
            break;
        case 'f': // C float
            value = cJSON_CreateNumber((double)*((float *)value_ref));
            break;
        
        default:
            fprintf(stderr, "Error: Unknown type specifier '%c'\n", type[0]);
            break;
    }
    if (cJSON_Array == cj_state->type) {
        cJSON_AddItemToArray(cj_state, value);
    } else {
        cJSON_AddItemToObject(cj_state, key, value);
    }
}

static void json_encode_memory(CoderState *state, const char *key, void *ptr, size_t length)
{
    cJSON_AddItemToObject((cJSON *)state, key, cJSON_CreateString("FIXME: Base64 encoded data ..."));
}

// FIXME
static void json_decode(CoderState *state, const char *key, void *value_ref, const char *type)
{
    cJSON *cj_state = (cJSON *)state;
    cJSON *value = NULL;

    if (cJSON_Array == cj_state->type) {
      value = cJSON_DetachItemFromArray(cj_state, 0);
    } else {
      value = cJSON_DetachItemFromObject(cj_state, key);
    }
  
    switch (type[0]) {
        case 's': // C string
        {
            *(char **)value_ref = strdup(value->valuestring);
        }
        break;
        case 'i': // C int
        {
            *(int *)value_ref = (int)(value->valueint);
        }
        break;
        case 'f': // C float
        {
            *(float *)value_ref = (float)(value->valuedouble);
        }
        break;
        
        default:
            fprintf(stderr, "Error: Unknown type specifier '%c'\n", type[0]);
            break;
    }
    cJSON_Delete(value);
}

static CoderState *json_decode_struct(CoderState *state, const char *key)
{
  cJSON *cj_state = (cJSON *)state;
  cJSON *object = NULL;
  
  if (cJSON_Array == cj_state->type) {
    object = cJSON_DetachItemFromArray(cj_state, 0);
  } else {
    object = cJSON_DetachItemFromObject(cj_state, key);
  }

  if (cJSON_Object != object->type) {
    fprintf(stderr, "Error: Requested object NOT a struct.");
  }
  
  return (void *)object;
}

static CoderState *json_decode_array(CoderState *state, const char *key)
{
  cJSON *cj_state = (cJSON *)state;
  cJSON *object = NULL;
  
  if (cJSON_Array == cj_state->type) {
    object = cJSON_DetachItemFromArray(cj_state, 0);
  } else {
    object = cJSON_DetachItemFromObject(cj_state, key);
  }

  if (cJSON_Array != object->type) {
    fprintf(stderr, "Error: Requested object NOT an array.");
  }
  
  return (void *)object;
}

void json_decode_memory(CoderState *state, const char *key, void *ptr, size_t length)
{
    // FIXME:
}

void *json_data(struct ActorCoder *this)
{
    ActorJSONCoder *coder = (ActorJSONCoder *)this;
    return coder->root;
}

void json_set_data(struct ActorCoder *this, void *closure)
{
    // If closure is NOT a C string, bad things will happen.
    ActorJSONCoder *coder = (ActorJSONCoder *)this;
    // FIXME: What to do if parse fails?
    cJSON *data = cJSON_Parse(closure);
    if (data) {
        cJSON_Delete(coder->root);
        coder->root = data;
    }
}

static const char *json_string_rep(ActorCoder *this)
{
    ActorJSONCoder *coder = (ActorJSONCoder *)this;
    free(coder->descr);
    coder->descr = cJSON_PrintUnformatted(coder->root);

    return coder->descr;
}

static void json_destructor(ActorCoder *this)
{
    ActorJSONCoder *coder = (ActorJSONCoder *)this;
    cJSON_Delete(coder->root);
    free(coder->descr);
}

ActorCoder *newJSONCoder(void)
{
    ActorJSONCoder *coder = malloc(sizeof(ActorJSONCoder));
    
    coder->root = cJSON_CreateObject();
    coder->descr = NULL;
    
    coder->baseCoder.init = json_init;
    coder->baseCoder.encode = json_encode;
    coder->baseCoder.encode_struct = json_encode_struct;
    coder->baseCoder.encode_array = json_encode_array;
    coder->baseCoder.encode_memory = json_encode_memory;
    
    coder->baseCoder.decode = json_decode;
    coder->baseCoder.decode_struct = json_decode_struct;
    coder->baseCoder.decode_array = json_decode_array;
    coder->baseCoder.decode_memory = json_decode_memory;
  
    coder->baseCoder.data = json_data;
    coder->baseCoder.set_data = json_set_data;

    coder->baseCoder.destructor = json_destructor;
    coder->baseCoder._description = json_string_rep;
    
    return (ActorCoder *)coder;
}



/* ========================================================================= */

#define DEBUG_BUFFER_SIZE 1024

typedef struct ActorDebugCoder {
    ActorCoder baseCoder;
} ActorDebugCoder;

CoderState *debug_init(struct ActorCoder *this)
{
    return NULL;
}

void debug_encode(CoderState *state, const char *key, void *value_ref, const char *type)
{
}

CoderState *debug_encode_struct(CoderState *state, const char *key)
{
    return NULL;
}

CoderState *debug_encode_array(CoderState *state, const char *key)
{
    return NULL;
}

void debug_encode_memory(CoderState *state, const char *key, void *ptr, size_t length)
{
}

void debug_decode(CoderState *state, const char *key, void *value_ref, const char *type)
{
}

void *debug_data(struct ActorCoder *this)
{
    return NULL;
}

void debug_set_data(struct ActorCoder *this, void *closure)
{
}


static const char *debug_string_rep(ActorCoder *this)
{
    return "DEBUG_CODER";
}

ActorCoder *newDebugCoder(void)
{
    ActorDebugCoder *coder = malloc(sizeof(ActorDebugCoder));
    
    coder->baseCoder.init = debug_init;
    coder->baseCoder.encode = debug_encode;
    coder->baseCoder.encode_struct = debug_encode_struct;
    coder->baseCoder.encode_array = debug_encode_array;
    coder->baseCoder.encode_memory = debug_encode_memory;
    
    coder->baseCoder.data = debug_data;
    coder->baseCoder.set_data = debug_set_data;
    
    coder->baseCoder.decode = debug_decode;
    
    coder->baseCoder.destructor = NULL;
    coder->baseCoder._description = debug_string_rep;
    
    return (ActorCoder *)coder;
}

/* ========================================================================= */

ActorCoder *newCoder(ActorCoderFormat fmt)
{
    ActorCoder *coder = NULL;
    
    switch (fmt) {
        case JSON_CODER:
            coder = newJSONCoder();
            break;
        case DEBUG_CODER: // Fallthrough
        default:
            coder = newDebugCoder();
            fmt = DEBUG_CODER;
            break;
    }
    coder->type = fmt;
    return coder;
}


void destroyCoder(ActorCoder *coder)
{
    if (coder->destructor) {
        coder->destructor(coder);
    }
    free(coder);
}



