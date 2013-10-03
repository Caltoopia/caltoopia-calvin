#include "actors-rts.h"
#include "natives.h"
#include "RVC__decoderDemo.h"
#define  IN0_I ART_INPUT(0)
#define  IN1_SIGNED ART_INPUT(1)
#define  OUT0_O ART_OUTPUT(0)

//Actor constants
static const int32_t isz = 32;
static const int32_t osz = 9;

//Actor state
typedef struct {
  AbstractActorInstance base;
  int _fsmState;
  bool_t sflag;
} ActorInstance_RVC_decoder__texture_Y__idct2d__clip;

//Actor functions
ART_ACTION_CONTEXT(2, 1)

ART_ACTION(action0__read_signed, ActorInstance_RVC_decoder__texture_Y__idct2d__clip);
ART_ACTION(action1__clip, ActorInstance_RVC_decoder__texture_Y__idct2d__clip);
ART_ACTION_SCHEDULER(RVC_decoder__texture_Y__idct2d__clip_action_scheduler);
static void ActorInstance_RVC_decoder__texture_Y__idct2d__clip_constructor(AbstractActorInstance *);

static const PortDescription inputPortDescriptions[]={
  {0, "I", sizeof(int32_t)},
  {0, "SIGNED", sizeof(bool_t)},
};
static const PortDescription outputPortDescriptions[]={
  {0, "O", sizeof(int32_t)},
};

static const int portRate_in_action0__read_signed[] = {0, 1};

static const int portRate_out_action0__read_signed[] = {0};

static const int portRate_in_action1__clip[] = {(64 * 1), 0};

static const int portRate_out_action1__clip[] = {(64 * 1)};

static const ActionDescription actionDescriptions[] = {
  {"action0__read_signed", portRate_in_action0__read_signed, portRate_out_action0__read_signed},
  {"action1__clip", portRate_in_action1__clip, portRate_out_action1__clip},
};

ActorClass klass=INIT_ActorClass(
  "RVC_decoder__texture_Y__idct2d__clip",
  ActorInstance_RVC_decoder__texture_Y__idct2d__clip,
  ActorInstance_RVC_decoder__texture_Y__idct2d__clip_constructor,
  0, //setParam not needed anymore (we instantiate with params)
  RVC_decoder__texture_Y__idct2d__clip_action_scheduler,
  0, // no destructor
  2, inputPortDescriptions,
  1, outputPortDescriptions,
  2, actionDescriptions
);


// read_signed
ART_ACTION(action0__read_signed, ActorInstance_RVC_decoder__texture_Y__idct2d__clip) {
  bool_t s;
  ART_ACTION_ENTER(action0__read_signed, 0);
  s = pinRead_bool_t(IN1_SIGNED);
  thisActor->sflag = s;
  ART_ACTION_EXIT(action0__read_signed, 0);
}


// clip
ART_ACTION(action1__clip, ActorInstance_RVC_decoder__texture_Y__idct2d__clip) {
  int32_t* x;
  int32_t* U__51;
  ART_ACTION_ENTER(action1__clip, 1);
  U__51 = malloc((sizeof(int32_t) * 64));
  x = malloc((sizeof(int32_t) * 64));
  pinReadRepeat_int32_t(IN0_I, x, 64);
  {
    int32_t i;
    for(i = 0; i <= 63; i++)
    {
      U__51[((0 + i) - 0)] = (((x[i] > 255)) ? (255):(((((!(thisActor->sflag)) && (x[i] < 0))) ? (0):((((x[i] < (-(255)))) ? ((-(255))):(x[i]))))));
    }
  }
  pinWriteRepeat_int32_t(OUT0_O, U__51, 64);
  free((void*) x);
  free((void*) U__51);
  ART_ACTION_EXIT(action1__clip, 1);
}

#define ActorInstance_RVC_decoder__texture_Y__idct2d__clip__set_sign_ID 0
#define ActorInstance_RVC_decoder__texture_Y__idct2d__clip__clip_ID 1
static void ActorInstance_RVC_decoder__texture_Y__idct2d__clip_constructor(AbstractActorInstance *pBase) {
  ActorInstance_RVC_decoder__texture_Y__idct2d__clip *thisActor=(ActorInstance_RVC_decoder__texture_Y__idct2d__clip*) pBase;
  thisActor->_fsmState = ActorInstance_RVC_decoder__texture_Y__idct2d__clip__set_sign_ID;//Initial state
  {
  }

}
static const int exitcode_block_Any[3]={1,0,1};
ART_ACTION_SCHEDULER(RVC_decoder__texture_Y__idct2d__clip_action_scheduler) {
  const int *result = EXIT_CODE_YIELD;
  ActorInstance_RVC_decoder__texture_Y__idct2d__clip *thisActor=(ActorInstance_RVC_decoder__texture_Y__idct2d__clip*) pBase;
  ART_ACTION_SCHEDULER_ENTER(2, 1)
  while(1) {
    switch(thisActor->_fsmState) {
      case ActorInstance_RVC_decoder__texture_Y__idct2d__clip__set_sign_ID:
        if ((pinAvailIn_bool_t(IN1_SIGNED) >= 1)) {
          ART_FIRE_ACTION(action0__read_signed);
          thisActor->_fsmState = ActorInstance_RVC_decoder__texture_Y__idct2d__clip__clip_ID;
          continue;
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__texture_Y__idct2d__clip__clip_ID:
        if ((pinAvailIn_int32_t(IN0_I) >= 64)) {
          if ((pinAvailOut_int32_t(OUT0_O) >= 64)) {
            ART_FIRE_ACTION(action1__clip);
            thisActor->_fsmState = ActorInstance_RVC_decoder__texture_Y__idct2d__clip__set_sign_ID;
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
  ART_ACTION_SCHEDULER_EXIT(2, 1)
  return result;
}