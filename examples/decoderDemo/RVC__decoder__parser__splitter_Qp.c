#include "actors-rts.h"
#include "natives.h"
#include "RVC__decoderDemo.h"
#define  IN0_QP ART_INPUT(0)
#define  OUT0_QUANT_Y ART_OUTPUT(0)
#define  OUT1_QUANT_U ART_OUTPUT(1)
#define  OUT2_QUANT_V ART_OUTPUT(2)

//Actor constants
static const int32_t QUANT_SZ = 6;

//Actor state
typedef struct {
  AbstractActorInstance base;
  int _fsmState;
} ActorInstance_RVC_decoder__parser__splitter_Qp;

//Actor functions
ART_ACTION_CONTEXT(1, 3)

ART_ACTION(action0__quant__split, ActorInstance_RVC_decoder__parser__splitter_Qp);
ART_ACTION_SCHEDULER(RVC_decoder__parser__splitter_Qp_action_scheduler);
static void ActorInstance_RVC_decoder__parser__splitter_Qp_constructor(AbstractActorInstance *);

static const PortDescription inputPortDescriptions[]={
  {0, "QP", sizeof(int32_t)},
};
static const PortDescription outputPortDescriptions[]={
  {0, "QUANT_Y", sizeof(int32_t)},
  {0, "QUANT_U", sizeof(int32_t)},
  {0, "QUANT_V", sizeof(int32_t)},
};

static const int portRate_in_action0__quant__split[] = {(6 * 1)};

static const int portRate_out_action0__quant__split[] = {4, 1, 1};

static const ActionDescription actionDescriptions[] = {
  {"action0__quant__split", portRate_in_action0__quant__split, portRate_out_action0__quant__split},
};

ActorClass klass=INIT_ActorClass(
  "RVC_decoder__parser__splitter_Qp",
  ActorInstance_RVC_decoder__parser__splitter_Qp,
  ActorInstance_RVC_decoder__parser__splitter_Qp_constructor,
  0, //setParam not needed anymore (we instantiate with params)
  RVC_decoder__parser__splitter_Qp_action_scheduler,
  0, // no destructor
  1, inputPortDescriptions,
  3, outputPortDescriptions,
  1, actionDescriptions
);


// quant.split
ART_ACTION(action0__quant__split, ActorInstance_RVC_decoder__parser__splitter_Qp) {
  int32_t* list;
  ART_ACTION_ENTER(action0__quant__split, 0);
  list = malloc((sizeof(int32_t) * 6));
  pinReadRepeat_int32_t(IN0_QP, list, 6);
  pinWrite_int32_t(OUT0_QUANT_Y, list[0]);
  pinWrite_int32_t(OUT0_QUANT_Y, list[1]);
  pinWrite_int32_t(OUT0_QUANT_Y, list[2]);
  pinWrite_int32_t(OUT0_QUANT_Y, list[3]);
  pinWrite_int32_t(OUT1_QUANT_U, list[4]);
  pinWrite_int32_t(OUT2_QUANT_V, list[5]);
  free((void*) list);
  ART_ACTION_EXIT(action0__quant__split, 0);
}

#define ActorInstance_RVC_decoder__parser__splitter_Qp__defaultState_ID 0
static void ActorInstance_RVC_decoder__parser__splitter_Qp_constructor(AbstractActorInstance *pBase) {
  ActorInstance_RVC_decoder__parser__splitter_Qp *thisActor=(ActorInstance_RVC_decoder__parser__splitter_Qp*) pBase;
  thisActor->_fsmState = ActorInstance_RVC_decoder__parser__splitter_Qp__defaultState_ID;//Initial state
  {
  }

}
static const int exitcode_block_Any[3]={1,0,1};
ART_ACTION_SCHEDULER(RVC_decoder__parser__splitter_Qp_action_scheduler) {
  const int *result = EXIT_CODE_YIELD;
  ActorInstance_RVC_decoder__parser__splitter_Qp *thisActor=(ActorInstance_RVC_decoder__parser__splitter_Qp*) pBase;
  ART_ACTION_SCHEDULER_ENTER(1, 3)
  while(1) {
    switch(thisActor->_fsmState) {
      case ActorInstance_RVC_decoder__parser__splitter_Qp__defaultState_ID:
        if ((pinAvailIn_int32_t(IN0_QP) >= 6)) {
          if ((pinAvailOut_int32_t(OUT0_QUANT_Y) >= 1*4) && (pinAvailOut_int32_t(OUT1_QUANT_U) >= 1) && (pinAvailOut_int32_t(OUT2_QUANT_V) >= 1)) {
            ART_FIRE_ACTION(action0__quant__split);
            thisActor->_fsmState = ActorInstance_RVC_decoder__parser__splitter_Qp__defaultState_ID;
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
  ART_ACTION_SCHEDULER_EXIT(1, 3)
  return result;
}