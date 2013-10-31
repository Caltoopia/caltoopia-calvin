#include "actors-rts.h"
#include "natives.h"
#include "RVC__decoderDemo.h"
#define  IN0_BTYPE ART_INPUT(0)
#define  OUT0_A ART_OUTPUT(0)

//Actor constants
static const int32_t MAXW_IN_MB = 121;
static const int32_t MB_COORD_SZ = 8;
static const int32_t BTYPE_SZ = 12;
static const int32_t NEWVOP = 2048;
static const int32_t INTER = 512;
static const int32_t MOTION = 8;
static const int32_t FOURMV = 4;
static const int32_t BUF_SIZE = 121;

//Actor state
typedef struct {
  AbstractActorInstance base;
  int _fsmState;
  bool_t right_edge;
  int32_t mbwidth;
  int32_t ptr;
  int32_t ptr_above;
  int32_t comp;
  int32_t mbx;
  int32_t ptr_above_right;
  int32_t ptr_left;
  bool_t top_edge;
} ActorInstance_RVC_decoder__parser__mvseq;

//Actor functions
static inline int32_t RVC_decoder__parser__mvseqdecrement(ActorInstance_RVC_decoder__parser__mvseq* thisActor, int32_t p){
  return (((p == 1)) ? ((BUF_SIZE - 1)):((p - 1)));
}
static inline int32_t RVC_decoder__parser__mvseqaccess(ActorInstance_RVC_decoder__parser__mvseq* thisActor, int32_t mbptr, int32_t c){
  return bitor(lshift(mbptr, 3), bitand(c, 3));
}
ART_ACTION_CONTEXT(1, 1)

ART_ACTION(action0__start, ActorInstance_RVC_decoder__parser__mvseq);
ART_ACTION(action1__getw, ActorInstance_RVC_decoder__parser__mvseq);
ART_ACTION(action2__geth, ActorInstance_RVC_decoder__parser__mvseq);
ART_ACTION(action3__read__noPredict, ActorInstance_RVC_decoder__parser__mvseq);
ART_ACTION(action4__read__predict__y0, ActorInstance_RVC_decoder__parser__mvseq);
ART_ACTION(action5__read__predict__y1, ActorInstance_RVC_decoder__parser__mvseq);
ART_ACTION(action6__read__predict__y2, ActorInstance_RVC_decoder__parser__mvseq);
ART_ACTION(action7__read__predict__y3, ActorInstance_RVC_decoder__parser__mvseq);
ART_ACTION_SCHEDULER(RVC_decoder__parser__mvseq_action_scheduler);
static void ActorInstance_RVC_decoder__parser__mvseq_constructor(AbstractActorInstance *);

static const PortDescription inputPortDescriptions[]={
  {0, "BTYPE", sizeof(int32_t)},
};
static const PortDescription outputPortDescriptions[]={
  {0, "A", sizeof(int32_t)},
};

static const int portRate_in_action0__start[] = {1};

static const int portRate_out_action0__start[] = {0};

static const int portRate_in_action1__getw[] = {1};

static const int portRate_out_action1__getw[] = {0};

static const int portRate_in_action2__geth[] = {1};

static const int portRate_out_action2__geth[] = {0};

static const int portRate_in_action3__read__noPredict[] = {1};

static const int portRate_out_action3__read__noPredict[] = {0};

static const int portRate_in_action4__read__predict__y0[] = {1};

static const int portRate_out_action4__read__predict__y0[] = {3};

static const int portRate_in_action5__read__predict__y1[] = {1};

static const int portRate_out_action5__read__predict__y1[] = {3};

static const int portRate_in_action6__read__predict__y2[] = {1};

static const int portRate_out_action6__read__predict__y2[] = {3};

static const int portRate_in_action7__read__predict__y3[] = {1};

static const int portRate_out_action7__read__predict__y3[] = {3};

static const ActionDescription actionDescriptions[] = {
  {"action0__start", portRate_in_action0__start, portRate_out_action0__start},
  {"action1__getw", portRate_in_action1__getw, portRate_out_action1__getw},
  {"action2__geth", portRate_in_action2__geth, portRate_out_action2__geth},
  {"action3__read__noPredict", portRate_in_action3__read__noPredict, portRate_out_action3__read__noPredict},
  {"action4__read__predict__y0", portRate_in_action4__read__predict__y0, portRate_out_action4__read__predict__y0},
  {"action5__read__predict__y1", portRate_in_action5__read__predict__y1, portRate_out_action5__read__predict__y1},
  {"action6__read__predict__y2", portRate_in_action6__read__predict__y2, portRate_out_action6__read__predict__y2},
  {"action7__read__predict__y3", portRate_in_action7__read__predict__y3, portRate_out_action7__read__predict__y3},
};

ActorClass klass=INIT_ActorClass(
  "RVC_decoder__parser__mvseq",
  ActorInstance_RVC_decoder__parser__mvseq,
  ActorInstance_RVC_decoder__parser__mvseq_constructor,
  0, //setParam not needed anymore (we instantiate with params)
  RVC_decoder__parser__mvseq_action_scheduler,
  0, // no destructor
  1, inputPortDescriptions,
  1, outputPortDescriptions,
  8, actionDescriptions
);

bool_t RVC_decoder__parser__mvseq__DOLLAR__d2107(art_action_context_t *context, ActorInstance_RVC_decoder__parser__mvseq *thisActor) {
  int32_t cmd;
  {
    bool_t ret;
    cmd = pinPeek_int32_t(IN0_BTYPE, 0);
    ret = (bitand(cmd, NEWVOP) != 0);
    return ret;
  }
}

// start
ART_ACTION(action0__start, ActorInstance_RVC_decoder__parser__mvseq) {
  int32_t cmd;
  ART_ACTION_ENTER(action0__start, 0);
  cmd = pinRead_int32_t(IN0_BTYPE);
  thisActor->mbx = 0;
  thisActor->top_edge = 1;
  thisActor->right_edge = 0;
  thisActor->comp = 0;
  ART_ACTION_EXIT(action0__start, 0);
}


// getw
ART_ACTION(action1__getw, ActorInstance_RVC_decoder__parser__mvseq) {
  int32_t w;
  ART_ACTION_ENTER(action1__getw, 1);
  w = pinRead_int32_t(IN0_BTYPE);
  thisActor->mbwidth = w;
  thisActor->ptr = 1;
  thisActor->ptr_left = 2;
  thisActor->ptr_above = (w + 1);
  thisActor->ptr_above_right = w;
  ART_ACTION_EXIT(action1__getw, 1);
}


// geth
ART_ACTION(action2__geth, ActorInstance_RVC_decoder__parser__mvseq) {
  int32_t h;
  ART_ACTION_ENTER(action2__geth, 2);
  h = pinRead_int32_t(IN0_BTYPE);
  ART_ACTION_EXIT(action2__geth, 2);
}

bool_t RVC_decoder__parser__mvseq__DOLLAR__d2136(art_action_context_t *context, ActorInstance_RVC_decoder__parser__mvseq *thisActor) {
  int32_t cmd;
  {
    bool_t ret;
    cmd = pinPeek_int32_t(IN0_BTYPE, 0);
    ret = (bitand(cmd, NEWVOP) == 0);
    return ret;
  }
}
bool_t RVC_decoder__parser__mvseq__DOLLAR__d2145(art_action_context_t *context, ActorInstance_RVC_decoder__parser__mvseq *thisActor) {
  int32_t cmd;
  {
    bool_t ret;
    cmd = pinPeek_int32_t(IN0_BTYPE, 0);
    cmd = pinPeek_int32_t(IN0_BTYPE, 0);
    cmd = pinPeek_int32_t(IN0_BTYPE, 0);
    ret = ((((thisActor->comp > 3) || (bitand(cmd, INTER) == 0)) || (bitand(cmd, MOTION) == 0)) || ((thisActor->comp != 0) && (bitand(cmd, FOURMV) == 0)));
    return ret;
  }
}

// read.noPredict
ART_ACTION(action3__read__noPredict, ActorInstance_RVC_decoder__parser__mvseq) {
  int32_t cmd;
  ART_ACTION_ENTER(action3__read__noPredict, 3);
  cmd = pinRead_int32_t(IN0_BTYPE);
  thisActor->comp = (thisActor->comp + 1);
  if ((thisActor->comp == 6)) {
    thisActor->comp = 0;
    thisActor->mbx = (thisActor->mbx + 1);
    thisActor->ptr = RVC_decoder__parser__mvseqdecrement(thisActor, thisActor->ptr);
    thisActor->ptr_left = RVC_decoder__parser__mvseqdecrement(thisActor, thisActor->ptr_left);
    thisActor->ptr_above = RVC_decoder__parser__mvseqdecrement(thisActor, thisActor->ptr_above);
    thisActor->ptr_above_right = RVC_decoder__parser__mvseqdecrement(thisActor, thisActor->ptr_above_right);
    if (thisActor->right_edge) {
      thisActor->mbx = 0;
      thisActor->right_edge = 0;
      thisActor->top_edge = 0;
    
    } else {
      if ((thisActor->mbx == (thisActor->mbwidth - 1))) {
        thisActor->right_edge = 1;
      }
    }
  }
  ART_ACTION_EXIT(action3__read__noPredict, 3);
}

bool_t RVC_decoder__parser__mvseq__DOLLAR__d2221(art_action_context_t *context, ActorInstance_RVC_decoder__parser__mvseq *thisActor) {
  int32_t cmd;
  {
    bool_t ret;
    cmd = pinPeek_int32_t(IN0_BTYPE, 0);
    ret = (bitand(cmd, NEWVOP) == 0);
    return ret;
  }
}
bool_t RVC_decoder__parser__mvseq__DOLLAR__d2230(art_action_context_t *context, ActorInstance_RVC_decoder__parser__mvseq *thisActor) {
  int32_t cmd;
  {
    bool_t ret;
    cmd = pinPeek_int32_t(IN0_BTYPE, 0);
    ret = (bitand(cmd, INTER) != 0);
    return ret;
  }
}
bool_t RVC_decoder__parser__mvseq__DOLLAR__d2239(art_action_context_t *context, ActorInstance_RVC_decoder__parser__mvseq *thisActor) {
  int32_t cmd;
  {
    bool_t ret;
    cmd = pinPeek_int32_t(IN0_BTYPE, 0);
    ret = (bitand(cmd, MOTION) != 0);
    return ret;
  }
}
bool_t RVC_decoder__parser__mvseq__DOLLAR__d2248(art_action_context_t *context, ActorInstance_RVC_decoder__parser__mvseq *thisActor) {
  {
    bool_t ret;
    ret = (thisActor->comp == 0);
    return ret;
  }
}

// read.predict.y0
ART_ACTION(action4__read__predict__y0, ActorInstance_RVC_decoder__parser__mvseq) {
  int32_t cmd;
  int32_t par;
  int32_t pl;
  int32_t pa;
  int32_t U__7;
  int32_t U__8;
  int32_t U__9;
  ART_ACTION_ENTER(action4__read__predict__y0, 4);
  cmd = pinRead_int32_t(IN0_BTYPE);
  par = (((thisActor->top_edge || thisActor->right_edge)) ? (0):(thisActor->ptr_above_right));
  pl = (((thisActor->mbx == 0)) ? (0):(thisActor->ptr_left));
  pa = ((thisActor->top_edge) ? (0):(thisActor->ptr_above));
  thisActor->comp = (thisActor->comp + 1);
  U__7 = RVC_decoder__parser__mvseqaccess(thisActor, pl, 1);
  U__8 = RVC_decoder__parser__mvseqaccess(thisActor, pa, 2);
  U__9 = RVC_decoder__parser__mvseqaccess(thisActor, par, 2);
  pinWrite_int32_t(OUT0_A, U__7);
  pinWrite_int32_t(OUT0_A, U__8);
  pinWrite_int32_t(OUT0_A, U__9);
  ART_ACTION_EXIT(action4__read__predict__y0, 4);
}

bool_t RVC_decoder__parser__mvseq__DOLLAR__d2302(art_action_context_t *context, ActorInstance_RVC_decoder__parser__mvseq *thisActor) {
  int32_t cmd;
  {
    bool_t ret;
    cmd = pinPeek_int32_t(IN0_BTYPE, 0);
    ret = (bitand(cmd, NEWVOP) == 0);
    return ret;
  }
}
bool_t RVC_decoder__parser__mvseq__DOLLAR__d2311(art_action_context_t *context, ActorInstance_RVC_decoder__parser__mvseq *thisActor) {
  int32_t cmd;
  {
    bool_t ret;
    cmd = pinPeek_int32_t(IN0_BTYPE, 0);
    ret = (bitand(cmd, INTER) != 0);
    return ret;
  }
}
bool_t RVC_decoder__parser__mvseq__DOLLAR__d2320(art_action_context_t *context, ActorInstance_RVC_decoder__parser__mvseq *thisActor) {
  int32_t cmd;
  {
    bool_t ret;
    cmd = pinPeek_int32_t(IN0_BTYPE, 0);
    ret = (bitand(cmd, MOTION) != 0);
    return ret;
  }
}
bool_t RVC_decoder__parser__mvseq__DOLLAR__d2329(art_action_context_t *context, ActorInstance_RVC_decoder__parser__mvseq *thisActor) {
  int32_t cmd;
  {
    bool_t ret;
    cmd = pinPeek_int32_t(IN0_BTYPE, 0);
    ret = (bitand(cmd, FOURMV) != 0);
    return ret;
  }
}
bool_t RVC_decoder__parser__mvseq__DOLLAR__d2338(art_action_context_t *context, ActorInstance_RVC_decoder__parser__mvseq *thisActor) {
  {
    bool_t ret;
    ret = (thisActor->comp == 1);
    return ret;
  }
}

// read.predict.y1
ART_ACTION(action5__read__predict__y1, ActorInstance_RVC_decoder__parser__mvseq) {
  int32_t cmd;
  int32_t par;
  int32_t pa;
  int32_t U__10;
  int32_t U__11;
  int32_t U__12;
  ART_ACTION_ENTER(action5__read__predict__y1, 5);
  cmd = pinRead_int32_t(IN0_BTYPE);
  par = (((thisActor->top_edge || thisActor->right_edge)) ? (0):(thisActor->ptr_above_right));
  pa = ((thisActor->top_edge) ? (0):(thisActor->ptr_above));
  thisActor->comp = (thisActor->comp + 1);
  U__10 = RVC_decoder__parser__mvseqaccess(thisActor, thisActor->ptr, 0);
  U__11 = RVC_decoder__parser__mvseqaccess(thisActor, pa, 3);
  U__12 = RVC_decoder__parser__mvseqaccess(thisActor, par, 2);
  pinWrite_int32_t(OUT0_A, U__10);
  pinWrite_int32_t(OUT0_A, U__11);
  pinWrite_int32_t(OUT0_A, U__12);
  ART_ACTION_EXIT(action5__read__predict__y1, 5);
}

bool_t RVC_decoder__parser__mvseq__DOLLAR__d2384(art_action_context_t *context, ActorInstance_RVC_decoder__parser__mvseq *thisActor) {
  int32_t cmd;
  {
    bool_t ret;
    cmd = pinPeek_int32_t(IN0_BTYPE, 0);
    ret = (bitand(cmd, NEWVOP) == 0);
    return ret;
  }
}
bool_t RVC_decoder__parser__mvseq__DOLLAR__d2393(art_action_context_t *context, ActorInstance_RVC_decoder__parser__mvseq *thisActor) {
  int32_t cmd;
  {
    bool_t ret;
    cmd = pinPeek_int32_t(IN0_BTYPE, 0);
    ret = (bitand(cmd, INTER) != 0);
    return ret;
  }
}
bool_t RVC_decoder__parser__mvseq__DOLLAR__d2402(art_action_context_t *context, ActorInstance_RVC_decoder__parser__mvseq *thisActor) {
  int32_t cmd;
  {
    bool_t ret;
    cmd = pinPeek_int32_t(IN0_BTYPE, 0);
    ret = (bitand(cmd, MOTION) != 0);
    return ret;
  }
}
bool_t RVC_decoder__parser__mvseq__DOLLAR__d2411(art_action_context_t *context, ActorInstance_RVC_decoder__parser__mvseq *thisActor) {
  int32_t cmd;
  {
    bool_t ret;
    cmd = pinPeek_int32_t(IN0_BTYPE, 0);
    ret = (bitand(cmd, FOURMV) != 0);
    return ret;
  }
}
bool_t RVC_decoder__parser__mvseq__DOLLAR__d2420(art_action_context_t *context, ActorInstance_RVC_decoder__parser__mvseq *thisActor) {
  {
    bool_t ret;
    ret = (thisActor->comp == 2);
    return ret;
  }
}

// read.predict.y2
ART_ACTION(action6__read__predict__y2, ActorInstance_RVC_decoder__parser__mvseq) {
  int32_t cmd;
  int32_t pl;
  int32_t U__13;
  int32_t U__14;
  int32_t U__15;
  ART_ACTION_ENTER(action6__read__predict__y2, 6);
  cmd = pinRead_int32_t(IN0_BTYPE);
  pl = (((thisActor->mbx == 0)) ? (0):(thisActor->ptr_left));
  thisActor->comp = (thisActor->comp + 1);
  U__13 = RVC_decoder__parser__mvseqaccess(thisActor, pl, 3);
  U__14 = RVC_decoder__parser__mvseqaccess(thisActor, thisActor->ptr, 0);
  U__15 = RVC_decoder__parser__mvseqaccess(thisActor, thisActor->ptr, 1);
  pinWrite_int32_t(OUT0_A, U__13);
  pinWrite_int32_t(OUT0_A, U__14);
  pinWrite_int32_t(OUT0_A, U__15);
  ART_ACTION_EXIT(action6__read__predict__y2, 6);
}

bool_t RVC_decoder__parser__mvseq__DOLLAR__d2460(art_action_context_t *context, ActorInstance_RVC_decoder__parser__mvseq *thisActor) {
  int32_t cmd;
  {
    bool_t ret;
    cmd = pinPeek_int32_t(IN0_BTYPE, 0);
    ret = (bitand(cmd, NEWVOP) == 0);
    return ret;
  }
}
bool_t RVC_decoder__parser__mvseq__DOLLAR__d2469(art_action_context_t *context, ActorInstance_RVC_decoder__parser__mvseq *thisActor) {
  int32_t cmd;
  {
    bool_t ret;
    cmd = pinPeek_int32_t(IN0_BTYPE, 0);
    ret = (bitand(cmd, INTER) != 0);
    return ret;
  }
}
bool_t RVC_decoder__parser__mvseq__DOLLAR__d2478(art_action_context_t *context, ActorInstance_RVC_decoder__parser__mvseq *thisActor) {
  int32_t cmd;
  {
    bool_t ret;
    cmd = pinPeek_int32_t(IN0_BTYPE, 0);
    ret = (bitand(cmd, MOTION) != 0);
    return ret;
  }
}
bool_t RVC_decoder__parser__mvseq__DOLLAR__d2487(art_action_context_t *context, ActorInstance_RVC_decoder__parser__mvseq *thisActor) {
  int32_t cmd;
  {
    bool_t ret;
    cmd = pinPeek_int32_t(IN0_BTYPE, 0);
    ret = (bitand(cmd, FOURMV) != 0);
    return ret;
  }
}
bool_t RVC_decoder__parser__mvseq__DOLLAR__d2496(art_action_context_t *context, ActorInstance_RVC_decoder__parser__mvseq *thisActor) {
  {
    bool_t ret;
    ret = (thisActor->comp == 3);
    return ret;
  }
}

// read.predict.y3
ART_ACTION(action7__read__predict__y3, ActorInstance_RVC_decoder__parser__mvseq) {
  int32_t cmd;
  int32_t U__16;
  int32_t U__17;
  int32_t U__18;
  ART_ACTION_ENTER(action7__read__predict__y3, 7);
  cmd = pinRead_int32_t(IN0_BTYPE);
  thisActor->comp = (thisActor->comp + 1);
  U__16 = RVC_decoder__parser__mvseqaccess(thisActor, thisActor->ptr, 2);
  U__17 = RVC_decoder__parser__mvseqaccess(thisActor, thisActor->ptr, 0);
  U__18 = RVC_decoder__parser__mvseqaccess(thisActor, thisActor->ptr, 1);
  pinWrite_int32_t(OUT0_A, U__16);
  pinWrite_int32_t(OUT0_A, U__17);
  pinWrite_int32_t(OUT0_A, U__18);
  ART_ACTION_EXIT(action7__read__predict__y3, 7);
}

#define ActorInstance_RVC_decoder__parser__mvseq__read_ID 0
#define ActorInstance_RVC_decoder__parser__mvseq__getw_ID 1
#define ActorInstance_RVC_decoder__parser__mvseq__geth_ID 2
static void ActorInstance_RVC_decoder__parser__mvseq_constructor(AbstractActorInstance *pBase) {
  ActorInstance_RVC_decoder__parser__mvseq *thisActor=(ActorInstance_RVC_decoder__parser__mvseq*) pBase;
  thisActor->_fsmState = ActorInstance_RVC_decoder__parser__mvseq__read_ID;//Initial state
  {
    thisActor->right_edge = 0;
    thisActor->mbwidth = 0;
    thisActor->comp = 0;
    thisActor->mbx = 0;
    thisActor->top_edge = 1;
  }

}
static const int exitcode_block_Any[3]={1,0,1};
ART_ACTION_SCHEDULER(RVC_decoder__parser__mvseq_action_scheduler) {
  const int *result = EXIT_CODE_YIELD;
  ActorInstance_RVC_decoder__parser__mvseq *thisActor=(ActorInstance_RVC_decoder__parser__mvseq*) pBase;
  ART_ACTION_SCHEDULER_ENTER(1, 1)
  while(1) {
    switch(thisActor->_fsmState) {
      case ActorInstance_RVC_decoder__parser__mvseq__read_ID:
        if ((pinAvailIn_int32_t(IN0_BTYPE) >= 1)) {
          if (RVC_decoder__parser__mvseq__DOLLAR__d2107(context, thisActor)) {
            ART_FIRE_ACTION(action0__start);
            thisActor->_fsmState = ActorInstance_RVC_decoder__parser__mvseq__getw_ID;
            continue;
          }
        }
        if ((pinAvailIn_int32_t(IN0_BTYPE) >= 1)) {
          if (RVC_decoder__parser__mvseq__DOLLAR__d2136(context, thisActor) && RVC_decoder__parser__mvseq__DOLLAR__d2145(context, thisActor)) {
            ART_FIRE_ACTION(action3__read__noPredict);
            thisActor->_fsmState = ActorInstance_RVC_decoder__parser__mvseq__read_ID;
            continue;
          }
        }
        if ((pinAvailIn_int32_t(IN0_BTYPE) >= 1)) {
          if (RVC_decoder__parser__mvseq__DOLLAR__d2221(context, thisActor) && RVC_decoder__parser__mvseq__DOLLAR__d2230(context, thisActor) && RVC_decoder__parser__mvseq__DOLLAR__d2239(context, thisActor) && RVC_decoder__parser__mvseq__DOLLAR__d2248(context, thisActor)) {
            if ((pinAvailOut_int32_t(OUT0_A) >= 1*3)) {
              ART_FIRE_ACTION(action4__read__predict__y0);
              thisActor->_fsmState = ActorInstance_RVC_decoder__parser__mvseq__read_ID;
              continue;
            
            } else {
              result = exitcode_block_Any;
              goto out;
            }
          }
        }
        if ((pinAvailIn_int32_t(IN0_BTYPE) >= 1)) {
          if (RVC_decoder__parser__mvseq__DOLLAR__d2302(context, thisActor) && RVC_decoder__parser__mvseq__DOLLAR__d2311(context, thisActor) && RVC_decoder__parser__mvseq__DOLLAR__d2320(context, thisActor) && RVC_decoder__parser__mvseq__DOLLAR__d2329(context, thisActor) && RVC_decoder__parser__mvseq__DOLLAR__d2338(context, thisActor)) {
            if ((pinAvailOut_int32_t(OUT0_A) >= 1*3)) {
              ART_FIRE_ACTION(action5__read__predict__y1);
              thisActor->_fsmState = ActorInstance_RVC_decoder__parser__mvseq__read_ID;
              continue;
            
            } else {
              result = exitcode_block_Any;
              goto out;
            }
          }
        }
        if ((pinAvailIn_int32_t(IN0_BTYPE) >= 1)) {
          if (RVC_decoder__parser__mvseq__DOLLAR__d2384(context, thisActor) && RVC_decoder__parser__mvseq__DOLLAR__d2393(context, thisActor) && RVC_decoder__parser__mvseq__DOLLAR__d2402(context, thisActor) && RVC_decoder__parser__mvseq__DOLLAR__d2411(context, thisActor) && RVC_decoder__parser__mvseq__DOLLAR__d2420(context, thisActor)) {
            if ((pinAvailOut_int32_t(OUT0_A) >= 1*3)) {
              ART_FIRE_ACTION(action6__read__predict__y2);
              thisActor->_fsmState = ActorInstance_RVC_decoder__parser__mvseq__read_ID;
              continue;
            
            } else {
              result = exitcode_block_Any;
              goto out;
            }
          }
        }
        if ((pinAvailIn_int32_t(IN0_BTYPE) >= 1)) {
          if (RVC_decoder__parser__mvseq__DOLLAR__d2460(context, thisActor) && RVC_decoder__parser__mvseq__DOLLAR__d2469(context, thisActor) && RVC_decoder__parser__mvseq__DOLLAR__d2478(context, thisActor) && RVC_decoder__parser__mvseq__DOLLAR__d2487(context, thisActor) && RVC_decoder__parser__mvseq__DOLLAR__d2496(context, thisActor)) {
            if ((pinAvailOut_int32_t(OUT0_A) >= 1*3)) {
              ART_FIRE_ACTION(action7__read__predict__y3);
              thisActor->_fsmState = ActorInstance_RVC_decoder__parser__mvseq__read_ID;
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
      
      case ActorInstance_RVC_decoder__parser__mvseq__getw_ID:
        if ((pinAvailIn_int32_t(IN0_BTYPE) >= 1)) {
          ART_FIRE_ACTION(action1__getw);
          thisActor->_fsmState = ActorInstance_RVC_decoder__parser__mvseq__geth_ID;
          continue;
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__parser__mvseq__geth_ID:
        if ((pinAvailIn_int32_t(IN0_BTYPE) >= 1)) {
          ART_FIRE_ACTION(action2__geth);
          thisActor->_fsmState = ActorInstance_RVC_decoder__parser__mvseq__read_ID;
          continue;
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
    }
  }
  out:
  ART_ACTION_SCHEDULER_EXIT(1, 1)
  return result;
}