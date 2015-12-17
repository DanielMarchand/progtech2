

# This script should be outside of the repository!

cat exercise/pennaLV/src/zoo/animal.hpp | grep -A10 "class animal" || return 1
