# Serialisation

### Why do we need serialisation?

* Save ___arbitrary data___ and parts of the ___program state___ to a file
* Send it over a ___network___
* ___Deserialise and use___ the stored objects

 => We have a struct and write it into / read it from a ___byte stream___

### What do we expect from our serialisation tool?

* simple: a single function
* non-intrusive
* cross platform
* all C++ standard data structures
* user defined types
* pointers: proper saving & restoration
* derived classes should work
* references and constants
* serialization independent of archive
* atomic
* versioning (can read last year's file)
