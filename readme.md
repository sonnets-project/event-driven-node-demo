Preface
===

This is a minimum-worked example of a generic event-driven application. Its
point: to give some idea about what an event-driven application might look like
in the wild. Long story short:

 - I introduce the concept of a node (we call 'stack' here), an event, and an
   event driver. I then explain how these might map in code form.

 - The 'event-drivenness' of the application is divorced from the application
   logic. This means application developers can work independently, using some
   common event-driven infrastructure if desired.

This is not:

 - A specification

 - Well tested

 - To be trusted

It is simply an illustration.

The System
===

An abridged view of an event-driven application is shown below.

![Abridged event-driven application](doc_images/overview.png)

 - Application logic defines the core behaviours of the node - it could be
   responsible for executing some machine learning algorithm, for example. The
   application logic provides an interface: a set of functions that operate on
   some internal state. By separating the application logic from the other
   components of the event-driven system, the application can operate in a
   standalone manner.

 - The driver acts as a communications broker between the node and the wider
   network. It fundamentally receives events, calls different functions
   prepared in the application interface, and sends events to other nodes. The
   driver is (typically) quiescent, in that it only does any work when an event
   is received from another node.

 - Events are nothing more than strings of bits that are exchanged between
   drivers over some transport layer (e.g. IP, sockets, MPI). The driver
   interprets these bits of strings to decide how to interact with the
   application logic (if at all).

 - A node is the coupling between a driver and some application logic. Many
   nodes can be connected together in an event-driven system to complete a
   task.

What results is a system where nodes send events to each other, events are
processed by nodes, and (hopefully) some useful work is done.

More documentation to come
===
