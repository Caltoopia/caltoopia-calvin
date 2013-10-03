#include "actors-rts.h"
#include "natives.h"
#include "RVC__decoderDemo.h"
#define  IN0_BTYPE ART_INPUT(0)
#define  OUT0_A ART_OUTPUT(0)
#define  OUT1_B ART_OUTPUT(1)
#define  OUT2_C ART_OUTPUT(2)

//Actor constants
static const int32_t MAXW_IN_MB = 121;
static const int32_t MB_COORD_SZ = 8;
static const int32_t BTYPE_SZ = 12;
static const int32_t NEWVOP = 2048;
static const int32_t INTRA = 1024;
static const int32_t BUF_SIZE = 123;

//Actor state
typedef struct {
  AbstractActorInstance base;
  int _fsmState;
  bool_t* coded;
  bool_t left_edge;
  int32_t ptr_left;
  int32_t ptr_above_left;
  int32_t ptr_above;
  int32_t mbwidth;
  int32_t mbx;
  int32_t ptr;
  bool_t top_edge;
} ActorInstance_RVC_decoder__texture_V__DCRecontruction__addressing;

//Actor functions
inline int32_t RVC_decoder__texture_V__DCRecontruction__addressingdecrement(ActorInstance_RVC_decoder__texture_V__DCRecontruction__addressing* thisActor, int32_t p){
  return (((p == 1)) ? ((BUF_SIZE - 1)):((p - 1)));
}
ART_ACTION_CONTEXT(1, 3)

ART_ACTION(action0__start, ActorInstance_RVC_decoder__texture_V__DCRecontruction__addressing);
ART_ACTION(action1__getw, ActorInstance_RVC_decoder__texture_V__DCRecontruction__addressing);
ART_ACTION(action2__geth, ActorInstance_RVC_decoder__texture_V__DCRecontruction__addressing);
ART_ACTION(action3__read__intra, ActorInstance_RVC_decoder__texture_V__DCRecontruction__addressing);
ART_ACTION(action4__read__other, ActorInstance_RVC_decoder__texture_V__DCRecontruction__addressing);
ART_ACTION(action5__advance, ActorInstance_RVC_decoder__texture_V__DCRecontruction__addressing);
ART_ACTION(action6__predict__b0, ActorInstance_RVC_decoder__texture_V__DCRecontruction__addressing);
ART_ACTION_SCHEDULER(RVC_decoder__texture_V__DCRecontruction__addressing_action_scheduler);
static void ActorInstance_RVC_decoder__texture_V__DCRecontruction__addressing_constructor(AbstractActorInstance *);

static const PortDescription inputPortDescriptions[]={
  {0, "BTYPE", sizeof(int32_t)},
};
static const PortDescription outputPortDescriptions[]={
  {0, "A", sizeof(int32_t)},
  {0, "B", sizeof(int32_t)},
  {0, "C", sizeof(int32_t)},
};

static const int portRate_in_action0__start[] = {1};

static const int portRate_out_action0__start[] = {0, 0, 0};

static const int portRate_in_action1__getw[] = {1};

static const int portRate_out_action1__getw[] = {0, 0, 0};

static const int portRate_in_action2__geth[] = {1};

static const int portRate_out_action2__geth[] = {0, 0, 0};

static const int portRate_in_action3__read__intra[] = {1};

static const int portRate_out_action3__read__intra[] = {0, 0, 0};

static const int portRate_in_action4__read__other[] = {1};

static const int portRate_out_action4__read__other[] = {0, 0, 0};

static const int portRate_in_action5__advance[] = {0};

static const int portRate_out_action5__advance[] = {0, 0, 0};

static const int portRate_in_action6__predict__b0[] = {0};

static const int portRate_out_action6__predict__b0[] = {1, 1, 1};

static const ActionDescription actionDescriptions[] = {
  {"action0__start", portRate_in_action0__start, portRate_out_action0__start},
  {"action1__getw", portRate_in_action1__getw, portRate_out_action1__getw},
  {"action2__geth", portRate_in_action2__geth, portRate_out_action2__geth},
  {"action3__read__intra", portRate_in_action3__read__intra, portRate_out_action3__read__intra},
  {"action4__read__other", portRate_in_action4__read__other, portRate_out_action4__read__other},
  {"action5__advance", portRate_in_action5__advance, portRate_out_action5__advance},
  {"action6__predict__b0", portRate_in_action6__predict__b0, portRate_out_action6__predict__b0},
};

ActorClass klass=INIT_ActorClass(
  "RVC_decoder__texture_V__DCRecontruction__addressing",
  ActorInstance_RVC_decoder__texture_V__DCRecontruction__addressing,
  ActorInstance_RVC_decoder__texture_V__DCRecontruction__addressing_constructor,
  0, //setParam not needed anymore (we instantiate with params)
  RVC_decoder__texture_V__DCRecontruction__addressing_action_scheduler,
  0, // no destructor
  1, inputPortDescriptions,
  3, outputPortDescriptions,
  7, actionDescriptions
);

bool_t RVC_decoder__texture_V__DCRecontruction__addressing__DOLLAR__d1306(art_action_context_t *context, ActorInstance_RVC_decoder__texture_V__DCRecontruction__addressing *thisActor) {
  int32_t cmd;
  {
    bool_t ret;
    cmd = pinPeek_int32_t(IN0_BTYPE, 0);
    ret = (bitand(cmd, NEWVOP) != 0);
    return ret;
  }
}

// start
ART_ACTION(action0__start, ActorInstance_RVC_decoder__texture_V__DCRecontruction__addressing) {
  int32_t cmd;
  ART_ACTION_ENTER(action0__start, 0);
  cmd = pinRead_int32_t(IN0_BTYPE);
  thisActor->mbx = 0;
  thisActor->top_edge = 1;
  thisActor->left_edge = 1;
  ART_ACTION_EXIT(action0__start, 0);
}


// getw
ART_ACTION(action1__getw, ActorInstance_RVC_decoder__texture_V__DCRecontruction__addressing) {
  int32_t w;
  ART_ACTION_ENTER(action1__getw, 1);
  w = pinRead_int32_t(IN0_BTYPE);
  thisActor->mbwidth = w;
  thisActor->ptr = 1;
  thisActor->ptr_left = 2;
  thisActor->ptr_above = (1 + w);
  thisActor->ptr_above_left = (2 + w);
  ART_ACTION_EXIT(action1__getw, 1);
}


// geth
ART_ACTION(action2__geth, ActorInstance_RVC_decoder__texture_V__DCRecontruction__addressing) {
  int32_t h;
  ART_ACTION_ENTER(action2__geth, 2);
  h = pinRead_int32_t(IN0_BTYPE);
  ART_ACTION_EXIT(action2__geth, 2);
}

bool_t RVC_decoder__texture_V__DCRecontruction__addressing__DOLLAR__d1336(art_action_context_t *context, ActorInstance_RVC_decoder__texture_V__DCRecontruction__addressing *thisActor) {
  int32_t blocktype;
  {
    bool_t ret;
    blocktype = pinPeek_int32_t(IN0_BTYPE, 0);
    ret = (bitand(blocktype, INTRA) != 0);
    return ret;
  }
}

// read.intra
ART_ACTION(action3__read__intra, ActorInstance_RVC_decoder__texture_V__DCRecontruction__addressing) {
  int32_t blocktype;
  ART_ACTION_ENTER(action3__read__intra, 3);
  blocktype = pinRead_int32_t(IN0_BTYPE);
  thisActor->coded[thisActor->ptr] = 1;
  ART_ACTION_EXIT(action3__read__intra, 3);
}


// read.other
ART_ACTION(action4__read__other, ActorInstance_RVC_decoder__texture_V__DCRecontruction__addressing) {
  int32_t blocktype;
  ART_ACTION_ENTER(action4__read__other, 4);
  blocktype = pinRead_int32_t(IN0_BTYPE);
  thisActor->coded[thisActor->ptr] = 0;
  ART_ACTION_EXIT(action4__read__other, 4);
}


// advance
ART_ACTION(action5__advance, ActorInstance_RVC_decoder__texture_V__DCRecontruction__addressing) {
  ART_ACTION_ENTER(action5__advance, 5);
  thisActor->mbx = (thisActor->mbx + 1);
  thisActor->left_edge = 0;
  if ((thisActor->mbx == thisActor->mbwidth)) {
    thisActor->mbx = 0;
    thisActor->top_edge = 0;
    thisActor->left_edge = 1;
  }
  thisActor->ptr = RVC_decoder__texture_V__DCRecontruction__addressingdecrement(thisActor, thisActor->ptr);
  thisActor->ptr_left = RVC_decoder__texture_V__DCRecontruction__addressingdecrement(thisActor, thisActor->ptr_left);
  thisActor->ptr_above = RVC_decoder__texture_V__DCRecontruction__addressingdecrement(thisActor, thisActor->ptr_above);
  thisActor->ptr_above_left = RVC_decoder__texture_V__DCRecontruction__addressingdecrement(thisActor, thisActor->ptr_above_left);
  ART_ACTION_EXIT(action5__advance, 5);
}


// predict.b0
ART_ACTION(action6__predict__b0, ActorInstance_RVC_decoder__texture_V__DCRecontruction__addressing) {
  int32_t c;
  int32_t a;
  int32_t b;
  ART_ACTION_ENTER(action6__predict__b0, 6);
  c = 0;
  a = 0;
  b = 0;
  if ((!(thisActor->left_edge))) {
    a = thisActor->ptr_left;
    if ((!(thisActor->coded[a]))) {
      a = 0;
    }
    if ((!(thisActor->top_edge))) {
      b = thisActor->ptr_above_left;
      if ((!(thisActor->coded[b]))) {
        b = 0;
      }
    }
  }
  if ((!(thisActor->top_edge))) {
    c = thisActor->ptr_above;
    if ((!(thisActor->coded[c]))) {
      c = 0;
    }
  }
  pinWrite_int32_t(OUT0_A, a);
  pinWrite_int32_t(OUT1_B, b);
  pinWrite_int32_t(OUT2_C, c);
  ART_ACTION_EXIT(action6__predict__b0, 6);
}

#define ActorInstance_RVC_decoder__texture_V__DCRecontruction__addressing__read_ID 0
#define ActorInstance_RVC_decoder__texture_V__DCRecontruction__addressing__getw_ID 1
#define ActorInstance_RVC_decoder__texture_V__DCRecontruction__addressing__geth_ID 2
#define ActorInstance_RVC_decoder__texture_V__DCRecontruction__addressing__predict_ID 3
#define ActorInstance_RVC_decoder__texture_V__DCRecontruction__addressing__advance_ID 4
static void ActorInstance_RVC_decoder__texture_V__DCRecontruction__addressing_constructor(AbstractActorInstance *pBase) {
  ActorInstance_RVC_decoder__texture_V__DCRecontruction__addressing *thisActor=(ActorInstance_RVC_decoder__texture_V__DCRecontruction__addressing*) pBase;
  thisActor->_fsmState = ActorInstance_RVC_decoder__texture_V__DCRecontruction__addressing__read_ID;//Initial state
  {
    thisActor->coded = malloc((sizeof(bool_t) * 123));
    {
      int32_t i;
      for(i = 1; i <= 123; i++)
      {
        thisActor->coded[((0 + i) - 1)] = 0;
      }
    }
    thisActor->mbwidth = 0;
    thisActor->mbx = 0;
    thisActor->top_edge = 1;
  }

}
static const int exitcode_block_Any[3]={1,0,1};
ART_ACTION_SCHEDULER(RVC_decoder__texture_V__DCRecontruction__addressing_action_scheduler) {
  const int *result = EXIT_CODE_YIELD;
  ActorInstance_RVC_decoder__texture_V__DCRecontruction__addressing *thisActor=(ActorInstance_RVC_decoder__texture_V__DCRecontruction__addressing*) pBase;
  ART_ACTION_SCHEDULER_ENTER(1, 3)
  while(1) {
    switch(thisActor->_fsmState) {
      case ActorInstance_RVC_decoder__texture_V__DCRecontruction__addressing__read_ID:
        if ((pinAvailIn_int32_t(IN0_BTYPE) >= 1)) {
          if (RVC_decoder__texture_V__DCRecontruction__addressing__DOLLAR__d1306(context, thisActor)) {
            ART_FIRE_ACTION(action0__start);
            thisActor->_fsmState = ActorInstance_RVC_decoder__texture_V__DCRecontruction__addressing__getw_ID;
            continue;
          }
        }
        if ((pinAvailIn_int32_t(IN0_BTYPE) >= 1)) {
          if (RVC_decoder__texture_V__DCRecontruction__addressing__DOLLAR__d1336(context, thisActor)) {
            ART_FIRE_ACTION(action3__read__intra);
            thisActor->_fsmState = ActorInstance_RVC_decoder__texture_V__DCRecontruction__addressing__predict_ID;
            continue;
          }
        }
        if ((pinAvailIn_int32_t(IN0_BTYPE) >= 1)) {
          ART_FIRE_ACTION(action4__read__other);
          thisActor->_fsmState = ActorInstance_RVC_decoder__texture_V__DCRecontruction__addressing__advance_ID;
          continue;
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__texture_V__DCRecontruction__addressing__getw_ID:
        if ((pinAvailIn_int32_t(IN0_BTYPE) >= 1)) {
          ART_FIRE_ACTION(action1__getw);
          thisActor->_fsmState = ActorInstance_RVC_decoder__texture_V__DCRecontruction__addressing__geth_ID;
          continue;
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__texture_V__DCRecontruction__addressing__geth_ID:
        if ((pinAvailIn_int32_t(IN0_BTYPE) >= 1)) {
          ART_FIRE_ACTION(action2__geth);
          thisActor->_fsmState = ActorInstance_RVC_decoder__texture_V__DCRecontruction__addressing__read_ID;
          continue;
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__texture_V__DCRecontruction__addressing__predict_ID:
        if ((pinAvailOut_int32_t(OUT0_A) >= 1) && (pinAvailOut_int32_t(OUT1_B) >= 1) && (pinAvailOut_int32_t(OUT2_C) >= 1)) {
          ART_FIRE_ACTION(action6__predict__b0);
          thisActor->_fsmState = ActorInstance_RVC_decoder__texture_V__DCRecontruction__addressing__advance_ID;
          continue;
        
        } else {
          result = exitcode_block_Any;
          goto out;
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__texture_V__DCRecontruction__addressing__advance_ID:
        ART_FIRE_ACTION(action5__advance);
        thisActor->_fsmState = ActorInstance_RVC_decoder__texture_V__DCRecontruction__addressing__read_ID;
        continue;
        result = exitcode_block_Any;
        goto out;
        break;
      
    }
  }
  out:
  ART_ACTION_SCHEDULER_EXIT(1, 3)
  return result;
}