#include "actors-rts.h"
#include "natives.h"
#include "RVC__decoderDemo.h"
#define  IN0_DC ART_INPUT(0)
#define  IN1_AC ART_INPUT(1)
#define  IN2_QP ART_INPUT(2)
#define  OUT0_OUT ART_OUTPUT(0)

//Actor constants
static const int32_t QUANT_SZ = 6;
static const int32_t SAMPLE_SZ = 13;

//Actor state
typedef struct {
  AbstractActorInstance base;
  int _fsmState;
  int32_t round;
  int32_t count;
  int32_t quant;
} ActorInstance_RVC_decoder__texture_V__IQ;

//Actor functions
static inline int32_t RVC_decoder__texture_V__IQsaturate(ActorInstance_RVC_decoder__texture_V__IQ* thisActor, int32_t x){
  bool_t minus;
  bool_t plus;
  int32_t ret;
  minus = (x < (-(2048)));
  plus = (x > 2047);
  ret = ((minus) ? ((-(2048))):(((plus) ? (2047):(x))));
  return ret;
}
static inline int32_t RVC_decoder__texture_V__IQabs(ActorInstance_RVC_decoder__texture_V__IQ* thisActor, int32_t x){
  return (((x < 0)) ? ((-(x))):(x));
}
ART_ACTION_CONTEXT(3, 1)

ART_ACTION(action0__get_qp, ActorInstance_RVC_decoder__texture_V__IQ);
ART_ACTION(action1__ac, ActorInstance_RVC_decoder__texture_V__IQ);
ART_ACTION_SCHEDULER(RVC_decoder__texture_V__IQ_action_scheduler);
static void ActorInstance_RVC_decoder__texture_V__IQ_constructor(AbstractActorInstance *);

static const PortDescription inputPortDescriptions[]={
  {0, "DC", sizeof(int32_t)},
  {0, "AC", sizeof(int32_t)},
  {0, "QP", sizeof(int32_t)},
};
static const PortDescription outputPortDescriptions[]={
  {0, "OUT", sizeof(int32_t)},
};

static const int portRate_in_action0__get_qp[] = {1, 0, 1};

static const int portRate_out_action0__get_qp[] = {1};

static const int portRate_in_action1__ac[] = {0, (63 * 1), 0};

static const int portRate_out_action1__ac[] = {(63 * 1)};

static const ActionDescription actionDescriptions[] = {
  {"action0__get_qp", portRate_in_action0__get_qp, portRate_out_action0__get_qp},
  {"action1__ac", portRate_in_action1__ac, portRate_out_action1__ac},
};

ActorClass klass=INIT_ActorClass(
  "RVC_decoder__texture_V__IQ",
  ActorInstance_RVC_decoder__texture_V__IQ,
  ActorInstance_RVC_decoder__texture_V__IQ_constructor,
  0, //setParam not needed anymore (we instantiate with params)
  RVC_decoder__texture_V__IQ_action_scheduler,
  0, // no destructor
  3, inputPortDescriptions,
  1, outputPortDescriptions,
  2, actionDescriptions
);


// get_qp
ART_ACTION(action0__get_qp, ActorInstance_RVC_decoder__texture_V__IQ) {
  int32_t q;
  int32_t i;
  ART_ACTION_ENTER(action0__get_qp, 0);
  i = pinRead_int32_t(IN0_DC);
  q = pinRead_int32_t(IN2_QP);
  thisActor->quant = q;
  thisActor->round = bitxor(bitand(q, 1), 1);
  thisActor->count = 0;
  pinWrite_int32_t(OUT0_OUT, i);
  ART_ACTION_EXIT(action0__get_qp, 0);
}


// ac
ART_ACTION(action1__ac, ActorInstance_RVC_decoder__texture_V__IQ) {
  int32_t* i;
  int32_t* v;
  int32_t* o;
  ART_ACTION_ENTER(action1__ac, 1);
  o = malloc((sizeof(int32_t) * 63));
  v = malloc((sizeof(int32_t) * 63));
  i = malloc((sizeof(int32_t) * 63));
  pinReadRepeat_int32_t(IN1_AC, i, 63);
  {
    int32_t j;
    for(j = 0; j <= 62; j++)
    {
      v[((0 + j) - 0)] = ((thisActor->quant * (lshift(RVC_decoder__texture_V__IQabs(thisActor, i[j]), 1) + 1)) - thisActor->round);
    }
  }
  {
    int32_t k;
    for(k = 0; k <= 62; k++)
    {
      o[((0 + k) - 0)] = (((i[k] == 0)) ? (0):((((i[k] < 0)) ? (RVC_decoder__texture_V__IQsaturate(thisActor, (-(v[k])))):(RVC_decoder__texture_V__IQsaturate(thisActor, v[k])))));
    }
  }
  pinWriteRepeat_int32_t(OUT0_OUT, o, 63);
  free((void*) i);
  free((void*) v);
  free((void*) o);
  ART_ACTION_EXIT(action1__ac, 1);
}

#define ActorInstance_RVC_decoder__texture_V__IQ__start_ID 0
#define ActorInstance_RVC_decoder__texture_V__IQ__ac_ID 1
static void ActorInstance_RVC_decoder__texture_V__IQ_constructor(AbstractActorInstance *pBase) {
  ActorInstance_RVC_decoder__texture_V__IQ *thisActor=(ActorInstance_RVC_decoder__texture_V__IQ*) pBase;
  thisActor->_fsmState = ActorInstance_RVC_decoder__texture_V__IQ__start_ID;//Initial state
  {
  }

}
static const int exitcode_block_Any[3]={1,0,1};
ART_ACTION_SCHEDULER(RVC_decoder__texture_V__IQ_action_scheduler) {
  const int *result = EXIT_CODE_YIELD;
  ActorInstance_RVC_decoder__texture_V__IQ *thisActor=(ActorInstance_RVC_decoder__texture_V__IQ*) pBase;
  ART_ACTION_SCHEDULER_ENTER(3, 1)
  while(1) {
    switch(thisActor->_fsmState) {
      case ActorInstance_RVC_decoder__texture_V__IQ__start_ID:
        if ((pinAvailIn_int32_t(IN2_QP) >= 1) && (pinAvailIn_int32_t(IN0_DC) >= 1)) {
          if ((pinAvailOut_int32_t(OUT0_OUT) >= 1)) {
            ART_FIRE_ACTION(action0__get_qp);
            thisActor->_fsmState = ActorInstance_RVC_decoder__texture_V__IQ__ac_ID;
            continue;
          
          } else {
            result = exitcode_block_Any;
            goto out;
          }
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__texture_V__IQ__ac_ID:
        if ((pinAvailIn_int32_t(IN1_AC) >= 63)) {
          if ((pinAvailOut_int32_t(OUT0_OUT) >= 63)) {
            ART_FIRE_ACTION(action1__ac);
            thisActor->_fsmState = ActorInstance_RVC_decoder__texture_V__IQ__start_ID;
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