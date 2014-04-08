# Minimal example to load actor classes, instantiate actors, and set up
# a network

# Load classes
LOAD ./Example__m1

# Create instances with parameters
NEW art_Source_txt src fileName=indata.txt
NEW art_Sink_txt snk1 fileName=outdata1.txt

# Create instances without parameters
NEW Example_m1 m1

# Connect the source to multipliers
CONNECT src.Out m1.In

# Connect multipliers to separate sinks
CONNECT m1.Out snk1.In

# Enable actors
ENABLE src snk1 m1

# Execute the application
# JOIN
