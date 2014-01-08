# serz__top
import calvin
l = calvin.Node("localhost", 9001, True)
l2 = calvin.Node("localhost", 9000, True)
l.load("./serz__f")
l2.load("./serz__s")
serz__f = l.new("serz__f", "serz__f")
serz__s = l2.new("serz__s", "serz__s")
serz__f.Out >> serz__s.In
serz__s.Out >> serz__f.In
actors = (serz__f,serz__s,)
for actor in actors:
  actor.enable()