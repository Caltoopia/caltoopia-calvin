/*
 * Copyright (c) Ericsson AB, 2009-2013
 * All rights reserved.
 *
 * License terms:
 *
 * Redistribution and use in source and binary forms,
 * with or without modification, are permitted provided
 * that the following conditions are met:
 *     * Redistributions of source code must retain the above
 *       copyright notice, this list of conditions and the
 *       following disclaimer.
 *     * Redistributions in binary form must reproduce the
 *       above copyright notice, this list of conditions and
 *       the following disclaimer in the documentation and/or
 *       other materials provided with the distribution.
 *     * Neither the name of the copyright holder nor the names
 *       of its contributors may be used to endorse or promote
 *       products derived from this software without specific
 *       prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * Actor art_Sink_txt (ActorClass_art_Sink_txt)
 * Generated on Wed Jun 03 14:12:24 CEST 2009 from sysactors/art_Sink_txt.xlim
 * by xlim2c version 0.6 (June 3, 2009)
 */

#include "actors-rts.h"
#include <stdio.h>
#include <errno.h>

typedef struct {
  AbstractActorInstance base;
  char *filename;
  FILE *file;
} ActorInstance_art_Sink;

static const int exitcode_block_In_1[] = {
  EXITCODE_BLOCK(1), 0, 1
};

ART_ACTION_CONTEXT(1, 0);

ART_ACTION_SCHEDULER(art_Sink_txt_action_scheduler)
{
  ActorInstance_art_Sink *thisActor=(ActorInstance_art_Sink*) pBase;
  const int *result = EXIT_CODE_YIELD;
  int numTokens;

  ART_ACTION_SCHEDULER_ENTER(1, 0);
  numTokens=pinAvailIn_int32_t(ART_INPUT(0));
  ART_ACTION_SCHEDULER_LOOP {
    ART_ACTION_SCHEDULER_LOOP_TOP;

    if (numTokens > 0) {
      numTokens--;
      ART_ACTION_ENTER(action1, 0);
      int32_t token=pinRead_int32_t(ART_INPUT(0));
      fprintf(thisActor->file, "%d\n", token);
	  fflush(thisActor->file);
      ART_ACTION_EXIT(action1, 0);
    } else {
      result = exitcode_block_In_1;
      goto out;
    }
    ART_ACTION_SCHEDULER_LOOP_BOTTOM;
  }
out:
  ART_ACTION_SCHEDULER_EXIT(1, 0)
  return result;
}

static void constructor(AbstractActorInstance *pBase) 
{
  ActorInstance_art_Sink *thisActor = (ActorInstance_art_Sink*)pBase;

  if (thisActor->filename == NULL) {
	thisActor->file = stdout;  
    //runtimeError(pBase,"Parameter not set: fileName");
  } else {
    thisActor->file = fopen(thisActor->filename, "w");
    if (thisActor->file == NULL) {
      runtimeError(pBase,"Cannot open file for output: %s: %s", 
		   thisActor->filename, strerror(errno));
    }
  }
}

static void destructor(AbstractActorInstance *pBase)
{
  ActorInstance_art_Sink *thisActor=(ActorInstance_art_Sink*) pBase;
  if (thisActor->file != NULL && thisActor->file != stdout) {
    fclose(thisActor->file);
  }
}

static void setParam(AbstractActorInstance *pBase, 
		     const char *paramName, 
		     const char *value)
{
  ActorInstance_art_Sink *thisActor=(ActorInstance_art_Sink*) pBase;
  if (strcmp(paramName,"fileName")==0) {
    thisActor->filename = strdup(value);
  } else {
    runtimeError(pBase,"No such parameter: %s", paramName);
  }
}

static const PortDescription inputPortDescriptions[]={
  {0, "In", sizeof(int32_t)}
};

static const int portRate_1[] = {
  1
};

static const ActionDescription actionDescriptions[] = {
  {"actionAtLine_7", portRate_1, 0}
};

ActorClass ActorClass_art_Sink_txt = INIT_ActorClass(
  "art_Sink_txt",
  ActorInstance_art_Sink,
  constructor,
  setParam,
  NULL,
  art_Sink_txt_action_scheduler,
  destructor,
  1, inputPortDescriptions,
  0, 0,
  1, actionDescriptions
);
