# serz__top
import calvin
l = calvin.Node("localhost", 9000, True)
l.load("./serz__f")
l.load("./serz__s")
serz__f = l.new("serz__f", "serz__f")
serz__s = l.new("serz__s", "serz__s")
serz__f.Out >> serz__s.In
serz__s.Out >> serz__f.In
actors = (serz__f,serz__s,)
for actor in actors:
  actor.enable()