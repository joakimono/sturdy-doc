# Looks for executable emacs

find_program(
  EMACS_EXECUTABLE
  NAMES emacs
  DOC "Path to emacs executable")

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(
  emacs
  "Failed to find emacs executable"
  EMACS_EXECUTABLE)
