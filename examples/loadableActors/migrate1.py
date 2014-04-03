#! /usr/bin/env python

import time
import calvin

# expects a calvin node to be running at localhost:9000

a = calvin.Node("localhost", 9000, True)
a.load("./accumulate.so")
a.load("./timed_counter.so")

src = a.new("timed_counter", "src")
snk = a.new("art_Sink_txt", "snk", fileName="outdata.txt")
acc = a.new("accumulate", "acc")

if False:
    src.Out >> snk.In
    src.enable()
    snk.enable()
else:
    src.Out >> acc.In
    acc.Out >> snk.In

    src.enable()
    snk.enable()
    acc.enable()


# Let the network produce some output ...
time.sleep(2)
# ... before fiddling with an actor ...
acc.disable()
state = acc.serialize()
acc.deserialize(state)
# ... and finally resume normal operation
acc.enable()


# a.join()
# a.destroyAll()
