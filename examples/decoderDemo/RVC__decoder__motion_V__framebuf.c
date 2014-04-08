#include "actors-rts.h"
#include "natives.h"
#include "RVC__decoderDemo.h"
#define  IN0_MV ART_INPUT(0)
#define  IN1_BTYPE ART_INPUT(1)
#define  IN2_WD ART_INPUT(2)
#define  OUT0_halfpel ART_OUTPUT(0)
#define  OUT1_RD ART_OUTPUT(1)

//Actor constants
static const int32_t SEARCHWIN_IN_MB = 3;
static const int32_t MAXW_IN_MB = 121;
static const int32_t MAXH_IN_MB = 69;
static const int32_t ADDR_SZ = 24;
static const int32_t FLAG_SZ = 4;
static const int32_t MV_SZ = 9;
static const int32_t MB_COORD_SZ = 8;
static const int32_t BTYPE_SZ = 12;
static const int32_t INTRA = 1024;
static const int32_t NEWVOP = 2048;
static const int32_t MOTION = 8;
static const int32_t ROUND_TYPE = 32;
static const int32_t LAYOUT = 0;
static const int32_t PIX_SZ = 9;
static const int32_t HALF_SEARCH = 2;
static const int32_t MAXH_IN_SAMPLES = 1104;
static const int32_t UNUSED32 = 2147483647;
static const int32_t SAMPLES_PER_MB = 8;
static const int32_t COMP_PER_MB = 1;
static const int32_t MAXW_IN_SAMPLES = 1936;
static const int32_t comp_offset[5] = {0, 8, 15488, 15496, 2147483647};
static const int32_t EXTRA_SPACE = 61952;
static const int32_t MAX_FRAME_SIZE = 2137344;
static const int32_t BUFFER_SIZE = 2199296;

//Actor state
typedef struct {
  AbstractActorInstance base;
  int _fsmState;
  int32_t vop_width_in_samples;
  int32_t vop_rounding_mode;
  int32_t comp_read;
  int32_t next_vop_width_write;
  int32_t next_vop_height_write;
  int32_t vop_height_in_samples;
  int32_t mbx_write;
  int32_t comp_write;
  int32_t start_of_prev_frame;
  int32_t max_outstanding_writes;
  int32_t mbx_read;
  int32_t mby_write;
  int32_t mvy;
  int32_t start_of_frame;
  int32_t vop_width_read;
  int32_t mvx;
  int32_t mb_write_ptr;
  int32_t mby_read;
  int32_t outstanding_writes;
  int32_t vop_height_read;
  int32_t vop_height_write;
  int32_t* frameBuffer;
  int32_t vop_width_write;
} ActorInstance_RVC_decoder__motion_V__framebuf;

//Actor functions
void RVC_decoder__motion_V__framebufadvance_block(ActorInstance_RVC_decoder__motion_V__framebuf* thisActor) {
  thisActor->outstanding_writes = (thisActor->outstanding_writes + 1);
  thisActor->comp_read = (thisActor->comp_read + 1);
  if ((thisActor->comp_read == 1)) {
    thisActor->comp_read = 0;
    thisActor->mbx_read = (thisActor->mbx_read + 1);
    if ((thisActor->mbx_read == thisActor->vop_width_read)) {
      thisActor->mbx_read = 0;
      thisActor->mby_read = (thisActor->mby_read + 1);
    }
  }
}
ART_ACTION_CONTEXT(3, 2)

ART_ACTION(action0__cmd__newVop, ActorInstance_RVC_decoder__motion_V__framebuf);
ART_ACTION(action1__read_w_h, ActorInstance_RVC_decoder__motion_V__framebuf);
ART_ACTION(action2__cmd__noMotion, ActorInstance_RVC_decoder__motion_V__framebuf);
ART_ACTION(action3__cmd__motion, ActorInstance_RVC_decoder__motion_V__framebuf);
ART_ACTION(action4__read_mv, ActorInstance_RVC_decoder__motion_V__framebuf);
ART_ACTION(action5__cmd__neither, ActorInstance_RVC_decoder__motion_V__framebuf);
ART_ACTION(action6__read_fb, ActorInstance_RVC_decoder__motion_V__framebuf);
ART_ACTION(action7, ActorInstance_RVC_decoder__motion_V__framebuf);
ART_ACTION_SCHEDULER(RVC_decoder__motion_V__framebuf_action_scheduler);
static void ActorInstance_RVC_decoder__motion_V__framebuf_constructor(AbstractActorInstance *);

static const PortDescription inputPortDescriptions[]={
  {0, "MV", sizeof(int32_t), NULL},
  {0, "BTYPE", sizeof(int32_t), NULL},
  {0, "WD", sizeof(int32_t), NULL},
};
static const PortDescription outputPortDescriptions[]={
  {0, "halfpel", sizeof(int32_t), NULL},
  {0, "RD", sizeof(int32_t), NULL},
};

static const int portRate_in_action0__cmd__newVop[] = {0, 1, 0};

static const int portRate_out_action0__cmd__newVop[] = {0, 0};

static const int portRate_in_action1__read_w_h[] = {0, 2, 0};

static const int portRate_out_action1__read_w_h[] = {0, 0};

static const int portRate_in_action2__cmd__noMotion[] = {0, 1, 0};

static const int portRate_out_action2__cmd__noMotion[] = {0, 0};

static const int portRate_in_action3__cmd__motion[] = {0, 1, 0};

static const int portRate_out_action3__cmd__motion[] = {0, 0};

static const int portRate_in_action4__read_mv[] = {2, 0, 0};

static const int portRate_out_action4__read_mv[] = {1, 0};

static const int portRate_in_action5__cmd__neither[] = {0, 1, 0};

static const int portRate_out_action5__cmd__neither[] = {1, 0};

static const int portRate_in_action6__read_fb[] = {0, 0, 0};

static const int portRate_out_action6__read_fb[] = {0, (81 * 1)};

static const int portRate_in_action7[] = {0, 0, (64 * 1)};

static const int portRate_out_action7[] = {0, 0};

static const ActionDescription actionDescriptions[] = {
  {"action0__cmd__newVop", portRate_in_action0__cmd__newVop, portRate_out_action0__cmd__newVop},
  {"action1__read_w_h", portRate_in_action1__read_w_h, portRate_out_action1__read_w_h},
  {"action2__cmd__noMotion", portRate_in_action2__cmd__noMotion, portRate_out_action2__cmd__noMotion},
  {"action3__cmd__motion", portRate_in_action3__cmd__motion, portRate_out_action3__cmd__motion},
  {"action4__read_mv", portRate_in_action4__read_mv, portRate_out_action4__read_mv},
  {"action5__cmd__neither", portRate_in_action5__cmd__neither, portRate_out_action5__cmd__neither},
  {"action6__read_fb", portRate_in_action6__read_fb, portRate_out_action6__read_fb},
  {"action7", portRate_in_action7, portRate_out_action7},
};

ActorClass klass=INIT_ActorClass(
  "RVC_decoder__motion_V__framebuf",
  ActorInstance_RVC_decoder__motion_V__framebuf,
  ActorInstance_RVC_decoder__motion_V__framebuf_constructor,
  0, //setParam not needed anymore (we instantiate with params)
  0, 0, // serialize/deserialize
  RVC_decoder__motion_V__framebuf_action_scheduler,
  0, // no destructor
  3, inputPortDescriptions,
  2, outputPortDescriptions,
  8, actionDescriptions
);

bool_t RVC_decoder__motion_V__framebuf__DOLLAR__d7382(art_action_context_t *context, ActorInstance_RVC_decoder__motion_V__framebuf *thisActor) {
  int32_t cmd;
  {
    bool_t ret;
    cmd = pinPeek_int32_t(IN1_BTYPE, 0);
    ret = (bitand(cmd, NEWVOP) != 0);
    return ret;
  }
}

// cmd.newVop
ART_ACTION(action0__cmd__newVop, ActorInstance_RVC_decoder__motion_V__framebuf) {
  int32_t cmd;
  int32_t round;
  ART_ACTION_ENTER(action0__cmd__newVop, 0);
  cmd = pinRead_int32_t(IN1_BTYPE);
  round = (((bitand(cmd, ROUND_TYPE) != 0)) ? (1):(0));
  thisActor->vop_rounding_mode = round;
  ART_ACTION_EXIT(action0__cmd__newVop, 0);
}

bool_t RVC_decoder__motion_V__framebuf__DOLLAR__d7406(art_action_context_t *context, ActorInstance_RVC_decoder__motion_V__framebuf *thisActor) {
  {
    bool_t ret;
    ret = ((thisActor->outstanding_writes < ((thisActor->vop_height_read * thisActor->vop_width_read) * 1)) || (thisActor->vop_height_read == 0));
    return ret;
  }
}

// read_w_h
ART_ACTION(action1__read_w_h, ActorInstance_RVC_decoder__motion_V__framebuf) {
  int32_t w;
  int32_t h;
  int32_t last_frame_size;
  ART_ACTION_ENTER(action1__read_w_h, 1);
  w = pinRead_int32_t(IN1_BTYPE);
  h = pinRead_int32_t(IN1_BTYPE);
  last_frame_size = ((thisActor->vop_height_read * 8) * 1936);
  thisActor->vop_width_read = w;
  thisActor->vop_height_read = h;
  thisActor->next_vop_width_write = w;
  thisActor->next_vop_height_write = h;
  thisActor->vop_width_in_samples = (w * 8);
  thisActor->vop_height_in_samples = (h * 8);
  thisActor->max_outstanding_writes = (((thisActor->vop_height_read - 2) * thisActor->vop_width_read) * 1);
  thisActor->mbx_read = 0;
  thisActor->mby_read = 0;
  thisActor->comp_read = 0;
  thisActor->start_of_prev_frame = thisActor->start_of_frame;
  thisActor->start_of_frame = (thisActor->start_of_frame + last_frame_size);
  if ((thisActor->start_of_frame >= 2199296)) {
    thisActor->start_of_frame = (thisActor->start_of_frame - 2199296);
  }
  ART_ACTION_EXIT(action1__read_w_h, 1);
}

bool_t RVC_decoder__motion_V__framebuf__DOLLAR__d7459(art_action_context_t *context, ActorInstance_RVC_decoder__motion_V__framebuf *thisActor) {
  int32_t cmd;
  {
    bool_t ret;
    cmd = pinPeek_int32_t(IN1_BTYPE, 0);
    ret = (bitand(cmd, INTRA) != 0);
    return ret;
  }
}

// cmd.noMotion
ART_ACTION(action2__cmd__noMotion, ActorInstance_RVC_decoder__motion_V__framebuf) {
  int32_t cmd;
  ART_ACTION_ENTER(action2__cmd__noMotion, 2);
  cmd = pinRead_int32_t(IN1_BTYPE);
  RVC_decoder__motion_V__framebufadvance_block(thisActor);
  ART_ACTION_EXIT(action2__cmd__noMotion, 2);
}

bool_t RVC_decoder__motion_V__framebuf__DOLLAR__d7471(art_action_context_t *context, ActorInstance_RVC_decoder__motion_V__framebuf *thisActor) {
  int32_t cmd;
  {
    bool_t ret;
    cmd = pinPeek_int32_t(IN1_BTYPE, 0);
    ret = (bitand(cmd, MOTION) != 0);
    return ret;
  }
}

// cmd.motion
ART_ACTION(action3__cmd__motion, ActorInstance_RVC_decoder__motion_V__framebuf) {
  int32_t cmd;
  ART_ACTION_ENTER(action3__cmd__motion, 3);
  cmd = pinRead_int32_t(IN1_BTYPE);
  ART_ACTION_EXIT(action3__cmd__motion, 3);
}


// read_mv
ART_ACTION(action4__read_mv, ActorInstance_RVC_decoder__motion_V__framebuf) {
  int32_t x;
  int32_t y;
  int32_t flag_x;
  int32_t flags;
  int32_t flag_y;
  ART_ACTION_ENTER(action4__read_mv, 4);
  x = pinRead_int32_t(IN0_MV);
  y = pinRead_int32_t(IN0_MV);
  flag_x = (((bitand(x, 1) == 1)) ? (4):(0));
  flags = ((lshift(bitand(x, 1), 2) + lshift(bitand(y, 1), 1)) + thisActor->vop_rounding_mode);
  flag_y = (((bitand(y, 1) == 1)) ? (2):(0));
  thisActor->mvx = rshift(x, 1);
  thisActor->mvy = rshift(y, 1);
  pinWrite_int32_t(OUT0_halfpel, flags);
  ART_ACTION_EXIT(action4__read_mv, 4);
}


// cmd.neither
ART_ACTION(action5__cmd__neither, ActorInstance_RVC_decoder__motion_V__framebuf) {
  int32_t cmd;
  int32_t U__43;
  ART_ACTION_ENTER(action5__cmd__neither, 5);
  cmd = pinRead_int32_t(IN1_BTYPE);
  thisActor->mvx = 0;
  thisActor->mvy = 0;
  U__43 = 0;
  pinWrite_int32_t(OUT0_halfpel, U__43);
  ART_ACTION_EXIT(action5__cmd__neither, 5);
}

bool_t RVC_decoder__motion_V__framebuf__DOLLAR__d7544(art_action_context_t *context, ActorInstance_RVC_decoder__motion_V__framebuf *thisActor) {
  {
    bool_t ret;
    ret = (thisActor->outstanding_writes < thisActor->max_outstanding_writes);
    return ret;
  }
}

// read_fb
ART_ACTION(action6__read_fb, ActorInstance_RVC_decoder__motion_V__framebuf) {
  int32_t clip_right;
  int32_t end_i;
  int32_t i;
  int32_t clip_left;
  int32_t temp;
  int32_t y;
  int32_t clip_y;
  int32_t x;
  int32_t clip_x;
  int32_t addr;
  int32_t start_of_row;
  int32_t* rd;
  ART_ACTION_ENTER(action6__read_fb, 6);
  rd = malloc((sizeof(int32_t) * 81));
  clip_right = 0;
  clip_left = 0;
  y = (((thisActor->mby_read * 8) + (8 * rshift(thisActor->comp_read, 1))) + thisActor->mvy);
  clip_y = (((y < 0)) ? (0):((((y < thisActor->vop_height_in_samples)) ? (y):((thisActor->vop_height_in_samples - 1)))));
  x = (((thisActor->mbx_read * 8) + (8 * bitand(thisActor->comp_read, 1))) + thisActor->mvx);
  clip_x = x;
  {
    int32_t k;
    for(k = 1; k <= 81; k++)
    {
      rd[((0 + k) - 1)] = 0;
    }
  }
  if ((x < 0)) {
    clip_x = 0;
    clip_left = (((x < (-(9)))) ? (9):((-(x))));
  
  } else {
    if (((x + 9) > thisActor->vop_width_in_samples)) {
      if ((x >= thisActor->vop_width_in_samples)) {
        clip_x = (thisActor->vop_width_in_samples - 1);
        clip_right = 8;
      
      } else {
        clip_right = ((x + 9) - thisActor->vop_width_in_samples);
      }
    }
  }
  start_of_row = ((thisActor->start_of_prev_frame + (clip_y * 1936)) + clip_x);
  if ((start_of_row >= 2199296)) {
    start_of_row = (start_of_row - 2199296);
  }
  i = 0;
  while ((i < 81)) {
    if ((clip_left != 0)) {
      end_i = (i + clip_left);
      temp = thisActor->frameBuffer[start_of_row];
      while ((i < end_i)) {
        rd[i] = temp;
        i = (i + 1);
      }
    }
    addr = start_of_row;
    end_i = (((i + 9) - clip_left) - clip_right);
    while ((i < end_i)) {
      rd[i] = thisActor->frameBuffer[addr];
      i = (i + 1);
      addr = (addr + 1);
    }
    if ((clip_right != 0)) {
      end_i = (i + clip_right);
      temp = thisActor->frameBuffer[(addr - 1)];
      while ((i < end_i)) {
        rd[i] = temp;
        i = (i + 1);
      }
    }
    y = (y + 1);
    if (((y > 0) && (y < thisActor->vop_height_in_samples))) {
      start_of_row = (start_of_row + 1936);
      if ((start_of_row >= 2199296)) {
        start_of_row = (start_of_row - 2199296);
      }
    }
  }
  RVC_decoder__motion_V__framebufadvance_block(thisActor);
  pinWriteRepeat_int32_t(OUT1_RD, rd, 81);
  free((void*) rd);
  ART_ACTION_EXIT(action6__read_fb, 6);
}

bool_t RVC_decoder__motion_V__framebuf__DOLLAR__d7758(art_action_context_t *context, ActorInstance_RVC_decoder__motion_V__framebuf *thisActor) {
  {
    bool_t ret;
    ret = (thisActor->outstanding_writes >= 1);
    return ret;
  }
}

// 
ART_ACTION(action7, ActorInstance_RVC_decoder__motion_V__framebuf) {
  int32_t* wd;
  int32_t i;
  int32_t nextRow;
  int32_t addr;
  ART_ACTION_ENTER(action7, 7);
  wd = malloc((sizeof(int32_t) * 64));
  pinReadRepeat_int32_t(IN2_WD, wd, 64);
  addr = (thisActor->mb_write_ptr + comp_offset[thisActor->comp_write]);
  if ((thisActor->mby_write == thisActor->vop_height_write)) {
    thisActor->mby_write = 0;
    thisActor->vop_width_write = thisActor->next_vop_width_write;
    thisActor->vop_height_write = thisActor->next_vop_height_write;
  }
  i = 0;
  while ((i < 64)) {
    nextRow = (i + 8);
    while ((i < nextRow)) {
      thisActor->frameBuffer[addr] = wd[i];
      addr = (addr + 1);
      i = (i + 1);
    }
    addr = (addr + 1928);
  }
  thisActor->outstanding_writes = (thisActor->outstanding_writes - 1);
  thisActor->comp_write = (thisActor->comp_write + 1);
  if ((thisActor->comp_write == 1)) {
    thisActor->mbx_write = (thisActor->mbx_write + 1);
    thisActor->mb_write_ptr = (thisActor->mb_write_ptr + 8);
    thisActor->comp_write = 0;
    if ((thisActor->mbx_write == thisActor->vop_width_write)) {
      thisActor->mbx_write = 0;
      thisActor->mby_write = (thisActor->mby_write + 1);
      thisActor->mb_write_ptr = ((thisActor->mb_write_ptr - (8 * thisActor->vop_width_write)) + 15488);
      if ((thisActor->mb_write_ptr == 2199296)) {
        thisActor->mb_write_ptr = 0;
      }
    }
  }
  free((void*) wd);
  ART_ACTION_EXIT(action7, 7);
}

#define ActorInstance_RVC_decoder__motion_V__framebuf__cmd_ID 0
#define ActorInstance_RVC_decoder__motion_V__framebuf__read_w_h_ID 1
#define ActorInstance_RVC_decoder__motion_V__framebuf__read_mv_ID 2
#define ActorInstance_RVC_decoder__motion_V__framebuf__read_fb_ID 3
static void ActorInstance_RVC_decoder__motion_V__framebuf_constructor(AbstractActorInstance *pBase) {
  ActorInstance_RVC_decoder__motion_V__framebuf *thisActor=(ActorInstance_RVC_decoder__motion_V__framebuf*) pBase;
  thisActor->_fsmState = ActorInstance_RVC_decoder__motion_V__framebuf__cmd_ID;//Initial state
  {
    thisActor->frameBuffer = malloc((sizeof(int32_t) * 2199296));
    thisActor->vop_width_in_samples = 0;
    thisActor->vop_rounding_mode = 0;
    thisActor->comp_read = 0;
    thisActor->next_vop_width_write = 0;
    thisActor->next_vop_height_write = 0;
    thisActor->vop_height_in_samples = 0;
    thisActor->mbx_write = 0;
    thisActor->comp_write = 0;
    thisActor->start_of_prev_frame = 0;
    thisActor->max_outstanding_writes = 0;
    thisActor->mbx_read = 0;
    thisActor->mby_write = 0;
    thisActor->start_of_frame = 0;
    thisActor->vop_width_read = 0;
    thisActor->mb_write_ptr = 0;
    thisActor->mby_read = 0;
    thisActor->outstanding_writes = 0;
    thisActor->vop_height_read = 0;
    thisActor->vop_height_write = 0;
    thisActor->vop_width_write = 0;
  }

}
static const int exitcode_block_Any[3]={1,0,1};
ART_ACTION_SCHEDULER(RVC_decoder__motion_V__framebuf_action_scheduler) {
  const int *result = EXIT_CODE_YIELD;
  ActorInstance_RVC_decoder__motion_V__framebuf *thisActor=(ActorInstance_RVC_decoder__motion_V__framebuf*) pBase;
  ART_ACTION_SCHEDULER_ENTER(3, 2)
  while(1) {
    if ((pinAvailIn_int32_t(IN2_WD) >= 64)) {
      if (RVC_decoder__motion_V__framebuf__DOLLAR__d7758(context, thisActor)) {
        ART_FIRE_ACTION(action7);
        continue;
      }
    }
    switch(thisActor->_fsmState) {
      case ActorInstance_RVC_decoder__motion_V__framebuf__cmd_ID:
        if ((pinAvailIn_int32_t(IN1_BTYPE) >= 1)) {
          if (RVC_decoder__motion_V__framebuf__DOLLAR__d7382(context, thisActor)) {
            ART_FIRE_ACTION(action0__cmd__newVop);
            thisActor->_fsmState = ActorInstance_RVC_decoder__motion_V__framebuf__read_w_h_ID;
            continue;
          }
        }
        if ((pinAvailIn_int32_t(IN1_BTYPE) >= 1)) {
          if (RVC_decoder__motion_V__framebuf__DOLLAR__d7459(context, thisActor)) {
            ART_FIRE_ACTION(action2__cmd__noMotion);
            thisActor->_fsmState = ActorInstance_RVC_decoder__motion_V__framebuf__cmd_ID;
            continue;
          }
        }
        if ((pinAvailIn_int32_t(IN1_BTYPE) >= 1)) {
          if (RVC_decoder__motion_V__framebuf__DOLLAR__d7471(context, thisActor)) {
            ART_FIRE_ACTION(action3__cmd__motion);
            thisActor->_fsmState = ActorInstance_RVC_decoder__motion_V__framebuf__read_mv_ID;
            continue;
          }
        }
        if ((pinAvailIn_int32_t(IN1_BTYPE) >= 1)) {
          if ((pinAvailOut_int32_t(OUT0_halfpel) >= 1)) {
            ART_FIRE_ACTION(action5__cmd__neither);
            thisActor->_fsmState = ActorInstance_RVC_decoder__motion_V__framebuf__read_fb_ID;
            continue;
          
          } else {
            result = exitcode_block_Any;
            goto out;
          }
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__motion_V__framebuf__read_w_h_ID:
        if ((pinAvailIn_int32_t(IN1_BTYPE) >= 1*2)) {
          if (RVC_decoder__motion_V__framebuf__DOLLAR__d7406(context, thisActor)) {
            ART_FIRE_ACTION(action1__read_w_h);
            thisActor->_fsmState = ActorInstance_RVC_decoder__motion_V__framebuf__cmd_ID;
            continue;
          }
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__motion_V__framebuf__read_mv_ID:
        if ((pinAvailIn_int32_t(IN0_MV) >= 1*2)) {
          if ((pinAvailOut_int32_t(OUT0_halfpel) >= 1)) {
            ART_FIRE_ACTION(action4__read_mv);
            thisActor->_fsmState = ActorInstance_RVC_decoder__motion_V__framebuf__read_fb_ID;
            continue;
          
          } else {
            result = exitcode_block_Any;
            goto out;
          }
        }
        result = exitcode_block_Any;
        goto out;
        break;
      
      case ActorInstance_RVC_decoder__motion_V__framebuf__read_fb_ID:
        if (RVC_decoder__motion_V__framebuf__DOLLAR__d7544(context, thisActor)) {
          if ((pinAvailOut_int32_t(OUT1_RD) >= 81)) {
            ART_FIRE_ACTION(action6__read_fb);
            thisActor->_fsmState = ActorInstance_RVC_decoder__motion_V__framebuf__cmd_ID;
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
  ART_ACTION_SCHEDULER_EXIT(3, 2)
  return result;
}