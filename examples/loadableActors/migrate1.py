#! /usr/bin/env python

import time
import calvin

# expects a calvin node to be running at localhost:9000

a = calvin.Node("localhost", 9000, True)
a.load("./accumulate.so")

src = a.new("art_Source_txt", "src", fileName="indata.txt")
snk = a.new("art_Sink_txt", "snk", fileName="outdata1.txt")
acc = a.new("accumulate", "acc")

src.Out >> acc.In
acc.Out >> snk.In

src.enable()
snk.enable()
acc.enable()

time.sleep(0.1)

acc.disable()
acc.serialize()
time.sleep(2)

acc.enable()

a.join()
a.destroyAll()
