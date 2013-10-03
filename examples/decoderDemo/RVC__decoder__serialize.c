#include "actors-rts.h"
#include "natives.h"
#include "RVC__decoderDemo.h"
#define  IN0_in8 ART_INPUT(0)
#define  OUT0_out ART_OUTPUT(0)

//Actor constants

//Actor state
typedef struct {
  AbstractActorInstance base;
  int _fsmState;
  int32_t count;
  int32_t buf;
} ActorInstance_RVC_decoder__serialize;

//Actor functions
ART_ACTION_CONTEXT(1, 1)

ART_ACTION(action0__reload, ActorInstance_RVC_decoder__serialize);
ART_ACTION(action1__shift, ActorInstance_RVC_decoder__serialize);
ART_ACTION_SCHEDULER(RVC_decoder__serialize_action_scheduler);
static void ActorInstance_RVC_decoder__serialize_constructor(AbstractActorInstance *);

static const PortDescription inputPortDescriptions[]={
  {0, "in8", sizeof(int32_t)},
};
static const PortDescription outputPortDescriptions[]={
  {0, "out", sizeof(bool_t)},
};

static const int portRate_in_action0__reload[] = {1};

static const int portRate_out_action0__reload[] = {0};

static const int portRate_in_action1__shift[] = {0};

static const int portRate_out_action1__shift[] = {1};

static const ActionDescription actionDescriptions[] = {
  {"action0__reload", portRate_in_action0__reload, portRate_out_action0__reload},
  {"action1__shift", portRate_in_action1__shift, portRate_out_action1__shift},
};

ActorClass klass=INIT_ActorClass(
  "RVC_decoder__serialize",
  ActorInstance_RVC_decoder__serialize,
  ActorInstance_RVC_decoder__serialize_constructor,
  0, //setParam not needed anymore (we instantiate with params)
  RVC_decoder__serialize_action_scheduler,
  0, // no destructor
  1, inputPortDescriptions,
  1, outputPortDescriptions,
  2, actionDescriptions
);

bool_t RVC_decoder__serialize__DOLLAR__d7932(art_action_context_t *context, ActorInstance_RVC_decoder__serialize *thisActor) {
  {
    bool_t ret;
    ret = (thisActor->count == 0);
    return ret;
  }
}

// reload
ART_ACTION(action0__reload, ActorInstance_RVC_decoder__serialize) {
  int32_t i;
  ART_ACTION_ENTER(action0__reload, 0);
  i = pinRead_int32_t(IN0_in8);
  thisActor->buf = i;
  thisActor->count = 8;
  dprint1("Read byte 0x%x \n", thisActor->buf);
  ART_ACTION_EXIT(action0__reload, 0);
}

bool_t RVC_decoder__serialize__DOLLAR__d7940(art_action_context_t *context, ActorInstance_RVC_decoder__serialize *thisActor) {
  {
    bool_t ret;
    ret = (thisActor->count != 0);
    return ret;
  }
}

// shift
ART_ACTION(action1__shift, ActorInstance_RVC_decoder__serialize) {
  bool_t bit;
  ART_ACTION_ENTER(action1__shift, 1);
  bit = (bitand(thisActor->buf, 128) != 0);
  dprint2("Sent %i bit %i\n", thisActor->count, ((bit) ? (1):(0)));
  thisActor->count = (thisActor->count - 1);
  thisActor->buf = lshift(thisActor->buf, 1);
  pinWrite_bool_t(OUT0_out, bit);
  ART_ACTION_EXIT(action1__shift, 1);
}

#define ActorInstance_RVC_decoder__serialize__defaultState_ID 0
static void ActorInstance_RVC_decoder__serialize_constructor(AbstractActorInstance *pBase) {
  ActorInstance_RVC_decoder__serialize *thisActor=(ActorInstance_RVC_decoder__serialize*) pBase;
  thisActor->_fsmState = ActorInstance_RVC_decoder__serialize__defaultState_ID;//Initial state
  {
    thisActor->count = 0;
  }

}
static const int exitcode_block_Any[3]={1,0,1};
ART_ACTION_SCHEDULER(RVC_decoder__serialize_action_scheduler) {
  const int *result = EXIT_CODE_YIELD;
  ActorInstance_RVC_decoder__serialize *thisActor=(ActorInstance_RVC_decoder__serialize*) pBase;
  ART_ACTION_SCHEDULER_ENTER(1, 1)
  while(1) {
    switch(thisActor->_fsmState) {
      case ActorInstance_RVC_decoder__serialize__defaultState_ID:
        if ((pinAvailIn_int32_t(IN0_in8) >= 1)) {
          if (RVC_decoder__serialize__DOLLAR__d7932(context, thisActor)) {
            ART_FIRE_ACTION(action0__reload);
            thisActor->_fsmState = ActorInstance_RVC_decoder__serialize__defaultState_ID;
            continue;
          }
        }
        if (RVC_decoder__serialize__DOLLAR__d7940(context, thisActor)) {
          if ((pinAvailOut_bool_t(OUT0_out) >= 1)) {
            ART_FIRE_ACTION(action1__shift);
            thisActor->_fsmState = ActorInstance_RVC_decoder__serialize__defaultState_ID;
            continue;
          
          } else {
            result = exitcode_block_Any;
            goto out;
          }
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
    }
  }
  out:
  ART_ACTION_SCHEDULER_EXIT(1, 1)
  return result;
}