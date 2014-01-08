#include "actors-rts.h"
#include "natives.h"
#include "RVC__decoderDemo.h"
#define  IN0_In ART_INPUT(0)
#define  OUT0_Out ART_OUTPUT(0)

//Actor constants

//Actor state
typedef struct {
  AbstractActorInstance base;
  int _fsmState;
} ActorInstance_RVC_decoder__texture_Y__idct2d__shift;

//Actor functions
ART_ACTION_CONTEXT(1, 1)

ART_ACTION(action0, ActorInstance_RVC_decoder__texture_Y__idct2d__shift);
ART_ACTION_SCHEDULER(RVC_decoder__texture_Y__idct2d__shift_action_scheduler);
static void ActorInstance_RVC_decoder__texture_Y__idct2d__shift_constructor(AbstractActorInstance *);

static const PortDescription inputPortDescriptions[]={
  {0, "In", sizeof(int32_t), NULL},
};
static const PortDescription outputPortDescriptions[]={
  {0, "Out", sizeof(int32_t), NULL},
};

static const int portRate_in_action0[] = {(64 * 1)};

static const int portRate_out_action0[] = {(64 * 1)};

static const ActionDescription actionDescriptions[] = {
  {"action0", portRate_in_action0, portRate_out_action0},
};

ActorClass klass=INIT_ActorClass(
  "RVC_decoder__texture_Y__idct2d__shift",
  ActorInstance_RVC_decoder__texture_Y__idct2d__shift,
  ActorInstance_RVC_decoder__texture_Y__idct2d__shift_constructor,
  0, //setParam not needed anymore (we instantiate with params)
  RVC_decoder__texture_Y__idct2d__shift_action_scheduler,
  0, // no destructor
  1, inputPortDescriptions,
  1, outputPortDescriptions,
  1, actionDescriptions
);


// 
ART_ACTION(action0, ActorInstance_RVC_decoder__texture_Y__idct2d__shift) {
  int32_t* x;
  int32_t* U__50;
  ART_ACTION_ENTER(action0, 0);
  U__50 = malloc((sizeof(int32_t) * 64));
  x = malloc((sizeof(int32_t) * 64));
  pinReadRepeat_int32_t(IN0_In, x, 64);
  {
    int32_t i;
    for(i = 0; i <= 63; i++)
    {
      U__50[((0 + i) - 0)] = rshift(x[i], 13);
    }
  }
  pinWriteRepeat_int32_t(OUT0_Out, U__50, 64);
  free((void*) x);
  free((void*) U__50);
  ART_ACTION_EXIT(action0, 0);
}

#define ActorInstance_RVC_decoder__texture_Y__idct2d__shift__defaultState_ID 0
static void ActorInstance_RVC_decoder__texture_Y__idct2d__shift_constructor(AbstractActorInstance *pBase) {
  ActorInstance_RVC_decoder__texture_Y__idct2d__shift *thisActor=(ActorInstance_RVC_decoder__texture_Y__idct2d__shift*) pBase;
  thisActor->_fsmState = ActorInstance_RVC_decoder__texture_Y__idct2d__shift__defaultState_ID;//Initial state
  {
  }

}
static const int exitcode_block_Any[3]={1,0,1};
ART_ACTION_SCHEDULER(RVC_decoder__texture_Y__idct2d__shift_action_scheduler) {
  const int *result = EXIT_CODE_YIELD;
  ActorInstance_RVC_decoder__texture_Y__idct2d__shift *thisActor=(ActorInstance_RVC_decoder__texture_Y__idct2d__shift*) pBase;
  ART_ACTION_SCHEDULER_ENTER(1, 1)
  while(1) {
    if ((pinAvailIn_int32_t(IN0_In) >= 64)) {
      if ((pinAvailOut_int32_t(OUT0_Out) >= 64)) {
        ART_FIRE_ACTION(action0);
        continue;
      
      } else {
        result = exitcode_block_Any;
        goto out;
      }
    }
    switch(thisActor->_fsmState) {
      case ActorInstance_RVC_decoder__texture_Y__idct2d__shift__defaultState_ID:
        result = exitcode_block_Any;
        goto out;
        break;
      
    }
  }
  out:
  ART_ACTION_SCHEDULER_EXIT(1, 1)
  return result;
}