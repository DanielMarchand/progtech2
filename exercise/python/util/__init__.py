import os
import sys

try:
   from boostpy_random import *
except ImportError:
    raise ImportError("Error: unable to import boostpy_random, please run make")
