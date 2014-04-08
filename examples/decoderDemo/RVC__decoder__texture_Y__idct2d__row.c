#include "actors-rts.h"
#include "natives.h"
#include "RVC__decoderDemo.h"
#define  IN0_In ART_INPUT(0)
#define  OUT0_Out ART_OUTPUT(0)

//Actor constants
static const int32_t IN_SZ = 32;
static const int32_t OUT_SZ = 32;

//Actor state
typedef struct {
  AbstractActorInstance base;
  int _fsmState;
} ActorInstance_RVC_decoder__texture_Y__idct2d__row;

//Actor functions
static inline int32_t RVC_decoder__texture_Y__idct2d__rowpmul_1_0(ActorInstance_RVC_decoder__texture_Y__idct2d__row* thisActor, int32_t X){
  int32_t Temp1;
  int32_t ret;
  Temp1 = (rshift(X, 3) - rshift(X, 7));
  ret = (X - Temp1);
  return ret;
}
static inline int32_t RVC_decoder__texture_Y__idct2d__rowpmul_1_1(ActorInstance_RVC_decoder__texture_Y__idct2d__row* thisActor, int32_t X){
  int32_t Temp1;
  int32_t Temp2;
  int32_t ret;
  Temp1 = (rshift(X, 3) - rshift(X, 7));
  Temp2 = (Temp1 - rshift(X, 11));
  ret = (Temp1 + rshift(Temp2, 1));
  return ret;
}
static inline int32_t RVC_decoder__texture_Y__idct2d__rowpmul_2_0(ActorInstance_RVC_decoder__texture_Y__idct2d__row* thisActor, int32_t X){
  int32_t Temp1;
  int32_t ret;
  Temp1 = (rshift(X, 9) - X);
  ret = (rshift(Temp1, 2) - Temp1);
  return ret;
}
static inline int32_t RVC_decoder__texture_Y__idct2d__rowpmul_2_1(ActorInstance_RVC_decoder__texture_Y__idct2d__row* thisActor, int32_t X){
  return rshift(X, 1);
}
static inline int32_t RVC_decoder__texture_Y__idct2d__rowpmul_3_0(ActorInstance_RVC_decoder__texture_Y__idct2d__row* thisActor, int32_t X){
  int32_t Temp1;
  int32_t Temp2;
  int32_t ret;
  Temp1 = (X + rshift(X, 5));
  Temp2 = rshift(Temp1, 2);
  ret = (Temp2 + rshift(X, 4));
  return ret;
}
static inline int32_t RVC_decoder__texture_Y__idct2d__rowpmul_3_1(ActorInstance_RVC_decoder__texture_Y__idct2d__row* thisActor, int32_t X){
  int32_t Temp1;
  int32_t Temp2;
  int32_t ret;
  Temp1 = (X + rshift(X, 5));
  Temp2 = rshift(Temp1, 2);
  ret = (Temp1 - Temp2);
  return ret;
}
ART_ACTION_CONTEXT(1, 1)

ART_ACTION(action0, ActorInstance_RVC_decoder__texture_Y__idct2d__row);
ART_ACTION_SCHEDULER(RVC_decoder__texture_Y__idct2d__row_action_scheduler);
static void ActorInstance_RVC_decoder__texture_Y__idct2d__row_constructor(AbstractActorInstance *);

static const PortDescription inputPortDescriptions[]={
  {0, "In", sizeof(int32_t), NULL},
};
static const PortDescription outputPortDescriptions[]={
  {0, "Out", sizeof(int32_t), NULL},
};

static const int portRate_in_action0[] = {(8 * 1)};

static const int portRate_out_action0[] = {(8 * 1)};

static const ActionDescription actionDescriptions[] = {
  {"action0", portRate_in_action0, portRate_out_action0},
};

ActorClass klass=INIT_ActorClass(
  "RVC_decoder__texture_Y__idct2d__row",
  ActorInstance_RVC_decoder__texture_Y__idct2d__row,
  ActorInstance_RVC_decoder__texture_Y__idct2d__row_constructor,
  0, //setParam not needed anymore (we instantiate with params)
  0, 0, // serialize/deserialize
  RVC_decoder__texture_Y__idct2d__row_action_scheduler,
  0, // no destructor
  1, inputPortDescriptions,
  1, outputPortDescriptions,
  1, actionDescriptions
);


// 
ART_ACTION(action0, ActorInstance_RVC_decoder__texture_Y__idct2d__row) {
  int32_t* x;
  int32_t temp2;
  int32_t xb;
  int32_t temp1;
  int32_t xa;
  int32_t temp3;
  int32_t temp4;
  int32_t* y;
  int32_t y___DOLLAR__d17116[8] = {0, 0, 0, 0, 0, 0, 0, 0};
  ART_ACTION_ENTER(action0, 0);
  y = malloc((sizeof(int32_t) * 8));
  x = malloc((sizeof(int32_t) * 8));
  pinReadRepeat_int32_t(IN0_In, x, 8);
  memcpy(y, (void*) &y___DOLLAR__d17116, (sizeof(int32_t) * 8));
  xa = (x[1] + x[7]);
  xb = (x[1] - x[7]);
  x[1] = (xa + x[3]);
  x[3] = (xa - x[3]);
  x[7] = (xb + x[5]);
  x[5] = (xb - x[5]);
  temp1 = RVC_decoder__texture_Y__idct2d__rowpmul_1_0(thisActor, x[3]);
  temp4 = RVC_decoder__texture_Y__idct2d__rowpmul_1_1(thisActor, x[3]);
  temp3 = RVC_decoder__texture_Y__idct2d__rowpmul_1_0(thisActor, x[5]);
  temp2 = RVC_decoder__texture_Y__idct2d__rowpmul_1_1(thisActor, x[5]);
  x[3] = (temp1 - temp2);
  x[5] = (temp3 + temp4);
  temp1 = RVC_decoder__texture_Y__idct2d__rowpmul_2_0(thisActor, x[1]);
  temp4 = RVC_decoder__texture_Y__idct2d__rowpmul_2_1(thisActor, x[1]);
  temp3 = RVC_decoder__texture_Y__idct2d__rowpmul_2_0(thisActor, x[7]);
  temp2 = RVC_decoder__texture_Y__idct2d__rowpmul_2_1(thisActor, x[7]);
  x[1] = (temp1 + temp2);
  x[7] = (temp3 - temp4);
  temp1 = RVC_decoder__texture_Y__idct2d__rowpmul_3_0(thisActor, x[2]);
  temp4 = RVC_decoder__texture_Y__idct2d__rowpmul_3_1(thisActor, x[2]);
  temp3 = RVC_decoder__texture_Y__idct2d__rowpmul_3_0(thisActor, x[6]);
  temp2 = RVC_decoder__texture_Y__idct2d__rowpmul_3_1(thisActor, x[6]);
  x[2] = (temp1 - temp2);
  x[6] = (temp3 + temp4);
  xa = (x[0] + x[4]);
  xb = (x[0] - x[4]);
  x[0] = (xa + x[6]);
  x[6] = (xa - x[6]);
  x[4] = (xb + x[2]);
  x[2] = (xb - x[2]);
  {
    y[0] = (x[0] + x[1]);
    y[1] = (x[4] + x[5]);
    y[2] = (x[2] + x[3]);
    y[3] = (x[6] + x[7]);
    y[4] = (x[6] - x[7]);
    y[5] = (x[2] - x[3]);
    y[6] = (x[4] - x[5]);
    y[7] = (x[0] - x[1]);
  }
  pinWriteRepeat_int32_t(OUT0_Out, y, 8);
  free((void*) x);
  free((void*) y);
  ART_ACTION_EXIT(action0, 0);
}

#define ActorInstance_RVC_decoder__texture_Y__idct2d__row__defaultState_ID 0
static void ActorInstance_RVC_decoder__texture_Y__idct2d__row_constructor(AbstractActorInstance *pBase) {
  ActorInstance_RVC_decoder__texture_Y__idct2d__row *thisActor=(ActorInstance_RVC_decoder__texture_Y__idct2d__row*) pBase;
  thisActor->_fsmState = ActorInstance_RVC_decoder__texture_Y__idct2d__row__defaultState_ID;//Initial state
  {
  }

}
static const int exitcode_block_Any[3]={1,0,1};
ART_ACTION_SCHEDULER(RVC_decoder__texture_Y__idct2d__row_action_scheduler) {
  const int *result = EXIT_CODE_YIELD;
  ActorInstance_RVC_decoder__texture_Y__idct2d__row *thisActor=(ActorInstance_RVC_decoder__texture_Y__idct2d__row*) pBase;
  ART_ACTION_SCHEDULER_ENTER(1, 1)
  while(1) {
    if ((pinAvailIn_int32_t(IN0_In) >= 8)) {
      if ((pinAvailOut_int32_t(OUT0_Out) >= 8)) {
        ART_FIRE_ACTION(action0);
        continue;
      
      } else {
        result = exitcode_block_Any;
        goto out;
      }
    }
    switch(thisActor->_fsmState) {
      case ActorInstance_RVC_decoder__texture_Y__idct2d__row__defaultState_ID:
        result = exitcode_block_Any;
        goto out;
        break;
      
    }
  }
  out:
  ART_ACTION_SCHEDULER_EXIT(1, 1)
  return result;
}