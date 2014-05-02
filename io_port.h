#ifndef IO_PORT_H_INCLUDED
#define IO_PORT_H_INCLUDED

#include "actors-rts.h"

void input_port_update_available(InputPort *self);
void input_port_update_drained_at(InputPort *self);
int input_port_has_producer(InputPort *self);
int input_port_update_tokens_consumed(InputPort *self);
int input_port_update_counter(InputPort *self);

int output_port_update_tokens_produced(OutputPort *self);
void output_port_update_full_at(OutputPort *self);
#endif
