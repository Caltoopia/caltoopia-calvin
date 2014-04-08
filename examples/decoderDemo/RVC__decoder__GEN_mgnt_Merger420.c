#include "actors-rts.h"
#include "natives.h"
#include "RVC__decoderDemo.h"
#define  IN0_Y ART_INPUT(0)
#define  IN1_U ART_INPUT(1)
#define  IN2_V ART_INPUT(2)
#define  OUT0_YUV ART_OUTPUT(0)

//Actor constants
static const int32_t PIX_SZ = 9;

//Actor state
typedef struct {
  AbstractActorInstance base;
  int _fsmState;
} ActorInstance_RVC_decoder__GEN_mgnt_Merger420;

//Actor functions
ART_ACTION_CONTEXT(3, 1)

ART_ACTION(action0__Ya, ActorInstance_RVC_decoder__GEN_mgnt_Merger420);
ART_ACTION(action1__Ua, ActorInstance_RVC_decoder__GEN_mgnt_Merger420);
ART_ACTION(action2__Va, ActorInstance_RVC_decoder__GEN_mgnt_Merger420);
ART_ACTION_SCHEDULER(RVC_decoder__GEN_mgnt_Merger420_action_scheduler);
static void ActorInstance_RVC_decoder__GEN_mgnt_Merger420_constructor(AbstractActorInstance *);

static const PortDescription inputPortDescriptions[]={
  {0, "Y", sizeof(int32_t), NULL},
  {0, "U", sizeof(int32_t), NULL},
  {0, "V", sizeof(int32_t), NULL},
};
static const PortDescription outputPortDescriptions[]={
  {0, "YUV", sizeof(int32_t), NULL},
};

static const int portRate_in_action0__Ya[] = {(256 * 1), 0, 0};

static const int portRate_out_action0__Ya[] = {(256 * 1)};

static const int portRate_in_action1__Ua[] = {0, (64 * 1), 0};

static const int portRate_out_action1__Ua[] = {(64 * 1)};

static const int portRate_in_action2__Va[] = {0, 0, (64 * 1)};

static const int portRate_out_action2__Va[] = {(64 * 1)};

static const ActionDescription actionDescriptions[] = {
  {"action0__Ya", portRate_in_action0__Ya, portRate_out_action0__Ya},
  {"action1__Ua", portRate_in_action1__Ua, portRate_out_action1__Ua},
  {"action2__Va", portRate_in_action2__Va, portRate_out_action2__Va},
};

ActorClass klass=INIT_ActorClass(
  "RVC_decoder__GEN_mgnt_Merger420",
  ActorInstance_RVC_decoder__GEN_mgnt_Merger420,
  ActorInstance_RVC_decoder__GEN_mgnt_Merger420_constructor,
  0, //setParam not needed anymore (we instantiate with params)
  0, 0, // serialize/deserialize
  RVC_decoder__GEN_mgnt_Merger420_action_scheduler,
  0, // no destructor
  3, inputPortDescriptions,
  1, outputPortDescriptions,
  3, actionDescriptions
);


// Ya
ART_ACTION(action0__Ya, ActorInstance_RVC_decoder__GEN_mgnt_Merger420) {
  int32_t* y;
  ART_ACTION_ENTER(action0__Ya, 0);
  y = malloc((sizeof(int32_t) * 256));
  pinReadRepeat_int32_t(IN0_Y, y, 256);
  pinWriteRepeat_int32_t(OUT0_YUV, y, 256);
  free((void*) y);
  ART_ACTION_EXIT(action0__Ya, 0);
}


// Ua
ART_ACTION(action1__Ua, ActorInstance_RVC_decoder__GEN_mgnt_Merger420) {
  int32_t* u;
  ART_ACTION_ENTER(action1__Ua, 1);
  u = malloc((sizeof(int32_t) * 64));
  pinReadRepeat_int32_t(IN1_U, u, 64);
  pinWriteRepeat_int32_t(OUT0_YUV, u, 64);
  free((void*) u);
  ART_ACTION_EXIT(action1__Ua, 1);
}


// Va
ART_ACTION(action2__Va, ActorInstance_RVC_decoder__GEN_mgnt_Merger420) {
  int32_t* v;
  ART_ACTION_ENTER(action2__Va, 2);
  v = malloc((sizeof(int32_t) * 64));
  pinReadRepeat_int32_t(IN2_V, v, 64);
  pinWriteRepeat_int32_t(OUT0_YUV, v, 64);
  free((void*) v);
  ART_ACTION_EXIT(action2__Va, 2);
}

#define ActorInstance_RVC_decoder__GEN_mgnt_Merger420__Y_ID 0
#define ActorInstance_RVC_decoder__GEN_mgnt_Merger420__U_ID 1
#define ActorInstance_RVC_decoder__GEN_mgnt_Merger420__V_ID 2
static void ActorInstance_RVC_decoder__GEN_mgnt_Merger420_constructor(AbstractActorInstance *pBase) {
  ActorInstance_RVC_decoder__GEN_mgnt_Merger420 *thisActor=(ActorInstance_RVC_decoder__GEN_mgnt_Merger420*) pBase;
  thisActor->_fsmState = ActorInstance_RVC_decoder__GEN_mgnt_Merger420__Y_ID;//Initial state
  {
  }

}
static const int exitcode_block_Any[3]={1,0,1};
ART_ACTION_SCHEDULER(RVC_decoder__GEN_mgnt_Merger420_action_scheduler) {
  const int *result = EXIT_CODE_YIELD;
  ActorInstance_RVC_decoder__GEN_mgnt_Merger420 *thisActor=(ActorInstance_RVC_decoder__GEN_mgnt_Merger420*) pBase;
  ART_ACTION_SCHEDULER_ENTER(3, 1)
  while(1) {
    switch(thisActor->_fsmState) {
      case ActorInstance_RVC_decoder__GEN_mgnt_Merger420__Y_ID:
        if ((pinAvailIn_int32_t(IN0_Y) >= 256)) {
          if ((pinAvailOut_int32_t(OUT0_YUV) >= 256)) {
            ART_FIRE_ACTION(action0__Ya);
            thisActor->_fsmState = ActorInstance_RVC_decoder__GEN_mgnt_Merger420__U_ID;
            continue;
          
          } else {
            result = exitcode_block_Any;
            goto out;
          }
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__GEN_mgnt_Merger420__U_ID:
        if ((pinAvailIn_int32_t(IN1_U) >= 64)) {
          if ((pinAvailOut_int32_t(OUT0_YUV) >= 64)) {
            ART_FIRE_ACTION(action1__Ua);
            thisActor->_fsmState = ActorInstance_RVC_decoder__GEN_mgnt_Merger420__V_ID;
            continue;
          
          } else {
            result = exitcode_block_Any;
            goto out;
          }
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__GEN_mgnt_Merger420__V_ID:
        if ((pinAvailIn_int32_t(IN2_V) >= 64)) {
          if ((pinAvailOut_int32_t(OUT0_YUV) >= 64)) {
            ART_FIRE_ACTION(action2__Va);
            thisActor->_fsmState = ActorInstance_RVC_decoder__GEN_mgnt_Merger420__Y_ID;
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
  ART_ACTION_SCHEDULER_EXIT(3, 1)
  return result;
}