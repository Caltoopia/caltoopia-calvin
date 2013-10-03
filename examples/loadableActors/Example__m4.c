#include "actors-rts.h"
#include "natives.h"
#include "Example__toppen.h"
#define  IN0_In ART_INPUT(0)
#define  OUT0_Out ART_OUTPUT(0)

//Actor constants
static const int32_t FACTOR = 7;

//Actor state
typedef struct {
  AbstractActorInstance base;
  int _fsmState;
} ActorInstance_Example_m4;

//Actor functions
ART_ACTION_CONTEXT(1, 1)

ART_ACTION(action0, ActorInstance_Example_m4);
ART_ACTION_SCHEDULER(Example_m4_action_scheduler);
static void ActorInstance_Example_m4_constructor(AbstractActorInstance *);

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

ActorClass klass = INIT_ActorClass(
  "Example_m4",
  ActorInstance_Example_m4,
  ActorInstance_Example_m4_constructor,
  0, //setParam not needed anymore (we instantiate with params)
  Example_m4_action_scheduler,
  0, // no destructor
  1, inputPortDescriptions,
  1, outputPortDescriptions,
  1, actionDescriptions
);


// 
ART_ACTION(action0, ActorInstance_Example_m4) {
  int32_t x;
  int32_t U__0;
  ART_ACTION_ENTER(action0, 0);
  x = pinRead_int32_t(IN0_In);
  U__0 = (x * 7);
  pinWrite_int32_t(OUT0_Out, U__0);
  ART_ACTION_EXIT(action0, 0);
}

#define ActorInstance_Example_m4__defaultState_ID 0
static void ActorInstance_Example_m4_constructor(AbstractActorInstance *pBase) {
  ActorInstance_Example_m4 *thisActor=(ActorInstance_Example_m4*) pBase;
  thisActor->_fsmState = ActorInstance_Example_m4__defaultState_ID;//Initial state
  {
  }

}
static const int exitcode_block_Any[3]={1,0,1};
ART_ACTION_SCHEDULER(Example_m4_action_scheduler) {
  const int *result = EXIT_CODE_YIELD;
  ActorInstance_Example_m4 *thisActor=(ActorInstance_Example_m4*) pBase;
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
      case ActorInstance_Example_m4__defaultState_ID:
        result = exitcode_block_Any;
        goto out;
        break;
      
    }
  }
  out:
  ART_ACTION_SCHEDULER_EXIT(1, 1)
  return result;
}
