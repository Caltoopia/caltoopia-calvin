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
} ActorInstance_RVC_decoder__texture_U__idct2d__retranspose;

//Actor functions
ART_ACTION_CONTEXT(1, 1)

ART_ACTION(action0, ActorInstance_RVC_decoder__texture_U__idct2d__retranspose);
ART_ACTION_SCHEDULER(RVC_decoder__texture_U__idct2d__retranspose_action_scheduler);
static void ActorInstance_RVC_decoder__texture_U__idct2d__retranspose_constructor(AbstractActorInstance *);

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
  "RVC_decoder__texture_U__idct2d__retranspose",
  ActorInstance_RVC_decoder__texture_U__idct2d__retranspose,
  ActorInstance_RVC_decoder__texture_U__idct2d__retranspose_constructor,
  0, //setParam not needed anymore (we instantiate with params)
  RVC_decoder__texture_U__idct2d__retranspose_action_scheduler,
  0, // no destructor
  1, inputPortDescriptions,
  1, outputPortDescriptions,
  1, actionDescriptions
);


// 
ART_ACTION(action0, ActorInstance_RVC_decoder__texture_U__idct2d__retranspose) {
  int32_t* x;
  int32_t* y;
  ART_ACTION_ENTER(action0, 0);
  y = malloc((sizeof(int32_t) * 64));
  x = malloc((sizeof(int32_t) * 64));
  pinReadRepeat_int32_t(IN0_In, x, 64);
  {
    int32_t r;
    for(r = 0; r <= 7; r++)
    {
      {
        int32_t c;
        for(c = 0; c <= 7; c++)
        {
          y[(r + (c * 8))] = x[((8 * r) + c)];
        }
      }
    }
  }
  pinWriteRepeat_int32_t(OUT0_Out, y, 64);
  free((void*) x);
  free((void*) y);
  ART_ACTION_EXIT(action0, 0);
}

#define ActorInstance_RVC_decoder__texture_U__idct2d__retranspose__defaultState_ID 0
static void ActorInstance_RVC_decoder__texture_U__idct2d__retranspose_constructor(AbstractActorInstance *pBase) {
  ActorInstance_RVC_decoder__texture_U__idct2d__retranspose *thisActor=(ActorInstance_RVC_decoder__texture_U__idct2d__retranspose*) pBase;
  thisActor->_fsmState = ActorInstance_RVC_decoder__texture_U__idct2d__retranspose__defaultState_ID;//Initial state
  {
  }

}
static const int exitcode_block_Any[3]={1,0,1};
ART_ACTION_SCHEDULER(RVC_decoder__texture_U__idct2d__retranspose_action_scheduler) {
  const int *result = EXIT_CODE_YIELD;
  ActorInstance_RVC_decoder__texture_U__idct2d__retranspose *thisActor=(ActorInstance_RVC_decoder__texture_U__idct2d__retranspose*) pBase;
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
      case ActorInstance_RVC_decoder__texture_U__idct2d__retranspose__defaultState_ID:
        result = exitcode_block_Any;
        goto out;
        break;
      
    }
  }
  out:
  ART_ACTION_SCHEDULER_EXIT(1, 1)
  return result;
}