#include "actors-rts.h"
#include "natives.h"
#include "RVC__decoderDemo.h"
#define  IN0_RD ART_INPUT(0)
#define  IN1_halfpel ART_INPUT(1)
#define  OUT0_MOT ART_OUTPUT(0)

//Actor constants
static const int32_t PIX_SZ = 9;
static const int32_t FLAG_SZ = 4;
static const bool_t _CAL_tokenMonitor = 1;

//Actor state
typedef struct {
  AbstractActorInstance base;
  int _fsmState;
  int32_t x;
  int32_t d5;
  int32_t flags;
  int32_t d9;
  int32_t d1;
  int32_t d0;
  int32_t d4;
  int32_t d6;
  int32_t d7;
  int32_t d3;
  int32_t d2;
  int32_t y;
  int32_t d8;
  int32_t round;
} ActorInstance_RVC_decoder__motion_V__interpolation;

//Actor functions
static inline int32_t RVC_decoder__motion_V__interpolationcompensate(ActorInstance_RVC_decoder__motion_V__interpolation* thisActor, int32_t p00, int32_t p10, int32_t p01, int32_t p11){
  return (((thisActor->flags == 0)) ? (p00):((((thisActor->flags == 1)) ? (rshift((((p00 + p01) + 1) - thisActor->round), 1)):((((thisActor->flags == 2)) ? (rshift((((p00 + p10) + 1) - thisActor->round), 1)):(rshift((((((p00 + p10) + p01) + p11) + 2) - thisActor->round), 2)))))));
}
ART_ACTION_CONTEXT(2, 1)

ART_ACTION(action0__start, ActorInstance_RVC_decoder__motion_V__interpolation);
ART_ACTION(action1__done, ActorInstance_RVC_decoder__motion_V__interpolation);
ART_ACTION(action2__row_col_0, ActorInstance_RVC_decoder__motion_V__interpolation);
ART_ACTION(action3__other, ActorInstance_RVC_decoder__motion_V__interpolation);
ART_ACTION_SCHEDULER(RVC_decoder__motion_V__interpolation_action_scheduler);
static void ActorInstance_RVC_decoder__motion_V__interpolation_constructor(AbstractActorInstance *);

static const PortDescription inputPortDescriptions[]={
  {0, "RD", sizeof(int32_t), NULL},
  {0, "halfpel", sizeof(int32_t), NULL},
};
static const PortDescription outputPortDescriptions[]={
  {0, "MOT", sizeof(int32_t), NULL},
};

static const int portRate_in_action0__start[] = {0, 1};

static const int portRate_out_action0__start[] = {0};

static const int portRate_in_action1__done[] = {0, 0};

static const int portRate_out_action1__done[] = {0};

static const int portRate_in_action2__row_col_0[] = {1, 0};

static const int portRate_out_action2__row_col_0[] = {0};

static const int portRate_in_action3__other[] = {1, 0};

static const int portRate_out_action3__other[] = {1};

static const ActionDescription actionDescriptions[] = {
  {"action0__start", portRate_in_action0__start, portRate_out_action0__start},
  {"action1__done", portRate_in_action1__done, portRate_out_action1__done},
  {"action2__row_col_0", portRate_in_action2__row_col_0, portRate_out_action2__row_col_0},
  {"action3__other", portRate_in_action3__other, portRate_out_action3__other},
};

ActorClass klass=INIT_ActorClass(
  "RVC_decoder__motion_V__interpolation",
  ActorInstance_RVC_decoder__motion_V__interpolation,
  ActorInstance_RVC_decoder__motion_V__interpolation_constructor,
  0, //setParam not needed anymore (we instantiate with params)
  0, 0, // serialize/deserialize
  RVC_decoder__motion_V__interpolation_action_scheduler,
  0, // no destructor
  2, inputPortDescriptions,
  1, outputPortDescriptions,
  4, actionDescriptions
);


// start
ART_ACTION(action0__start, ActorInstance_RVC_decoder__motion_V__interpolation) {
  int32_t f;
  ART_ACTION_ENTER(action0__start, 0);
  f = pinRead_int32_t(IN1_halfpel);
  thisActor->x = 0;
  thisActor->y = 0;
  thisActor->flags = rshift(f, 1);
  thisActor->round = bitand(f, 1);
  ART_ACTION_EXIT(action0__start, 0);
}

bool_t RVC_decoder__motion_V__interpolation__DOLLAR__d1756(art_action_context_t *context, ActorInstance_RVC_decoder__motion_V__interpolation *thisActor) {
  {
    bool_t ret;
    ret = (thisActor->y == 9);
    return ret;
  }
}

// done
ART_ACTION(action1__done, ActorInstance_RVC_decoder__motion_V__interpolation) {
  ART_ACTION_ENTER(action1__done, 1);
  ART_ACTION_EXIT(action1__done, 1);
}

bool_t RVC_decoder__motion_V__interpolation__DOLLAR__d1763(art_action_context_t *context, ActorInstance_RVC_decoder__motion_V__interpolation *thisActor) {
  {
    bool_t ret;
    ret = ((thisActor->x == 0) || (thisActor->y == 0));
    return ret;
  }
}

// row_col_0
ART_ACTION(action2__row_col_0, ActorInstance_RVC_decoder__motion_V__interpolation) {
  int32_t d;
  ART_ACTION_ENTER(action2__row_col_0, 2);
  d = pinRead_int32_t(IN0_RD);
  thisActor->d9 = thisActor->d8;
  thisActor->d8 = thisActor->d7;
  thisActor->d7 = thisActor->d6;
  thisActor->d6 = thisActor->d5;
  thisActor->d5 = thisActor->d4;
  thisActor->d4 = thisActor->d3;
  thisActor->d3 = thisActor->d2;
  thisActor->d2 = thisActor->d1;
  thisActor->d1 = thisActor->d0;
  thisActor->d0 = d;
  thisActor->x = (thisActor->x + 1);
  if ((thisActor->x >= 9)) {
    thisActor->x = 0;
    thisActor->y = (thisActor->y + 1);
  }
  ART_ACTION_EXIT(action2__row_col_0, 2);
}

bool_t RVC_decoder__motion_V__interpolation__DOLLAR__d1796(art_action_context_t *context, ActorInstance_RVC_decoder__motion_V__interpolation *thisActor) {
  {
    bool_t ret;
    ret = (thisActor->x != 0);
    return ret;
  }
}
bool_t RVC_decoder__motion_V__interpolation__DOLLAR__d1800(art_action_context_t *context, ActorInstance_RVC_decoder__motion_V__interpolation *thisActor) {
  {
    bool_t ret;
    ret = (thisActor->y != 0);
    return ret;
  }
}
bool_t RVC_decoder__motion_V__interpolation__DOLLAR__d1804(art_action_context_t *context, ActorInstance_RVC_decoder__motion_V__interpolation *thisActor) {
  {
    bool_t ret;
    ret = (thisActor->y != 9);
    return ret;
  }
}

// other
ART_ACTION(action3__other, ActorInstance_RVC_decoder__motion_V__interpolation) {
  int32_t d;
  int32_t p;
  ART_ACTION_ENTER(action3__other, 3);
  d = pinRead_int32_t(IN0_RD);
  p = RVC_decoder__motion_V__interpolationcompensate(thisActor, thisActor->d9, thisActor->d8, thisActor->d0, d);
  thisActor->d9 = thisActor->d8;
  thisActor->d8 = thisActor->d7;
  thisActor->d7 = thisActor->d6;
  thisActor->d6 = thisActor->d5;
  thisActor->d5 = thisActor->d4;
  thisActor->d4 = thisActor->d3;
  thisActor->d3 = thisActor->d2;
  thisActor->d2 = thisActor->d1;
  thisActor->d1 = thisActor->d0;
  thisActor->d0 = d;
  thisActor->x = (thisActor->x + 1);
  if ((thisActor->x >= 9)) {
    thisActor->x = 0;
    thisActor->y = (thisActor->y + 1);
  }
  pinWrite_int32_t(OUT0_MOT, p);
  ART_ACTION_EXIT(action3__other, 3);
}

#define ActorInstance_RVC_decoder__motion_V__interpolation__start_ID 0
#define ActorInstance_RVC_decoder__motion_V__interpolation__interpolate_ID 1
static void ActorInstance_RVC_decoder__motion_V__interpolation_constructor(AbstractActorInstance *pBase) {
  ActorInstance_RVC_decoder__motion_V__interpolation *thisActor=(ActorInstance_RVC_decoder__motion_V__interpolation*) pBase;
  thisActor->_fsmState = ActorInstance_RVC_decoder__motion_V__interpolation__start_ID;//Initial state
  {
  }

}
static const int exitcode_block_Any[3]={1,0,1};
ART_ACTION_SCHEDULER(RVC_decoder__motion_V__interpolation_action_scheduler) {
  const int *result = EXIT_CODE_YIELD;
  ActorInstance_RVC_decoder__motion_V__interpolation *thisActor=(ActorInstance_RVC_decoder__motion_V__interpolation*) pBase;
  ART_ACTION_SCHEDULER_ENTER(2, 1)
  while(1) {
    switch(thisActor->_fsmState) {
      case ActorInstance_RVC_decoder__motion_V__interpolation__start_ID:
        if ((pinAvailIn_int32_t(IN1_halfpel) >= 1)) {
          ART_FIRE_ACTION(action0__start);
          thisActor->_fsmState = ActorInstance_RVC_decoder__motion_V__interpolation__interpolate_ID;
          continue;
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__motion_V__interpolation__interpolate_ID:
        if (RVC_decoder__motion_V__interpolation__DOLLAR__d1756(context, thisActor)) {
          ART_FIRE_ACTION(action1__done);
          thisActor->_fsmState = ActorInstance_RVC_decoder__motion_V__interpolation__start_ID;
          continue;
        }
        if ((pinAvailIn_int32_t(IN0_RD) >= 1)) {
          if (RVC_decoder__motion_V__interpolation__DOLLAR__d1763(context, thisActor)) {
            ART_FIRE_ACTION(action2__row_col_0);
            thisActor->_fsmState = ActorInstance_RVC_decoder__motion_V__interpolation__interpolate_ID;
            continue;
          }
        }
        if ((pinAvailIn_int32_t(IN0_RD) >= 1)) {
          if (RVC_decoder__motion_V__interpolation__DOLLAR__d1796(context, thisActor) && RVC_decoder__motion_V__interpolation__DOLLAR__d1800(context, thisActor) && RVC_decoder__motion_V__interpolation__DOLLAR__d1804(context, thisActor)) {
            if ((pinAvailOut_int32_t(OUT0_MOT) >= 1)) {
              ART_FIRE_ACTION(action3__other);
              thisActor->_fsmState = ActorInstance_RVC_decoder__motion_V__interpolation__interpolate_ID;
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