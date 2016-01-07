# Git bisect example
#
# The simplest bisecting approach is to run a shell command with "run sh -c".
# We look at the log for the first commit hash (here: 63b9678), start the bisect
# and run the command of interest (here: check if he animal class is still
# around):
#
#   git log --oneline | tail
#   git bisect start HEAD 63b9678
#   git bisect run sh -c "cat exercise/pennaLV/src/zoo/animal.hpp | grep -A10 'class animal'"
#
#
# If we need a more complex set of commands, compilation (make), or branching,
# we can outsource the command to a script file.
# This script should not be commited to the repository we run the bisect on,
# because it will change when checking out different commits!
# Ideally, it's outside of the repository, and we must make sure the script is
# executable:
#
#   chmod +x ../path/to/bisect.sh
#   git log --oneline | tail
#   git bisect start HEAD 63b9678
#   git bisect run ../path/to/bisect.sh
#
# Return 1 (here for verbosity, as it's already done by cat/grep) if the commit
# is "bad", and 0 if it's "good".

cat exercise/pennaLV/src/zoo/animal.hpp | grep -A10 "class animal" || return 1
