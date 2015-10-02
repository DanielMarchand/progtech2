# Testing

## What do we expect from our testing framework?

* easy to use (make test)
* platform independent
* easy setup
* informative (with color)
* notify when test fails / is done
* accept source & build tool
* integration (only allow to commit if tests work)
* granularity (small low level test and system-wide tests)
* fast
* statistics (test-coverage, how many parts of the code are tested)
* check-correctness of:
    - output-data (business-logic)
    - interface
    - performance
    - invarinats
    - different levels
    - call count
    - correct errors
