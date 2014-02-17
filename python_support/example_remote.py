import calvin

# expects two calvin nodes to be running at localhost:9000 and localhost:9001

a = calvin.Node("localhost", 9000, True)
b = calvin.Node("localhost", 9001, True)

src = a.new("art_Source_txt", "src", fileName="pyin.txt")
snk = b.new("art_Sink_txt", "snk", fileName="pyout.txt")
src.Out >> snk.In

src.enable()
snk.enable()

a.join
b.join
