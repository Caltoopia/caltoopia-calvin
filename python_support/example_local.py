import calvin

# expects a calvin node to be running at localhost:9000

a = calvin.Node("localhost", 9000)

src = a.new("art_Source_txt", "src", fileName="pyin.txt")
snk = a.new("art_Sink_txt", "snk", fileName="pyout.txt")

src.Out >> snk.In

src.enable()
snk.enable()

a.join()
a.destroyAll()
