//
//  timed_counter.c
//  Calvin
//
//  Created by Per Persson on 2014-04-02.
//
//

#include "actors-rts.h"
// #include "Example__toppen.h"
#include <sys/time.h>


static int32_t _now_ms(void)
{
    struct timeval tv;
    if (gettimeofday(&tv, NULL)) {
        return 0;
    }
    int32_t ms = tv.tv_sec * 1000;
    ms += tv.tv_usec/1000;
    
    return ms;
}
    
//Actor state
typedef struct {
    AbstractActorInstance base;
    int _fsmState;
    int32_t counter;
    int32_t next_firing;
    int32_t firing_interval;
    
} ActorInstance_timed_counter;

//Actor functions

// Expands to: nothing
ART_ACTION_CONTEXT(1, 1)

// Expands to prototype:
// static void action0(ActorInstance_timed_counter *thisActor);
ART_ACTION(action0, ActorInstance_timed_counter);

// Expands to prototype:
// static const int *timed_counter_action_scheduler(AbstractActorInstance *pBase);
ART_ACTION_SCHEDULER(timed_counter_action_scheduler);

static void ActorInstance_timed_counter_constructor(AbstractActorInstance *);

static const PortDescription outputPortDescriptions[]={
    {0, "Out", sizeof(int32_t)},
};

static const int portRate_out_action0[] = {1};

static const ActionDescription actionDescriptions[] = {
    {"action0", 0, portRate_out_action0},
};

static void serialize(AbstractActorInstance *actor, ActorCoder *coder)
{
    ActorInstance_timed_counter *this = (ActorInstance_timed_counter *)actor;
    CoderState *state = coder->init(coder);
    // fsmState
    coder->encode(coder, state, "_fsmState", &this->_fsmState, "i");
    coder->encode(coder, state, "counter", &this->counter, "i");
    coder->encode(coder, state, "next_firing", &this->next_firing, "i");
    coder->encode(coder, state, "firing_interval", &this->firing_interval, "i");
    
};

static void deserialize(AbstractActorInstance *actor, ActorCoder *coder)
{
    ActorInstance_timed_counter *this = (ActorInstance_timed_counter *)actor;
    CoderState *state = coder->data(coder);
    coder->decode(coder, state, "_fsmState", (void *)&this->_fsmState, "i");
    coder->decode(coder, state, "counter", (void *)&this->counter, "i");
    coder->decode(coder, state, "next_firing", (void *)&this->next_firing, "i");
    coder->decode(coder, state, "firing_interval", (void *)&this->firing_interval, "i");
    
};

ActorClass klass = INIT_ActorClass(
                                   "timed_counter",
                                   ActorInstance_timed_counter,
                                   ActorInstance_timed_counter_constructor,
                                   0, //setParam not needed anymore (we instantiate with params)
                                   serialize,
                                   deserialize,
                                   timed_counter_action_scheduler,
                                   0, // no destructor
                                   0, NULL,
                                   1, outputPortDescriptions,
                                   1, actionDescriptions
                                   );


// static void action0(ActorInstance_timed_counter *thisActor)
ART_ACTION(action0, ActorInstance_timed_counter)
{
    ART_ACTION_ENTER(action0, 0);
    
    int32_t U__0 = thisActor->counter + 1;
    thisActor->counter = U__0;
    
    pinWrite_int32_t(ART_OUTPUT(0), U__0);
    
    ART_ACTION_EXIT(action0, 0);
}

#define ActorInstance_timed_counter__defaultState_ID 0

static void ActorInstance_timed_counter_constructor(AbstractActorInstance *pBase)
{
    ActorInstance_timed_counter *thisActor = (ActorInstance_timed_counter *)pBase;
    thisActor->_fsmState = ActorInstance_timed_counter__defaultState_ID;
    thisActor->counter = 0;
    thisActor->next_firing = _now_ms(); // Fire ASAP first time around
    thisActor->firing_interval = 1000;   // milliseconds
}

static const int exitcode_block_Any[3] = {1, 0, 1};

ART_ACTION_SCHEDULER(timed_counter_action_scheduler)
{
    const int *result = exitcode_block_Any;
    ActorInstance_timed_counter *thisActor = (ActorInstance_timed_counter *)pBase;
    
    ART_ACTION_SCHEDULER_ENTER(0, 1)
    
    int32_t now = _now_ms();
    
    if (now >= thisActor->next_firing) {
        if ((pinAvailOut_int32_t(ART_OUTPUT(0)) > 0)) {
            ART_FIRE_ACTION(action0);
            // Update firing based on the time of this firing; alternatively,
            // the next firing could be based on the last wanted firing time.
            thisActor->next_firing = now + thisActor->firing_interval;
            result = EXIT_CODE_YIELD;
        } else {
            // Can't fire because no room in output buffer
        }
    } else {
        // Basically blocked by the sands of time
    }
    
    ART_ACTION_SCHEDULER_EXIT(0, 1)
    return result;
}
