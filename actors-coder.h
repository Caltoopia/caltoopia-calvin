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

typedef struct ActorCoder {
    ActorCoderFormat type;
    void (*encode)(struct ActorCoder *this, void *value_ref, const char *key, const char *type);
    void (*decode)(struct ActorCoder *this, void *value_ref, const char *key, const char *type);
    // Semi-private
    const char *(*_description)(struct ActorCoder *this);
    // Private
    void (*destructor)(struct ActorCoder *this);
} ActorCoder;

ActorCoder *newCoder(ActorCoderFormat fmt);
void destroyCoder(ActorCoder *coder);

#endif // ACTORS_CODER_H
