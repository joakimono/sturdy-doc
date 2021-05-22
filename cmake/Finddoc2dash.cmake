# Looks for executable doc2dash

find_program(
  DOC2DASH_EXECUTABLE
  NAMES doc2dash
  DOC "Path to doc2dash executable")

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(
  doc2dash
  "Failed to find doc2dash executable"
  DOC2DASH_EXECUTABLE)
