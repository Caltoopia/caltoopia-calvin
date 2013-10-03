#include "actors-rts.h"
#include "natives.h"
#include "RVC__decoderDemo.h"
#define  IN0_MOT ART_INPUT(0)
#define  IN1_TEX ART_INPUT(1)
#define  IN2_BTYPE ART_INPUT(2)
#define  OUT0_VID ART_OUTPUT(0)

//Actor constants
static const int32_t PIX_SZ = 9;
static const int32_t MB_COORD_SZ = 8;
static const int32_t BTYPE_SZ = 12;
static const int32_t NEWVOP = 2048;
static const int32_t INTRA = 1024;
static const int32_t ACCODED = 2;

//Actor state
typedef struct {
  AbstractActorInstance base;
  int _fsmState;
} ActorInstance_RVC_decoder__motion_U__add;

//Actor functions
ART_ACTION_CONTEXT(3, 1)

ART_ACTION(action0__cmd__newVop, ActorInstance_RVC_decoder__motion_U__add);
ART_ACTION(action1__cmd__textureOnly, ActorInstance_RVC_decoder__motion_U__add);
ART_ACTION(action2__cmd__motionOnly, ActorInstance_RVC_decoder__motion_U__add);
ART_ACTION(action3__cmd__other, ActorInstance_RVC_decoder__motion_U__add);
ART_ACTION(action4__texture, ActorInstance_RVC_decoder__motion_U__add);
ART_ACTION(action5__motion, ActorInstance_RVC_decoder__motion_U__add);
ART_ACTION(action6__combine, ActorInstance_RVC_decoder__motion_U__add);
ART_ACTION_SCHEDULER(RVC_decoder__motion_U__add_action_scheduler);
static void ActorInstance_RVC_decoder__motion_U__add_constructor(AbstractActorInstance *);

static const PortDescription inputPortDescriptions[]={
  {0, "MOT", sizeof(int32_t)},
  {0, "TEX", sizeof(int32_t)},
  {0, "BTYPE", sizeof(int32_t)},
};
static const PortDescription outputPortDescriptions[]={
  {0, "VID", sizeof(int32_t)},
};

static const int portRate_in_action0__cmd__newVop[] = {0, 0, 1};

static const int portRate_out_action0__cmd__newVop[] = {0};

static const int portRate_in_action1__cmd__textureOnly[] = {0, 0, 1};

static const int portRate_out_action1__cmd__textureOnly[] = {0};

static const int portRate_in_action2__cmd__motionOnly[] = {0, 0, 1};

static const int portRate_out_action2__cmd__motionOnly[] = {0};

static const int portRate_in_action3__cmd__other[] = {0, 0, 1};

static const int portRate_out_action3__cmd__other[] = {0};

static const int portRate_in_action4__texture[] = {0, (64 * 1), 0};

static const int portRate_out_action4__texture[] = {(64 * 1)};

static const int portRate_in_action5__motion[] = {(64 * 1), 0, 0};

static const int portRate_out_action5__motion[] = {(64 * 1)};

static const int portRate_in_action6__combine[] = {(64 * 1), (64 * 1), 0};

static const int portRate_out_action6__combine[] = {(64 * 1)};

static const ActionDescription actionDescriptions[] = {
  {"action0__cmd__newVop", portRate_in_action0__cmd__newVop, portRate_out_action0__cmd__newVop},
  {"action1__cmd__textureOnly", portRate_in_action1__cmd__textureOnly, portRate_out_action1__cmd__textureOnly},
  {"action2__cmd__motionOnly", portRate_in_action2__cmd__motionOnly, portRate_out_action2__cmd__motionOnly},
  {"action3__cmd__other", portRate_in_action3__cmd__other, portRate_out_action3__cmd__other},
  {"action4__texture", portRate_in_action4__texture, portRate_out_action4__texture},
  {"action5__motion", portRate_in_action5__motion, portRate_out_action5__motion},
  {"action6__combine", portRate_in_action6__combine, portRate_out_action6__combine},
};

ActorClass klass=INIT_ActorClass(
  "RVC_decoder__motion_U__add",
  ActorInstance_RVC_decoder__motion_U__add,
  ActorInstance_RVC_decoder__motion_U__add_constructor,
  0, //setParam not needed anymore (we instantiate with params)
  RVC_decoder__motion_U__add_action_scheduler,
  0, // no destructor
  3, inputPortDescriptions,
  1, outputPortDescriptions,
  7, actionDescriptions
);

bool_t RVC_decoder__motion_U__add__DOLLAR__d1551(art_action_context_t *context, ActorInstance_RVC_decoder__motion_U__add *thisActor) {
  int32_t cmd;
  {
    bool_t ret;
    cmd = pinPeek_int32_t(IN2_BTYPE, 0);
    ret = (bitand(cmd, NEWVOP) != 0);
    return ret;
  }
}

// cmd.newVop
ART_ACTION(action0__cmd__newVop, ActorInstance_RVC_decoder__motion_U__add) {
  int32_t cmd;
  ART_ACTION_ENTER(action0__cmd__newVop, 0);
  cmd = pinRead_int32_t(IN2_BTYPE);
  ART_ACTION_EXIT(action0__cmd__newVop, 0);
}

bool_t RVC_decoder__motion_U__add__DOLLAR__d1563(art_action_context_t *context, ActorInstance_RVC_decoder__motion_U__add *thisActor) {
  int32_t cmd;
  {
    bool_t ret;
    cmd = pinPeek_int32_t(IN2_BTYPE, 0);
    ret = (bitand(cmd, INTRA) != 0);
    return ret;
  }
}

// cmd.textureOnly
ART_ACTION(action1__cmd__textureOnly, ActorInstance_RVC_decoder__motion_U__add) {
  int32_t cmd;
  ART_ACTION_ENTER(action1__cmd__textureOnly, 1);
  cmd = pinRead_int32_t(IN2_BTYPE);
  ART_ACTION_EXIT(action1__cmd__textureOnly, 1);
}

bool_t RVC_decoder__motion_U__add__DOLLAR__d1575(art_action_context_t *context, ActorInstance_RVC_decoder__motion_U__add *thisActor) {
  int32_t cmd;
  {
    bool_t ret;
    cmd = pinPeek_int32_t(IN2_BTYPE, 0);
    ret = (bitand(cmd, ACCODED) == 0);
    return ret;
  }
}

// cmd.motionOnly
ART_ACTION(action2__cmd__motionOnly, ActorInstance_RVC_decoder__motion_U__add) {
  int32_t cmd;
  ART_ACTION_ENTER(action2__cmd__motionOnly, 2);
  cmd = pinRead_int32_t(IN2_BTYPE);
  ART_ACTION_EXIT(action2__cmd__motionOnly, 2);
}


// cmd.other
ART_ACTION(action3__cmd__other, ActorInstance_RVC_decoder__motion_U__add) {
  int32_t cmd;
  ART_ACTION_ENTER(action3__cmd__other, 3);
  cmd = pinRead_int32_t(IN2_BTYPE);
  ART_ACTION_EXIT(action3__cmd__other, 3);
}


// texture
ART_ACTION(action4__texture, ActorInstance_RVC_decoder__motion_U__add) {
  int32_t* tex;
  ART_ACTION_ENTER(action4__texture, 4);
  tex = malloc((sizeof(int32_t) * 64));
  pinReadRepeat_int32_t(IN1_TEX, tex, 64);
  pinWriteRepeat_int32_t(OUT0_VID, tex, 64);
  free((void*) tex);
  ART_ACTION_EXIT(action4__texture, 4);
}


// motion
ART_ACTION(action5__motion, ActorInstance_RVC_decoder__motion_U__add) {
  int32_t* mot;
  ART_ACTION_ENTER(action5__motion, 5);
  mot = malloc((sizeof(int32_t) * 64));
  pinReadRepeat_int32_t(IN0_MOT, mot, 64);
  pinWriteRepeat_int32_t(OUT0_VID, mot, 64);
  free((void*) mot);
  ART_ACTION_EXIT(action5__motion, 5);
}


// combine
ART_ACTION(action6__combine, ActorInstance_RVC_decoder__motion_U__add) {
  int32_t* mot;
  int32_t* tex;
  int32_t* U__6;
  ART_ACTION_ENTER(action6__combine, 6);
  U__6 = malloc((sizeof(int32_t) * 64));
  tex = malloc((sizeof(int32_t) * 64));
  mot = malloc((sizeof(int32_t) * 64));
  pinReadRepeat_int32_t(IN1_TEX, tex, 64);
  pinReadRepeat_int32_t(IN0_MOT, mot, 64);
  {
    int32_t i;
    for(i = 0; i <= 63; i++)
    {
      U__6[((0 + i) - 0)] = ((((tex[i] + mot[i]) < 0)) ? (0):(((((tex[i] + mot[i]) > 255)) ? (255):((tex[i] + mot[i])))));
    }
  }
  pinWriteRepeat_int32_t(OUT0_VID, U__6, 64);
  free((void*) mot);
  free((void*) tex);
  free((void*) U__6);
  ART_ACTION_EXIT(action6__combine, 6);
}

#define ActorInstance_RVC_decoder__motion_U__add__cmd_ID 0
#define ActorInstance_RVC_decoder__motion_U__add__skipw_ID 1
#define ActorInstance_RVC_decoder__motion_U__add__texture_ID 2
#define ActorInstance_RVC_decoder__motion_U__add__motion_ID 3
#define ActorInstance_RVC_decoder__motion_U__add__combine_ID 4
#define ActorInstance_RVC_decoder__motion_U__add__skiph_ID 5
static void ActorInstance_RVC_decoder__motion_U__add_constructor(AbstractActorInstance *pBase) {
  ActorInstance_RVC_decoder__motion_U__add *thisActor=(ActorInstance_RVC_decoder__motion_U__add*) pBase;
  thisActor->_fsmState = ActorInstance_RVC_decoder__motion_U__add__cmd_ID;//Initial state
  {
  }

}
static const int exitcode_block_Any[3]={1,0,1};
ART_ACTION_SCHEDULER(RVC_decoder__motion_U__add_action_scheduler) {
  const int *result = EXIT_CODE_YIELD;
  ActorInstance_RVC_decoder__motion_U__add *thisActor=(ActorInstance_RVC_decoder__motion_U__add*) pBase;
  ART_ACTION_SCHEDULER_ENTER(3, 1)
  while(1) {
    switch(thisActor->_fsmState) {
      case ActorInstance_RVC_decoder__motion_U__add__cmd_ID:
        if ((pinAvailIn_int32_t(IN2_BTYPE) >= 1)) {
          if (RVC_decoder__motion_U__add__DOLLAR__d1551(context, thisActor)) {
            ART_FIRE_ACTION(action0__cmd__newVop);
            thisActor->_fsmState = ActorInstance_RVC_decoder__motion_U__add__skipw_ID;
            continue;
          }
        }
        if ((pinAvailIn_int32_t(IN2_BTYPE) >= 1)) {
          if (RVC_decoder__motion_U__add__DOLLAR__d1563(context, thisActor)) {
            ART_FIRE_ACTION(action1__cmd__textureOnly);
            thisActor->_fsmState = ActorInstance_RVC_decoder__motion_U__add__texture_ID;
            continue;
          }
        }
        if ((pinAvailIn_int32_t(IN2_BTYPE) >= 1)) {
          if (RVC_decoder__motion_U__add__DOLLAR__d1575(context, thisActor)) {
            ART_FIRE_ACTION(action2__cmd__motionOnly);
            thisActor->_fsmState = ActorInstance_RVC_decoder__motion_U__add__motion_ID;
            continue;
          }
        }
        if ((pinAvailIn_int32_t(IN2_BTYPE) >= 1)) {
          ART_FIRE_ACTION(action3__cmd__other);
          thisActor->_fsmState = ActorInstance_RVC_decoder__motion_U__add__combine_ID;
          continue;
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__motion_U__add__skipw_ID:
        if ((pinAvailIn_int32_t(IN2_BTYPE) >= 1)) {
          ART_FIRE_ACTION(action3__cmd__other);
          thisActor->_fsmState = ActorInstance_RVC_decoder__motion_U__add__skiph_ID;
          continue;
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__motion_U__add__texture_ID:
        if ((pinAvailIn_int32_t(IN1_TEX) >= 64)) {
          if ((pinAvailOut_int32_t(OUT0_VID) >= 64)) {
            ART_FIRE_ACTION(action4__texture);
            thisActor->_fsmState = ActorInstance_RVC_decoder__motion_U__add__cmd_ID;
            continue;
          
          } else {
            result = exitcode_block_Any;
            goto out;
          }
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__motion_U__add__motion_ID:
        if ((pinAvailIn_int32_t(IN0_MOT) >= 64)) {
          if ((pinAvailOut_int32_t(OUT0_VID) >= 64)) {
            ART_FIRE_ACTION(action5__motion);
            thisActor->_fsmState = ActorInstance_RVC_decoder__motion_U__add__cmd_ID;
            continue;
          
          } else {
            result = exitcode_block_Any;
            goto out;
          }
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__motion_U__add__combine_ID:
        if ((pinAvailIn_int32_t(IN0_MOT) >= 64) && (pinAvailIn_int32_t(IN1_TEX) >= 64)) {
          if ((pinAvailOut_int32_t(OUT0_VID) >= 64)) {
            ART_FIRE_ACTION(action6__combine);
            thisActor->_fsmState = ActorInstance_RVC_decoder__motion_U__add__cmd_ID;
            continue;
          
          } else {
            result = exitcode_block_Any;
            goto out;
          }
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__motion_U__add__skiph_ID:
        if ((pinAvailIn_int32_t(IN2_BTYPE) >= 1)) {
          ART_FIRE_ACTION(action3__cmd__other);
          thisActor->_fsmState = ActorInstance_RVC_decoder__motion_U__add__cmd_ID;
          continue;
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