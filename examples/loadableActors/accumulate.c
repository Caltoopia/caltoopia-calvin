//
//  accumulate.c
//  Calvin
//
//  Created by Per Persson on 2014-03-31.
//
//


#include "logging.h"
#include "actors-rts.h"
#include "natives.h"
#include "Example__toppen.h"

#define  IN0_In ART_INPUT(0)
#define  OUT0_Out ART_OUTPUT(0)

//Actor state
typedef struct {
  AbstractActorInstance base;
  int _fsmState;
  int32_t sum;
} ActorInstance_accumulate;

//Actor functions
ART_ACTION_CONTEXT(1, 1)

  ART_ACTION(action0, ActorInstance_accumulate);
  ART_ACTION_SCHEDULER(accumulate_action_scheduler);

  static void ActorInstance_accumulate_constructor(AbstractActorInstance *);

  static const PortDescription inputPortDescriptions[]={
    {0, "In", sizeof(int32_t)},
  };
static const PortDescription outputPortDescriptions[]={
  {0, "Out", sizeof(int32_t)},
};

static const int portRate_in_action0[] = {1};

static const int portRate_out_action0[] = {1};

static const ActionDescription actionDescriptions[] = {
  {"action0", portRate_in_action0, portRate_out_action0},
};

static void
serialize(AbstractActorInstance *actor, ActorCoder *coder)
{
  ActorInstance_accumulate *this = (ActorInstance_accumulate *)actor;
  const ActorClass *actorClass = actor->actorClass;
  CoderState *state = coder->init(coder);

  // Class info
  coder->encode(coder, state, "class", (void *)&actorClass->name, "s");
  // Instance state
  coder->encode(coder, state, "_fsmState", &this->_fsmState, "i");
  coder->encode(coder, state, "sum", &this->sum, "i");
  // Output ports
  if (actorClass->numOutputPorts) {
    CoderState *ports = coder->encode_struct(coder, state, "outports");
    for (int i = 0; i < actorClass->numOutputPorts; i++) {
      // ToDo: Let ports serialize themselves
      const char *portname = actorClass->outputPortDescriptions[i].name;
      CoderState *port = coder->encode_struct(coder, ports, portname);
      CoderState *buffer = coder->encode_array(coder, port, "buffer");
      int count = 0;
      OutputPort *output = output_port_array_get(actor->outputPort, i);
      InputPort *consumer = output_port_first_consumer(output);
      // FIXME: Multiple consumers (fan-out) not supported
      if (!consumer) {
        m_critical("No consumer connected");
      }
      // FIXME: Assume FIFO is int32_t for now
      int32_t *bufferEnd = (int32_t *)output_port_buffer_end(output);
      int32_t *writePtr = (int32_t*)output_port_write_ptr(output);
      int32_t *readPtr = (int32_t*)input_port_read_ptr(consumer);
      while(readPtr != writePtr) {
        coder->encode(coder, buffer, NULL, readPtr, "i");
        m_info("Encoded : %d", *readPtr);
        count++;
        readPtr++;
        if (readPtr >= bufferEnd) {
          readPtr = (int32_t *)output_port_buffer_start(output);
        }
      }
#if 0
      {
        int j = -1;
        coder->encode(coder, buffer, NULL, &j, "i");
        count++;
      }
#endif
      coder->encode(coder, port, "length", &count, "i");
    }
  }
}

static void
deserialize_buffer(OutputPort *output_port, ActorCoder *coder, CoderState *port)
{
  int32_t *write_ptr;
  int buffer_size;
  int32_t *bufferEnd;
  int32_t *bufferStart;
  int idx;
  int32_t buffer_value;
  CoderState *buffer;

  write_ptr = (int32_t*)output_port_write_ptr(output_port);
  bufferEnd = (int32_t *) output_port_buffer_end(output_port);
  bufferStart = (int32_t *) output_port_buffer_start(output_port);
  buffer = coder->decode_array(coder, port, "buffer");
  coder->decode(coder, port, "length", &buffer_size, "i");

  for (idx = 0; idx < buffer_size; ++idx) {
    coder->decode(coder, buffer, NULL, &buffer_value, "i");
    *write_ptr = buffer_value;
    write_ptr++;
    m_info("Decoded %i", buffer_value);
    if (write_ptr >= bufferEnd) {
      write_ptr = bufferStart;
    }
  }
  output_port_set_write_ptr(output_port, write_ptr);
}

static void
deserialize_port(AbstractActorInstance *actor, ActorCoder *coder,
    CoderState *ports, int port_number)
{
  const char *portname;
  CoderState *port;
  OutputPort *output_port;

  portname = actor->actorClass->outputPortDescriptions[port_number].name;
  port = coder->decode_struct(coder, ports, portname);
  output_port = output_port_array_get(actor->outputPort, port_number);

  deserialize_buffer(output_port, coder, port);
}

  static void
deserialize(AbstractActorInstance *actor, ActorCoder *coder)
{
  ActorInstance_accumulate *this = (ActorInstance_accumulate *)actor;
  CoderState *state;
  CoderState *ports;
  int idx;

  state = coder->init(coder);
  coder->decode(coder, state, "_fsmState", (void *)&this->_fsmState, "i");
  coder->decode(coder, state, "sum", (void *)&this->sum, "i");
  ports = coder->decode_struct(coder, state, "outports");
  for (idx = 0; idx < actor->actorClass->numOutputPorts; ++idx) {
    deserialize_port(actor, coder, ports, idx);
  }
}


ActorClass klass = INIT_ActorClass(
    "accumulate",
    ActorInstance_accumulate,
    ActorInstance_accumulate_constructor,
    0, //setParam not needed anymore (we instantiate with params)
    serialize,
    deserialize,
    accumulate_action_scheduler,
    0, // no destructor
    1, inputPortDescriptions,
    1, outputPortDescriptions,
    1, actionDescriptions
    );



ART_ACTION(action0, ActorInstance_accumulate) {
  int32_t x;
  int32_t U__0;
  ART_ACTION_ENTER(action0, 0);
  x = pinRead_int32_t(IN0_In);
  U__0 = (x + thisActor->sum);
  thisActor->sum = U__0;
  m_info("Accumulate: %d", U__0);
  pinWrite_int32_t(OUT0_Out, U__0);
  ART_ACTION_EXIT(action0, 0);
}

#define ActorInstance_accumulate__defaultState_ID 0
static void ActorInstance_accumulate_constructor(AbstractActorInstance *pBase) {
  ActorInstance_accumulate *thisActor=(ActorInstance_accumulate*) pBase;
  thisActor->_fsmState = ActorInstance_accumulate__defaultState_ID;//Initial state
  {
  }

}
static const int exitcode_block_Any[3]={1,0,1};
ART_ACTION_SCHEDULER(accumulate_action_scheduler) {
  const int *result = EXIT_CODE_YIELD;
  ActorInstance_accumulate *thisActor=(ActorInstance_accumulate*) pBase;
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
        case ActorInstance_accumulate__defaultState_ID:
          result = exitcode_block_Any;
          goto out;
          break;

      }
    }
out:
  ART_ACTION_SCHEDULER_EXIT(1, 1)
    return result;
}
