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
 * Actor art_Source_txt (ActorClass_art_Source_txt)
 * Generated on Wed Jun 03 14:27:41 CEST 2009 from sysactors/art_Source_txt.xlim
 * by xlim2c version 0.6 (June 3, 2009)
 */

#include "actors-rts.h"
#include "actors-coder.h"
#include <stdio.h>
#include <errno.h>

typedef struct {
  AbstractActorInstance base;
  char *filename;
  FILE *file;
} ActorInstance_art_Source;

static const int exitcode_block_Out_1[] = {
  EXITCODE_BLOCK(1), 0, 1
};

ART_ACTION_CONTEXT(0, 1);

ART_ACTION_SCHEDULER(art_Source_txt_action_scheduler)
{
  const int *result = EXIT_CODE_YIELD;
  ActorInstance_art_Source *thisActor = (ActorInstance_art_Source*)pBase;
  int n;
  ART_ACTION_SCHEDULER_ENTER(0, 1);

  n = pinAvailOut_int32_t(ART_OUTPUT(0));
  ART_ACTION_SCHEDULER_LOOP {
    ART_ACTION_SCHEDULER_LOOP_TOP;
    if (n > 0) {
      int token;

      if (fscanf(thisActor->file, "%d", &token) < 0) {
	result = EXITCODE_TERMINATE;
	goto out;
      } else {
	n--;
	ART_ACTION_ENTER(action1, 0);
	pinWrite_int32_t(ART_OUTPUT(0), token);
	ART_ACTION_EXIT(action1, 0);
      }
    } else {
      result = exitcode_block_Out_1;
      goto out;
    }
    ART_ACTION_SCHEDULER_LOOP_BOTTOM;
  }
out:
  ART_ACTION_SCHEDULER_EXIT(0, 1);
  return result;

}

static void constructor(AbstractActorInstance *pBase) 
{
  ActorInstance_art_Source *thisActor = (ActorInstance_art_Source*)pBase;

  if (thisActor->filename == NULL) {
    runtimeError(pBase,"Parameter not set: fileName");
  } else {
    thisActor->file = fopen(thisActor->filename, "r");
    if (thisActor->file == NULL) {
      runtimeError(pBase,"Cannot open file for reading: %s: %s", 
                   thisActor->filename, strerror(errno));
    }
  }
}

static void destructor(AbstractActorInstance *pBase)
{
  ActorInstance_art_Source *thisActor=(ActorInstance_art_Source*) pBase;
  if (thisActor->file != NULL && thisActor->file != stdin) {
    fclose(thisActor->file);
  }
}

static void setParam(AbstractActorInstance *pBase, 
                     const char *paramName, 
                     const char *value)
{
  ActorInstance_art_Source *thisActor=(ActorInstance_art_Source*) pBase;
  if (strcmp(paramName, "fileName")==0) {
    thisActor->filename = strdup(value);
  } else {
    runtimeError(pBase,"No such parameter: %s", paramName);
  }
}

static void serialize(AbstractActorInstance *actor, ActorCoder *coder)
{
    ActorInstance_art_Source *this = (ActorInstance_art_Source *)actor;
    void *state = coder->init(coder);
    coder->encode(state, "filename", this->filename, "s");
}

static const PortDescription outputPortDescriptions[]={
  {0, "Out", sizeof(int32_t)}
};

static const int portRate_0[] = {
  0
};

static const int portRate_1[] = {
  1
};

static const ActionDescription actionDescriptions[] = {
  {"actionAtLine_7", 0, portRate_1}
};

ActorClass ActorClass_art_Source_txt = INIT_ActorClass(
  "art_Source_txt",
  ActorInstance_art_Source,
  constructor,
  setParam,
  serialize,
  art_Source_txt_action_scheduler,
  destructor,
  0, 0,
  1, outputPortDescriptions,
  1, actionDescriptions
);
