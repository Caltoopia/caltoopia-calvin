#include "io_port.h"

  /*
   * InputPort
   * Extends LocalInputPort, computes available tokens in pre-fire step,
   * updates tokensConsumed in post-fire step
   */
  struct InputPort {
    dllist_element_t asConsumer;        // member of producer's 'consumers' list

    OutputPort *producer;

    LocalInputPort localInputPort;
    unsigned tokensConsumed;          // number of tokens consumed
    unsigned drainedAt;               // point at which all tokensConsumed
    unsigned capacity;                // minimum capacity of buffer (in tokens)

    tokenFn functions;                // functions to handle structured tokens
  };

  /*
   * OutputPort
   * Extends LocalOutputPort: computes spaceLeft in pre-fire step,
   * updates tokensProduced in post-fire step
   */
  struct OutputPort {
    LocalOutputPort localOutputPort;
    unsigned capacity;                   // capacity of buffer (in tokens)
    unsigned tokensProduced;             // number of tokens produced
    unsigned fullAt;                     // tokensProduced when FIFO is full

    tokenFn functions;                   // functions to handle structured tokens

    dllist_head_t consumers;
  };


void
input_port_update_available(InputPort *self)
{
  unsigned int available;

  available = self->producer->tokensProduced - self->tokensConsumed;

  self->localInputPort.available = available;
}

void
input_port_update_drained_at(InputPort *self)
{
  self->drainedAt = self->tokensConsumed + self->localInputPort.available;
}

int
input_port_has_producer(InputPort *self)
{
  return self->producer != NULL;
}

int
input_port_update_counter(InputPort *self)
{
  unsigned int counter;
  int fired = 0;

  counter = self->drainedAt - self->localInputPort.available;
  if (counter != self->tokensConsumed) {
    self->tokensConsumed = counter;
    fired = 1;
  }
  return fired;
}

int
output_port_update_tokens_produced(OutputPort *self)
{
  unsigned int counter;
  int fired = 0;

  counter = self->fullAt - self->localOutputPort.spaceLeft;

  if (counter != self->tokensProduced) {
    self->tokensProduced = counter;
    fired = 1;
  }
  return fired;
}

void
output_port_update_full_at(OutputPort *self)
{
  unsigned int max_available;
  unsigned int space_left;

  max_available = output_port_max_available(self);
  space_left = self->capacity - max_available;
  self->localOutputPort.spaceLeft = space_left;
  // fullAt: tokensProduced counter when FIFO is full
  self->fullAt = self->tokensProduced + space_left;
}

unsigned int
input_port_available(InputPort *self)
{
  return self->localInputPort.available;
}

unsigned int
output_port_space_left(OutputPort *self)
{
  return self->localOutputPort.spaceLeft;
}

struct InputPort *
input_port_new(void)
{
  return input_port_array_new(1);
}


struct OutputPort *
output_port_new(void)
{
  return output_port_array_new(1);
}

struct OutputPort *
output_port_array_new(int number_of_ports)
{
  return calloc(number_of_ports, sizeof(struct OutputPort));
}

void
output_port_array_free(OutputPort *arr)
{
  free(arr);
}

void
input_port_array_free(InputPort *arr)
{
  free(arr);
}

struct InputPort *
input_port_array_new(int number_of_ports)
{
  return calloc(number_of_ports, sizeof(struct InputPort));
}

struct InputPort *
input_port_array_get(InputPort *arr, int index)
{
  return &arr[index];
}

struct OutputPort *
output_port_array_get(OutputPort *arr, int index)
{
  return &arr[index];
}

void
input_port_set_producer(InputPort *self, OutputPort *producer)
{
  self->producer = producer;
}

void *
output_port_buffer_start(OutputPort *self)
{
  return self->localOutputPort.bufferStart;
}

void
input_port_set_buffer_start(InputPort *self, void *buffer_start)
{
  self->localInputPort.bufferStart = buffer_start;
}

void
input_port_set_read_ptr(InputPort *self, void *read_ptr)
{
  self->localInputPort.readPtr = read_ptr;
}

void
output_port_set_write_ptr(OutputPort *self, void *write_ptr)
{
  self->localOutputPort.writePtr = write_ptr;
}

void *
output_port_write_ptr(OutputPort *self)
{
  return self->localOutputPort.writePtr;
}

const void *
input_port_read_ptr(InputPort *self)
{
  return self->localInputPort.readPtr;
}

void
output_port_set_buffer_end(OutputPort *self, void *buffer_end)
{
  self->localOutputPort.bufferEnd = buffer_end;
}

void
output_port_set_capacity(OutputPort *self, int capacity)
{
  self->capacity = capacity;
}

void *
output_port_buffer_end(OutputPort *self)
{
  return self->localOutputPort.bufferEnd;
}

void
input_port_set_buffer_end(InputPort *self, void *buffer_end)
{
  self->localInputPort.bufferEnd = buffer_end;
}

int
output_port_capacity(OutputPort *self)
{
  return self->capacity;
}

void
input_port_set_capacity(InputPort *self, int capacity)
{
  self->capacity = capacity;
}

void
input_port_set_functions(InputPort *self, tokenFn *functions)
{
  if (functions != NULL) {
    memcpy(&self->functions, functions, sizeof self->functions);
  } else {
    memset(&self->functions, 0, sizeof self->functions);
  }
}

void
output_port_set_functions(OutputPort *self, tokenFn *functions)
{
  if (functions != NULL) {
    memcpy(&self->functions, functions, sizeof self->functions);
  } else {
    memset(&self->functions, 0, sizeof self->functions);
  }
}

void
output_port_set_buffer_start(OutputPort *self, void *buffer_start)
{
  self->localOutputPort.bufferStart = buffer_start;
}

OutputPort *
input_port_producer(InputPort *self)
{
  return self->producer;
}

void
output_port_buffer_start_free(OutputPort *self)
{
  free(self->localOutputPort.bufferStart);
}

tokenFn *
output_port_functions(OutputPort *self)
{
  return &self->functions;
}

int
output_port_tokens_produced(OutputPort *self)
{
  return self->tokensProduced;
} 

void
output_port_set_tokens_produced(OutputPort *self, int tokens_produced)
{
  self->tokensProduced = tokens_produced;
}

int
input_port_tokens_consumed(InputPort *self)
{
  return self->tokensConsumed;
}

void
input_port_set_tokens_consumed(InputPort *self, int tokens_consumed)
{
  self->tokensConsumed = tokens_consumed;
}

void
input_port_init_consumer(InputPort *self)
{
  dllist_init_element(&self->asConsumer);
}

void
output_port_add_consumer(OutputPort *self, InputPort *input)
{
  dllist_append(&self->consumers, &input->asConsumer);
}

void
output_port_init_consumer_list(OutputPort *self)
{
  dllist_create(&self->consumers);
}

void
output_port_remove_consumer(OutputPort *self, InputPort *input)
{
  dllist_remove(&self->consumers, &input->asConsumer);
}

void
output_port_disconnect_consumers(OutputPort *self)
{
  dllist_element_t *elem = dllist_first(&self->consumers);

  while (elem) {
    input_port_set_producer((InputPort *)elem, NULL);
    elem = dllist_next(&self->consumers, elem);
  }
}

InputPort *
output_port_first_consumer(OutputPort *self)
{
  dllist_element_t *elem = dllist_first(&self->consumers);
  return (InputPort*)elem;
}

InputPort *
input_port_next_consumer(InputPort *self)
{
  return NULL;
}

OutputPort *
input_port_as_consumer(InputPort *self)
{
  return (OutputPort *)&self->asConsumer;
}

unsigned int
output_port_max_available(OutputPort *self)
{
  unsigned int max_available = 0;
  dllist_element_t *elem = dllist_first(&self->consumers);

  while (elem != NULL) {
    unsigned int available =
      output_port_tokens_produced(self) -
      input_port_tokens_consumed((InputPort *)elem);
    if (available > max_available) {
      max_available = available;
    }
    elem = dllist_next(&self->consumers, elem);
  }
  return max_available;
}

LocalOutputPort *
output_port_local_port(OutputPort *self)
{
  return &self->localOutputPort;
}

LocalInputPort *
input_port_local_port(InputPort *self)
{
  return &self->localInputPort;
}

