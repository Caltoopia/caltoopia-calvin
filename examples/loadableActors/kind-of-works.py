#! /usr/bin/env python
import sys
import time
from random import shuffle
import calvin


hosts = [ "10.0.0.3", "10.0.0.4", "10.0.0.6", "10.0.0.7", "10.0.0.10", "10.0.0.12" ]
#node_ports = [ 9000 + i for i in range(0,NUM_NODES-1) ]

nodes = [ calvin.Node(node, 9000, True) for node in hosts]

# Node 0 is 'host'
nodes[0].load("./timed_counter")
for n in nodes :
    n.load("./accumulate")

src = nodes[0].new("timed_counter", "src")
snk = nodes[0].new("art_Sink_txt", "snk", fileName="outdata.txt")
accumulators = [ n.new("accumulate", "acc-%d" % (nodes.index(n))) for n in nodes ]

src.Out >> accumulators[0].In
accumulators[0].Out >> snk.In

src.enable()
snk.enable()
accumulators[0].enable()

enabled = 0

iterations = 1

time.sleep(3)

acc = accumulators[0]

while True :
  print " === iteration %d : %s === " % (iterations, acc.name)

  #time.sleep(1)
  # ... before fiddling with an actor ...

  state = acc.serialize()
  src.disable()
  acc.disable()
  snk.disable()

  state = acc.serialize()
  src.Out.disconnectFromInput(acc.In)
  acc.Out.disconnectFromInput(snk.In)

  # enabled = (enabled + 1) % len(nodes)
  shuffle(accumulators)

  acc = accumulators[0]

  acc.deserialize(state)
  src.Out >> acc.In
  acc.Out >> snk.In

  # ... and finally resume normal operation
  snk.enable()
  src.enable()
  acc.enable()
  iterations = iterations + 1
