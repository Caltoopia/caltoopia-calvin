//
//  accumulate.c
//  Calvin
//
//  Created by Per Persson on 2014-03-31.
//
//

#include "actors-rts.h"
#include "natives.h"
#include "Example__toppen.h"

#define  IN0_In ART_INPUT(0)
#define  OUT0_Out ART_OUTPUT(0)

//Actor state
typedef struct {
    AbstractActorInstance base;
    int _fsmState;
    int32_t sum;
} ActorInstance_accumulate;

//Actor functions
ART_ACTION_CONTEXT(1, 1)

ART_ACTION(action0, ActorInstance_accumulate);
ART_ACTION_SCHEDULER(accumulate_action_scheduler);
static void ActorInstance_accumulate_constructor(AbstractActorInstance *);

static const PortDescription inputPortDescriptions[]={
    {0, "In", sizeof(int32_t)},
};
static const PortDescription outputPortDescriptions[]={
    {0, "Out", sizeof(int32_t)},
};

static const int portRate_in_action0[] = {1};

static const int portRate_out_action0[] = {1};

static const ActionDescription actionDescriptions[] = {
    {"action0", portRate_in_action0, portRate_out_action0},
};

static void serialize(AbstractActorInstance *actor, ActorCoder *coder)
{
    ActorInstance_accumulate *this = (ActorInstance_accumulate *)actor;
    CoderState *state = coder->init(coder);
    
    // fsmState
    coder->encode(state, "_fsmState", &this->_fsmState, "i");
    coder->encode(state, "sum", &this->sum, "i");

};


ActorClass klass = INIT_ActorClass(
                                   "accumulate",
                                   ActorInstance_accumulate,
                                   ActorInstance_accumulate_constructor,
                                   0, //setParam not needed anymore (we instantiate with params)
                                   serialize,
                                   accumulate_action_scheduler,
                                   0, // no destructor
                                   1, inputPortDescriptions,
                                   1, outputPortDescriptions,
                                   1, actionDescriptions
                                   );


//
ART_ACTION(action0, ActorInstance_accumulate) {
    int32_t x;
    int32_t U__0;
    ART_ACTION_ENTER(action0, 0);
    x = pinRead_int32_t(IN0_In);
    U__0 = (x + thisActor->sum);
    thisActor->sum = U__0;
    pinWrite_int32_t(OUT0_Out, U__0);
    ART_ACTION_EXIT(action0, 0);
}

#define ActorInstance_accumulate__defaultState_ID 0
static void ActorInstance_accumulate_constructor(AbstractActorInstance *pBase) {
    ActorInstance_accumulate *thisActor=(ActorInstance_accumulate*) pBase;
    thisActor->_fsmState = ActorInstance_accumulate__defaultState_ID;//Initial state
    {
    }
    
}
static const int exitcode_block_Any[3]={1,0,1};
ART_ACTION_SCHEDULER(accumulate_action_scheduler) {
    const int *result = EXIT_CODE_YIELD;
    ActorInstance_accumulate *thisActor=(ActorInstance_accumulate*) pBase;
    ART_ACTION_SCHEDULER_ENTER(1, 1)
    while(1) {
        if ((pinAvailIn_int32_t(IN0_In) >= 1)) {
            if ((pinAvailOut_int32_t(OUT0_Out) >= 1)) {
                ART_FIRE_ACTION(action0);
                continue;
                
            } else {
                result = exitcode_block_Any;
                goto out;
            }
        }
        switch(thisActor->_fsmState) {
            case ActorInstance_accumulate__defaultState_ID:
                result = exitcode_block_Any;
                goto out;
                break;
                
        }
    }
out:
    ART_ACTION_SCHEDULER_EXIT(1, 1)
    return result;
}
