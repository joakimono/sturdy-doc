# Looks for executable breathe-apidoc

find_program(
  BREATHE_EXECUTABLE
  NAMES breathe-apidoc
  DOC "Path to breathe-apidoc executable")

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(
  Breathe
  "Failed to find breathe-apidoc executable"
  BREATHE_EXECUTABLE)
