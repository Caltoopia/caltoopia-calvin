#include "actors-rts.h"
#include "natives.h"
#include "RVC__decoderDemo.h"
#define  IN0_BTYPE ART_INPUT(0)
#define  IN1_MVIN ART_INPUT(1)
#define  IN2_A ART_INPUT(2)
#define  OUT0_MV ART_OUTPUT(0)

//Actor constants
static const int32_t MAXW_IN_MB = 121;
static const int32_t MB_COORD_SZ = 8;
static const int32_t BTYPE_SZ = 12;
static const int32_t MV_SZ = 9;
static const int32_t NEWVOP = 2048;
static const int32_t INTER = 512;
static const int32_t FCODE_MASK = 448;
static const int32_t FCODE_SHIFT = 6;
static const int32_t FOURMV = 4;
static const int32_t MOTION = 8;
static const int32_t BUF_SIZE = 968;
static const int32_t Y_SELECT = 4;

//Actor state
typedef struct {
  AbstractActorInstance base;
  int _fsmState;
  int32_t mbx;
  int32_t sum_y;
  int32_t apred;
  bool_t top_edge;
  bool_t x_flag;
  int32_t ptr;
  int32_t pred_x;
  int32_t res_shift;
  int32_t sum_x;
  int32_t aptr;
  int32_t mv_low;
  int32_t pred_y;
  int32_t* buf;
  int32_t mbwidth;
  int32_t bptr;
  int32_t cptr;
  int32_t cpred;
  int32_t comp;
  bool_t fourmv;
  int32_t mv_rsize;
  int32_t mv_y;
  int32_t bpred;
  int32_t mv_high;
  int32_t mv_range;
  int32_t mv_x;
  int32_t mag;
} ActorInstance_RVC_decoder__parser__mvrecon;

//Actor functions
static inline int32_t RVC_decoder__parser__mvreconmiddle(ActorInstance_RVC_decoder__parser__mvrecon* thisActor, int32_t a, int32_t b, int32_t c){
  return (((a < b)) ? ((((a > c)) ? (a):((((b < c)) ? (b):(c))))):((((b > c)) ? (b):((((a < c)) ? (a):(c))))));
}
static inline int32_t RVC_decoder__parser__mvreconmvcalc(ActorInstance_RVC_decoder__parser__mvrecon* thisActor, int32_t pred, int32_t mv_mag, int32_t mag_shift){
  return ((((thisActor->mv_rsize == 0) || (mv_mag == 0))) ? ((pred + mv_mag)):((((mv_mag < 0)) ? ((pred - mag_shift)):((pred + mag_shift)))));
}
static inline int32_t RVC_decoder__parser__mvreconmvclip(ActorInstance_RVC_decoder__parser__mvrecon* thisActor, int32_t v){
  return (((v < thisActor->mv_low)) ? ((v + thisActor->mv_range)):((((v > thisActor->mv_high)) ? ((v - thisActor->mv_range)):(v))));
}
static inline int32_t RVC_decoder__parser__mvreconuvclip_1(ActorInstance_RVC_decoder__parser__mvrecon* thisActor, int32_t v){
  int32_t vv;
  int32_t ret;
  vv = rshift(v, 1);
  ret = bitor(vv, (((bitand(v, 3) == 0)) ? (0):(1)));
  return ret;
}
static inline int32_t RVC_decoder__parser__mvreconuvclip_4(ActorInstance_RVC_decoder__parser__mvrecon* thisActor, int32_t v){
  bool_t sign;
  int32_t absv;
  int32_t resv;
  int32_t delta;
  int32_t vv;
  int32_t ret;
  sign = (v < 0);
  absv = ((sign) ? ((-(v))):(v));
  resv = (absv - lshift(rshift(absv, 4), 4));
  delta = (((resv < 3)) ? (0):((((resv > 13)) ? (2):(1))));
  vv = (lshift(rshift(absv, 4), 1) + delta);
  ret = ((sign) ? ((-(vv))):(vv));
  return ret;
}
ART_ACTION_CONTEXT(3, 1)

ART_ACTION(action0__start, ActorInstance_RVC_decoder__parser__mvrecon);
ART_ACTION(action1__getw, ActorInstance_RVC_decoder__parser__mvrecon);
ART_ACTION(action2__geth, ActorInstance_RVC_decoder__parser__mvrecon);
ART_ACTION(action3__read__noMotion, ActorInstance_RVC_decoder__parser__mvrecon);
ART_ACTION(action4__read__motion, ActorInstance_RVC_decoder__parser__mvrecon);
ART_ACTION(action5__compute__done, ActorInstance_RVC_decoder__parser__mvrecon);
ART_ACTION(action6__compute__start, ActorInstance_RVC_decoder__parser__mvrecon);
ART_ACTION(action7__get_pred, ActorInstance_RVC_decoder__parser__mvrecon);
ART_ACTION(action8__do_pred, ActorInstance_RVC_decoder__parser__mvrecon);
ART_ACTION(action9__get_mag, ActorInstance_RVC_decoder__parser__mvrecon);
ART_ACTION(action10__get_residual__init, ActorInstance_RVC_decoder__parser__mvrecon);
ART_ACTION(action11__get_residual__shift, ActorInstance_RVC_decoder__parser__mvrecon);
ART_ACTION(action12__get_residual__adjust, ActorInstance_RVC_decoder__parser__mvrecon);
ART_ACTION(action13__get_residual__calc, ActorInstance_RVC_decoder__parser__mvrecon);
ART_ACTION(action14__get_residual__clip, ActorInstance_RVC_decoder__parser__mvrecon);
ART_ACTION(action15__get_residual__final, ActorInstance_RVC_decoder__parser__mvrecon);
ART_ACTION(action16__write__luma, ActorInstance_RVC_decoder__parser__mvrecon);
ART_ACTION(action17__write__chroma, ActorInstance_RVC_decoder__parser__mvrecon);
ART_ACTION(action18__advance, ActorInstance_RVC_decoder__parser__mvrecon);
ART_ACTION_SCHEDULER(RVC_decoder__parser__mvrecon_action_scheduler);
static void ActorInstance_RVC_decoder__parser__mvrecon_constructor(AbstractActorInstance *);

static const PortDescription inputPortDescriptions[]={
  {0, "BTYPE", sizeof(int32_t), NULL},
  {0, "MVIN", sizeof(int32_t), NULL},
  {0, "A", sizeof(int32_t), NULL},
};
static const PortDescription outputPortDescriptions[]={
  {0, "MV", sizeof(int32_t), NULL},
};

static const int portRate_in_action0__start[] = {1, 0, 0};

static const int portRate_out_action0__start[] = {0};

static const int portRate_in_action1__getw[] = {1, 0, 0};

static const int portRate_out_action1__getw[] = {0};

static const int portRate_in_action2__geth[] = {1, 0, 0};

static const int portRate_out_action2__geth[] = {0};

static const int portRate_in_action3__read__noMotion[] = {1, 0, 0};

static const int portRate_out_action3__read__noMotion[] = {0};

static const int portRate_in_action4__read__motion[] = {1, 0, 0};

static const int portRate_out_action4__read__motion[] = {0};

static const int portRate_in_action5__compute__done[] = {0, 0, 0};

static const int portRate_out_action5__compute__done[] = {0};

static const int portRate_in_action6__compute__start[] = {0, 0, 1};

static const int portRate_out_action6__compute__start[] = {0};

static const int portRate_in_action7__get_pred[] = {0, 0, 0};

static const int portRate_out_action7__get_pred[] = {0};

static const int portRate_in_action8__do_pred[] = {0, 0, 0};

static const int portRate_out_action8__do_pred[] = {0};

static const int portRate_in_action9__get_mag[] = {0, 1, 0};

static const int portRate_out_action9__get_mag[] = {0};

static const int portRate_in_action10__get_residual__init[] = {0, 0, 0};

static const int portRate_out_action10__get_residual__init[] = {0};

static const int portRate_in_action11__get_residual__shift[] = {0, 0, 0};

static const int portRate_out_action11__get_residual__shift[] = {0};

static const int portRate_in_action12__get_residual__adjust[] = {0, 1, 0};

static const int portRate_out_action12__get_residual__adjust[] = {0};

static const int portRate_in_action13__get_residual__calc[] = {0, 0, 0};

static const int portRate_out_action13__get_residual__calc[] = {0};

static const int portRate_in_action14__get_residual__clip[] = {0, 0, 0};

static const int portRate_out_action14__get_residual__clip[] = {0};

static const int portRate_in_action15__get_residual__final[] = {0, 0, 0};

static const int portRate_out_action15__get_residual__final[] = {0};

static const int portRate_in_action16__write__luma[] = {0, 0, 0};

static const int portRate_out_action16__write__luma[] = {1};

static const int portRate_in_action17__write__chroma[] = {0, 0, 0};

static const int portRate_out_action17__write__chroma[] = {1};

static const int portRate_in_action18__advance[] = {0, 0, 0};

static const int portRate_out_action18__advance[] = {0};

static const ActionDescription actionDescriptions[] = {
  {"action0__start", portRate_in_action0__start, portRate_out_action0__start},
  {"action1__getw", portRate_in_action1__getw, portRate_out_action1__getw},
  {"action2__geth", portRate_in_action2__geth, portRate_out_action2__geth},
  {"action3__read__noMotion", portRate_in_action3__read__noMotion, portRate_out_action3__read__noMotion},
  {"action4__read__motion", portRate_in_action4__read__motion, portRate_out_action4__read__motion},
  {"action5__compute__done", portRate_in_action5__compute__done, portRate_out_action5__compute__done},
  {"action6__compute__start", portRate_in_action6__compute__start, portRate_out_action6__compute__start},
  {"action7__get_pred", portRate_in_action7__get_pred, portRate_out_action7__get_pred},
  {"action8__do_pred", portRate_in_action8__do_pred, portRate_out_action8__do_pred},
  {"action9__get_mag", portRate_in_action9__get_mag, portRate_out_action9__get_mag},
  {"action10__get_residual__init", portRate_in_action10__get_residual__init, portRate_out_action10__get_residual__init},
  {"action11__get_residual__shift", portRate_in_action11__get_residual__shift, portRate_out_action11__get_residual__shift},
  {"action12__get_residual__adjust", portRate_in_action12__get_residual__adjust, portRate_out_action12__get_residual__adjust},
  {"action13__get_residual__calc", portRate_in_action13__get_residual__calc, portRate_out_action13__get_residual__calc},
  {"action14__get_residual__clip", portRate_in_action14__get_residual__clip, portRate_out_action14__get_residual__clip},
  {"action15__get_residual__final", portRate_in_action15__get_residual__final, portRate_out_action15__get_residual__final},
  {"action16__write__luma", portRate_in_action16__write__luma, portRate_out_action16__write__luma},
  {"action17__write__chroma", portRate_in_action17__write__chroma, portRate_out_action17__write__chroma},
  {"action18__advance", portRate_in_action18__advance, portRate_out_action18__advance},
};

ActorClass klass=INIT_ActorClass(
  "RVC_decoder__parser__mvrecon",
  ActorInstance_RVC_decoder__parser__mvrecon,
  ActorInstance_RVC_decoder__parser__mvrecon_constructor,
  0, //setParam not needed anymore (we instantiate with params)
  0, 0, // serialize/deserialize
  RVC_decoder__parser__mvrecon_action_scheduler,
  0, // no destructor
  3, inputPortDescriptions,
  1, outputPortDescriptions,
  19, actionDescriptions
);

bool_t RVC_decoder__parser__mvrecon__DOLLAR__d297(art_action_context_t *context, ActorInstance_RVC_decoder__parser__mvrecon *thisActor) {
  int32_t cmd;
  {
    bool_t ret;
    cmd = pinPeek_int32_t(IN0_BTYPE, 0);
    ret = (bitand(cmd, NEWVOP) != 0);
    return ret;
  }
}

// start
ART_ACTION(action0__start, ActorInstance_RVC_decoder__parser__mvrecon) {
  int32_t cmd;
  int32_t fcode;
  ART_ACTION_ENTER(action0__start, 0);
  cmd = pinRead_int32_t(IN0_BTYPE);
  fcode = rshift(bitand(cmd, FCODE_MASK), FCODE_SHIFT);
  thisActor->mbx = 0;
  thisActor->top_edge = 1;
  thisActor->comp = 0;
  if ((fcode > 0)) {
    thisActor->mv_rsize = (fcode - 1);
    thisActor->mv_range = lshift(1, (thisActor->mv_rsize + 5));
    thisActor->mv_low = (-(thisActor->mv_range));
    thisActor->mv_high = (thisActor->mv_range - 1);
    thisActor->mv_range = lshift(thisActor->mv_range, 1);
  }
  ART_ACTION_EXIT(action0__start, 0);
}


// getw
ART_ACTION(action1__getw, ActorInstance_RVC_decoder__parser__mvrecon) {
  int32_t w;
  ART_ACTION_ENTER(action1__getw, 1);
  w = pinRead_int32_t(IN0_BTYPE);
  thisActor->mbwidth = w;
  thisActor->ptr = 8;
  ART_ACTION_EXIT(action1__getw, 1);
}


// geth
ART_ACTION(action2__geth, ActorInstance_RVC_decoder__parser__mvrecon) {
  int32_t h;
  ART_ACTION_ENTER(action2__geth, 2);
  h = pinRead_int32_t(IN0_BTYPE);
  ART_ACTION_EXIT(action2__geth, 2);
}

bool_t RVC_decoder__parser__mvrecon__DOLLAR__d352(art_action_context_t *context, ActorInstance_RVC_decoder__parser__mvrecon *thisActor) {
  int32_t cmd;
  {
    bool_t ret;
    cmd = pinPeek_int32_t(IN0_BTYPE, 0);
    cmd = pinPeek_int32_t(IN0_BTYPE, 0);
    ret = ((bitand(cmd, INTER) == 0) || (bitand(cmd, MOTION) == 0));
    return ret;
  }
}
bool_t RVC_decoder__parser__mvrecon__DOLLAR__d370(art_action_context_t *context, ActorInstance_RVC_decoder__parser__mvrecon *thisActor) {
  int32_t cmd;
  {
    bool_t ret;
    cmd = pinPeek_int32_t(IN0_BTYPE, 0);
    ret = (bitand(cmd, NEWVOP) == 0);
    return ret;
  }
}

// read.noMotion
ART_ACTION(action3__read__noMotion, ActorInstance_RVC_decoder__parser__mvrecon) {
  int32_t cmd;
  int32_t p;
  ART_ACTION_ENTER(action3__read__noMotion, 3);
  cmd = pinRead_int32_t(IN0_BTYPE);
  p = bitor(thisActor->ptr, thisActor->comp);
  if ((thisActor->comp < 4)) {
    thisActor->buf[p] = 0;
    thisActor->buf[bitor(p, Y_SELECT)] = 0;
  }
  ART_ACTION_EXIT(action3__read__noMotion, 3);
}

bool_t RVC_decoder__parser__mvrecon__DOLLAR__d402(art_action_context_t *context, ActorInstance_RVC_decoder__parser__mvrecon *thisActor) {
  int32_t cmd;
  {
    bool_t ret;
    cmd = pinPeek_int32_t(IN0_BTYPE, 0);
    ret = (bitand(cmd, INTER) != 0);
    return ret;
  }
}
bool_t RVC_decoder__parser__mvrecon__DOLLAR__d411(art_action_context_t *context, ActorInstance_RVC_decoder__parser__mvrecon *thisActor) {
  int32_t cmd;
  {
    bool_t ret;
    cmd = pinPeek_int32_t(IN0_BTYPE, 0);
    ret = (bitand(cmd, MOTION) != 0);
    return ret;
  }
}
bool_t RVC_decoder__parser__mvrecon__DOLLAR__d420(art_action_context_t *context, ActorInstance_RVC_decoder__parser__mvrecon *thisActor) {
  int32_t cmd;
  {
    bool_t ret;
    cmd = pinPeek_int32_t(IN0_BTYPE, 0);
    ret = (bitand(cmd, NEWVOP) == 0);
    return ret;
  }
}

// read.motion
ART_ACTION(action4__read__motion, ActorInstance_RVC_decoder__parser__mvrecon) {
  int32_t cmd;
  ART_ACTION_ENTER(action4__read__motion, 4);
  cmd = pinRead_int32_t(IN0_BTYPE);
  if ((thisActor->comp == 0)) {
    thisActor->fourmv = (bitand(cmd, FOURMV) != 0);
    thisActor->sum_x = 0;
    thisActor->sum_y = 0;
  }
  ART_ACTION_EXIT(action4__read__motion, 4);
}

bool_t RVC_decoder__parser__mvrecon__DOLLAR__d442(art_action_context_t *context, ActorInstance_RVC_decoder__parser__mvrecon *thisActor) {
  {
    bool_t ret;
    ret = ((thisActor->comp > 3) || ((thisActor->comp != 0) && (!(thisActor->fourmv))));
    return ret;
  }
}

// compute.done
ART_ACTION(action5__compute__done, ActorInstance_RVC_decoder__parser__mvrecon) {
  ART_ACTION_ENTER(action5__compute__done, 5);
  ART_ACTION_EXIT(action5__compute__done, 5);
}


// compute.start
ART_ACTION(action6__compute__start, ActorInstance_RVC_decoder__parser__mvrecon) {
  int32_t a;
  ART_ACTION_ENTER(action6__compute__start, 6);
  a = pinRead_int32_t(IN2_A);
  thisActor->aptr = thisActor->bptr;
  thisActor->bptr = thisActor->cptr;
  thisActor->cptr = a;
  ART_ACTION_EXIT(action6__compute__start, 6);
}


// get_pred
ART_ACTION(action7__get_pred, ActorInstance_RVC_decoder__parser__mvrecon) {
  int32_t t;
  ART_ACTION_ENTER(action7__get_pred, 7);
  t = thisActor->aptr;
  thisActor->apred = thisActor->bpred;
  thisActor->bpred = thisActor->cpred;
  thisActor->cpred = thisActor->buf[t];
  thisActor->aptr = thisActor->bptr;
  thisActor->bptr = thisActor->cptr;
  thisActor->cptr = bitor(t, Y_SELECT);
  ART_ACTION_EXIT(action7__get_pred, 7);
}


// do_pred
ART_ACTION(action8__do_pred, ActorInstance_RVC_decoder__parser__mvrecon) {
  ART_ACTION_ENTER(action8__do_pred, 8);
  if (((thisActor->comp >= 2) || (!(thisActor->top_edge)))) {
    thisActor->apred = RVC_decoder__parser__mvreconmiddle(thisActor, thisActor->apred, thisActor->bpred, thisActor->cpred);
  }
  ART_ACTION_EXIT(action8__do_pred, 8);
}


// get_mag
ART_ACTION(action9__get_mag, ActorInstance_RVC_decoder__parser__mvrecon) {
  int32_t m;
  ART_ACTION_ENTER(action9__get_mag, 9);
  m = pinRead_int32_t(IN1_MVIN);
  thisActor->mag = m;
  ART_ACTION_EXIT(action9__get_mag, 9);
}


// get_residual.init
ART_ACTION(action10__get_residual__init, ActorInstance_RVC_decoder__parser__mvrecon) {
  ART_ACTION_ENTER(action10__get_residual__init, 10);
  thisActor->res_shift = (((thisActor->mag < 0)) ? (bitnot(thisActor->mag)):((thisActor->mag - 1)));
  ART_ACTION_EXIT(action10__get_residual__init, 10);
}


// get_residual.shift
ART_ACTION(action11__get_residual__shift, ActorInstance_RVC_decoder__parser__mvrecon) {
  int32_t count;
  ART_ACTION_ENTER(action11__get_residual__shift, 11);
  count = thisActor->mv_rsize;
  while ((count > 0)) {
    thisActor->res_shift = lshift(thisActor->res_shift, 1);
    count = (count - 1);
  }
  ART_ACTION_EXIT(action11__get_residual__shift, 11);
}


// get_residual.adjust
ART_ACTION(action12__get_residual__adjust, ActorInstance_RVC_decoder__parser__mvrecon) {
  int32_t s;
  ART_ACTION_ENTER(action12__get_residual__adjust, 12);
  s = pinRead_int32_t(IN1_MVIN);
  thisActor->res_shift = ((thisActor->res_shift + s) + 1);
  ART_ACTION_EXIT(action12__get_residual__adjust, 12);
}


// get_residual.calc
ART_ACTION(action13__get_residual__calc, ActorInstance_RVC_decoder__parser__mvrecon) {
  ART_ACTION_ENTER(action13__get_residual__calc, 13);
  thisActor->res_shift = RVC_decoder__parser__mvreconmvcalc(thisActor, thisActor->apred, thisActor->mag, thisActor->res_shift);
  ART_ACTION_EXIT(action13__get_residual__calc, 13);
}


// get_residual.clip
ART_ACTION(action14__get_residual__clip, ActorInstance_RVC_decoder__parser__mvrecon) {
  ART_ACTION_ENTER(action14__get_residual__clip, 14);
  thisActor->res_shift = RVC_decoder__parser__mvreconmvclip(thisActor, thisActor->res_shift);
  ART_ACTION_EXIT(action14__get_residual__clip, 14);
}


// get_residual.final
ART_ACTION(action15__get_residual__final, ActorInstance_RVC_decoder__parser__mvrecon) {
  int32_t sum;
  ART_ACTION_ENTER(action15__get_residual__final, 15);
  sum = (thisActor->sum_x + thisActor->res_shift);
  thisActor->mv_x = thisActor->mv_y;
  thisActor->mv_y = thisActor->res_shift;
  thisActor->sum_x = thisActor->sum_y;
  thisActor->sum_y = sum;
  thisActor->x_flag = 1;
  ART_ACTION_EXIT(action15__get_residual__final, 15);
}

bool_t RVC_decoder__parser__mvrecon__DOLLAR__d545(art_action_context_t *context, ActorInstance_RVC_decoder__parser__mvrecon *thisActor) {
  {
    bool_t ret;
    ret = (thisActor->comp < 4);
    return ret;
  }
}

// write.luma
ART_ACTION(action16__write__luma, ActorInstance_RVC_decoder__parser__mvrecon) {
  int32_t t;
  int32_t p;
  ART_ACTION_ENTER(action16__write__luma, 16);
  t = thisActor->mv_x;
  p = bitor(thisActor->ptr, thisActor->comp);
  thisActor->buf[bitor(p, ((thisActor->x_flag) ? (0):(Y_SELECT)))] = thisActor->mv_x;
  thisActor->mv_x = thisActor->mv_y;
  thisActor->mv_y = t;
  thisActor->x_flag = (!(thisActor->x_flag));
  pinWrite_int32_t(OUT0_MV, t);
  ART_ACTION_EXIT(action16__write__luma, 16);
}


// write.chroma
ART_ACTION(action17__write__chroma, ActorInstance_RVC_decoder__parser__mvrecon) {
  int32_t mv;
  int32_t t;
  ART_ACTION_ENTER(action17__write__chroma, 17);
  mv = ((thisActor->fourmv) ? (RVC_decoder__parser__mvreconuvclip_4(thisActor, thisActor->sum_x)):(RVC_decoder__parser__mvreconuvclip_1(thisActor, thisActor->sum_x)));
  t = thisActor->sum_x;
  thisActor->sum_x = thisActor->sum_y;
  thisActor->sum_y = t;
  pinWrite_int32_t(OUT0_MV, mv);
  ART_ACTION_EXIT(action17__write__chroma, 17);
}


// advance
ART_ACTION(action18__advance, ActorInstance_RVC_decoder__parser__mvrecon) {
  ART_ACTION_ENTER(action18__advance, 18);
  thisActor->comp = (thisActor->comp + 1);
  if ((thisActor->comp == 6)) {
    thisActor->comp = 0;
    thisActor->mbx = (thisActor->mbx + 1);
    if ((thisActor->mbx == thisActor->mbwidth)) {
      thisActor->top_edge = 0;
    }
    thisActor->ptr = (((thisActor->ptr == 8)) ? ((BUF_SIZE - 8)):((thisActor->ptr - 8)));
  }
  ART_ACTION_EXIT(action18__advance, 18);
}

#define ActorInstance_RVC_decoder__parser__mvrecon__read_ID 0
#define ActorInstance_RVC_decoder__parser__mvrecon__getw_ID 1
#define ActorInstance_RVC_decoder__parser__mvrecon__compute_ID 2
#define ActorInstance_RVC_decoder__parser__mvrecon__advance_ID 3
#define ActorInstance_RVC_decoder__parser__mvrecon__geth_ID 4
#define ActorInstance_RVC_decoder__parser__mvrecon__get_pred_p_ID 5
#define ActorInstance_RVC_decoder__parser__mvrecon__write_ID 6
#define ActorInstance_RVC_decoder__parser__mvrecon__get_pred_p1_ID 7
#define ActorInstance_RVC_decoder__parser__mvrecon__get_pred_x_ID 8
#define ActorInstance_RVC_decoder__parser__mvrecon__get_pred_x1_ID 9
#define ActorInstance_RVC_decoder__parser__mvrecon__get_pred_x2_ID 10
#define ActorInstance_RVC_decoder__parser__mvrecon__do_pred_x_ID 11
#define ActorInstance_RVC_decoder__parser__mvrecon__get_mag_x_ID 12
#define ActorInstance_RVC_decoder__parser__mvrecon__get_res_x_ID 13
#define ActorInstance_RVC_decoder__parser__mvrecon__get_res_x_a_ID 14
#define ActorInstance_RVC_decoder__parser__mvrecon__get_res_x_b_ID 15
#define ActorInstance_RVC_decoder__parser__mvrecon__get_res_x_c_ID 16
#define ActorInstance_RVC_decoder__parser__mvrecon__get_res_x_d_ID 17
#define ActorInstance_RVC_decoder__parser__mvrecon__get_res_x_e_ID 18
#define ActorInstance_RVC_decoder__parser__mvrecon__get_pred_y_ID 19
#define ActorInstance_RVC_decoder__parser__mvrecon__get_pred_y1_ID 20
#define ActorInstance_RVC_decoder__parser__mvrecon__get_pred_y2_ID 21
#define ActorInstance_RVC_decoder__parser__mvrecon__do_pred_y_ID 22
#define ActorInstance_RVC_decoder__parser__mvrecon__get_mag_y_ID 23
#define ActorInstance_RVC_decoder__parser__mvrecon__get_res_y_ID 24
#define ActorInstance_RVC_decoder__parser__mvrecon__get_res_y_a_ID 25
#define ActorInstance_RVC_decoder__parser__mvrecon__get_res_y_b_ID 26
#define ActorInstance_RVC_decoder__parser__mvrecon__get_res_y_c_ID 27
#define ActorInstance_RVC_decoder__parser__mvrecon__get_res_y_d_ID 28
#define ActorInstance_RVC_decoder__parser__mvrecon__get_res_y_e_ID 29
#define ActorInstance_RVC_decoder__parser__mvrecon__write_y_ID 30
static void ActorInstance_RVC_decoder__parser__mvrecon_constructor(AbstractActorInstance *pBase) {
  ActorInstance_RVC_decoder__parser__mvrecon *thisActor=(ActorInstance_RVC_decoder__parser__mvrecon*) pBase;
  thisActor->_fsmState = ActorInstance_RVC_decoder__parser__mvrecon__read_ID;//Initial state
  {
    thisActor->buf = malloc((sizeof(int32_t) * 968));
    thisActor->mbx = 0;
    thisActor->top_edge = 1;
    {
      int32_t i;
      for(i = 1; i <= 968; i++)
      {
        thisActor->buf[((0 + i) - 1)] = 0;
      }
    }
    thisActor->mbwidth = 0;
    thisActor->comp = 0;
  }

}
static const int exitcode_block_Any[3]={1,0,1};
ART_ACTION_SCHEDULER(RVC_decoder__parser__mvrecon_action_scheduler) {
  const int *result = EXIT_CODE_YIELD;
  ActorInstance_RVC_decoder__parser__mvrecon *thisActor=(ActorInstance_RVC_decoder__parser__mvrecon*) pBase;
  ART_ACTION_SCHEDULER_ENTER(3, 1)
  while(1) {
    switch(thisActor->_fsmState) {
      case ActorInstance_RVC_decoder__parser__mvrecon__read_ID:
        if ((pinAvailIn_int32_t(IN0_BTYPE) >= 1)) {
          if (RVC_decoder__parser__mvrecon__DOLLAR__d297(context, thisActor)) {
            ART_FIRE_ACTION(action0__start);
            thisActor->_fsmState = ActorInstance_RVC_decoder__parser__mvrecon__getw_ID;
            continue;
          }
        }
        if ((pinAvailIn_int32_t(IN0_BTYPE) >= 1)) {
          if (RVC_decoder__parser__mvrecon__DOLLAR__d352(context, thisActor) && RVC_decoder__parser__mvrecon__DOLLAR__d370(context, thisActor)) {
            ART_FIRE_ACTION(action3__read__noMotion);
            thisActor->_fsmState = ActorInstance_RVC_decoder__parser__mvrecon__advance_ID;
            continue;
          }
        }
        if ((pinAvailIn_int32_t(IN0_BTYPE) >= 1)) {
          if (RVC_decoder__parser__mvrecon__DOLLAR__d402(context, thisActor) && RVC_decoder__parser__mvrecon__DOLLAR__d411(context, thisActor) && RVC_decoder__parser__mvrecon__DOLLAR__d420(context, thisActor)) {
            ART_FIRE_ACTION(action4__read__motion);
            thisActor->_fsmState = ActorInstance_RVC_decoder__parser__mvrecon__compute_ID;
            continue;
          }
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__parser__mvrecon__getw_ID:
        if ((pinAvailIn_int32_t(IN0_BTYPE) >= 1)) {
          ART_FIRE_ACTION(action1__getw);
          thisActor->_fsmState = ActorInstance_RVC_decoder__parser__mvrecon__geth_ID;
          continue;
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__parser__mvrecon__compute_ID:
        if (RVC_decoder__parser__mvrecon__DOLLAR__d442(context, thisActor)) {
          ART_FIRE_ACTION(action5__compute__done);
          thisActor->_fsmState = ActorInstance_RVC_decoder__parser__mvrecon__write_ID;
          continue;
        }
        if ((pinAvailIn_int32_t(IN2_A) >= 1)) {
          ART_FIRE_ACTION(action6__compute__start);
          thisActor->_fsmState = ActorInstance_RVC_decoder__parser__mvrecon__get_pred_p_ID;
          continue;
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__parser__mvrecon__advance_ID:
        ART_FIRE_ACTION(action18__advance);
        thisActor->_fsmState = ActorInstance_RVC_decoder__parser__mvrecon__read_ID;
        continue;
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__parser__mvrecon__geth_ID:
        if ((pinAvailIn_int32_t(IN0_BTYPE) >= 1)) {
          ART_FIRE_ACTION(action2__geth);
          thisActor->_fsmState = ActorInstance_RVC_decoder__parser__mvrecon__read_ID;
          continue;
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__parser__mvrecon__get_pred_p_ID:
        if ((pinAvailIn_int32_t(IN2_A) >= 1)) {
          ART_FIRE_ACTION(action6__compute__start);
          thisActor->_fsmState = ActorInstance_RVC_decoder__parser__mvrecon__get_pred_p1_ID;
          continue;
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__parser__mvrecon__write_ID:
        if (RVC_decoder__parser__mvrecon__DOLLAR__d545(context, thisActor)) {
          if ((pinAvailOut_int32_t(OUT0_MV) >= 1)) {
            ART_FIRE_ACTION(action16__write__luma);
            thisActor->_fsmState = ActorInstance_RVC_decoder__parser__mvrecon__write_y_ID;
            continue;
          
          } else {
            result = exitcode_block_Any;
            goto out;
          }
        }
        if ((pinAvailOut_int32_t(OUT0_MV) >= 1)) {
          ART_FIRE_ACTION(action17__write__chroma);
          thisActor->_fsmState = ActorInstance_RVC_decoder__parser__mvrecon__write_y_ID;
          continue;
        
        } else {
          result = exitcode_block_Any;
          goto out;
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__parser__mvrecon__get_pred_p1_ID:
        if ((pinAvailIn_int32_t(IN2_A) >= 1)) {
          ART_FIRE_ACTION(action6__compute__start);
          thisActor->_fsmState = ActorInstance_RVC_decoder__parser__mvrecon__get_pred_x_ID;
          continue;
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__parser__mvrecon__get_pred_x_ID:
        ART_FIRE_ACTION(action7__get_pred);
        thisActor->_fsmState = ActorInstance_RVC_decoder__parser__mvrecon__get_pred_x1_ID;
        continue;
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__parser__mvrecon__get_pred_x1_ID:
        ART_FIRE_ACTION(action7__get_pred);
        thisActor->_fsmState = ActorInstance_RVC_decoder__parser__mvrecon__get_pred_x2_ID;
        continue;
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__parser__mvrecon__get_pred_x2_ID:
        ART_FIRE_ACTION(action7__get_pred);
        thisActor->_fsmState = ActorInstance_RVC_decoder__parser__mvrecon__do_pred_x_ID;
        continue;
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__parser__mvrecon__do_pred_x_ID:
        ART_FIRE_ACTION(action8__do_pred);
        thisActor->_fsmState = ActorInstance_RVC_decoder__parser__mvrecon__get_mag_x_ID;
        continue;
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__parser__mvrecon__get_mag_x_ID:
        if ((pinAvailIn_int32_t(IN1_MVIN) >= 1)) {
          ART_FIRE_ACTION(action9__get_mag);
          thisActor->_fsmState = ActorInstance_RVC_decoder__parser__mvrecon__get_res_x_ID;
          continue;
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__parser__mvrecon__get_res_x_ID:
        ART_FIRE_ACTION(action10__get_residual__init);
        thisActor->_fsmState = ActorInstance_RVC_decoder__parser__mvrecon__get_res_x_a_ID;
        continue;
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__parser__mvrecon__get_res_x_a_ID:
        ART_FIRE_ACTION(action11__get_residual__shift);
        thisActor->_fsmState = ActorInstance_RVC_decoder__parser__mvrecon__get_res_x_b_ID;
        continue;
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__parser__mvrecon__get_res_x_b_ID:
        if ((pinAvailIn_int32_t(IN1_MVIN) >= 1)) {
          ART_FIRE_ACTION(action12__get_residual__adjust);
          thisActor->_fsmState = ActorInstance_RVC_decoder__parser__mvrecon__get_res_x_c_ID;
          continue;
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__parser__mvrecon__get_res_x_c_ID:
        ART_FIRE_ACTION(action13__get_residual__calc);
        thisActor->_fsmState = ActorInstance_RVC_decoder__parser__mvrecon__get_res_x_d_ID;
        continue;
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__parser__mvrecon__get_res_x_d_ID:
        ART_FIRE_ACTION(action14__get_residual__clip);
        thisActor->_fsmState = ActorInstance_RVC_decoder__parser__mvrecon__get_res_x_e_ID;
        continue;
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__parser__mvrecon__get_res_x_e_ID:
        ART_FIRE_ACTION(action15__get_residual__final);
        thisActor->_fsmState = ActorInstance_RVC_decoder__parser__mvrecon__get_pred_y_ID;
        continue;
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__parser__mvrecon__get_pred_y_ID:
        ART_FIRE_ACTION(action7__get_pred);
        thisActor->_fsmState = ActorInstance_RVC_decoder__parser__mvrecon__get_pred_y1_ID;
        continue;
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__parser__mvrecon__get_pred_y1_ID:
        ART_FIRE_ACTION(action7__get_pred);
        thisActor->_fsmState = ActorInstance_RVC_decoder__parser__mvrecon__get_pred_y2_ID;
        continue;
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__parser__mvrecon__get_pred_y2_ID:
        ART_FIRE_ACTION(action7__get_pred);
        thisActor->_fsmState = ActorInstance_RVC_decoder__parser__mvrecon__do_pred_y_ID;
        continue;
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__parser__mvrecon__do_pred_y_ID:
        ART_FIRE_ACTION(action8__do_pred);
        thisActor->_fsmState = ActorInstance_RVC_decoder__parser__mvrecon__get_mag_y_ID;
        continue;
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__parser__mvrecon__get_mag_y_ID:
        if ((pinAvailIn_int32_t(IN1_MVIN) >= 1)) {
          ART_FIRE_ACTION(action9__get_mag);
          thisActor->_fsmState = ActorInstance_RVC_decoder__parser__mvrecon__get_res_y_ID;
          continue;
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__parser__mvrecon__get_res_y_ID:
        ART_FIRE_ACTION(action10__get_residual__init);
        thisActor->_fsmState = ActorInstance_RVC_decoder__parser__mvrecon__get_res_y_a_ID;
        continue;
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__parser__mvrecon__get_res_y_a_ID:
        ART_FIRE_ACTION(action11__get_residual__shift);
        thisActor->_fsmState = ActorInstance_RVC_decoder__parser__mvrecon__get_res_y_b_ID;
        continue;
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__parser__mvrecon__get_res_y_b_ID:
        if ((pinAvailIn_int32_t(IN1_MVIN) >= 1)) {
          ART_FIRE_ACTION(action12__get_residual__adjust);
          thisActor->_fsmState = ActorInstance_RVC_decoder__parser__mvrecon__get_res_y_c_ID;
          continue;
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__parser__mvrecon__get_res_y_c_ID:
        ART_FIRE_ACTION(action13__get_residual__calc);
        thisActor->_fsmState = ActorInstance_RVC_decoder__parser__mvrecon__get_res_y_d_ID;
        continue;
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__parser__mvrecon__get_res_y_d_ID:
        ART_FIRE_ACTION(action14__get_residual__clip);
        thisActor->_fsmState = ActorInstance_RVC_decoder__parser__mvrecon__get_res_y_e_ID;
        continue;
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__parser__mvrecon__get_res_y_e_ID:
        ART_FIRE_ACTION(action15__get_residual__final);
        thisActor->_fsmState = ActorInstance_RVC_decoder__parser__mvrecon__write_ID;
        continue;
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__parser__mvrecon__write_y_ID:
        if (RVC_decoder__parser__mvrecon__DOLLAR__d545(context, thisActor)) {
          if ((pinAvailOut_int32_t(OUT0_MV) >= 1)) {
            ART_FIRE_ACTION(action16__write__luma);
            thisActor->_fsmState = ActorInstance_RVC_decoder__parser__mvrecon__advance_ID;
            continue;
          
          } else {
            result = exitcode_block_Any;
            goto out;
          }
        }
        if ((pinAvailOut_int32_t(OUT0_MV) >= 1)) {
          ART_FIRE_ACTION(action17__write__chroma);
          thisActor->_fsmState = ActorInstance_RVC_decoder__parser__mvrecon__advance_ID;
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
  ART_ACTION_SCHEDULER_EXIT(3, 1)
  return result;
}