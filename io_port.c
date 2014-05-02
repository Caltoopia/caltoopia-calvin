#include "io_port.h"

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

static unsigned int
output_port_max_available(OutputPort *self)
{
  unsigned int max_available = 0;

  InputPort *consumer = (InputPort *)dllist_first_lock(&self->consumers);
  while (consumer != NULL) {
    unsigned int available = self->tokensProduced - consumer->tokensConsumed;
    if (available > max_available) {
      max_available = available;
    }
    consumer = (InputPort *)dllist_next_locked(&self->consumers, &consumer->asConsumer);
  }
  dllist_unlock(&self->consumers);
  return max_available;
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
