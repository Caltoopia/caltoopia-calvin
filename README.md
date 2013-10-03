Calvin: a Cal virtual machine
=============================

Calvin is a Cal runtime system that allows for dynamic loading of
actors. The idea is to have Calvin running continously, and
load/unload actors and networks as needed. Calvin then runs as a service on
a node, much like an operating system rather than an application. Applications
are represented by networks of Cal actors.

Calvin currently runs primarily in Linux, but partial support for Mac OS X
is available. Calvin relies on pthreads for execution (and optionally SDL, for video
display).

How to build Calvin and a simple example
----------------------------------------

Running an application requires the following:

* Calvin
* one or more actors, in the form of hot-loadable .so files
* a network description, typically in CalvinScript format

Calvin is built in the most obvious way:

    make

Actors are built into .so files (or, on Mac OS X, .bundle files) using the same Makefile. To build the four actors in the loadableActors example, do (in Linux)

    cd examples/loadableActors
    make -f ../../Makefile \
      Example__m1.so Example__m2.so \
      Example__m3.so Example__m4.so

or (on a Mac)

    cd examples/loadableActors
    make -f ../../Makefile \
      Example__m1.bundle Example__m2.bundle \
      Example__m3.bundle Example__m4.bundle

How to run the example
----------------------

For the 'loadableActor' example above, the network is described in
Example.cs. Assuming that 'examples/loadableActors' is still the
current working directory:

    ../../calvin Example.cs

This line loads Calvin, loads and instantiates four actor classes, connects a network, and runs it to completion. You should now have four files
named outdata1..outdata4.txt in your directory.

More documentation
------------------

More information is available in the file doc/calvin.pdf in this repository.