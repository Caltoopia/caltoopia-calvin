#include "actors-rts.h"
#include "natives.h"
#include "RVC__decoderDemo.h"
#define  IN0_SIn ART_INPUT(0)
#define  OUT0_SOut ART_OUTPUT(0)

//Actor constants
static const int32_t SIN_SZ = 13;
static const int32_t SOUT_SZ = 32;
static const int32_t E = 1264;
static const int32_t G = 1788;
static const int32_t H = 2923;
static const int32_t J = 2528;
static const int32_t F = 1922;
static const int32_t C = 1730;
static const int32_t A = 1024;
static const int32_t D = 1609;
static const int32_t I = 2718;
static const int32_t B = 1138;
static const int32_t scale[64] = {1024, 1138, 1730, 1609, 1024, 1609, 1730, 1138, 1138, 1264, 1922, 1788, 1138, 1788, 1922, 1264, 1730, 1922, 2923, 2718, 1730, 2718, 2923, 1922, 1609, 1788, 2718, 2528, 1609, 2528, 2718, 1788, 1024, 1138, 1730, 1609, 1024, 1609, 1730, 1138, 1609, 1788, 2718, 2528, 1609, 2528, 2718, 1788, 1730, 1922, 2923, 2718, 1730, 2718, 2923, 1922, 1138, 1264, 1922, 1788, 1138, 1788, 1922, 1264};

//Actor state
typedef struct {
  AbstractActorInstance base;
  int _fsmState;
} ActorInstance_RVC_decoder__texture_V__idct2d__scale;

//Actor functions
ART_ACTION_CONTEXT(1, 1)

ART_ACTION(action0, ActorInstance_RVC_decoder__texture_V__idct2d__scale);
ART_ACTION_SCHEDULER(RVC_decoder__texture_V__idct2d__scale_action_scheduler);
static void ActorInstance_RVC_decoder__texture_V__idct2d__scale_constructor(AbstractActorInstance *);

static const PortDescription inputPortDescriptions[]={
  {0, "SIn", sizeof(int32_t)},
};
static const PortDescription outputPortDescriptions[]={
  {0, "SOut", sizeof(int32_t)},
};

static const int portRate_in_action0[] = {(64 * 1)};

static const int portRate_out_action0[] = {(64 * 1)};

static const ActionDescription actionDescriptions[] = {
  {"action0", portRate_in_action0, portRate_out_action0},
};

ActorClass klass=INIT_ActorClass(
  "RVC_decoder__texture_V__idct2d__scale",
  ActorInstance_RVC_decoder__texture_V__idct2d__scale,
  ActorInstance_RVC_decoder__texture_V__idct2d__scale_constructor,
  0, //setParam not needed anymore (we instantiate with params)
  RVC_decoder__texture_V__idct2d__scale_action_scheduler,
  0, // no destructor
  1, inputPortDescriptions,
  1, outputPortDescriptions,
  1, actionDescriptions
);


// 
ART_ACTION(action0, ActorInstance_RVC_decoder__texture_V__idct2d__scale) {
  int32_t* x;
  int32_t* y;
  ART_ACTION_ENTER(action0, 0);
  y = malloc((sizeof(int32_t) * 64));
  x = malloc((sizeof(int32_t) * 64));
  pinReadRepeat_int32_t(IN0_SIn, x, 64);
  {
    int32_t i;
    for(i = 1; i <= 64; i++)
    {
      y[((0 + i) - 1)] = 0;
    }
  }
  {
    int32_t i;
    for(i = 0; i <= 63; i++)
    {
      y[((0 + i) - 0)] = (x[i] * scale[i]);
    }
  }
  y[0] = (y[0] + 4096);
  pinWriteRepeat_int32_t(OUT0_SOut, y, 64);
  free((void*) x);
  free((void*) y);
  ART_ACTION_EXIT(action0, 0);
}

#define ActorInstance_RVC_decoder__texture_V__idct2d__scale__defaultState_ID 0
static void ActorInstance_RVC_decoder__texture_V__idct2d__scale_constructor(AbstractActorInstance *pBase) {
  ActorInstance_RVC_decoder__texture_V__idct2d__scale *thisActor=(ActorInstance_RVC_decoder__texture_V__idct2d__scale*) pBase;
  thisActor->_fsmState = ActorInstance_RVC_decoder__texture_V__idct2d__scale__defaultState_ID;//Initial state
  {
  }

}
static const int exitcode_block_Any[3]={1,0,1};
ART_ACTION_SCHEDULER(RVC_decoder__texture_V__idct2d__scale_action_scheduler) {
  const int *result = EXIT_CODE_YIELD;
  ActorInstance_RVC_decoder__texture_V__idct2d__scale *thisActor=(ActorInstance_RVC_decoder__texture_V__idct2d__scale*) pBase;
  ART_ACTION_SCHEDULER_ENTER(1, 1)
  while(1) {
    if ((pinAvailIn_int32_t(IN0_SIn) >= 64)) {
      if ((pinAvailOut_int32_t(OUT0_SOut) >= 64)) {
        ART_FIRE_ACTION(action0);
        continue;
      
      } else {
        result = exitcode_block_Any;
        goto out;
      }
    }
    switch(thisActor->_fsmState) {
      case ActorInstance_RVC_decoder__texture_V__idct2d__scale__defaultState_ID:
        result = exitcode_block_Any;
        goto out;
        break;
      
    }
  }
  out:
  ART_ACTION_SCHEDULER_EXIT(1, 1)
  return result;
}