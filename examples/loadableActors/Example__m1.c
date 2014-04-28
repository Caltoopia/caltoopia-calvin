/******************************************************************************
 *
 * Generated from CAL:
 *
 *  actor Multiplier (int FACTOR) int In ==> int Out :
 *    action In:[x] ==> Out:[x * FACTOR]
 *    end
 *  end
 *
 *****************************************************************************/

#include "actors-rts.h"
#include "natives.h"
#include "Example__toppen.h"
#define  IN0_In ART_INPUT(0)
#define  OUT0_Out ART_OUTPUT(0)

//Actor constants
static const int32_t FACTOR = 2;

typedef struct test_struct {
    int a;
    int b;
    struct test_struct *another;
} test_struct;

//Actor state
typedef struct {
    AbstractActorInstance base;
    int _fsmState;
    int array[4];
    test_struct s;
    test_struct sa[2];
} ActorInstance_Example_m1;

//Actor functions
ART_ACTION_CONTEXT(1, 1)

ART_ACTION(action0, ActorInstance_Example_m1);
ART_ACTION_SCHEDULER(Example_m1_action_scheduler);
static void ActorInstance_Example_m1_constructor(AbstractActorInstance *);

static const PortDescription inputPortDescriptions[]={
  {0, "In", sizeof(int32_t), NULL},
};
static const PortDescription outputPortDescriptions[]={
  {0, "Out", sizeof(int32_t), NULL},
};

static const int portRate_in_action0[] = {1};

static const int portRate_out_action0[] = {1};

static const ActionDescription actionDescriptions[] = {
  {"action0", portRate_in_action0, portRate_out_action0},
};

static void serialize(AbstractActorInstance *actor, ActorCoder *coder)
{
    ActorInstance_Example_m1 *this = (ActorInstance_Example_m1 *)actor;
    CoderState *state = coder->init(coder);
    
    // fsmState
    coder->encode(coder, state, "fsmState", &this->_fsmState, "i");
    
    // int array
    CoderState *array_state = coder->encode_array(coder, state, "my_array");
    for (int i=0; i<4; i++) {
        coder->encode(coder, array_state, NULL, &this->array[i], "i");
    }
    
    // Structs with structs 
    CoderState *struct_state = coder->encode_struct(coder, state, "s");
    coder->encode(coder, struct_state, "a", &this->s.a, "i");
    coder->encode(coder, struct_state, "b", &this->s.b, "i");
    if (this->s.another) {
        CoderState *another_state = coder->encode_struct(coder, struct_state, "s");
        coder->encode(coder, another_state, "a", &this->s.another->a, "i");
        coder->encode(coder, another_state, "b", &this->s.another->b, "i");
    }
    
    // Array of structs
    array_state = coder->encode_array(coder, state, "sa");
    struct_state = coder->encode_struct(coder, array_state, "s");
    coder->encode(coder, struct_state, "a", &this->sa[0].a, "i");
    coder->encode(coder, struct_state, "b", &this->sa[0].b, "i");
    struct_state = coder->encode_struct(coder, array_state, "s");
    coder->encode(coder, struct_state, "a", &this->sa[1].a, "i");
    coder->encode(coder, struct_state, "b", &this->sa[1].b, "i");
    
};


ActorClass klass = INIT_ActorClass(
  "Example_m1",
  ActorInstance_Example_m1,
  ActorInstance_Example_m1_constructor,
  0, //setParam not needed anymore (we instantiate with params)
  serialize,
  NULL,
  Example_m1_action_scheduler,
  0, // no destructor
  1, inputPortDescriptions,
  1, outputPortDescriptions,
  1, actionDescriptions
);


// 
ART_ACTION(action0, ActorInstance_Example_m1) {
  int32_t x;
  int32_t U__0;
  ART_ACTION_ENTER(action0, 0);
  x = pinRead_int32_t(IN0_In);
  U__0 = (x * 2);
  pinWrite_int32_t(OUT0_Out, U__0);
  ART_ACTION_EXIT(action0, 0);
}

#define ActorInstance_Example_m1__defaultState_ID 0
static void ActorInstance_Example_m1_constructor(AbstractActorInstance *pBase) {
  ActorInstance_Example_m1 *thisActor=(ActorInstance_Example_m1*) pBase;
  thisActor->_fsmState = ActorInstance_Example_m1__defaultState_ID;//Initial state
  {
  }
    thisActor->array[0] = 1;
    thisActor->array[1] = 11;
    thisActor->array[2] = 111;
    thisActor->array[3] = 1111;
    
    thisActor->s.a = 1;
    thisActor->s.b = 2;
    thisActor->s.another = malloc(sizeof(test_struct));
    thisActor->s.another->a = 11;
    thisActor->s.another->b = 22;
    
    thisActor->sa[0].a= 111;
    thisActor->sa[0].b=222;
    thisActor->sa[0].another = NULL;
    thisActor->sa[1].a = 1111;
    thisActor->sa[1].b = 2222;
    thisActor->sa[1].another = NULL;
    
}
static const int exitcode_block_Any[3]={1,0,1};
ART_ACTION_SCHEDULER(Example_m1_action_scheduler) {
  const int *result = EXIT_CODE_YIELD;
  ActorInstance_Example_m1 *thisActor=(ActorInstance_Example_m1*) pBase;
  ART_ACTION_SCHEDULER_ENTER(1, 1)
  while(1) {
    if ((pinAvailIn_int32_t(IN0_In) >= 1)) {
      if ((pinAvailOut_int32_t(OUT0_Out) >= 1)) {
        ART_FIRE_ACTION(action0);
        continue;
      
      } else {
        result = exitcode_block_Any;
        goto out;
      }
    }
    switch(thisActor->_fsmState) {
      case ActorInstance_Example_m1__defaultState_ID:
        result = exitcode_block_Any;
        goto out;
        break;
      
    }
  }
  out:
  ART_ACTION_SCHEDULER_EXIT(1, 1)
  return result;
}
