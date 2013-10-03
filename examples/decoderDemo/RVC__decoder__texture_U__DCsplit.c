#include "actors-rts.h"
#include "natives.h"
#include "RVC__decoderDemo.h"
#define  IN0_IN ART_INPUT(0)
#define  OUT0_DC ART_OUTPUT(0)
#define  OUT1_AC ART_OUTPUT(1)

//Actor constants
static const int32_t SAMPLE_SZ = 13;

//Actor state
typedef struct {
  AbstractActorInstance base;
  int _fsmState;
} ActorInstance_RVC_decoder__texture_U__DCsplit;

//Actor functions
ART_ACTION_CONTEXT(1, 2)

ART_ACTION(action0, ActorInstance_RVC_decoder__texture_U__DCsplit);
ART_ACTION_SCHEDULER(RVC_decoder__texture_U__DCsplit_action_scheduler);
static void ActorInstance_RVC_decoder__texture_U__DCsplit_constructor(AbstractActorInstance *);

static const PortDescription inputPortDescriptions[]={
  {0, "IN", sizeof(int32_t)},
};
static const PortDescription outputPortDescriptions[]={
  {0, "DC", sizeof(int32_t)},
  {0, "AC", sizeof(int32_t)},
};

static const int portRate_in_action0[] = {(64 * 1)};

static const int portRate_out_action0[] = {1, (63 * 1)};

static const ActionDescription actionDescriptions[] = {
  {"action0", portRate_in_action0, portRate_out_action0},
};

ActorClass klass=INIT_ActorClass(
  "RVC_decoder__texture_U__DCsplit",
  ActorInstance_RVC_decoder__texture_U__DCsplit,
  ActorInstance_RVC_decoder__texture_U__DCsplit_constructor,
  0, //setParam not needed anymore (we instantiate with params)
  RVC_decoder__texture_U__DCsplit_action_scheduler,
  0, // no destructor
  1, inputPortDescriptions,
  2, outputPortDescriptions,
  1, actionDescriptions
);


// 
ART_ACTION(action0, ActorInstance_RVC_decoder__texture_U__DCsplit) {
  int32_t* x;
  int32_t* U__42;
  ART_ACTION_ENTER(action0, 0);
  U__42 = malloc((sizeof(int32_t) * 63));
  x = malloc((sizeof(int32_t) * 64));
  pinReadRepeat_int32_t(IN0_IN, x, 64);
  pinWrite_int32_t(OUT0_DC, x[0]);
  {
    int32_t i;
    for(i = 1; i <= 63; i++)
    {
      U__42[((0 + i) - 1)] = x[i];
    }
  }
  pinWriteRepeat_int32_t(OUT1_AC, U__42, 63);
  free((void*) x);
  free((void*) U__42);
  ART_ACTION_EXIT(action0, 0);
}

#define ActorInstance_RVC_decoder__texture_U__DCsplit__defaultState_ID 0
static void ActorInstance_RVC_decoder__texture_U__DCsplit_constructor(AbstractActorInstance *pBase) {
  ActorInstance_RVC_decoder__texture_U__DCsplit *thisActor=(ActorInstance_RVC_decoder__texture_U__DCsplit*) pBase;
  thisActor->_fsmState = ActorInstance_RVC_decoder__texture_U__DCsplit__defaultState_ID;//Initial state
  {
  }

}
static const int exitcode_block_Any[3]={1,0,1};
ART_ACTION_SCHEDULER(RVC_decoder__texture_U__DCsplit_action_scheduler) {
  const int *result = EXIT_CODE_YIELD;
  ActorInstance_RVC_decoder__texture_U__DCsplit *thisActor=(ActorInstance_RVC_decoder__texture_U__DCsplit*) pBase;
  ART_ACTION_SCHEDULER_ENTER(1, 2)
  while(1) {
    if ((pinAvailIn_int32_t(IN0_IN) >= 64)) {
      if ((pinAvailOut_int32_t(OUT0_DC) >= 1) && (pinAvailOut_int32_t(OUT1_AC) >= 63)) {
        ART_FIRE_ACTION(action0);
        continue;
      
      } else {
        result = exitcode_block_Any;
        goto out;
      }
    }
    switch(thisActor->_fsmState) {
      case ActorInstance_RVC_decoder__texture_U__DCsplit__defaultState_ID:
        result = exitcode_block_Any;
        goto out;
        break;
      
    }
  }
  out:
  ART_ACTION_SCHEDULER_EXIT(1, 2)
  return result;
}