#ifndef IO_PORT_H_INCLUDED
#define IO_PORT_H_INCLUDED

struct InputPort;
struct OutputPort;
struct LocalOutputPort;

struct tokenFn {
  char * (*serialize)(void *, char*);
  char * (*deserialize)(void **, char*);
  long (*size)(void *);
  int  (*free)(void *, int);
};

typedef struct tokenFn tokenFn;

typedef struct InputPort InputPort;
typedef struct OutputPort OutputPort;

#include "actors-rts.h"

void input_port_update_available(InputPort *self);
void input_port_update_drained_at(InputPort *self);
int input_port_has_producer(InputPort *self);
int input_port_update_tokens_consumed(InputPort *self);
int input_port_update_counter(InputPort *self);

int output_port_update_tokens_produced(OutputPort *self);
void output_port_update_full_at(OutputPort *self);

struct InputPort *input_port_new(void);
struct OutputPort *output_port_new(void);

struct InputPort *input_port_array_new(int number_of_ports);
struct OutputPort *output_port_array_new(int number_of_ports);
struct InputPort *input_port_array_get(InputPort *arr, int index);
struct OutputPort *output_port_array_get(OutputPort *arr, int index);
void output_port_array_free(OutputPort *arr);
void input_port_array_free(InputPort *arr);

void input_port_set_producer(InputPort *self, OutputPort *producer);
OutputPort *input_port_producer(InputPort *self);
OutputPort *input_port_as_consumer(InputPort *self);
void *output_port_buffer_start(OutputPort *self);
void output_port_set_buffer_start(OutputPort *self, void *buffer_start);
void *output_port_buffer_end(OutputPort *self);
void *output_port_write_ptr(OutputPort *self);
const void *input_port_read_ptr(InputPort *self);
void input_port_set_buffer_start(InputPort *self, void *buffer_start);
void input_port_set_read_ptr(InputPort *self, void *read_ptr);
void output_port_set_capacity(OutputPort *self, int capacity);
void output_port_set_write_ptr(OutputPort *self, void *write_ptr);
void *output_port_buffer_end(OutputPort *self);
void output_port_set_buffer_end(OutputPort *self, void *buffer_end);
void input_port_set_buffer_end(InputPort *self, void *buffer_end);
void output_port_buffer_start_free(OutputPort *self);
int output_port_capacity(OutputPort *self);
void input_port_set_capacity(InputPort *self, int capacity);

void input_port_set_functions(InputPort *self, tokenFn *functions);
tokenFn *output_port_functions(OutputPort *self);
void output_port_set_functions(OutputPort *self, tokenFn *functions);

int output_port_tokens_produced(OutputPort *self);
void output_port_set_tokens_produced(OutputPort *self, int tokens_produced);
int input_port_tokens_consumed(InputPort *self);
void input_port_set_tokens_consumed(InputPort *self, int tokens_consumed);

void input_port_init_consumer(InputPort *self);
void output_port_init_consumer_list(OutputPort *self);
void output_port_remove_consumer(OutputPort *self, InputPort *input);
void output_port_add_consumer(OutputPort *self, InputPort *input);
void output_port_disconnect_consumers(OutputPort *self);
unsigned int output_port_max_available(OutputPort *self);

InputPort *output_port_first_consumer(OutputPort *self);
InputPort *input_port_next_consumer(InputPort *self);

/* temporary - remove */
struct LocalOutputPort *output_port_local_port(OutputPort *self);
struct LocalInputPort *input_port_local_port(InputPort *self);
#endif
