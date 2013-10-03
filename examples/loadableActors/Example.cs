# simple example to load actor classes, instantiate actors, and set up
# a network

# Load classes
LOAD ./Example__m1.so
LOAD ./Example__m2.so
LOAD ./Example__m3.so
LOAD ./Example__m4.so

# Create instances with parameters
NEW art_Source_txt src fileName=indata.txt
NEW art_Sink_txt snk1 fileName=outdata1.txt
NEW art_Sink_txt snk2 fileName=outdata2.txt
NEW art_Sink_txt snk3 fileName=outdata3.txt
NEW art_Sink_txt snk4 fileName=outdata4.txt

# Create instances without parameters
NEW Example_m1 m1
NEW Example_m2 m2
NEW Example_m3 m3
NEW Example_m4 m4

# Connect the source to multipliers
CONNECT src.Out m1.In
CONNECT src.Out m2.In
CONNECT src.Out m3.In
CONNECT src.Out m4.In

# Connect multipliers to separate sinks
CONNECT m1.Out snk1.In
CONNECT m2.Out snk2.In
CONNECT m3.Out snk3.In
CONNECT m4.Out snk4.In

# Enable actors
ENABLE src snk1 snk2 snk3 snk4 m1 m2 m3 m4

# Execute the application
JOIN
