#! /usr/bin/env python
import sys
import time
import calvin

# expects a calvin node to be running at localhost:9000

a = calvin.Node("10.0.2.15", 9000, True)
b = calvin.Node("10.0.2.15", 9001, True)
c = calvin.Node("10.0.2.15", 9002, True)

a.load("./timed_counter")
c.load("./accumulate")
b.load("./accumulate")

src = a.new("timed_counter", "src")
snk = a.new("art_Sink_txt", "snk", fileName="outdata.txt")
acd = b.new("accumulate", "acd")
acc = c.new("accumulate", "acc")

src.Out >> acc.In
acc.Out >> snk.In

src.enable()
snk.enable()
acc.enable()

enabled = acc
disabled = acd

while True :
  # Let the network produce some output ...
  time.sleep(3)
  # ... before fiddling with an actor ...
  src.disable()
  enabled.disable()
  snk.disable()

  state = enabled.serialize()
  src.Out.disconnectFromInput(enabled.In)
  enabled.Out.disconnectFromInput(snk.In)

  src.Out >> disabled.In
  disabled.Out >> snk.In
  disabled.deserialize(state)

  tmp = disabled
  disabled = enabled
  enabled = tmp

  # ... and finally resume normal operation
  snk.enable()
  src.enable()
  enabled.enable()
  time.sleep(0.3)
