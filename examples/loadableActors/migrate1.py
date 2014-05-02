#! /usr/bin/env python

import time
import calvin

# expects a calvin node to be running at localhost:9000

a = calvin.Node("localhost", 9000, True)
b = calvin.Node("localhost", 9001, True)
a.load("./accumulate")
a.load("./timed_counter")
b.load("./accumulate")

src = a.new("timed_counter", "src")
snk = a.new("art_Sink_txt", "snk", fileName="outdata.txt")
acc = a.new("accumulate", "acc")
acd = b.new("accumulate", "acd")

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
time.sleep(1)
# ... before fiddling with an actor ...
acc.disable()
state = acc.serialize()
acc.destroy()
src.Out >> acd.In
acd.Out >> snk.In
acd.deserialize(state)
# ... and finally resume normal operation
time.sleep(1)
acd.enable()

# a.join()
# a.destroyAll()
