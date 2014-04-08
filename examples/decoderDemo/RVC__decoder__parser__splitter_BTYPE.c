#include "actors-rts.h"
#include "natives.h"
#include "RVC__decoderDemo.h"
#define  IN0_BTYPE ART_INPUT(0)
#define  OUT0_Y ART_OUTPUT(0)
#define  OUT1_U ART_OUTPUT(1)
#define  OUT2_V ART_OUTPUT(2)

//Actor constants
static const int32_t BTYPE_SZ = 12;
static const int32_t NEWVOP = 2048;

//Actor state
typedef struct {
  AbstractActorInstance base;
  int _fsmState;
} ActorInstance_RVC_decoder__parser__splitter_BTYPE;

//Actor functions
ART_ACTION_CONTEXT(1, 3)

ART_ACTION(action0__cmd__newVop, ActorInstance_RVC_decoder__parser__splitter_BTYPE);
ART_ACTION(action1__skip, ActorInstance_RVC_decoder__parser__splitter_BTYPE);
ART_ACTION(action2__cmd__split, ActorInstance_RVC_decoder__parser__splitter_BTYPE);
ART_ACTION_SCHEDULER(RVC_decoder__parser__splitter_BTYPE_action_scheduler);
static void ActorInstance_RVC_decoder__parser__splitter_BTYPE_constructor(AbstractActorInstance *);

static const PortDescription inputPortDescriptions[]={
  {0, "BTYPE", sizeof(int32_t), NULL},
};
static const PortDescription outputPortDescriptions[]={
  {0, "Y", sizeof(int32_t), NULL},
  {0, "U", sizeof(int32_t), NULL},
  {0, "V", sizeof(int32_t), NULL},
};

static const int portRate_in_action0__cmd__newVop[] = {1};

static const int portRate_out_action0__cmd__newVop[] = {1, 1, 1};

static const int portRate_in_action1__skip[] = {(2 * 1)};

static const int portRate_out_action1__skip[] = {2, 2, 2};

static const int portRate_in_action2__cmd__split[] = {(6 * 1)};

static const int portRate_out_action2__cmd__split[] = {4, 1, 1};

static const ActionDescription actionDescriptions[] = {
  {"action0__cmd__newVop", portRate_in_action0__cmd__newVop, portRate_out_action0__cmd__newVop},
  {"action1__skip", portRate_in_action1__skip, portRate_out_action1__skip},
  {"action2__cmd__split", portRate_in_action2__cmd__split, portRate_out_action2__cmd__split},
};

ActorClass klass=INIT_ActorClass(
  "RVC_decoder__parser__splitter_BTYPE",
  ActorInstance_RVC_decoder__parser__splitter_BTYPE,
  ActorInstance_RVC_decoder__parser__splitter_BTYPE_constructor,
  0, //setParam not needed anymore (we instantiate with params)
  0, 0, // serialize/deserialize
  RVC_decoder__parser__splitter_BTYPE_action_scheduler,
  0, // no destructor
  1, inputPortDescriptions,
  3, outputPortDescriptions,
  3, actionDescriptions
);

bool_t RVC_decoder__parser__splitter_BTYPE__DOLLAR__d637(art_action_context_t *context, ActorInstance_RVC_decoder__parser__splitter_BTYPE *thisActor) {
  int32_t cmd;
  {
    bool_t ret;
    cmd = pinPeek_int32_t(IN0_BTYPE, 0);
    ret = (bitand(cmd, NEWVOP) != 0);
    return ret;
  }
}

// cmd.newVop
ART_ACTION(action0__cmd__newVop, ActorInstance_RVC_decoder__parser__splitter_BTYPE) {
  int32_t cmd;
  ART_ACTION_ENTER(action0__cmd__newVop, 0);
  cmd = pinRead_int32_t(IN0_BTYPE);
  pinWrite_int32_t(OUT0_Y, cmd);
  pinWrite_int32_t(OUT1_U, cmd);
  pinWrite_int32_t(OUT2_V, cmd);
  ART_ACTION_EXIT(action0__cmd__newVop, 0);
}


// skip
ART_ACTION(action1__skip, ActorInstance_RVC_decoder__parser__splitter_BTYPE) {
  int32_t* cmd;
  ART_ACTION_ENTER(action1__skip, 1);
  cmd = malloc((sizeof(int32_t) * 2));
  pinReadRepeat_int32_t(IN0_BTYPE, cmd, 2);
  pinWrite_int32_t(OUT0_Y, cmd[0]);
  pinWrite_int32_t(OUT0_Y, cmd[1]);
  pinWrite_int32_t(OUT1_U, cmd[0]);
  pinWrite_int32_t(OUT1_U, cmd[1]);
  pinWrite_int32_t(OUT2_V, cmd[0]);
  pinWrite_int32_t(OUT2_V, cmd[1]);
  free((void*) cmd);
  ART_ACTION_EXIT(action1__skip, 1);
}


// cmd.split
ART_ACTION(action2__cmd__split, ActorInstance_RVC_decoder__parser__splitter_BTYPE) {
  int32_t* list;
  ART_ACTION_ENTER(action2__cmd__split, 2);
  list = malloc((sizeof(int32_t) * 6));
  pinReadRepeat_int32_t(IN0_BTYPE, list, 6);
  pinWrite_int32_t(OUT0_Y, list[0]);
  pinWrite_int32_t(OUT0_Y, list[1]);
  pinWrite_int32_t(OUT0_Y, list[2]);
  pinWrite_int32_t(OUT0_Y, list[3]);
  pinWrite_int32_t(OUT1_U, list[4]);
  pinWrite_int32_t(OUT2_V, list[5]);
  free((void*) list);
  ART_ACTION_EXIT(action2__cmd__split, 2);
}

#define ActorInstance_RVC_decoder__parser__splitter_BTYPE__cmd_ID 0
#define ActorInstance_RVC_decoder__parser__splitter_BTYPE__skip_ID 1
static void ActorInstance_RVC_decoder__parser__splitter_BTYPE_constructor(AbstractActorInstance *pBase) {
  ActorInstance_RVC_decoder__parser__splitter_BTYPE *thisActor=(ActorInstance_RVC_decoder__parser__splitter_BTYPE*) pBase;
  thisActor->_fsmState = ActorInstance_RVC_decoder__parser__splitter_BTYPE__cmd_ID;//Initial state
  {
  }

}
static const int exitcode_block_Any[3]={1,0,1};
ART_ACTION_SCHEDULER(RVC_decoder__parser__splitter_BTYPE_action_scheduler) {
  const int *result = EXIT_CODE_YIELD;
  ActorInstance_RVC_decoder__parser__splitter_BTYPE *thisActor=(ActorInstance_RVC_decoder__parser__splitter_BTYPE*) pBase;
  ART_ACTION_SCHEDULER_ENTER(1, 3)
  while(1) {
    switch(thisActor->_fsmState) {
      case ActorInstance_RVC_decoder__parser__splitter_BTYPE__cmd_ID:
        if ((pinAvailIn_int32_t(IN0_BTYPE) >= 1)) {
          if (RVC_decoder__parser__splitter_BTYPE__DOLLAR__d637(context, thisActor)) {
            if ((pinAvailOut_int32_t(OUT0_Y) >= 1) && (pinAvailOut_int32_t(OUT1_U) >= 1) && (pinAvailOut_int32_t(OUT2_V) >= 1)) {
              ART_FIRE_ACTION(action0__cmd__newVop);
              thisActor->_fsmState = ActorInstance_RVC_decoder__parser__splitter_BTYPE__skip_ID;
              continue;
            
            } else {
              result = exitcode_block_Any;
              goto out;
            }
          }
        }
        if ((pinAvailIn_int32_t(IN0_BTYPE) >= 6)) {
          if ((pinAvailOut_int32_t(OUT0_Y) >= 1*4) && (pinAvailOut_int32_t(OUT1_U) >= 1) && (pinAvailOut_int32_t(OUT2_V) >= 1)) {
            ART_FIRE_ACTION(action2__cmd__split);
            thisActor->_fsmState = ActorInstance_RVC_decoder__parser__splitter_BTYPE__cmd_ID;
            continue;
          
          } else {
            result = exitcode_block_Any;
            goto out;
          }
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__parser__splitter_BTYPE__skip_ID:
        if ((pinAvailIn_int32_t(IN0_BTYPE) >= 2)) {
          if ((pinAvailOut_int32_t(OUT0_Y) >= 1*2) && (pinAvailOut_int32_t(OUT1_U) >= 1*2) && (pinAvailOut_int32_t(OUT2_V) >= 1*2)) {
            ART_FIRE_ACTION(action1__skip);
            thisActor->_fsmState = ActorInstance_RVC_decoder__parser__splitter_BTYPE__cmd_ID;
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