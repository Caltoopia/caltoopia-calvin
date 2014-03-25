//
//  actors-coder.h
//  Calvin
//
//  Created by Per Persson on 2014-03-24.
//
//

#ifndef ACTORS_CODER_H
#define ACTORS_CODER_H

// FIXME: Add type info to struct
typedef struct ActorCoder {
    void (*encode)(struct ActorCoder *this, void *value_ref, const char *key, const char *type);
    void (*decode)(struct ActorCoder *this, void *value_ref, const char *key, const char *type);
    // Semi-private
    const char *(*_description)(struct ActorCoder *this);
} ActorCoder;

// FIXME: Make format a parameter
ActorCoder *newDebugCoder(void);
ActorCoder *newJSONCoder(void);

void destroyCoder(ActorCoder *coder);

#endif // ACTORS_CODER_H
