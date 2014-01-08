#include "actors-rts.h"
#include "natives.h"
#include "RVC__decoderDemo.h"
#define  IN0_MV ART_INPUT(0)
#define  IN1_BTYPE ART_INPUT(1)
#define  OUT0_Y ART_OUTPUT(0)
#define  OUT1_U ART_OUTPUT(1)
#define  OUT2_V ART_OUTPUT(2)

//Actor constants
static const int32_t MV_SZ = 9;
static const int32_t BTYPE_SZ = 12;
static const int32_t MOTION = 8;
static const int32_t NEWVOP = 2048;

//Actor state
typedef struct {
  AbstractActorInstance base;
  int _fsmState;
} ActorInstance_RVC_decoder__parser__splitter_MV;

//Actor functions
ART_ACTION_CONTEXT(2, 3)

ART_ACTION(action0__newvop, ActorInstance_RVC_decoder__parser__splitter_MV);
ART_ACTION(action1__skip, ActorInstance_RVC_decoder__parser__splitter_MV);
ART_ACTION(action2__skipbtype, ActorInstance_RVC_decoder__parser__splitter_MV);
ART_ACTION(action3__B1, ActorInstance_RVC_decoder__parser__splitter_MV);
ART_ACTION(action4__B2, ActorInstance_RVC_decoder__parser__splitter_MV);
ART_ACTION(action5__B3, ActorInstance_RVC_decoder__parser__splitter_MV);
ART_ACTION(action6__B4, ActorInstance_RVC_decoder__parser__splitter_MV);
ART_ACTION(action7__B5, ActorInstance_RVC_decoder__parser__splitter_MV);
ART_ACTION(action8__B6, ActorInstance_RVC_decoder__parser__splitter_MV);
ART_ACTION_SCHEDULER(RVC_decoder__parser__splitter_MV_action_scheduler);
static void ActorInstance_RVC_decoder__parser__splitter_MV_constructor(AbstractActorInstance *);

static const PortDescription inputPortDescriptions[]={
  {0, "MV", sizeof(int32_t), NULL},
  {0, "BTYPE", sizeof(int32_t), NULL},
};
static const PortDescription outputPortDescriptions[]={
  {0, "Y", sizeof(int32_t), NULL},
  {0, "U", sizeof(int32_t), NULL},
  {0, "V", sizeof(int32_t), NULL},
};

static const int portRate_in_action0__newvop[] = {0, 1};

static const int portRate_out_action0__newvop[] = {0, 0, 0};

static const int portRate_in_action1__skip[] = {0, (2 * 1)};

static const int portRate_out_action1__skip[] = {0, 0, 0};

static const int portRate_in_action2__skipbtype[] = {0, 1};

static const int portRate_out_action2__skipbtype[] = {0, 0, 0};

static const int portRate_in_action3__B1[] = {(2 * 1), 1};

static const int portRate_out_action3__B1[] = {2, 0, 0};

static const int portRate_in_action4__B2[] = {(2 * 1), 1};

static const int portRate_out_action4__B2[] = {2, 0, 0};

static const int portRate_in_action5__B3[] = {(2 * 1), 1};

static const int portRate_out_action5__B3[] = {2, 0, 0};

static const int portRate_in_action6__B4[] = {(2 * 1), 1};

static const int portRate_out_action6__B4[] = {2, 0, 0};

static const int portRate_in_action7__B5[] = {(2 * 1), 1};

static const int portRate_out_action7__B5[] = {0, 2, 0};

static const int portRate_in_action8__B6[] = {(2 * 1), 1};

static const int portRate_out_action8__B6[] = {0, 0, 2};

static const ActionDescription actionDescriptions[] = {
  {"action0__newvop", portRate_in_action0__newvop, portRate_out_action0__newvop},
  {"action1__skip", portRate_in_action1__skip, portRate_out_action1__skip},
  {"action2__skipbtype", portRate_in_action2__skipbtype, portRate_out_action2__skipbtype},
  {"action3__B1", portRate_in_action3__B1, portRate_out_action3__B1},
  {"action4__B2", portRate_in_action4__B2, portRate_out_action4__B2},
  {"action5__B3", portRate_in_action5__B3, portRate_out_action5__B3},
  {"action6__B4", portRate_in_action6__B4, portRate_out_action6__B4},
  {"action7__B5", portRate_in_action7__B5, portRate_out_action7__B5},
  {"action8__B6", portRate_in_action8__B6, portRate_out_action8__B6},
};

ActorClass klass=INIT_ActorClass(
  "RVC_decoder__parser__splitter_MV",
  ActorInstance_RVC_decoder__parser__splitter_MV,
  ActorInstance_RVC_decoder__parser__splitter_MV_constructor,
  0, //setParam not needed anymore (we instantiate with params)
  RVC_decoder__parser__splitter_MV_action_scheduler,
  0, // no destructor
  2, inputPortDescriptions,
  3, outputPortDescriptions,
  9, actionDescriptions
);

bool_t RVC_decoder__parser__splitter_MV__DOLLAR__d8472(art_action_context_t *context, ActorInstance_RVC_decoder__parser__splitter_MV *thisActor) {
  int32_t cmd;
  {
    bool_t ret;
    cmd = pinPeek_int32_t(IN1_BTYPE, 0);
    ret = (bitand(cmd, NEWVOP) != 0);
    return ret;
  }
}

// newvop
ART_ACTION(action0__newvop, ActorInstance_RVC_decoder__parser__splitter_MV) {
  int32_t cmd;
  ART_ACTION_ENTER(action0__newvop, 0);
  cmd = pinRead_int32_t(IN1_BTYPE);
  ART_ACTION_EXIT(action0__newvop, 0);
}


// skip
ART_ACTION(action1__skip, ActorInstance_RVC_decoder__parser__splitter_MV) {
  int32_t* btype;
  ART_ACTION_ENTER(action1__skip, 1);
  btype = malloc((sizeof(int32_t) * 2));
  pinReadRepeat_int32_t(IN1_BTYPE, btype, 2);
  free((void*) btype);
  ART_ACTION_EXIT(action1__skip, 1);
}

bool_t RVC_decoder__parser__splitter_MV__DOLLAR__d8488(art_action_context_t *context, ActorInstance_RVC_decoder__parser__splitter_MV *thisActor) {
  int32_t btype;
  {
    bool_t ret;
    btype = pinPeek_int32_t(IN1_BTYPE, 0);
    ret = (bitand(btype, MOTION) == 0);
    return ret;
  }
}
bool_t RVC_decoder__parser__splitter_MV__DOLLAR__d8497(art_action_context_t *context, ActorInstance_RVC_decoder__parser__splitter_MV *thisActor) {
  int32_t btype;
  {
    bool_t ret;
    btype = pinPeek_int32_t(IN1_BTYPE, 0);
    ret = (bitand(btype, NEWVOP) == 0);
    return ret;
  }
}

// skipbtype
ART_ACTION(action2__skipbtype, ActorInstance_RVC_decoder__parser__splitter_MV) {
  int32_t btype;
  ART_ACTION_ENTER(action2__skipbtype, 2);
  btype = pinRead_int32_t(IN1_BTYPE);
  ART_ACTION_EXIT(action2__skipbtype, 2);
}

bool_t RVC_decoder__parser__splitter_MV__DOLLAR__d8513(art_action_context_t *context, ActorInstance_RVC_decoder__parser__splitter_MV *thisActor) {
  int32_t btype;
  {
    bool_t ret;
    btype = pinPeek_int32_t(IN1_BTYPE, 0);
    ret = (bitand(btype, MOTION) != 0);
    return ret;
  }
}

// B1
ART_ACTION(action3__B1, ActorInstance_RVC_decoder__parser__splitter_MV) {
  int32_t* mv;
  int32_t btype;
  ART_ACTION_ENTER(action3__B1, 3);
  mv = malloc((sizeof(int32_t) * 2));
  btype = pinRead_int32_t(IN1_BTYPE);
  pinReadRepeat_int32_t(IN0_MV, mv, 2);
  pinWrite_int32_t(OUT0_Y, mv[0]);
  pinWrite_int32_t(OUT0_Y, mv[1]);
  free((void*) mv);
  ART_ACTION_EXIT(action3__B1, 3);
}

bool_t RVC_decoder__parser__splitter_MV__DOLLAR__d8535(art_action_context_t *context, ActorInstance_RVC_decoder__parser__splitter_MV *thisActor) {
  int32_t btype;
  {
    bool_t ret;
    btype = pinPeek_int32_t(IN1_BTYPE, 0);
    ret = (bitand(btype, MOTION) != 0);
    return ret;
  }
}

// B2
ART_ACTION(action4__B2, ActorInstance_RVC_decoder__parser__splitter_MV) {
  int32_t* mv;
  int32_t btype;
  ART_ACTION_ENTER(action4__B2, 4);
  mv = malloc((sizeof(int32_t) * 2));
  btype = pinRead_int32_t(IN1_BTYPE);
  pinReadRepeat_int32_t(IN0_MV, mv, 2);
  pinWrite_int32_t(OUT0_Y, mv[0]);
  pinWrite_int32_t(OUT0_Y, mv[1]);
  free((void*) mv);
  ART_ACTION_EXIT(action4__B2, 4);
}

bool_t RVC_decoder__parser__splitter_MV__DOLLAR__d8557(art_action_context_t *context, ActorInstance_RVC_decoder__parser__splitter_MV *thisActor) {
  int32_t btype;
  {
    bool_t ret;
    btype = pinPeek_int32_t(IN1_BTYPE, 0);
    ret = (bitand(btype, MOTION) != 0);
    return ret;
  }
}

// B3
ART_ACTION(action5__B3, ActorInstance_RVC_decoder__parser__splitter_MV) {
  int32_t* mv;
  int32_t btype;
  ART_ACTION_ENTER(action5__B3, 5);
  mv = malloc((sizeof(int32_t) * 2));
  btype = pinRead_int32_t(IN1_BTYPE);
  pinReadRepeat_int32_t(IN0_MV, mv, 2);
  pinWrite_int32_t(OUT0_Y, mv[0]);
  pinWrite_int32_t(OUT0_Y, mv[1]);
  free((void*) mv);
  ART_ACTION_EXIT(action5__B3, 5);
}

bool_t RVC_decoder__parser__splitter_MV__DOLLAR__d8579(art_action_context_t *context, ActorInstance_RVC_decoder__parser__splitter_MV *thisActor) {
  int32_t btype;
  {
    bool_t ret;
    btype = pinPeek_int32_t(IN1_BTYPE, 0);
    ret = (bitand(btype, MOTION) != 0);
    return ret;
  }
}

// B4
ART_ACTION(action6__B4, ActorInstance_RVC_decoder__parser__splitter_MV) {
  int32_t* mv;
  int32_t btype;
  ART_ACTION_ENTER(action6__B4, 6);
  mv = malloc((sizeof(int32_t) * 2));
  btype = pinRead_int32_t(IN1_BTYPE);
  pinReadRepeat_int32_t(IN0_MV, mv, 2);
  pinWrite_int32_t(OUT0_Y, mv[0]);
  pinWrite_int32_t(OUT0_Y, mv[1]);
  free((void*) mv);
  ART_ACTION_EXIT(action6__B4, 6);
}

bool_t RVC_decoder__parser__splitter_MV__DOLLAR__d8601(art_action_context_t *context, ActorInstance_RVC_decoder__parser__splitter_MV *thisActor) {
  int32_t btype;
  {
    bool_t ret;
    btype = pinPeek_int32_t(IN1_BTYPE, 0);
    ret = (bitand(btype, MOTION) != 0);
    return ret;
  }
}

// B5
ART_ACTION(action7__B5, ActorInstance_RVC_decoder__parser__splitter_MV) {
  int32_t* mv;
  int32_t btype;
  ART_ACTION_ENTER(action7__B5, 7);
  mv = malloc((sizeof(int32_t) * 2));
  btype = pinRead_int32_t(IN1_BTYPE);
  pinReadRepeat_int32_t(IN0_MV, mv, 2);
  pinWrite_int32_t(OUT1_U, mv[0]);
  pinWrite_int32_t(OUT1_U, mv[1]);
  free((void*) mv);
  ART_ACTION_EXIT(action7__B5, 7);
}

bool_t RVC_decoder__parser__splitter_MV__DOLLAR__d8623(art_action_context_t *context, ActorInstance_RVC_decoder__parser__splitter_MV *thisActor) {
  int32_t btype;
  {
    bool_t ret;
    btype = pinPeek_int32_t(IN1_BTYPE, 0);
    ret = (bitand(btype, MOTION) != 0);
    return ret;
  }
}

// B6
ART_ACTION(action8__B6, ActorInstance_RVC_decoder__parser__splitter_MV) {
  int32_t* mv;
  int32_t btype;
  ART_ACTION_ENTER(action8__B6, 8);
  mv = malloc((sizeof(int32_t) * 2));
  btype = pinRead_int32_t(IN1_BTYPE);
  pinReadRepeat_int32_t(IN0_MV, mv, 2);
  pinWrite_int32_t(OUT2_V, mv[0]);
  pinWrite_int32_t(OUT2_V, mv[1]);
  free((void*) mv);
  ART_ACTION_EXIT(action8__B6, 8);
}

#define ActorInstance_RVC_decoder__parser__splitter_MV__cmd_ID 0
#define ActorInstance_RVC_decoder__parser__splitter_MV__skip_ID 1
#define ActorInstance_RVC_decoder__parser__splitter_MV__block2_ID 2
#define ActorInstance_RVC_decoder__parser__splitter_MV__block3_ID 3
#define ActorInstance_RVC_decoder__parser__splitter_MV__block4_ID 4
#define ActorInstance_RVC_decoder__parser__splitter_MV__block5_ID 5
#define ActorInstance_RVC_decoder__parser__splitter_MV__block6_ID 6
static void ActorInstance_RVC_decoder__parser__splitter_MV_constructor(AbstractActorInstance *pBase) {
  ActorInstance_RVC_decoder__parser__splitter_MV *thisActor=(ActorInstance_RVC_decoder__parser__splitter_MV*) pBase;
  thisActor->_fsmState = ActorInstance_RVC_decoder__parser__splitter_MV__cmd_ID;//Initial state
  {
  }

}
static const int exitcode_block_Any[3]={1,0,1};
ART_ACTION_SCHEDULER(RVC_decoder__parser__splitter_MV_action_scheduler) {
  const int *result = EXIT_CODE_YIELD;
  ActorInstance_RVC_decoder__parser__splitter_MV *thisActor=(ActorInstance_RVC_decoder__parser__splitter_MV*) pBase;
  ART_ACTION_SCHEDULER_ENTER(2, 3)
  while(1) {
    switch(thisActor->_fsmState) {
      case ActorInstance_RVC_decoder__parser__splitter_MV__cmd_ID:
        if ((pinAvailIn_int32_t(IN1_BTYPE) >= 1)) {
          if (RVC_decoder__parser__splitter_MV__DOLLAR__d8472(context, thisActor)) {
            ART_FIRE_ACTION(action0__newvop);
            thisActor->_fsmState = ActorInstance_RVC_decoder__parser__splitter_MV__skip_ID;
            continue;
          }
        }
        if ((pinAvailIn_int32_t(IN1_BTYPE) >= 1)) {
          if (RVC_decoder__parser__splitter_MV__DOLLAR__d8488(context, thisActor) && RVC_decoder__parser__splitter_MV__DOLLAR__d8497(context, thisActor)) {
            ART_FIRE_ACTION(action2__skipbtype);
            thisActor->_fsmState = ActorInstance_RVC_decoder__parser__splitter_MV__block2_ID;
            continue;
          }
        }
        if ((pinAvailIn_int32_t(IN0_MV) >= 2) && (pinAvailIn_int32_t(IN1_BTYPE) >= 1)) {
          if (RVC_decoder__parser__splitter_MV__DOLLAR__d8513(context, thisActor)) {
            if ((pinAvailOut_int32_t(OUT0_Y) >= 1*2)) {
              ART_FIRE_ACTION(action3__B1);
              thisActor->_fsmState = ActorInstance_RVC_decoder__parser__splitter_MV__block2_ID;
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
      
      case ActorInstance_RVC_decoder__parser__splitter_MV__skip_ID:
        if ((pinAvailIn_int32_t(IN1_BTYPE) >= 2)) {
          ART_FIRE_ACTION(action1__skip);
          thisActor->_fsmState = ActorInstance_RVC_decoder__parser__splitter_MV__cmd_ID;
          continue;
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__parser__splitter_MV__block2_ID:
        if ((pinAvailIn_int32_t(IN1_BTYPE) >= 1)) {
          if (RVC_decoder__parser__splitter_MV__DOLLAR__d8488(context, thisActor) && RVC_decoder__parser__splitter_MV__DOLLAR__d8497(context, thisActor)) {
            ART_FIRE_ACTION(action2__skipbtype);
            thisActor->_fsmState = ActorInstance_RVC_decoder__parser__splitter_MV__block3_ID;
            continue;
          }
        }
        if ((pinAvailIn_int32_t(IN0_MV) >= 2) && (pinAvailIn_int32_t(IN1_BTYPE) >= 1)) {
          if (RVC_decoder__parser__splitter_MV__DOLLAR__d8535(context, thisActor)) {
            if ((pinAvailOut_int32_t(OUT0_Y) >= 1*2)) {
              ART_FIRE_ACTION(action4__B2);
              thisActor->_fsmState = ActorInstance_RVC_decoder__parser__splitter_MV__block3_ID;
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
      
      case ActorInstance_RVC_decoder__parser__splitter_MV__block3_ID:
        if ((pinAvailIn_int32_t(IN1_BTYPE) >= 1)) {
          if (RVC_decoder__parser__splitter_MV__DOLLAR__d8488(context, thisActor) && RVC_decoder__parser__splitter_MV__DOLLAR__d8497(context, thisActor)) {
            ART_FIRE_ACTION(action2__skipbtype);
            thisActor->_fsmState = ActorInstance_RVC_decoder__parser__splitter_MV__block4_ID;
            continue;
          }
        }
        if ((pinAvailIn_int32_t(IN0_MV) >= 2) && (pinAvailIn_int32_t(IN1_BTYPE) >= 1)) {
          if (RVC_decoder__parser__splitter_MV__DOLLAR__d8557(context, thisActor)) {
            if ((pinAvailOut_int32_t(OUT0_Y) >= 1*2)) {
              ART_FIRE_ACTION(action5__B3);
              thisActor->_fsmState = ActorInstance_RVC_decoder__parser__splitter_MV__block4_ID;
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
      
      case ActorInstance_RVC_decoder__parser__splitter_MV__block4_ID:
        if ((pinAvailIn_int32_t(IN1_BTYPE) >= 1)) {
          if (RVC_decoder__parser__splitter_MV__DOLLAR__d8488(context, thisActor) && RVC_decoder__parser__splitter_MV__DOLLAR__d8497(context, thisActor)) {
            ART_FIRE_ACTION(action2__skipbtype);
            thisActor->_fsmState = ActorInstance_RVC_decoder__parser__splitter_MV__block5_ID;
            continue;
          }
        }
        if ((pinAvailIn_int32_t(IN0_MV) >= 2) && (pinAvailIn_int32_t(IN1_BTYPE) >= 1)) {
          if (RVC_decoder__parser__splitter_MV__DOLLAR__d8579(context, thisActor)) {
            if ((pinAvailOut_int32_t(OUT0_Y) >= 1*2)) {
              ART_FIRE_ACTION(action6__B4);
              thisActor->_fsmState = ActorInstance_RVC_decoder__parser__splitter_MV__block5_ID;
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
      
      case ActorInstance_RVC_decoder__parser__splitter_MV__block5_ID:
        if ((pinAvailIn_int32_t(IN0_MV) >= 2) && (pinAvailIn_int32_t(IN1_BTYPE) >= 1)) {
          if (RVC_decoder__parser__splitter_MV__DOLLAR__d8601(context, thisActor)) {
            if ((pinAvailOut_int32_t(OUT1_U) >= 1*2)) {
              ART_FIRE_ACTION(action7__B5);
              thisActor->_fsmState = ActorInstance_RVC_decoder__parser__splitter_MV__block6_ID;
              continue;
            
            } else {
              result = exitcode_block_Any;
              goto out;
            }
          }
        }
        if ((pinAvailIn_int32_t(IN1_BTYPE) >= 1)) {
          if (RVC_decoder__parser__splitter_MV__DOLLAR__d8488(context, thisActor) && RVC_decoder__parser__splitter_MV__DOLLAR__d8497(context, thisActor)) {
            ART_FIRE_ACTION(action2__skipbtype);
            thisActor->_fsmState = ActorInstance_RVC_decoder__parser__splitter_MV__block6_ID;
            continue;
          }
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__parser__splitter_MV__block6_ID:
        if ((pinAvailIn_int32_t(IN1_BTYPE) >= 1)) {
          if (RVC_decoder__parser__splitter_MV__DOLLAR__d8488(context, thisActor) && RVC_decoder__parser__splitter_MV__DOLLAR__d8497(context, thisActor)) {
            ART_FIRE_ACTION(action2__skipbtype);
            thisActor->_fsmState = ActorInstance_RVC_decoder__parser__splitter_MV__cmd_ID;
            continue;
          }
        }
        if ((pinAvailIn_int32_t(IN0_MV) >= 2) && (pinAvailIn_int32_t(IN1_BTYPE) >= 1)) {
          if (RVC_decoder__parser__splitter_MV__DOLLAR__d8623(context, thisActor)) {
            if ((pinAvailOut_int32_t(OUT2_V) >= 1*2)) {
              ART_FIRE_ACTION(action8__B6);
              thisActor->_fsmState = ActorInstance_RVC_decoder__parser__splitter_MV__cmd_ID;
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
      
    }
  }
  out:
  ART_ACTION_SCHEDULER_EXIT(2, 3)
  return result;
}