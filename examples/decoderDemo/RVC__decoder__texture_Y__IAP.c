#include "actors-rts.h"
#include "natives.h"
#include "RVC__decoderDemo.h"
#define  IN0_PQF_AC ART_INPUT(0)
#define  IN1_PTR ART_INPUT(1)
#define  IN2_AC_PRED_DIR ART_INPUT(2)
#define  IN3_QP ART_INPUT(3)
#define  IN4_PREV_QP ART_INPUT(4)
#define  OUT0_QF_AC ART_OUTPUT(0)

//Actor constants
static const int32_t MAXW_IN_MB = 121;
static const int32_t MB_COORD_SZ = 8;
static const int32_t SAMPLE_SZ = 13;
static const int32_t BUF_SIZE = 492;

//Actor state
typedef struct {
  AbstractActorInstance base;
  int _fsmState;
  int32_t s_prev_quant;
  bool_t acpred_flag;
  int32_t s_quant;
  int32_t ptr;
  int32_t comp;
  int32_t pred_ptr;
  int32_t count;
  bool_t top;
  int32_t* buf;
} ActorInstance_RVC_decoder__texture_Y__IAP;

//Actor functions
static inline int32_t RVC_decoder__texture_Y__IAPdivroundnearest(ActorInstance_RVC_decoder__texture_Y__IAP* thisActor, int32_t i, int32_t iDenom){
  return (((i >= 0)) ? (((i + (iDenom >> 1)) / iDenom)):(((i - (iDenom >> 1)) / iDenom)));
}
ART_ACTION_CONTEXT(5, 1)

ART_ACTION(action0__newvop, ActorInstance_RVC_decoder__texture_Y__IAP);
ART_ACTION(action1__skip, ActorInstance_RVC_decoder__texture_Y__IAP);
ART_ACTION(action2__start, ActorInstance_RVC_decoder__texture_Y__IAP);
ART_ACTION(action3__advance, ActorInstance_RVC_decoder__texture_Y__IAP);
ART_ACTION(action4__copy, ActorInstance_RVC_decoder__texture_Y__IAP);
ART_ACTION_SCHEDULER(RVC_decoder__texture_Y__IAP_action_scheduler);
static void ActorInstance_RVC_decoder__texture_Y__IAP_constructor(AbstractActorInstance *);

static const PortDescription inputPortDescriptions[]={
  {0, "PQF_AC", sizeof(int32_t)},
  {0, "PTR", sizeof(int32_t)},
  {0, "AC_PRED_DIR", sizeof(int32_t)},
  {0, "QP", sizeof(int32_t)},
  {0, "PREV_QP", sizeof(int32_t)},
};
static const PortDescription outputPortDescriptions[]={
  {0, "QF_AC", sizeof(int32_t)},
};

static const int portRate_in_action0__newvop[] = {0, 0, 1, 0, 0};

static const int portRate_out_action0__newvop[] = {0};

static const int portRate_in_action1__skip[] = {0, 0, 1, 0, 0};

static const int portRate_out_action1__skip[] = {0};

static const int portRate_in_action2__start[] = {0, 1, 1, 1, 1};

static const int portRate_out_action2__start[] = {0};

static const int portRate_in_action3__advance[] = {0, 0, 0, 0, 0};

static const int portRate_out_action3__advance[] = {0};

static const int portRate_in_action4__copy[] = {1, 0, 0, 0, 0};

static const int portRate_out_action4__copy[] = {1};

static const ActionDescription actionDescriptions[] = {
  {"action0__newvop", portRate_in_action0__newvop, portRate_out_action0__newvop},
  {"action1__skip", portRate_in_action1__skip, portRate_out_action1__skip},
  {"action2__start", portRate_in_action2__start, portRate_out_action2__start},
  {"action3__advance", portRate_in_action3__advance, portRate_out_action3__advance},
  {"action4__copy", portRate_in_action4__copy, portRate_out_action4__copy},
};

ActorClass klass=INIT_ActorClass(
  "RVC_decoder__texture_Y__IAP",
  ActorInstance_RVC_decoder__texture_Y__IAP,
  ActorInstance_RVC_decoder__texture_Y__IAP_constructor,
  0, //setParam not needed anymore (we instantiate with params)
  RVC_decoder__texture_Y__IAP_action_scheduler,
  0, // no destructor
  5, inputPortDescriptions,
  1, outputPortDescriptions,
  5, actionDescriptions
);

bool_t RVC_decoder__texture_Y__IAP__DOLLAR__d9077(art_action_context_t *context, ActorInstance_RVC_decoder__texture_Y__IAP *thisActor) {
  int32_t s;
  {
    bool_t ret;
    s = pinPeek_int32_t(IN2_AC_PRED_DIR, 0);
    ret = (s == -2);
    return ret;
  }
}

// newvop
ART_ACTION(action0__newvop, ActorInstance_RVC_decoder__texture_Y__IAP) {
  int32_t s;
  ART_ACTION_ENTER(action0__newvop, 0);
  s = pinRead_int32_t(IN2_AC_PRED_DIR);
  thisActor->comp = 0;
  thisActor->ptr = 4;
  ART_ACTION_EXIT(action0__newvop, 0);
}

bool_t RVC_decoder__texture_Y__IAP__DOLLAR__d9089(art_action_context_t *context, ActorInstance_RVC_decoder__texture_Y__IAP *thisActor) {
  int32_t s;
  {
    bool_t ret;
    s = pinPeek_int32_t(IN2_AC_PRED_DIR, 0);
    ret = (s < 0);
    return ret;
  }
}

// skip
ART_ACTION(action1__skip, ActorInstance_RVC_decoder__texture_Y__IAP) {
  int32_t s;
  ART_ACTION_ENTER(action1__skip, 1);
  s = pinRead_int32_t(IN2_AC_PRED_DIR);
  thisActor->count = 64;
  ART_ACTION_EXIT(action1__skip, 1);
}


// start
ART_ACTION(action2__start, ActorInstance_RVC_decoder__texture_Y__IAP) {
  int32_t s;
  int32_t p;
  int32_t qp;
  int32_t prev_qp;
  ART_ACTION_ENTER(action2__start, 2);
  prev_qp = pinRead_int32_t(IN4_PREV_QP);
  qp = pinRead_int32_t(IN3_QP);
  p = pinRead_int32_t(IN1_PTR);
  s = pinRead_int32_t(IN2_AC_PRED_DIR);
  thisActor->s_quant = qp;
  thisActor->s_prev_quant = prev_qp;
  thisActor->count = 1;
  thisActor->pred_ptr = p;
  thisActor->top = (s == 2);
  thisActor->acpred_flag = (s != 0);
  ART_ACTION_EXIT(action2__start, 2);
}

bool_t RVC_decoder__texture_Y__IAP__DOLLAR__d9120(art_action_context_t *context, ActorInstance_RVC_decoder__texture_Y__IAP *thisActor) {
  {
    bool_t ret;
    ret = (thisActor->count == 64);
    return ret;
  }
}

// advance
ART_ACTION(action3__advance, ActorInstance_RVC_decoder__texture_Y__IAP) {
  ART_ACTION_ENTER(action3__advance, 3);
  thisActor->comp = (thisActor->comp + 1);
  if ((thisActor->comp == 4)) {
    thisActor->comp = 0;
    thisActor->ptr = (((thisActor->ptr == 4)) ? ((BUF_SIZE - 4)):((thisActor->ptr - 4)));
  }
  ART_ACTION_EXIT(action3__advance, 3);
}


// copy
ART_ACTION(action4__copy, ActorInstance_RVC_decoder__texture_Y__IAP) {
  int32_t ac;
  int32_t h;
  bool_t top_edge;
  int32_t v;
  int32_t index;
  bool_t left_edge;
  int32_t pred;
  ART_ACTION_ENTER(action4__copy, 4);
  ac = pinRead_int32_t(IN0_PQF_AC);
  h = bitand(rshift(thisActor->count, 3), 7);
  top_edge = (h == 0);
  v = bitand(thisActor->count, 7);
  index = ((top_edge) ? (v):(bitor(h, 8)));
  left_edge = (v == 0);
  pred = ac;
  if ((thisActor->acpred_flag && ((thisActor->top && top_edge) || ((!(thisActor->top)) && left_edge)))) {
    if ((thisActor->s_prev_quant == thisActor->s_quant)) {
      pred = (pred + thisActor->buf[bitor(lshift(thisActor->pred_ptr, 4), index)]);
    
    } else {
      pred = (pred + RVC_decoder__texture_Y__IAPdivroundnearest(thisActor, (thisActor->buf[bitor(lshift(thisActor->pred_ptr, 4), index)] * thisActor->s_prev_quant), thisActor->s_quant));
    }
  }
  if ((left_edge || top_edge)) {
    thisActor->buf[bitor(lshift(bitor(thisActor->ptr, thisActor->comp), 4), index)] = pred;
  }
  thisActor->count = (thisActor->count + 1);
  pinWrite_int32_t(OUT0_QF_AC, pred);
  ART_ACTION_EXIT(action4__copy, 4);
}

#define ActorInstance_RVC_decoder__texture_Y__IAP__start_ID 0
#define ActorInstance_RVC_decoder__texture_Y__IAP__pred_ID 1
static void ActorInstance_RVC_decoder__texture_Y__IAP_constructor(AbstractActorInstance *pBase) {
  ActorInstance_RVC_decoder__texture_Y__IAP *thisActor=(ActorInstance_RVC_decoder__texture_Y__IAP*) pBase;
  thisActor->_fsmState = ActorInstance_RVC_decoder__texture_Y__IAP__start_ID;//Initial state
  {
    thisActor->buf = malloc((sizeof(int32_t) * 7872));
    {
      int32_t k;
      for(k = 1; k <= 7872; k++)
      {
        thisActor->buf[((0 + k) - 1)] = 0;
      }
    }
  }

}
static const int exitcode_block_Any[3]={1,0,1};
ART_ACTION_SCHEDULER(RVC_decoder__texture_Y__IAP_action_scheduler) {
  const int *result = EXIT_CODE_YIELD;
  ActorInstance_RVC_decoder__texture_Y__IAP *thisActor=(ActorInstance_RVC_decoder__texture_Y__IAP*) pBase;
  ART_ACTION_SCHEDULER_ENTER(5, 1)
  while(1) {
    switch(thisActor->_fsmState) {
      case ActorInstance_RVC_decoder__texture_Y__IAP__start_ID:
        if ((pinAvailIn_int32_t(IN2_AC_PRED_DIR) >= 1)) {
          if (RVC_decoder__texture_Y__IAP__DOLLAR__d9077(context, thisActor)) {
            ART_FIRE_ACTION(action0__newvop);
            thisActor->_fsmState = ActorInstance_RVC_decoder__texture_Y__IAP__start_ID;
            continue;
          }
        }
        if ((pinAvailIn_int32_t(IN2_AC_PRED_DIR) >= 1)) {
          if (RVC_decoder__texture_Y__IAP__DOLLAR__d9089(context, thisActor)) {
            ART_FIRE_ACTION(action1__skip);
            thisActor->_fsmState = ActorInstance_RVC_decoder__texture_Y__IAP__pred_ID;
            continue;
          }
        }
        if ((pinAvailIn_int32_t(IN2_AC_PRED_DIR) >= 1) && (pinAvailIn_int32_t(IN1_PTR) >= 1) && (pinAvailIn_int32_t(IN3_QP) >= 1) && (pinAvailIn_int32_t(IN4_PREV_QP) >= 1)) {
          ART_FIRE_ACTION(action2__start);
          thisActor->_fsmState = ActorInstance_RVC_decoder__texture_Y__IAP__pred_ID;
          continue;
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__texture_Y__IAP__pred_ID:
        if (RVC_decoder__texture_Y__IAP__DOLLAR__d9120(context, thisActor)) {
          ART_FIRE_ACTION(action3__advance);
          thisActor->_fsmState = ActorInstance_RVC_decoder__texture_Y__IAP__start_ID;
          continue;
        }
        if ((pinAvailIn_int32_t(IN0_PQF_AC) >= 1)) {
          if ((pinAvailOut_int32_t(OUT0_QF_AC) >= 1)) {
            ART_FIRE_ACTION(action4__copy);
            thisActor->_fsmState = ActorInstance_RVC_decoder__texture_Y__IAP__pred_ID;
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
  ART_ACTION_SCHEDULER_EXIT(5, 1)
  return result;
}