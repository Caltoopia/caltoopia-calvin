#include "actors-rts.h"
#include "natives.h"
#include "RVC__decoderDemo.h"
#define  IN0_AC_PRED_DIR ART_INPUT(0)
#define  IN1_QFS_AC ART_INPUT(1)
#define  OUT0_PQF_AC ART_OUTPUT(0)

//Actor constants
static const int32_t SAMPLE_SZ = 13;
static const int32_t BUF_SIZE = 128;
static const int32_t Scanmode[192] = {0, 1, 5, 6, 14, 15, 27, 28, 2, 4, 7, 13, 16, 26, 29, 42, 3, 8, 12, 17, 25, 30, 41, 43, 9, 11, 18, 24, 31, 40, 44, 53, 10, 19, 23, 32, 39, 45, 52, 54, 20, 22, 33, 38, 46, 51, 55, 60, 21, 34, 37, 47, 50, 56, 59, 61, 35, 36, 48, 49, 57, 58, 62, 63, 0, 4, 6, 20, 22, 36, 38, 52, 1, 5, 7, 21, 23, 37, 39, 53, 2, 8, 19, 24, 34, 40, 50, 54, 3, 9, 18, 25, 35, 41, 51, 55, 10, 17, 26, 30, 42, 46, 56, 60, 11, 16, 27, 31, 43, 47, 57, 61, 12, 15, 28, 32, 44, 48, 58, 62, 13, 14, 29, 33, 45, 49, 59, 63, 0, 1, 2, 3, 10, 11, 12, 13, 4, 5, 8, 9, 17, 16, 15, 14, 6, 7, 19, 18, 26, 27, 28, 29, 20, 21, 24, 25, 30, 31, 32, 33, 22, 23, 34, 35, 42, 43, 44, 45, 36, 37, 40, 41, 46, 47, 48, 49, 38, 39, 50, 51, 56, 57, 58, 59, 52, 53, 54, 55, 60, 61, 62, 63};

//Actor state
typedef struct {
  AbstractActorInstance base;
  int _fsmState;
  int32_t addr;
  int32_t add_buf;
  bool_t half;
  int32_t count;
  int32_t* buf;
} ActorInstance_RVC_decoder__texture_V__IS;

//Actor functions
static inline int32_t RVC_decoder__texture_V__ISwa(ActorInstance_RVC_decoder__texture_V__IS* thisActor){
  return bitor(bitand(thisActor->count, 63), ((thisActor->half) ? (64):(0)));
}
static inline int32_t RVC_decoder__texture_V__ISra(ActorInstance_RVC_decoder__texture_V__IS* thisActor, int32_t address){
  return bitor(bitand(address, 63), ((thisActor->half) ? (0):(64)));
}
ART_ACTION_CONTEXT(2, 1)

ART_ACTION(action0__skip, ActorInstance_RVC_decoder__texture_V__IS);
ART_ACTION(action1__start, ActorInstance_RVC_decoder__texture_V__IS);
ART_ACTION(action2__done, ActorInstance_RVC_decoder__texture_V__IS);
ART_ACTION(action3__read_only, ActorInstance_RVC_decoder__texture_V__IS);
ART_ACTION(action4__write_only, ActorInstance_RVC_decoder__texture_V__IS);
ART_ACTION(action5__read_write, ActorInstance_RVC_decoder__texture_V__IS);
ART_ACTION_SCHEDULER(RVC_decoder__texture_V__IS_action_scheduler);
static void ActorInstance_RVC_decoder__texture_V__IS_constructor(AbstractActorInstance *);

static const PortDescription inputPortDescriptions[]={
  {0, "AC_PRED_DIR", sizeof(int32_t), NULL},
  {0, "QFS_AC", sizeof(int32_t), NULL},
};
static const PortDescription outputPortDescriptions[]={
  {0, "PQF_AC", sizeof(int32_t), NULL},
};

static const int portRate_in_action0__skip[] = {1, 0};

static const int portRate_out_action0__skip[] = {0};

static const int portRate_in_action1__start[] = {1, 0};

static const int portRate_out_action1__start[] = {0};

static const int portRate_in_action2__done[] = {0, 0};

static const int portRate_out_action2__done[] = {0};

static const int portRate_in_action3__read_only[] = {0, 1};

static const int portRate_out_action3__read_only[] = {0};

static const int portRate_in_action4__write_only[] = {0, 0};

static const int portRate_out_action4__write_only[] = {1};

static const int portRate_in_action5__read_write[] = {0, 1};

static const int portRate_out_action5__read_write[] = {1};

static const ActionDescription actionDescriptions[] = {
  {"action0__skip", portRate_in_action0__skip, portRate_out_action0__skip},
  {"action1__start", portRate_in_action1__start, portRate_out_action1__start},
  {"action2__done", portRate_in_action2__done, portRate_out_action2__done},
  {"action3__read_only", portRate_in_action3__read_only, portRate_out_action3__read_only},
  {"action4__write_only", portRate_in_action4__write_only, portRate_out_action4__write_only},
  {"action5__read_write", portRate_in_action5__read_write, portRate_out_action5__read_write},
};

ActorClass klass=INIT_ActorClass(
  "RVC_decoder__texture_V__IS",
  ActorInstance_RVC_decoder__texture_V__IS,
  ActorInstance_RVC_decoder__texture_V__IS_constructor,
  0, //setParam not needed anymore (we instantiate with params)
  0, 0, // serialize/deserialize
  RVC_decoder__texture_V__IS_action_scheduler,
  0, // no destructor
  2, inputPortDescriptions,
  1, outputPortDescriptions,
  6, actionDescriptions
);

bool_t RVC_decoder__texture_V__IS__DOLLAR__d7125(art_action_context_t *context, ActorInstance_RVC_decoder__texture_V__IS *thisActor) {
  int32_t i;
  {
    bool_t ret;
    i = pinPeek_int32_t(IN0_AC_PRED_DIR, 0);
    ret = (i < 0);
    return ret;
  }
}

// skip
ART_ACTION(action0__skip, ActorInstance_RVC_decoder__texture_V__IS) {
  int32_t i;
  ART_ACTION_ENTER(action0__skip, 0);
  i = pinRead_int32_t(IN0_AC_PRED_DIR);
  ART_ACTION_EXIT(action0__skip, 0);
}

bool_t RVC_decoder__texture_V__IS__DOLLAR__d7134(art_action_context_t *context, ActorInstance_RVC_decoder__texture_V__IS *thisActor) {
  int32_t i;
  {
    bool_t ret;
    i = pinPeek_int32_t(IN0_AC_PRED_DIR, 0);
    ret = (i >= 0);
    return ret;
  }
}

// start
ART_ACTION(action1__start, ActorInstance_RVC_decoder__texture_V__IS) {
  int32_t i;
  ART_ACTION_ENTER(action1__start, 1);
  i = pinRead_int32_t(IN0_AC_PRED_DIR);
  thisActor->add_buf = i;
  ART_ACTION_EXIT(action1__start, 1);
}

bool_t RVC_decoder__texture_V__IS__DOLLAR__d7141(art_action_context_t *context, ActorInstance_RVC_decoder__texture_V__IS *thisActor) {
  {
    bool_t ret;
    ret = (thisActor->count == 64);
    return ret;
  }
}

// done
ART_ACTION(action2__done, ActorInstance_RVC_decoder__texture_V__IS) {
  ART_ACTION_ENTER(action2__done, 2);
  thisActor->count = 1;
  thisActor->half = (!(thisActor->half));
  thisActor->addr = (((thisActor->add_buf == 0)) ? (0):((((thisActor->add_buf == 1)) ? (64):(128))));
  ART_ACTION_EXIT(action2__done, 2);
}

bool_t RVC_decoder__texture_V__IS__DOLLAR__d7162(art_action_context_t *context, ActorInstance_RVC_decoder__texture_V__IS *thisActor) {
  {
    bool_t ret;
    ret = (thisActor->count < 64);
    return ret;
  }
}

// read_only
ART_ACTION(action3__read_only, ActorInstance_RVC_decoder__texture_V__IS) {
  int32_t ac;
  ART_ACTION_ENTER(action3__read_only, 3);
  ac = pinRead_int32_t(IN1_QFS_AC);
  thisActor->buf[bitor(bitand(thisActor->count, 63), ((thisActor->half) ? (64):(0)))] = ac;
  thisActor->count = (thisActor->count + 1);
  ART_ACTION_EXIT(action3__read_only, 3);
}

bool_t RVC_decoder__texture_V__IS__DOLLAR__d7172(art_action_context_t *context, ActorInstance_RVC_decoder__texture_V__IS *thisActor) {
  {
    bool_t ret;
    ret = (thisActor->count < 64);
    return ret;
  }
}

// write_only
ART_ACTION(action4__write_only, ActorInstance_RVC_decoder__texture_V__IS) {
  ART_ACTION_ENTER(action4__write_only, 4);
  thisActor->addr = (thisActor->addr + 1);
  thisActor->count = (thisActor->count + 1);
  pinWrite_int32_t(OUT0_PQF_AC, thisActor->buf[RVC_decoder__texture_V__ISra(thisActor, Scanmode[thisActor->addr])]);
  ART_ACTION_EXIT(action4__write_only, 4);
}

bool_t RVC_decoder__texture_V__IS__DOLLAR__d7192(art_action_context_t *context, ActorInstance_RVC_decoder__texture_V__IS *thisActor) {
  {
    bool_t ret;
    ret = (thisActor->count < 64);
    return ret;
  }
}

// read_write
ART_ACTION(action5__read_write, ActorInstance_RVC_decoder__texture_V__IS) {
  int32_t ac;
  ART_ACTION_ENTER(action5__read_write, 5);
  ac = pinRead_int32_t(IN1_QFS_AC);
  thisActor->buf[bitor(bitand(thisActor->count, 63), ((thisActor->half) ? (64):(0)))] = ac;
  thisActor->count = (thisActor->count + 1);
  thisActor->addr = (thisActor->addr + 1);
  pinWrite_int32_t(OUT0_PQF_AC, thisActor->buf[RVC_decoder__texture_V__ISra(thisActor, Scanmode[thisActor->addr])]);
  ART_ACTION_EXIT(action5__read_write, 5);
}

#define ActorInstance_RVC_decoder__texture_V__IS__rest_ID 0
#define ActorInstance_RVC_decoder__texture_V__IS__read_ID 1
#define ActorInstance_RVC_decoder__texture_V__IS__full_ID 2
#define ActorInstance_RVC_decoder__texture_V__IS__write_ID 3
#define ActorInstance_RVC_decoder__texture_V__IS__both_ID 4
static void ActorInstance_RVC_decoder__texture_V__IS_constructor(AbstractActorInstance *pBase) {
  ActorInstance_RVC_decoder__texture_V__IS *thisActor=(ActorInstance_RVC_decoder__texture_V__IS*) pBase;
  thisActor->_fsmState = ActorInstance_RVC_decoder__texture_V__IS__rest_ID;//Initial state
  {
    thisActor->buf = malloc((sizeof(int32_t) * 128));
    thisActor->half = 0;
    thisActor->count = 1;
    {
      int32_t k;
      for(k = 1; k <= 128; k++)
      {
        thisActor->buf[((0 + k) - 1)] = 0;
      }
    }
  }

}
static const int exitcode_block_Any[3]={1,0,1};
ART_ACTION_SCHEDULER(RVC_decoder__texture_V__IS_action_scheduler) {
  const int *result = EXIT_CODE_YIELD;
  ActorInstance_RVC_decoder__texture_V__IS *thisActor=(ActorInstance_RVC_decoder__texture_V__IS*) pBase;
  ART_ACTION_SCHEDULER_ENTER(2, 1)
  while(1) {
    switch(thisActor->_fsmState) {
      case ActorInstance_RVC_decoder__texture_V__IS__rest_ID:
        if ((pinAvailIn_int32_t(IN0_AC_PRED_DIR) >= 1)) {
          if (RVC_decoder__texture_V__IS__DOLLAR__d7125(context, thisActor)) {
            ART_FIRE_ACTION(action0__skip);
            thisActor->_fsmState = ActorInstance_RVC_decoder__texture_V__IS__rest_ID;
            continue;
          }
        }
        if ((pinAvailIn_int32_t(IN0_AC_PRED_DIR) >= 1)) {
          if (RVC_decoder__texture_V__IS__DOLLAR__d7134(context, thisActor)) {
            ART_FIRE_ACTION(action1__start);
            thisActor->_fsmState = ActorInstance_RVC_decoder__texture_V__IS__read_ID;
            continue;
          }
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__texture_V__IS__read_ID:
        if (RVC_decoder__texture_V__IS__DOLLAR__d7141(context, thisActor)) {
          ART_FIRE_ACTION(action2__done);
          thisActor->_fsmState = ActorInstance_RVC_decoder__texture_V__IS__full_ID;
          continue;
        }
        if ((pinAvailIn_int32_t(IN1_QFS_AC) >= 1)) {
          if (RVC_decoder__texture_V__IS__DOLLAR__d7162(context, thisActor)) {
            ART_FIRE_ACTION(action3__read_only);
            thisActor->_fsmState = ActorInstance_RVC_decoder__texture_V__IS__read_ID;
            continue;
          }
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__texture_V__IS__full_ID:
        if ((pinAvailIn_int32_t(IN0_AC_PRED_DIR) >= 1)) {
          if (RVC_decoder__texture_V__IS__DOLLAR__d7125(context, thisActor)) {
            ART_FIRE_ACTION(action0__skip);
            thisActor->_fsmState = ActorInstance_RVC_decoder__texture_V__IS__write_ID;
            continue;
          }
        }
        if ((pinAvailIn_int32_t(IN0_AC_PRED_DIR) >= 1)) {
          if (RVC_decoder__texture_V__IS__DOLLAR__d7134(context, thisActor)) {
            ART_FIRE_ACTION(action1__start);
            thisActor->_fsmState = ActorInstance_RVC_decoder__texture_V__IS__both_ID;
            continue;
          }
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__texture_V__IS__write_ID:
        if (RVC_decoder__texture_V__IS__DOLLAR__d7141(context, thisActor)) {
          ART_FIRE_ACTION(action2__done);
          thisActor->_fsmState = ActorInstance_RVC_decoder__texture_V__IS__rest_ID;
          continue;
        }
        if (RVC_decoder__texture_V__IS__DOLLAR__d7172(context, thisActor)) {
          if ((pinAvailOut_int32_t(OUT0_PQF_AC) >= 1)) {
            ART_FIRE_ACTION(action4__write_only);
            thisActor->_fsmState = ActorInstance_RVC_decoder__texture_V__IS__write_ID;
            continue;
          
          } else {
            result = exitcode_block_Any;
            goto out;
          }
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__texture_V__IS__both_ID:
        if (RVC_decoder__texture_V__IS__DOLLAR__d7141(context, thisActor)) {
          ART_FIRE_ACTION(action2__done);
          thisActor->_fsmState = ActorInstance_RVC_decoder__texture_V__IS__full_ID;
          continue;
        }
        if ((pinAvailIn_int32_t(IN1_QFS_AC) >= 1)) {
          if (RVC_decoder__texture_V__IS__DOLLAR__d7192(context, thisActor)) {
            if ((pinAvailOut_int32_t(OUT0_PQF_AC) >= 1)) {
              ART_FIRE_ACTION(action5__read_write);
              thisActor->_fsmState = ActorInstance_RVC_decoder__texture_V__IS__both_ID;
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
  ART_ACTION_SCHEDULER_EXIT(2, 1)
  return result;
}