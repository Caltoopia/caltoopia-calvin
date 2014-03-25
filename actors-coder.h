//
//  actors-coder.h
//  Calvin
//
//  Created by Per Persson on 2014-03-24.
//
//

#ifndef ACTORS_CODER_H
#define ACTORS_CODER_H

typedef struct ActorCoder {
    void (*encode)(void *value_ref, const char *key, const char *type);
    void (*decode)(void *value_ref, const char *key, const char *type);
    // Semi-private
    const char *(*string_rep)(void);
} ActorCoder;


ActorCoder *newDebugCoder(void);
void destroyCoder(ActorCoder *coder);

#endif // ACTORS_CODER_H
