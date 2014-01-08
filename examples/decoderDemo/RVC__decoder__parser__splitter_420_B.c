#include "actors-rts.h"
#include "natives.h"
#include "RVC__decoderDemo.h"
#define  IN0_B ART_INPUT(0)
#define  IN1_BTYPE ART_INPUT(1)
#define  OUT0_Y ART_OUTPUT(0)
#define  OUT1_U ART_OUTPUT(1)
#define  OUT2_V ART_OUTPUT(2)

//Actor constants
static const int32_t BLOCK_SZ = 64;
static const int32_t SAMPLE_SZ = 13;
static const int32_t BTYPE_SZ = 12;
static const int32_t NEWVOP = 2048;
static const int32_t INTRA = 1024;
static const int32_t INTER = 512;
static const int32_t ACCODED = 2;

//Actor state
typedef struct {
  AbstractActorInstance base;
  int _fsmState;
  int32_t comp;
} ActorInstance_RVC_decoder__parser__splitter_420_B;

//Actor functions
ART_ACTION_CONTEXT(2, 3)

ART_ACTION(action0__start, ActorInstance_RVC_decoder__parser__splitter_420_B);
ART_ACTION(action1__consume, ActorInstance_RVC_decoder__parser__splitter_420_B);
ART_ACTION(action2__skip_uncoded, ActorInstance_RVC_decoder__parser__splitter_420_B);
ART_ACTION(action3__skip_other, ActorInstance_RVC_decoder__parser__splitter_420_B);
ART_ACTION(action4__splitY, ActorInstance_RVC_decoder__parser__splitter_420_B);
ART_ACTION(action5__splitU, ActorInstance_RVC_decoder__parser__splitter_420_B);
ART_ACTION(action6__splitV, ActorInstance_RVC_decoder__parser__splitter_420_B);
ART_ACTION_SCHEDULER(RVC_decoder__parser__splitter_420_B_action_scheduler);
static void ActorInstance_RVC_decoder__parser__splitter_420_B_constructor(AbstractActorInstance *);

static const PortDescription inputPortDescriptions[]={
  {0, "B", sizeof(int32_t), NULL},
  {0, "BTYPE", sizeof(int32_t), NULL},
};
static const PortDescription outputPortDescriptions[]={
  {0, "Y", sizeof(int32_t), NULL},
  {0, "U", sizeof(int32_t), NULL},
  {0, "V", sizeof(int32_t), NULL},
};

static const int portRate_in_action0__start[] = {0, 1};

static const int portRate_out_action0__start[] = {0, 0, 0};

static const int portRate_in_action1__consume[] = {0, 1};

static const int portRate_out_action1__consume[] = {0, 0, 0};

static const int portRate_in_action2__skip_uncoded[] = {0, 1};

static const int portRate_out_action2__skip_uncoded[] = {0, 0, 0};

static const int portRate_in_action3__skip_other[] = {0, 1};

static const int portRate_out_action3__skip_other[] = {0, 0, 0};

static const int portRate_in_action4__splitY[] = {(64 * 1), 1};

static const int portRate_out_action4__splitY[] = {(64 * 1), 0, 0};

static const int portRate_in_action5__splitU[] = {(64 * 1), 1};

static const int portRate_out_action5__splitU[] = {0, (64 * 1), 0};

static const int portRate_in_action6__splitV[] = {(64 * 1), 1};

static const int portRate_out_action6__splitV[] = {0, 0, (64 * 1)};

static const ActionDescription actionDescriptions[] = {
  {"action0__start", portRate_in_action0__start, portRate_out_action0__start},
  {"action1__consume", portRate_in_action1__consume, portRate_out_action1__consume},
  {"action2__skip_uncoded", portRate_in_action2__skip_uncoded, portRate_out_action2__skip_uncoded},
  {"action3__skip_other", portRate_in_action3__skip_other, portRate_out_action3__skip_other},
  {"action4__splitY", portRate_in_action4__splitY, portRate_out_action4__splitY},
  {"action5__splitU", portRate_in_action5__splitU, portRate_out_action5__splitU},
  {"action6__splitV", portRate_in_action6__splitV, portRate_out_action6__splitV},
};

ActorClass klass=INIT_ActorClass(
  "RVC_decoder__parser__splitter_420_B",
  ActorInstance_RVC_decoder__parser__splitter_420_B,
  ActorInstance_RVC_decoder__parser__splitter_420_B_constructor,
  0, //setParam not needed anymore (we instantiate with params)
  RVC_decoder__parser__splitter_420_B_action_scheduler,
  0, // no destructor
  2, inputPortDescriptions,
  3, outputPortDescriptions,
  7, actionDescriptions
);

bool_t RVC_decoder__parser__splitter_420_B__DOLLAR__d1866(art_action_context_t *context, ActorInstance_RVC_decoder__parser__splitter_420_B *thisActor) {
  int32_t cmd;
  {
    bool_t ret;
    cmd = pinPeek_int32_t(IN1_BTYPE, 0);
    ret = (bitand(cmd, NEWVOP) != 0);
    return ret;
  }
}

// start
ART_ACTION(action0__start, ActorInstance_RVC_decoder__parser__splitter_420_B) {
  int32_t cmd;
  ART_ACTION_ENTER(action0__start, 0);
  cmd = pinRead_int32_t(IN1_BTYPE);
  ART_ACTION_EXIT(action0__start, 0);
}


// consume
ART_ACTION(action1__consume, ActorInstance_RVC_decoder__parser__splitter_420_B) {
  int32_t cmd;
  ART_ACTION_ENTER(action1__consume, 1);
  cmd = pinRead_int32_t(IN1_BTYPE);
  ART_ACTION_EXIT(action1__consume, 1);
}

bool_t RVC_decoder__parser__splitter_420_B__DOLLAR__d1881(art_action_context_t *context, ActorInstance_RVC_decoder__parser__splitter_420_B *thisActor) {
  int32_t cmd;
  {
    bool_t ret;
    cmd = pinPeek_int32_t(IN1_BTYPE, 0);
    ret = (bitand(cmd, INTER) != 0);
    return ret;
  }
}
bool_t RVC_decoder__parser__splitter_420_B__DOLLAR__d1890(art_action_context_t *context, ActorInstance_RVC_decoder__parser__splitter_420_B *thisActor) {
  int32_t cmd;
  {
    bool_t ret;
    cmd = pinPeek_int32_t(IN1_BTYPE, 0);
    ret = (bitand(cmd, ACCODED) == 0);
    return ret;
  }
}

// skip_uncoded
ART_ACTION(action2__skip_uncoded, ActorInstance_RVC_decoder__parser__splitter_420_B) {
  int32_t cmd;
  ART_ACTION_ENTER(action2__skip_uncoded, 2);
  cmd = pinRead_int32_t(IN1_BTYPE);
  thisActor->comp = (thisActor->comp + 1);
  if ((thisActor->comp == 6)) {
    thisActor->comp = 0;
  }
  ART_ACTION_EXIT(action2__skip_uncoded, 2);
}

bool_t RVC_decoder__parser__splitter_420_B__DOLLAR__d1911(art_action_context_t *context, ActorInstance_RVC_decoder__parser__splitter_420_B *thisActor) {
  int32_t cmd;
  {
    bool_t ret;
    cmd = pinPeek_int32_t(IN1_BTYPE, 0);
    ret = (bitand(cmd, INTER) == 0);
    return ret;
  }
}
bool_t RVC_decoder__parser__splitter_420_B__DOLLAR__d1920(art_action_context_t *context, ActorInstance_RVC_decoder__parser__splitter_420_B *thisActor) {
  int32_t cmd;
  {
    bool_t ret;
    cmd = pinPeek_int32_t(IN1_BTYPE, 0);
    ret = (bitand(cmd, INTRA) == 0);
    return ret;
  }
}

// skip_other
ART_ACTION(action3__skip_other, ActorInstance_RVC_decoder__parser__splitter_420_B) {
  int32_t cmd;
  ART_ACTION_ENTER(action3__skip_other, 3);
  cmd = pinRead_int32_t(IN1_BTYPE);
  thisActor->comp = (thisActor->comp + 1);
  if ((thisActor->comp == 6)) {
    thisActor->comp = 0;
  }
  ART_ACTION_EXIT(action3__skip_other, 3);
}

bool_t RVC_decoder__parser__splitter_420_B__DOLLAR__d1945(art_action_context_t *context, ActorInstance_RVC_decoder__parser__splitter_420_B *thisActor) {
  {
    bool_t ret;
    ret = (thisActor->comp < 4);
    return ret;
  }
}

// splitY
ART_ACTION(action4__splitY, ActorInstance_RVC_decoder__parser__splitter_420_B) {
  int32_t cmd;
  int32_t* x;
  ART_ACTION_ENTER(action4__splitY, 4);
  x = malloc((sizeof(int32_t) * 64));
  pinReadRepeat_int32_t(IN0_B, x, 64);
  cmd = pinRead_int32_t(IN1_BTYPE);
  thisActor->comp = (thisActor->comp + 1);
  pinWriteRepeat_int32_t(OUT0_Y, x, 64);
  free((void*) x);
  ART_ACTION_EXIT(action4__splitY, 4);
}

bool_t RVC_decoder__parser__splitter_420_B__DOLLAR__d1963(art_action_context_t *context, ActorInstance_RVC_decoder__parser__splitter_420_B *thisActor) {
  {
    bool_t ret;
    ret = (thisActor->comp == 4);
    return ret;
  }
}

// splitU
ART_ACTION(action5__splitU, ActorInstance_RVC_decoder__parser__splitter_420_B) {
  int32_t cmd;
  int32_t* x;
  ART_ACTION_ENTER(action5__splitU, 5);
  x = malloc((sizeof(int32_t) * 64));
  pinReadRepeat_int32_t(IN0_B, x, 64);
  cmd = pinRead_int32_t(IN1_BTYPE);
  thisActor->comp = (thisActor->comp + 1);
  pinWriteRepeat_int32_t(OUT1_U, x, 64);
  free((void*) x);
  ART_ACTION_EXIT(action5__splitU, 5);
}

bool_t RVC_decoder__parser__splitter_420_B__DOLLAR__d1981(art_action_context_t *context, ActorInstance_RVC_decoder__parser__splitter_420_B *thisActor) {
  {
    bool_t ret;
    ret = (thisActor->comp == 5);
    return ret;
  }
}

// splitV
ART_ACTION(action6__splitV, ActorInstance_RVC_decoder__parser__splitter_420_B) {
  int32_t cmd;
  int32_t* x;
  ART_ACTION_ENTER(action6__splitV, 6);
  x = malloc((sizeof(int32_t) * 64));
  pinReadRepeat_int32_t(IN0_B, x, 64);
  cmd = pinRead_int32_t(IN1_BTYPE);
  thisActor->comp = 0;
  pinWriteRepeat_int32_t(OUT2_V, x, 64);
  free((void*) x);
  ART_ACTION_EXIT(action6__splitV, 6);
}

#define ActorInstance_RVC_decoder__parser__splitter_420_B__READ_ID 0
#define ActorInstance_RVC_decoder__parser__splitter_420_B__GETW_ID 1
#define ActorInstance_RVC_decoder__parser__splitter_420_B__GETH_ID 2
static void ActorInstance_RVC_decoder__parser__splitter_420_B_constructor(AbstractActorInstance *pBase) {
  ActorInstance_RVC_decoder__parser__splitter_420_B *thisActor=(ActorInstance_RVC_decoder__parser__splitter_420_B*) pBase;
  thisActor->_fsmState = ActorInstance_RVC_decoder__parser__splitter_420_B__READ_ID;//Initial state
  {
    thisActor->comp = 0;
  }

}
static const int exitcode_block_Any[3]={1,0,1};
ART_ACTION_SCHEDULER(RVC_decoder__parser__splitter_420_B_action_scheduler) {
  const int *result = EXIT_CODE_YIELD;
  ActorInstance_RVC_decoder__parser__splitter_420_B *thisActor=(ActorInstance_RVC_decoder__parser__splitter_420_B*) pBase;
  ART_ACTION_SCHEDULER_ENTER(2, 3)
  while(1) {
    switch(thisActor->_fsmState) {
      case ActorInstance_RVC_decoder__parser__splitter_420_B__READ_ID:
        if ((pinAvailIn_int32_t(IN1_BTYPE) >= 1)) {
          if (RVC_decoder__parser__splitter_420_B__DOLLAR__d1866(context, thisActor)) {
            ART_FIRE_ACTION(action0__start);
            thisActor->_fsmState = ActorInstance_RVC_decoder__parser__splitter_420_B__GETW_ID;
            continue;
          }
        }
        if ((pinAvailIn_int32_t(IN1_BTYPE) >= 1)) {
          if (RVC_decoder__parser__splitter_420_B__DOLLAR__d1881(context, thisActor) && RVC_decoder__parser__splitter_420_B__DOLLAR__d1890(context, thisActor)) {
            ART_FIRE_ACTION(action2__skip_uncoded);
            thisActor->_fsmState = ActorInstance_RVC_decoder__parser__splitter_420_B__READ_ID;
            continue;
          }
        }
        if ((pinAvailIn_int32_t(IN1_BTYPE) >= 1)) {
          if (RVC_decoder__parser__splitter_420_B__DOLLAR__d1911(context, thisActor) && RVC_decoder__parser__splitter_420_B__DOLLAR__d1920(context, thisActor)) {
            ART_FIRE_ACTION(action3__skip_other);
            thisActor->_fsmState = ActorInstance_RVC_decoder__parser__splitter_420_B__READ_ID;
            continue;
          }
        }
        if ((pinAvailIn_int32_t(IN1_BTYPE) >= 1) && (pinAvailIn_int32_t(IN0_B) >= 64)) {
          if (RVC_decoder__parser__splitter_420_B__DOLLAR__d1945(context, thisActor)) {
            if ((pinAvailOut_int32_t(OUT0_Y) >= 64)) {
              ART_FIRE_ACTION(action4__splitY);
              thisActor->_fsmState = ActorInstance_RVC_decoder__parser__splitter_420_B__READ_ID;
              continue;
            
            } else {
              result = exitcode_block_Any;
              goto out;
            }
          }
        }
        if ((pinAvailIn_int32_t(IN1_BTYPE) >= 1) && (pinAvailIn_int32_t(IN0_B) >= 64)) {
          if (RVC_decoder__parser__splitter_420_B__DOLLAR__d1963(context, thisActor)) {
            if ((pinAvailOut_int32_t(OUT1_U) >= 64)) {
              ART_FIRE_ACTION(action5__splitU);
              thisActor->_fsmState = ActorInstance_RVC_decoder__parser__splitter_420_B__READ_ID;
              continue;
            
            } else {
              result = exitcode_block_Any;
              goto out;
            }
          }
        }
        if ((pinAvailIn_int32_t(IN1_BTYPE) >= 1) && (pinAvailIn_int32_t(IN0_B) >= 64)) {
          if (RVC_decoder__parser__splitter_420_B__DOLLAR__d1981(context, thisActor)) {
            if ((pinAvailOut_int32_t(OUT2_V) >= 64)) {
              ART_FIRE_ACTION(action6__splitV);
              thisActor->_fsmState = ActorInstance_RVC_decoder__parser__splitter_420_B__READ_ID;
              continue;
            
            } else {
              result = exitcode_block_Any;
              goto out;
            }
          }
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__parser__splitter_420_B__GETW_ID:
        if ((pinAvailIn_int32_t(IN1_BTYPE) >= 1)) {
          ART_FIRE_ACTION(action1__consume);
          thisActor->_fsmState = ActorInstance_RVC_decoder__parser__splitter_420_B__GETH_ID;
          continue;
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__parser__splitter_420_B__GETH_ID:
        if ((pinAvailIn_int32_t(IN1_BTYPE) >= 1)) {
          ART_FIRE_ACTION(action1__consume);
          thisActor->_fsmState = ActorInstance_RVC_decoder__parser__splitter_420_B__READ_ID;
          continue;
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
    }
  }
  out:
  ART_ACTION_SCHEDULER_EXIT(2, 3)
  return result;
}