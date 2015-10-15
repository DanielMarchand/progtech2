// Global static variables/functions

int x = 2;           // external linkage, this is the default for global variables

int y = 4;           // must NOT be static to be visible in 02_global_a.cpp

int z = 6;           // can be static since 02_global_a.cpp has its own

extern int w;        // brain teaser:
int v = w+1;         // locals are implicitly initialised first, then non-locals dynamically in the order they are defined in the translation unit
                     // to avoid this problem, often functions with static locals (as in 01_local.cpp) can be used

int bar() {          // must NOT be static to be visible in 02_global_a.cpp
    return 8;
}
