#include "actors-rts.h"
#include "natives.h"
#include "RVC__decoderDemo.h"
#define  IN0_RUN ART_INPUT(0)
#define  IN1_VALUE ART_INPUT(1)
#define  IN2_LAST ART_INPUT(2)
#define  OUT0_OUT ART_OUTPUT(0)

//Actor constants
static const int32_t SAMPLE_COUNT_SZ = 8;
static const int32_t SAMPLE_SZ = 13;
static const int32_t BLOCK_SIZE = 64;

//Actor state
typedef struct {
  AbstractActorInstance base;
  int _fsmState;
  bool_t last;
  int32_t next_value;
  int32_t count;
  int32_t run;
} ActorInstance_RVC_decoder__parser__blkexp;

//Actor functions
ART_ACTION_CONTEXT(3, 1)

ART_ACTION(action0__done, ActorInstance_RVC_decoder__parser__blkexp);
ART_ACTION(action1__write__value, ActorInstance_RVC_decoder__parser__blkexp);
ART_ACTION(action2__write__zero, ActorInstance_RVC_decoder__parser__blkexp);
ART_ACTION(action3__read__immediate, ActorInstance_RVC_decoder__parser__blkexp);
ART_ACTION(action4__read__save, ActorInstance_RVC_decoder__parser__blkexp);
ART_ACTION_SCHEDULER(RVC_decoder__parser__blkexp_action_scheduler);
static void ActorInstance_RVC_decoder__parser__blkexp_constructor(AbstractActorInstance *);

static const PortDescription inputPortDescriptions[]={
  {0, "RUN", sizeof(int32_t), NULL},
  {0, "VALUE", sizeof(int32_t), NULL},
  {0, "LAST", sizeof(bool_t), NULL},
};
static const PortDescription outputPortDescriptions[]={
  {0, "OUT", sizeof(int32_t), NULL},
};

static const int portRate_in_action0__done[] = {0, 0, 0};

static const int portRate_out_action0__done[] = {0};

static const int portRate_in_action1__write__value[] = {0, 0, 0};

static const int portRate_out_action1__write__value[] = {1};

static const int portRate_in_action2__write__zero[] = {0, 0, 0};

static const int portRate_out_action2__write__zero[] = {1};

static const int portRate_in_action3__read__immediate[] = {1, 1, 1};

static const int portRate_out_action3__read__immediate[] = {1};

static const int portRate_in_action4__read__save[] = {1, 1, 1};

static const int portRate_out_action4__read__save[] = {1};

static const ActionDescription actionDescriptions[] = {
  {"action0__done", portRate_in_action0__done, portRate_out_action0__done},
  {"action1__write__value", portRate_in_action1__write__value, portRate_out_action1__write__value},
  {"action2__write__zero", portRate_in_action2__write__zero, portRate_out_action2__write__zero},
  {"action3__read__immediate", portRate_in_action3__read__immediate, portRate_out_action3__read__immediate},
  {"action4__read__save", portRate_in_action4__read__save, portRate_out_action4__read__save},
};

ActorClass klass=INIT_ActorClass(
  "RVC_decoder__parser__blkexp",
  ActorInstance_RVC_decoder__parser__blkexp,
  ActorInstance_RVC_decoder__parser__blkexp_constructor,
  0, //setParam not needed anymore (we instantiate with params)
  0, 0, // serialize/deserialize
  RVC_decoder__parser__blkexp_action_scheduler,
  0, // no destructor
  3, inputPortDescriptions,
  1, outputPortDescriptions,
  5, actionDescriptions
);

bool_t RVC_decoder__parser__blkexp__DOLLAR__d2549(art_action_context_t *context, ActorInstance_RVC_decoder__parser__blkexp *thisActor) {
  {
    bool_t ret;
    ret = (thisActor->count == 64);
    return ret;
  }
}

// done
ART_ACTION(action0__done, ActorInstance_RVC_decoder__parser__blkexp) {
  ART_ACTION_ENTER(action0__done, 0);
  thisActor->count = 0;
  thisActor->run = -1;
  thisActor->last = 0;
  ART_ACTION_EXIT(action0__done, 0);
}

bool_t RVC_decoder__parser__blkexp__DOLLAR__d2557(art_action_context_t *context, ActorInstance_RVC_decoder__parser__blkexp *thisActor) {
  {
    bool_t ret;
    ret = (thisActor->run == 0);
    return ret;
  }
}

// write.value
ART_ACTION(action1__write__value, ActorInstance_RVC_decoder__parser__blkexp) {
  ART_ACTION_ENTER(action1__write__value, 1);
  thisActor->run = -1;
  thisActor->count = (thisActor->count + 1);
  pinWrite_int32_t(OUT0_OUT, thisActor->next_value);
  ART_ACTION_EXIT(action1__write__value, 1);
}

bool_t RVC_decoder__parser__blkexp__DOLLAR__d2569(art_action_context_t *context, ActorInstance_RVC_decoder__parser__blkexp *thisActor) {
  {
    bool_t ret;
    ret = ((thisActor->run > 0) || thisActor->last);
    return ret;
  }
}

// write.zero
ART_ACTION(action2__write__zero, ActorInstance_RVC_decoder__parser__blkexp) {
  int32_t U__19;
  ART_ACTION_ENTER(action2__write__zero, 2);
  thisActor->run = (thisActor->run - 1);
  thisActor->count = (thisActor->count + 1);
  U__19 = 0;
  pinWrite_int32_t(OUT0_OUT, U__19);
  ART_ACTION_EXIT(action2__write__zero, 2);
}

bool_t RVC_decoder__parser__blkexp__DOLLAR__d2594(art_action_context_t *context, ActorInstance_RVC_decoder__parser__blkexp *thisActor) {
  int32_t r;
  {
    bool_t ret;
    r = pinPeek_int32_t(IN0_RUN, 0);
    ret = (r == 0);
    return ret;
  }
}
bool_t RVC_decoder__parser__blkexp__DOLLAR__d2600(art_action_context_t *context, ActorInstance_RVC_decoder__parser__blkexp *thisActor) {
  {
    bool_t ret;
    ret = (thisActor->count != 64);
    return ret;
  }
}

// read.immediate
ART_ACTION(action3__read__immediate, ActorInstance_RVC_decoder__parser__blkexp) {
  int32_t r;
  int32_t v;
  bool_t l;
  ART_ACTION_ENTER(action3__read__immediate, 3);
  l = pinRead_bool_t(IN2_LAST);
  v = pinRead_int32_t(IN1_VALUE);
  r = pinRead_int32_t(IN0_RUN);
  thisActor->last = l;
  thisActor->count = (thisActor->count + 1);
  pinWrite_int32_t(OUT0_OUT, v);
  ART_ACTION_EXIT(action3__read__immediate, 3);
}

bool_t RVC_decoder__parser__blkexp__DOLLAR__d2619(art_action_context_t *context, ActorInstance_RVC_decoder__parser__blkexp *thisActor) {
  {
    bool_t ret;
    ret = (thisActor->count != 64);
    return ret;
  }
}

// read.save
ART_ACTION(action4__read__save, ActorInstance_RVC_decoder__parser__blkexp) {
  int32_t r;
  int32_t v;
  bool_t l;
  int32_t U__20;
  ART_ACTION_ENTER(action4__read__save, 4);
  l = pinRead_bool_t(IN2_LAST);
  v = pinRead_int32_t(IN1_VALUE);
  r = pinRead_int32_t(IN0_RUN);
  thisActor->run = (r - 1);
  thisActor->next_value = v;
  thisActor->last = l;
  thisActor->count = (thisActor->count + 1);
  U__20 = 0;
  pinWrite_int32_t(OUT0_OUT, U__20);
  ART_ACTION_EXIT(action4__read__save, 4);
}

#define ActorInstance_RVC_decoder__parser__blkexp__defaultState_ID 0
static void ActorInstance_RVC_decoder__parser__blkexp_constructor(AbstractActorInstance *pBase) {
  ActorInstance_RVC_decoder__parser__blkexp *thisActor=(ActorInstance_RVC_decoder__parser__blkexp*) pBase;
  thisActor->_fsmState = ActorInstance_RVC_decoder__parser__blkexp__defaultState_ID;//Initial state
  {
    thisActor->last = 0;
    thisActor->count = 0;
    thisActor->run = -1;
  }

}
static const int exitcode_block_Any[3]={1,0,1};
ART_ACTION_SCHEDULER(RVC_decoder__parser__blkexp_action_scheduler) {
  const int *result = EXIT_CODE_YIELD;
  ActorInstance_RVC_decoder__parser__blkexp *thisActor=(ActorInstance_RVC_decoder__parser__blkexp*) pBase;
  ART_ACTION_SCHEDULER_ENTER(3, 1)
  while(1) {
    switch(thisActor->_fsmState) {
      case ActorInstance_RVC_decoder__parser__blkexp__defaultState_ID:
        if (RVC_decoder__parser__blkexp__DOLLAR__d2549(context, thisActor)) {
          ART_FIRE_ACTION(action0__done);
          thisActor->_fsmState = ActorInstance_RVC_decoder__parser__blkexp__defaultState_ID;
          continue;
        }
        if (RVC_decoder__parser__blkexp__DOLLAR__d2557(context, thisActor)) {
          if ((pinAvailOut_int32_t(OUT0_OUT) >= 1)) {
            ART_FIRE_ACTION(action1__write__value);
            thisActor->_fsmState = ActorInstance_RVC_decoder__parser__blkexp__defaultState_ID;
            continue;
          
          } else {
            result = exitcode_block_Any;
            goto out;
          }
        }
        if (RVC_decoder__parser__blkexp__DOLLAR__d2569(context, thisActor)) {
          if ((pinAvailOut_int32_t(OUT0_OUT) >= 1)) {
            ART_FIRE_ACTION(action2__write__zero);
            thisActor->_fsmState = ActorInstance_RVC_decoder__parser__blkexp__defaultState_ID;
            continue;
          
          } else {
            result = exitcode_block_Any;
            goto out;
          }
        }
        if ((pinAvailIn_int32_t(IN0_RUN) >= 1) && (pinAvailIn_int32_t(IN1_VALUE) >= 1) && (pinAvailIn_bool_t(IN2_LAST) >= 1)) {
          if (RVC_decoder__parser__blkexp__DOLLAR__d2594(context, thisActor) && RVC_decoder__parser__blkexp__DOLLAR__d2600(context, thisActor)) {
            if ((pinAvailOut_int32_t(OUT0_OUT) >= 1)) {
              ART_FIRE_ACTION(action3__read__immediate);
              thisActor->_fsmState = ActorInstance_RVC_decoder__parser__blkexp__defaultState_ID;
              continue;
            
            } else {
              result = exitcode_block_Any;
              goto out;
            }
          }
        }
        if ((pinAvailIn_int32_t(IN0_RUN) >= 1) && (pinAvailIn_int32_t(IN1_VALUE) >= 1) && (pinAvailIn_bool_t(IN2_LAST) >= 1)) {
          if (RVC_decoder__parser__blkexp__DOLLAR__d2619(context, thisActor)) {
            if ((pinAvailOut_int32_t(OUT0_OUT) >= 1)) {
              ART_FIRE_ACTION(action4__read__save);
              thisActor->_fsmState = ActorInstance_RVC_decoder__parser__blkexp__defaultState_ID;
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
  ART_ACTION_SCHEDULER_EXIT(3, 1)
  return result;
}