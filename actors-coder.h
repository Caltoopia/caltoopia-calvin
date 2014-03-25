//
//  actors-coder.h
//  Calvin
//
//  Created by Per Persson on 2014-03-24.
//
//

#ifndef ACTORS_CODER_H
#define ACTORS_CODER_H

typedef enum CODER_FORMAT {
    JSON_CODER,
    DEBUG_CODER
} ActorCoderFormat;

typedef void CoderState;

/* ==== API sketch ====
 
 Types
 -----
 c : char, int8
 s : C-string
 i : int32
 I : int64
 f : float
 b : boolean
 
 ref = root(this)
 encode(ref, key, value_ptr, type);
 encode_memory(ref, value_ptr, length); // Base64 encoded
 ref' = encode_array(ref, key);
 ref' = encode_struct(ref, key);
 
 */


typedef struct ActorCoder {
    // Public API
    ActorCoderFormat type;
    CoderState *(*init)(struct ActorCoder *this);
    void (*encode)(CoderState *state, const char *key, void *value_ref, const char *type);
    CoderState *(*encode_struct)(CoderState *state, const char *key);
    CoderState *(*encode_array)(CoderState *state, const char *key);
    void (*encode_memory)(CoderState *state, const char *key, void *ptr, size_t length);
    
    // FIXME: Decoding functions corresponding to the above
    void (*decode)(struct ActorCoder *this, void *value_ref, const char *key, const char *type);

    // Semi-private API
    const char *(*_description)(struct ActorCoder *this);
    
    // Private API
    void (*destructor)(struct ActorCoder *this);
} ActorCoder;

ActorCoder *newCoder(ActorCoderFormat fmt);
void destroyCoder(ActorCoder *coder);

#endif // ACTORS_CODER_H
