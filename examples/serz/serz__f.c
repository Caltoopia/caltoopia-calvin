// serz, first, f, $d114279
#include "actors-rts.h"
#include "natives.h"
#include "commonSpec.h"
#define  IN0_In ART_INPUT(0)
#define  OUT0_Out ART_OUTPUT(0)

//Actor constants

//Actor state
typedef struct {
  AbstractActorInstance base;
  int _fsmState;
  /*TODO DD T1 of varType unknown and type import */
  /*TODO DD T2 of varType unknown and type import */
  /*TODO DD dprint1 of varType externProc and NOT anticipated */
} ActorInstance_serz__f;

//Actor functions
/*TODO DF T1 of varType unknown and type import*/
/*TODO DF T2 of varType unknown and type import*/
/*TODO DF dprint1 of varType externProc and NOT anticipated*/
ART_ACTION_CONTEXT(1, 1)

ART_ACTION(action0__doit, ActorInstance_serz__f);
ART_ACTION_SCHEDULER(serz__f_action_scheduler);
static void ActorInstance_serz__f_constructor(AbstractActorInstance *);

static const PortDescription inputPortDescriptions[]={
  {0, "In", sizeof(void*)
  #ifdef CAL_RT_CALVIN
  , &(tokenFn){(char * (*)(void *, char*))serializeStructT2_t, (char * (*)(void **, char*))deserializeStructT2_t, (long (*)(void *))sizeStructT2_t, (int (*)(void *, int))freeStructT2_t}
  #endif
  },
};
static const PortDescription outputPortDescriptions[]={
  {0, "Out", sizeof(void*)
  #ifdef CAL_RT_CALVIN
  , &(tokenFn){(char * (*)(void *, char*))serializeStructT2_t, (char * (*)(void **, char*))deserializeStructT2_t, (long (*)(void *))sizeStructT2_t, (int (*)(void *, int))freeStructT2_t}
  #endif
  },
};

static const int portRate_in_action0__doit[] = {1};

static const int portRate_out_action0__doit[] = {1};

static const ActionDescription actionDescriptions[] = {
  {"action0__doit", portRate_in_action0__doit, portRate_out_action0__doit},
};

#ifdef CAL_RT_CALVIN
ActorClass klass
#else
ActorClass ActorClass_serz__f
#endif
   = INIT_ActorClass(
  "serz__f",
  ActorInstance_serz__f,
  ActorInstance_serz__f_constructor,
  0, //setParam not needed anymore (we instantiate with params)
  serz__f_action_scheduler,
  0, // no destructor
  1, inputPortDescriptions,
  1, outputPortDescriptions,
  1, actionDescriptions
);

ART_ACTION(action0__doit, ActorInstance_serz__f)
{
  void * __tempVoidPointer;
  __array4void __tempArray;
  T2_t* i = NULL;
  T2_t* o = NULL;
  T1_t* t1 = NULL;
  T1_t* t1i = NULL;
  dprint("serz__f action0__doit\n");  ART_ACTION_ENTER(action0__doit, 0);
  i = pinRead_ref(IN0_In);
  switch (i->tag) {
  case T2___A:
    {
      void * __tempVoidPointer;
      __array4void __tempArray;
      T1_t* __x = i->members.A.a;
      /*
      T:{Variable_VarLocalAccess=scalarUserType, Variable_VarType=actionVar, Variable_VarAssign=assigned, Variable_VarPlacement=auto}
      E:{Variable_VarLocalAccess=scalarUserType, Variable_VarType=blockConstVar, Variable_VarPlacement=constant}
      */
      copyStructT1_t(&t1i, __x);
    }
    break;
  default:
    break;
  }
  switch (t1i->tag) {
  case T1___A:
    {
      void * __tempVoidPointer;
      __array4void __tempArray;
      int32_t __x2 = t1i->members.A.a;
      int32_t __y2 = t1i->members.A.b;
      __array4int32_t __temp___DOLLAR__d114702 = (__array4int32_t){malloc(sizeof(int32_t)*10), 0xf, 1, {10}};
      /*
      T:{Variable_VarLocalAccess=scalarUserType, Variable_VarType=actionVar, Variable_VarAssign=assigned, Variable_VarPlacement=auto, Variable_VarLiteral=assignedTypeConstruct}
      E:{Variable_VarLiteral=assignedTypeConstruct}
      */
      constructT1___A(&t1, (__x2 + __y2), __y2);
      /*
      A:{Variable_ListSize=0}
      T:{Variable_VarLocalAccess=listSingle, Variable_VarType=blockVar, Variable_VarAssign=assigned, Variable_VarPlacement=autoListHeap, Variable_VarLiteral=assignedLit}
      */
      __temp___DOLLAR__d114702.p[(0)] = 0;
      /*
      T:{Variable_VarLocalAccess=listSingle, Variable_VarType=blockVar, Variable_VarAssign=assigned, Variable_VarPlacement=autoListHeap, Variable_VarLiteral=assignedLit}
      */
      __temp___DOLLAR__d114702.p[(1)] = 1;
      /*
      T:{Variable_VarLocalAccess=listSingle, Variable_VarType=blockVar, Variable_VarAssign=assigned, Variable_VarPlacement=autoListHeap, Variable_VarLiteral=assignedLit}
      */
      __temp___DOLLAR__d114702.p[(2)] = 2;
      /*
      T:{Variable_VarLocalAccess=listSingle, Variable_VarType=blockVar, Variable_VarAssign=assigned, Variable_VarPlacement=autoListHeap, Variable_VarLiteral=assignedLit}
      */
      __temp___DOLLAR__d114702.p[(3)] = 3;
      /*
      T:{Variable_VarLocalAccess=listSingle, Variable_VarType=blockVar, Variable_VarAssign=assigned, Variable_VarPlacement=autoListHeap, Variable_VarLiteral=assignedLit}
      */
      __temp___DOLLAR__d114702.p[(4)] = 4;
      /*
      T:{Variable_VarLocalAccess=listSingle, Variable_VarType=blockVar, Variable_VarAssign=assigned, Variable_VarPlacement=autoListHeap, Variable_VarLiteral=assignedLit}
      */
      __temp___DOLLAR__d114702.p[(5)] = 5;
      /*
      T:{Variable_VarLocalAccess=listSingle, Variable_VarType=blockVar, Variable_VarAssign=assigned, Variable_VarPlacement=autoListHeap, Variable_VarLiteral=assignedLit}
      */
      __temp___DOLLAR__d114702.p[(6)] = 6;
      /*
      T:{Variable_VarLocalAccess=listSingle, Variable_VarType=blockVar, Variable_VarAssign=assigned, Variable_VarPlacement=autoListHeap, Variable_VarLiteral=assignedLit}
      */
      __temp___DOLLAR__d114702.p[(7)] = 7;
      /*
      T:{Variable_VarLocalAccess=listSingle, Variable_VarType=blockVar, Variable_VarAssign=assigned, Variable_VarPlacement=autoListHeap, Variable_VarLiteral=assignedLit}
      */
      __temp___DOLLAR__d114702.p[(8)] = 8;
      /*
      T:{Variable_VarLocalAccess=listSingle, Variable_VarType=blockVar, Variable_VarAssign=assigned, Variable_VarPlacement=autoListHeap, Variable_VarLiteral=assignedLit}
      */
      __temp___DOLLAR__d114702.p[(9)] = 9;
      /*
      T:{Variable_VarLocalAccess=scalarUserType, Variable_VarType=outPortVar, Variable_VarAssign=assigned, Variable_VarPlacement=fifo, Variable_VarAccessOut=scalarUserTypeSingle, Variable_VarLiteral=assignedTypeConstruct}
      E:{Variable_VarLiteral=assignedTypeConstruct}
      */
      constructT2___A(&o, t1, __temp___DOLLAR__d114702);
      __temp___DOLLAR__d114702.flags = 0x0;
      dprint1("First A %i\n", (__x2 + __y2));
      freeint32_t(&__temp___DOLLAR__d114702, TRUE);
    }
    break;
  case T1___B:
    {
      void * __tempVoidPointer;
      __array4void __tempArray;
      int32_t __x2 = t1i->members.B.a;
      int32_t __y2 = t1i->members.B.c;
      __array4int32_t __temp___DOLLAR__d114705 = (__array4int32_t){malloc(sizeof(int32_t)*10), 0xf, 1, {10}};
      /*
      T:{Variable_VarLocalAccess=scalarUserType, Variable_VarType=actionVar, Variable_VarAssign=assigned, Variable_VarPlacement=auto, Variable_VarLiteral=assignedTypeConstruct}
      E:{Variable_VarLiteral=assignedTypeConstruct}
      */
      constructT1___B(&t1, (__x2 + __y2), __y2);
      /*
      A:{Variable_ListSize=0}
      T:{Variable_VarLocalAccess=listSingle, Variable_VarType=blockVar, Variable_VarAssign=assigned, Variable_VarPlacement=autoListHeap, Variable_VarLiteral=assignedLit}
      */
      __temp___DOLLAR__d114705.p[(0)] = 0;
      /*
      T:{Variable_VarLocalAccess=listSingle, Variable_VarType=blockVar, Variable_VarAssign=assigned, Variable_VarPlacement=autoListHeap, Variable_VarLiteral=assignedLit}
      */
      __temp___DOLLAR__d114705.p[(1)] = 1;
      /*
      T:{Variable_VarLocalAccess=listSingle, Variable_VarType=blockVar, Variable_VarAssign=assigned, Variable_VarPlacement=autoListHeap, Variable_VarLiteral=assignedLit}
      */
      __temp___DOLLAR__d114705.p[(2)] = 2;
      /*
      T:{Variable_VarLocalAccess=listSingle, Variable_VarType=blockVar, Variable_VarAssign=assigned, Variable_VarPlacement=autoListHeap, Variable_VarLiteral=assignedLit}
      */
      __temp___DOLLAR__d114705.p[(3)] = 3;
      /*
      T:{Variable_VarLocalAccess=listSingle, Variable_VarType=blockVar, Variable_VarAssign=assigned, Variable_VarPlacement=autoListHeap, Variable_VarLiteral=assignedLit}
      */
      __temp___DOLLAR__d114705.p[(4)] = 4;
      /*
      T:{Variable_VarLocalAccess=listSingle, Variable_VarType=blockVar, Variable_VarAssign=assigned, Variable_VarPlacement=autoListHeap, Variable_VarLiteral=assignedLit}
      */
      __temp___DOLLAR__d114705.p[(5)] = 5;
      /*
      T:{Variable_VarLocalAccess=listSingle, Variable_VarType=blockVar, Variable_VarAssign=assigned, Variable_VarPlacement=autoListHeap, Variable_VarLiteral=assignedLit}
      */
      __temp___DOLLAR__d114705.p[(6)] = 6;
      /*
      T:{Variable_VarLocalAccess=listSingle, Variable_VarType=blockVar, Variable_VarAssign=assigned, Variable_VarPlacement=autoListHeap, Variable_VarLiteral=assignedLit}
      */
      __temp___DOLLAR__d114705.p[(7)] = 7;
      /*
      T:{Variable_VarLocalAccess=listSingle, Variable_VarType=blockVar, Variable_VarAssign=assigned, Variable_VarPlacement=autoListHeap, Variable_VarLiteral=assignedLit}
      */
      __temp___DOLLAR__d114705.p[(8)] = 8;
      /*
      T:{Variable_VarLocalAccess=listSingle, Variable_VarType=blockVar, Variable_VarAssign=assigned, Variable_VarPlacement=autoListHeap, Variable_VarLiteral=assignedLit}
      */
      __temp___DOLLAR__d114705.p[(9)] = 9;
      /*
      T:{Variable_VarLocalAccess=scalarUserType, Variable_VarType=outPortVar, Variable_VarAssign=assigned, Variable_VarPlacement=fifo, Variable_VarAccessOut=scalarUserTypeSingle, Variable_VarLiteral=assignedTypeConstruct}
      E:{Variable_VarLiteral=assignedTypeConstruct}
      */
      constructT2___A(&o, t1, __temp___DOLLAR__d114705);
      __temp___DOLLAR__d114705.flags = 0x0;
      dprint1("First B %i\n", (__x2 + __y2));
      freeint32_t(&__temp___DOLLAR__d114705, TRUE);
    }
    break;
  default:
    break;
  }
  pinWrite_ref(OUT0_Out, o);
  freeStructT2_t(i, TRUE);
  freeStructT1_t(t1, TRUE);
  freeStructT1_t(t1i, TRUE);
  ART_ACTION_EXIT(action0__doit, 0);
}


#define ActorInstance_serz__f__defaultState_ID 0
static void ActorInstance_serz__f_constructor(AbstractActorInstance *pBase) {
  ActorInstance_serz__f *thisActor=(ActorInstance_serz__f*) pBase;
  thisActor->_fsmState = ActorInstance_serz__f__defaultState_ID;//Initial state

}
static const int exitcode_block_Any[3]={1,0,1};
ART_ACTION_SCHEDULER(serz__f_action_scheduler) {
  const int *result = EXIT_CODE_YIELD;
  ActorInstance_serz__f *thisActor=(ActorInstance_serz__f*) pBase;
  ART_ACTION_SCHEDULER_ENTER(1, 1)
  while(1) {
    switch(thisActor->_fsmState) {
    case ActorInstance_serz__f__defaultState_ID:
      if ((pinAvailIn_ref(IN0_In) >= 1)) {
        if ((pinAvailOut_ref(OUT0_Out) >= 1)) {
          ART_FIRE_ACTION(action0__doit);
          if(thisActor->_fsmState != ActorInstance_serz__f__defaultState_ID) {
            dprint2("%i --> %i ActorInstance_serz__f__defaultState\n", thisActor->_fsmState, ActorInstance_serz__f__defaultState_ID);
          }
          thisActor->_fsmState = ActorInstance_serz__f__defaultState_ID;
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
  ART_ACTION_SCHEDULER_EXIT(1, 1)
  return result;
}
