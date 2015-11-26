# Storage & Serialisation

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

### What do we store in the long term?

Aim for ___reproducibility___, i.e. if you store a plot:

* numbers in plot (_data_)
* inputs to code that generated data (_parameters_)
* raw _data + instructions_ (if possible)

_How long_ is long term for simulation data?

* papers for a few decades
* if it's important, much longer

### What do we expect from our storage solution?

| archival                                      | storage medium                                    | reproducibility        |
|-----------------------------------------------|---------------------------------------------------|------------------------|
| data integrity                                | trusted location (only ETH-affiliated networks, e.g. not dropbox) |codes, build |
| established format (standard)                 | frequent back-ups                                 |  environment, compiler |
| read-only (WORM, write once read manytimes)   | hardware redundancy (i.e. RAID)                   | input, references      |
| hashes (error detection)                      | location redundancy (offsite backup)              |    instructions        |

### Storage Format

Options:

* Keep fixed structure (bump serialization version if layout changes, e.g. `boost::serialization`)
* Allow extensions (XML e.g. is flexible when adding members to a C++ struct)

| human readable    | binary            | database  |
|-------------------|-------------------|-----------|
|-space             |+space             |           |
|slow parse         |fast (lookup table)|fast (live)|
|+portability       |~portability       |           |
|+readability       |                   |           |
|(can guess format) |must know format   |           |
|txt, xml, csv, svg |hdf5, metcdf, png  |SQL        |


### Take Home Message

Work as if you have to ___reproduce___ anything you do for the ___next decade___.
