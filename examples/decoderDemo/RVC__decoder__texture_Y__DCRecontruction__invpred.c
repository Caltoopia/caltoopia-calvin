#include "actors-rts.h"
#include "natives.h"
#include "RVC__decoderDemo.h"
#define  IN0_BTYPE ART_INPUT(0)
#define  IN1_A ART_INPUT(1)
#define  IN2_B ART_INPUT(2)
#define  IN3_C ART_INPUT(3)
#define  IN4_QFS_DC ART_INPUT(4)
#define  IN5_QP ART_INPUT(5)
#define  OUT0_QF_DC ART_OUTPUT(0)
#define  OUT1_PTR ART_OUTPUT(1)
#define  OUT2_AC_PRED_DIR ART_OUTPUT(2)
#define  OUT3_SIGNED ART_OUTPUT(3)
#define  OUT4_QUANT ART_OUTPUT(4)
#define  OUT5_PREV_QUANT ART_OUTPUT(5)

//Actor constants
static const int32_t DCVAL = 1024;
static const int32_t MAXW_IN_MB = 121;
static const int32_t MB_COORD_SZ = 8;
static const int32_t BTYPE_SZ = 12;
static const int32_t SAMPLE_SZ = 13;
static const int32_t NEWVOP = 2048;
static const int32_t INTRA = 1024;
static const int32_t INTER = 512;
static const int32_t QUANT_MASK = 31;
static const int32_t ACCODED = 2;
static const int32_t ACPRED = 1;
static const int32_t QUANT_SZ = 6;
static const int32_t SCALER_SZ = 7;
static const int32_t BUF_SIZE = 492;

//Actor state
typedef struct {
  AbstractActorInstance base;
  int _fsmState;
  int32_t mbwidth;
  int32_t dc_pred;
  int32_t scaler;
  int32_t round;
  int32_t s_qp;
  int32_t s_prev_qp;
  int32_t dc_val;
  bool_t is_signed;
  int32_t* buf_qp;
  int32_t* dc_buf;
  int32_t ptr;
  int32_t cnt;
  int32_t comp;
} ActorInstance_RVC_decoder__texture_Y__DCRecontruction__invpred;

//Actor functions
inline int32_t RVC_decoder__texture_Y__DCRecontruction__invpredabs(ActorInstance_RVC_decoder__texture_Y__DCRecontruction__invpred* thisActor, int32_t x){
  return (((x < 0)) ? ((-(x))):(x));
}
inline int32_t RVC_decoder__texture_Y__DCRecontruction__invpreddc_scaler(ActorInstance_RVC_decoder__texture_Y__DCRecontruction__invpred* thisActor){
  return ((((thisActor->s_qp > 0) && (thisActor->s_qp < 5))) ? (8):(((((thisActor->s_qp > 4) && (thisActor->s_qp < 9))) ? ((2 * thisActor->s_qp)):(((((thisActor->s_qp > 8) && (thisActor->s_qp < 25))) ? ((thisActor->s_qp + 8)):(((2 * thisActor->s_qp) - 16)))))));
}
inline int32_t RVC_decoder__texture_Y__DCRecontruction__invpredsaturate(ActorInstance_RVC_decoder__texture_Y__DCRecontruction__invpred* thisActor, int32_t x){
  bool_t minus;
  bool_t plus;
  int32_t ret;
  minus = (x < (-(2048)));
  plus = (x > 2047);
  ret = ((minus) ? ((-(2048))):(((plus) ? (2047):(x))));
  return ret;
}
ART_ACTION_CONTEXT(6, 6)

ART_ACTION(action0__start, ActorInstance_RVC_decoder__texture_Y__DCRecontruction__invpred);
ART_ACTION(action1__getw, ActorInstance_RVC_decoder__texture_Y__DCRecontruction__invpred);
ART_ACTION(action2__skip, ActorInstance_RVC_decoder__texture_Y__DCRecontruction__invpred);
ART_ACTION(action3__read__inter_ac, ActorInstance_RVC_decoder__texture_Y__DCRecontruction__invpred);
ART_ACTION(action4__read__other, ActorInstance_RVC_decoder__texture_Y__DCRecontruction__invpred);
ART_ACTION(action5__read__intra, ActorInstance_RVC_decoder__texture_Y__DCRecontruction__invpred);
ART_ACTION(action6__getdc__inter, ActorInstance_RVC_decoder__texture_Y__DCRecontruction__invpred);
ART_ACTION(action7__getdc__intra, ActorInstance_RVC_decoder__texture_Y__DCRecontruction__invpred);
ART_ACTION(action8__sat, ActorInstance_RVC_decoder__texture_Y__DCRecontruction__invpred);
ART_ACTION(action9__advance, ActorInstance_RVC_decoder__texture_Y__DCRecontruction__invpred);
ART_ACTION_SCHEDULER(RVC_decoder__texture_Y__DCRecontruction__invpred_action_scheduler);
static void ActorInstance_RVC_decoder__texture_Y__DCRecontruction__invpred_constructor(AbstractActorInstance *);

static const PortDescription inputPortDescriptions[]={
  {0, "BTYPE", sizeof(int32_t)},
  {0, "A", sizeof(int32_t)},
  {0, "B", sizeof(int32_t)},
  {0, "C", sizeof(int32_t)},
  {0, "QFS_DC", sizeof(int32_t)},
  {0, "QP", sizeof(int32_t)},
};
static const PortDescription outputPortDescriptions[]={
  {0, "QF_DC", sizeof(int32_t)},
  {0, "PTR", sizeof(int32_t)},
  {0, "AC_PRED_DIR", sizeof(int32_t)},
  {0, "SIGNED", sizeof(bool_t)},
  {0, "QUANT", sizeof(int32_t)},
  {0, "PREV_QUANT", sizeof(int32_t)},
};

static const int portRate_in_action0__start[] = {1, 0, 0, 0, 0, 0};

static const int portRate_out_action0__start[] = {0, 0, 1, 0, 0, 0};

static const int portRate_in_action1__getw[] = {1, 0, 0, 0, 0, 0};

static const int portRate_out_action1__getw[] = {0, 0, 0, 0, 0, 0};

static const int portRate_in_action2__skip[] = {1, 0, 0, 0, 0, 0};

static const int portRate_out_action2__skip[] = {0, 0, 0, 0, 0, 0};

static const int portRate_in_action3__read__inter_ac[] = {1, 0, 0, 0, 0, 1};

static const int portRate_out_action3__read__inter_ac[] = {0, 1, 1, 1, 1, 1};

static const int portRate_in_action4__read__other[] = {1, 0, 0, 0, 0, 1};

static const int portRate_out_action4__read__other[] = {0, 0, 1, 0, 0, 0};

static const int portRate_in_action5__read__intra[] = {1, 1, 1, 1, 0, 1};

static const int portRate_out_action5__read__intra[] = {0, 1, 1, 1, 1, 1};

static const int portRate_in_action6__getdc__inter[] = {0, 0, 0, 0, 1, 0};

static const int portRate_out_action6__getdc__inter[] = {0, 0, 0, 0, 0, 0};

static const int portRate_in_action7__getdc__intra[] = {0, 0, 0, 0, 1, 0};

static const int portRate_out_action7__getdc__intra[] = {0, 0, 0, 0, 0, 0};

static const int portRate_in_action8__sat[] = {0, 0, 0, 0, 0, 0};

static const int portRate_out_action8__sat[] = {1, 0, 0, 0, 0, 0};

static const int portRate_in_action9__advance[] = {0, 0, 0, 0, 0, 0};

static const int portRate_out_action9__advance[] = {0, 0, 0, 0, 0, 0};

static const ActionDescription actionDescriptions[] = {
  {"action0__start", portRate_in_action0__start, portRate_out_action0__start},
  {"action1__getw", portRate_in_action1__getw, portRate_out_action1__getw},
  {"action2__skip", portRate_in_action2__skip, portRate_out_action2__skip},
  {"action3__read__inter_ac", portRate_in_action3__read__inter_ac, portRate_out_action3__read__inter_ac},
  {"action4__read__other", portRate_in_action4__read__other, portRate_out_action4__read__other},
  {"action5__read__intra", portRate_in_action5__read__intra, portRate_out_action5__read__intra},
  {"action6__getdc__inter", portRate_in_action6__getdc__inter, portRate_out_action6__getdc__inter},
  {"action7__getdc__intra", portRate_in_action7__getdc__intra, portRate_out_action7__getdc__intra},
  {"action8__sat", portRate_in_action8__sat, portRate_out_action8__sat},
  {"action9__advance", portRate_in_action9__advance, portRate_out_action9__advance},
};

ActorClass klass=INIT_ActorClass(
  "RVC_decoder__texture_Y__DCRecontruction__invpred",
  ActorInstance_RVC_decoder__texture_Y__DCRecontruction__invpred,
  ActorInstance_RVC_decoder__texture_Y__DCRecontruction__invpred_constructor,
  0, //setParam not needed anymore (we instantiate with params)
  RVC_decoder__texture_Y__DCRecontruction__invpred_action_scheduler,
  0, // no destructor
  6, inputPortDescriptions,
  6, outputPortDescriptions,
  10, actionDescriptions
);

bool_t RVC_decoder__texture_Y__DCRecontruction__invpred__DOLLAR__d9433(art_action_context_t *context, ActorInstance_RVC_decoder__texture_Y__DCRecontruction__invpred *thisActor) {
  int32_t cmd;
  {
    bool_t ret;
    cmd = pinPeek_int32_t(IN0_BTYPE, 0);
    ret = (bitand(cmd, NEWVOP) != 0);
    return ret;
  }
}

// start
ART_ACTION(action0__start, ActorInstance_RVC_decoder__texture_Y__DCRecontruction__invpred) {
  int32_t cmd;
  int32_t U__44;
  ART_ACTION_ENTER(action0__start, 0);
  cmd = pinRead_int32_t(IN0_BTYPE);
  thisActor->comp = 0;
  thisActor->ptr = 4;
  U__44 = -2;
  pinWrite_int32_t(OUT2_AC_PRED_DIR, U__44);
  ART_ACTION_EXIT(action0__start, 0);
}


// getw
ART_ACTION(action1__getw, ActorInstance_RVC_decoder__texture_Y__DCRecontruction__invpred) {
  int32_t x;
  ART_ACTION_ENTER(action1__getw, 1);
  x = pinRead_int32_t(IN0_BTYPE);
  thisActor->mbwidth = x;
  ART_ACTION_EXIT(action1__getw, 1);
}


// skip
ART_ACTION(action2__skip, ActorInstance_RVC_decoder__texture_Y__DCRecontruction__invpred) {
  int32_t x;
  ART_ACTION_ENTER(action2__skip, 2);
  x = pinRead_int32_t(IN0_BTYPE);
  ART_ACTION_EXIT(action2__skip, 2);
}

bool_t RVC_decoder__texture_Y__DCRecontruction__invpred__DOLLAR__d9463(art_action_context_t *context, ActorInstance_RVC_decoder__texture_Y__DCRecontruction__invpred *thisActor) {
  int32_t cmd;
  {
    bool_t ret;
    cmd = pinPeek_int32_t(IN0_BTYPE, 0);
    ret = (bitand(cmd, INTER) != 0);
    return ret;
  }
}
bool_t RVC_decoder__texture_Y__DCRecontruction__invpred__DOLLAR__d9472(art_action_context_t *context, ActorInstance_RVC_decoder__texture_Y__DCRecontruction__invpred *thisActor) {
  int32_t cmd;
  {
    bool_t ret;
    cmd = pinPeek_int32_t(IN0_BTYPE, 0);
    ret = (bitand(cmd, ACCODED) != 0);
    return ret;
  }
}

// read.inter_ac
ART_ACTION(action3__read__inter_ac, ActorInstance_RVC_decoder__texture_Y__DCRecontruction__invpred) {
  int32_t cmd;
  int32_t qp;
  int32_t U__45;
  int32_t U__46;
  bool_t U__47;
  ART_ACTION_ENTER(action3__read__inter_ac, 3);
  qp = pinRead_int32_t(IN5_QP);
  cmd = pinRead_int32_t(IN0_BTYPE);
  thisActor->s_qp = qp;
  thisActor->round = bitxor(bitand(thisActor->s_qp, 1), 1);
  thisActor->is_signed = 1;
  thisActor->s_prev_qp = thisActor->s_qp;
  thisActor->buf_qp[thisActor->cnt] = thisActor->s_qp;
  U__45 = 0;
  pinWrite_int32_t(OUT2_AC_PRED_DIR, U__45);
  U__46 = 0;
  pinWrite_int32_t(OUT1_PTR, U__46);
  U__47 = 1;
  pinWrite_bool_t(OUT3_SIGNED, U__47);
  pinWrite_int32_t(OUT4_QUANT, thisActor->s_qp);
  pinWrite_int32_t(OUT5_PREV_QUANT, thisActor->s_prev_qp);
  ART_ACTION_EXIT(action3__read__inter_ac, 3);
}

bool_t RVC_decoder__texture_Y__DCRecontruction__invpred__DOLLAR__d9521(art_action_context_t *context, ActorInstance_RVC_decoder__texture_Y__DCRecontruction__invpred *thisActor) {
  int32_t cmd;
  {
    bool_t ret;
    cmd = pinPeek_int32_t(IN0_BTYPE, 0);
    ret = (bitand(cmd, ACCODED) == 0);
    return ret;
  }
}
bool_t RVC_decoder__texture_Y__DCRecontruction__invpred__DOLLAR__d9530(art_action_context_t *context, ActorInstance_RVC_decoder__texture_Y__DCRecontruction__invpred *thisActor) {
  int32_t cmd;
  {
    bool_t ret;
    cmd = pinPeek_int32_t(IN0_BTYPE, 0);
    ret = (bitand(cmd, INTRA) == 0);
    return ret;
  }
}
bool_t RVC_decoder__texture_Y__DCRecontruction__invpred__DOLLAR__d9539(art_action_context_t *context, ActorInstance_RVC_decoder__texture_Y__DCRecontruction__invpred *thisActor) {
  int32_t cmd;
  {
    bool_t ret;
    cmd = pinPeek_int32_t(IN0_BTYPE, 0);
    ret = (bitand(cmd, NEWVOP) == 0);
    return ret;
  }
}

// read.other
ART_ACTION(action4__read__other, ActorInstance_RVC_decoder__texture_Y__DCRecontruction__invpred) {
  int32_t cmd;
  int32_t qp;
  int32_t U__48;
  ART_ACTION_ENTER(action4__read__other, 4);
  qp = pinRead_int32_t(IN5_QP);
  cmd = pinRead_int32_t(IN0_BTYPE);
  U__48 = -1;
  pinWrite_int32_t(OUT2_AC_PRED_DIR, U__48);
  ART_ACTION_EXIT(action4__read__other, 4);
}

bool_t RVC_decoder__texture_Y__DCRecontruction__invpred__DOLLAR__d9575(art_action_context_t *context, ActorInstance_RVC_decoder__texture_Y__DCRecontruction__invpred *thisActor) {
  int32_t cmd;
  {
    bool_t ret;
    cmd = pinPeek_int32_t(IN0_BTYPE, 0);
    ret = (bitand(cmd, INTRA) != 0);
    return ret;
  }
}

// read.intra
ART_ACTION(action5__read__intra, ActorInstance_RVC_decoder__texture_Y__DCRecontruction__invpred) {
  int32_t cmd;
  int32_t qp;
  int32_t a;
  int32_t b;
  int32_t c;
  int32_t s;
  int32_t dcc;
  int32_t dca;
  int32_t dcb;
  int32_t vert;
  int32_t horiz;
  bool_t top;
  bool_t ac;
  int32_t U__49;
  ART_ACTION_ENTER(action5__read__intra, 5);
  c = pinRead_int32_t(IN3_C);
  b = pinRead_int32_t(IN2_B);
  a = pinRead_int32_t(IN1_A);
  qp = pinRead_int32_t(IN5_QP);
  cmd = pinRead_int32_t(IN0_BTYPE);
  dcc = thisActor->dc_buf[c];
  dca = thisActor->dc_buf[a];
  dcb = thisActor->dc_buf[b];
  vert = RVC_decoder__texture_Y__DCRecontruction__invpredabs(thisActor, (dca - dcb));
  horiz = RVC_decoder__texture_Y__DCRecontruction__invpredabs(thisActor, (dcb - dcc));
  top = (vert < horiz);
  ac = (bitand(cmd, ACPRED) != 0);
  thisActor->s_qp = qp;
  thisActor->s_prev_qp = qp;
  thisActor->round = bitxor(bitand(thisActor->s_qp, 1), 1);
  thisActor->scaler = ((((thisActor->s_qp > 0) && (thisActor->s_qp < 5))) ? (8):(((((thisActor->s_qp > 4) && (thisActor->s_qp < 9))) ? ((2 * thisActor->s_qp)):(((((thisActor->s_qp > 8) && (thisActor->s_qp < 25))) ? ((thisActor->s_qp + 8)):(((2 * thisActor->s_qp) - 16)))))));
  thisActor->dc_pred = ((((top) ? (dcc):(dca)) + rshift(thisActor->scaler, 1)) / thisActor->scaler);
  s = (((!(ac))) ? (0):(((top) ? (2):(1))));
  thisActor->is_signed = (thisActor->scaler == 0);
  if ((s == 2)) {
    if (((thisActor->comp == 0) || (thisActor->comp == 1))) {
      thisActor->s_prev_qp = thisActor->buf_qp[(thisActor->cnt + 2)];
    
    } else {
      if (((thisActor->comp == 2) || (thisActor->comp == 3))) {
        thisActor->s_prev_qp = thisActor->buf_qp[(thisActor->cnt - 2)];
      }
    }
  }
  if (((s == 1) && (thisActor->cnt >= 3))) {
    if (((thisActor->comp == 0) || (thisActor->comp == 2))) {
      thisActor->s_prev_qp = thisActor->buf_qp[(thisActor->cnt - 3)];
    
    } else {
      if (((thisActor->comp == 1) || (thisActor->comp == 3))) {
        thisActor->s_prev_qp = thisActor->buf_qp[(thisActor->cnt - 1)];
      }
    }
  }
  thisActor->buf_qp[thisActor->cnt] = thisActor->s_qp;
  U__49 = ((top) ? (c):(a));
  pinWrite_int32_t(OUT1_PTR, U__49);
  pinWrite_int32_t(OUT2_AC_PRED_DIR, s);
  pinWrite_bool_t(OUT3_SIGNED, thisActor->is_signed);
  pinWrite_int32_t(OUT4_QUANT, thisActor->s_qp);
  pinWrite_int32_t(OUT5_PREV_QUANT, thisActor->s_prev_qp);
  ART_ACTION_EXIT(action5__read__intra, 5);
}


// getdc.inter
ART_ACTION(action6__getdc__inter, ActorInstance_RVC_decoder__texture_Y__DCRecontruction__invpred) {
  int32_t dc;
  int32_t v;
  ART_ACTION_ENTER(action6__getdc__inter, 6);
  dc = pinRead_int32_t(IN4_QFS_DC);
  v = ((thisActor->s_qp * (lshift(RVC_decoder__texture_Y__DCRecontruction__invpredabs(thisActor, dc), 1) + 1)) - thisActor->round);
  thisActor->dc_val = (((dc == 0)) ? (0):((((!(thisActor->is_signed))) ? (dc):((((dc < 0)) ? ((-(v))):(v))))));
  ART_ACTION_EXIT(action6__getdc__inter, 6);
}


// getdc.intra
ART_ACTION(action7__getdc__intra, ActorInstance_RVC_decoder__texture_Y__DCRecontruction__invpred) {
  int32_t dc;
  ART_ACTION_ENTER(action7__getdc__intra, 7);
  dc = pinRead_int32_t(IN4_QFS_DC);
  thisActor->dc_val = ((dc + thisActor->dc_pred) * thisActor->scaler);
  ART_ACTION_EXIT(action7__getdc__intra, 7);
}


// sat
ART_ACTION(action8__sat, ActorInstance_RVC_decoder__texture_Y__DCRecontruction__invpred) {
  int32_t dc;
  ART_ACTION_ENTER(action8__sat, 8);
  dc = RVC_decoder__texture_Y__DCRecontruction__invpredsaturate(thisActor, thisActor->dc_val);
  thisActor->dc_buf[bitor(thisActor->ptr, thisActor->comp)] = dc;
  pinWrite_int32_t(OUT0_QF_DC, dc);
  ART_ACTION_EXIT(action8__sat, 8);
}


// advance
ART_ACTION(action9__advance, ActorInstance_RVC_decoder__texture_Y__DCRecontruction__invpred) {
  ART_ACTION_ENTER(action9__advance, 9);
  thisActor->cnt = (thisActor->cnt + 1);
  if ((thisActor->cnt == (thisActor->mbwidth * 4))) {
    thisActor->cnt = 0;
  }
  thisActor->comp = (thisActor->comp + 1);
  if ((thisActor->comp == 4)) {
    thisActor->comp = 0;
    thisActor->ptr = (((thisActor->ptr == 4)) ? ((BUF_SIZE - 4)):((thisActor->ptr - 4)));
  }
  ART_ACTION_EXIT(action9__advance, 9);
}

#define ActorInstance_RVC_decoder__texture_Y__DCRecontruction__invpred__read_ID 0
#define ActorInstance_RVC_decoder__texture_Y__DCRecontruction__invpred__getw_ID 1
#define ActorInstance_RVC_decoder__texture_Y__DCRecontruction__invpred__inter_ID 2
#define ActorInstance_RVC_decoder__texture_Y__DCRecontruction__invpred__intra_ID 3
#define ActorInstance_RVC_decoder__texture_Y__DCRecontruction__invpred__advance_ID 4
#define ActorInstance_RVC_decoder__texture_Y__DCRecontruction__invpred__geth_ID 5
#define ActorInstance_RVC_decoder__texture_Y__DCRecontruction__invpred__sat_ID 6
static void ActorInstance_RVC_decoder__texture_Y__DCRecontruction__invpred_constructor(AbstractActorInstance *pBase) {
  ActorInstance_RVC_decoder__texture_Y__DCRecontruction__invpred *thisActor=(ActorInstance_RVC_decoder__texture_Y__DCRecontruction__invpred*) pBase;
  thisActor->_fsmState = ActorInstance_RVC_decoder__texture_Y__DCRecontruction__invpred__read_ID;//Initial state
  {
    thisActor->dc_buf = malloc((sizeof(int32_t) * 492));
    thisActor->buf_qp = malloc((sizeof(int32_t) * 1968));
    thisActor->mbwidth = 0;
    {
      int32_t k;
      for(k = 1; k <= 1968; k++)
      {
        thisActor->buf_qp[((0 + k) - 1)] = 0;
      }
    }
    {
      int32_t k;
      for(k = 1; k <= 492; k++)
      {
        thisActor->dc_buf[((0 + k) - 1)] = 1024;
      }
    }
    thisActor->ptr = 4;
    thisActor->cnt = 0;
    thisActor->comp = 0;
  }

}
static const int exitcode_block_Any[3]={1,0,1};
ART_ACTION_SCHEDULER(RVC_decoder__texture_Y__DCRecontruction__invpred_action_scheduler) {
  const int *result = EXIT_CODE_YIELD;
  ActorInstance_RVC_decoder__texture_Y__DCRecontruction__invpred *thisActor=(ActorInstance_RVC_decoder__texture_Y__DCRecontruction__invpred*) pBase;
  ART_ACTION_SCHEDULER_ENTER(6, 6)
  while(1) {
    switch(thisActor->_fsmState) {
      case ActorInstance_RVC_decoder__texture_Y__DCRecontruction__invpred__read_ID:
        if ((pinAvailIn_int32_t(IN0_BTYPE) >= 1)) {
          if (RVC_decoder__texture_Y__DCRecontruction__invpred__DOLLAR__d9433(context, thisActor)) {
            if ((pinAvailOut_int32_t(OUT2_AC_PRED_DIR) >= 1)) {
              ART_FIRE_ACTION(action0__start);
              thisActor->_fsmState = ActorInstance_RVC_decoder__texture_Y__DCRecontruction__invpred__getw_ID;
              continue;
            
            } else {
              result = exitcode_block_Any;
              goto out;
            }
          }
        }
        if ((pinAvailIn_int32_t(IN0_BTYPE) >= 1) && (pinAvailIn_int32_t(IN5_QP) >= 1)) {
          if (RVC_decoder__texture_Y__DCRecontruction__invpred__DOLLAR__d9463(context, thisActor) && RVC_decoder__texture_Y__DCRecontruction__invpred__DOLLAR__d9472(context, thisActor)) {
            if ((pinAvailOut_int32_t(OUT2_AC_PRED_DIR) >= 1) && (pinAvailOut_int32_t(OUT1_PTR) >= 1) && (pinAvailOut_bool_t(OUT3_SIGNED) >= 1) && (pinAvailOut_int32_t(OUT4_QUANT) >= 1) && (pinAvailOut_int32_t(OUT5_PREV_QUANT) >= 1)) {
              ART_FIRE_ACTION(action3__read__inter_ac);
              thisActor->_fsmState = ActorInstance_RVC_decoder__texture_Y__DCRecontruction__invpred__inter_ID;
              continue;
            
            } else {
              result = exitcode_block_Any;
              goto out;
            }
          }
        }
        if ((pinAvailIn_int32_t(IN0_BTYPE) >= 1) && (pinAvailIn_int32_t(IN5_QP) >= 1)) {
          if (RVC_decoder__texture_Y__DCRecontruction__invpred__DOLLAR__d9521(context, thisActor) && RVC_decoder__texture_Y__DCRecontruction__invpred__DOLLAR__d9530(context, thisActor) && RVC_decoder__texture_Y__DCRecontruction__invpred__DOLLAR__d9539(context, thisActor)) {
            if ((pinAvailOut_int32_t(OUT2_AC_PRED_DIR) >= 1)) {
              ART_FIRE_ACTION(action4__read__other);
              thisActor->_fsmState = ActorInstance_RVC_decoder__texture_Y__DCRecontruction__invpred__advance_ID;
              continue;
            
            } else {
              result = exitcode_block_Any;
              goto out;
            }
          }
        }
        if ((pinAvailIn_int32_t(IN0_BTYPE) >= 1) && (pinAvailIn_int32_t(IN5_QP) >= 1) && (pinAvailIn_int32_t(IN1_A) >= 1) && (pinAvailIn_int32_t(IN2_B) >= 1) && (pinAvailIn_int32_t(IN3_C) >= 1)) {
          if (RVC_decoder__texture_Y__DCRecontruction__invpred__DOLLAR__d9575(context, thisActor)) {
            if ((pinAvailOut_int32_t(OUT1_PTR) >= 1) && (pinAvailOut_int32_t(OUT2_AC_PRED_DIR) >= 1) && (pinAvailOut_bool_t(OUT3_SIGNED) >= 1) && (pinAvailOut_int32_t(OUT4_QUANT) >= 1) && (pinAvailOut_int32_t(OUT5_PREV_QUANT) >= 1)) {
              ART_FIRE_ACTION(action5__read__intra);
              thisActor->_fsmState = ActorInstance_RVC_decoder__texture_Y__DCRecontruction__invpred__intra_ID;
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
      
      case ActorInstance_RVC_decoder__texture_Y__DCRecontruction__invpred__getw_ID:
        if ((pinAvailIn_int32_t(IN0_BTYPE) >= 1)) {
          ART_FIRE_ACTION(action1__getw);
          thisActor->_fsmState = ActorInstance_RVC_decoder__texture_Y__DCRecontruction__invpred__geth_ID;
          continue;
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__texture_Y__DCRecontruction__invpred__inter_ID:
        if ((pinAvailIn_int32_t(IN4_QFS_DC) >= 1)) {
          ART_FIRE_ACTION(action6__getdc__inter);
          thisActor->_fsmState = ActorInstance_RVC_decoder__texture_Y__DCRecontruction__invpred__sat_ID;
          continue;
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__texture_Y__DCRecontruction__invpred__intra_ID:
        if ((pinAvailIn_int32_t(IN4_QFS_DC) >= 1)) {
          ART_FIRE_ACTION(action7__getdc__intra);
          thisActor->_fsmState = ActorInstance_RVC_decoder__texture_Y__DCRecontruction__invpred__sat_ID;
          continue;
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__texture_Y__DCRecontruction__invpred__advance_ID:
        ART_FIRE_ACTION(action9__advance);
        thisActor->_fsmState = ActorInstance_RVC_decoder__texture_Y__DCRecontruction__invpred__read_ID;
        continue;
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__texture_Y__DCRecontruction__invpred__geth_ID:
        if ((pinAvailIn_int32_t(IN0_BTYPE) >= 1)) {
          ART_FIRE_ACTION(action2__skip);
          thisActor->_fsmState = ActorInstance_RVC_decoder__texture_Y__DCRecontruction__invpred__read_ID;
          continue;
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__texture_Y__DCRecontruction__invpred__sat_ID:
        if ((pinAvailOut_int32_t(OUT0_QF_DC) >= 1)) {
          ART_FIRE_ACTION(action8__sat);
          thisActor->_fsmState = ActorInstance_RVC_decoder__texture_Y__DCRecontruction__invpred__advance_ID;
          continue;
        
        } else {
          result = exitcode_block_Any;
          goto out;
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
    }
  }
  out:
  ART_ACTION_SCHEDULER_EXIT(6, 6)
  return result;
}