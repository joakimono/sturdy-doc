
find_package(Doxygen REQUIRED)
find_package(Sphinx REQUIRED) # optional
find_package(Breathe REQUIRED) # optional
find_package(Emacs REQUIRED) # optional

# All targets contains all targets of the project
message(STATUS "All targets are: ${STURDY_ALL_TARGETS}")
#
get_target_property(STURDY_PUBLIC fishy PUBLIC_HEADER)
# Should private headers be added as well?

# --------------------------------------------------------------------
# Doxygen xml generation
# --------------------------------------------------------------------

set(DOXYGEN_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/doxygen)
set(DOXYGEN_XML_OUTPUT xml)

set(DOXYGEN_GENERATE_HTML YES)
set(DOXYGEN_HTML_OUTPUT html)
set(DOXYGEN_USE_MATHJAX YES) # To disable latex compilation for now in html.
set(DOXYGEN_GENERATE_XML YES)
set(DOXYGEN_GENERATE_LATEX NO)
set(DOXYGEN_FULL_PATH_NAMES YES)
#set(DOXYGEN_PLANTUML_JAR_PATH /usr/share/plantuml/plantuml.jar) # optional?

# Suggested settings by Exhale docs
set(DOXYGEN_ENABLE_PREPROCESSING YES)
set(DOXYGEN_MACRO_EXPANSION YES)
set(DOXYGEN_SKIP_FUNCTION_MACROS NO)
set(DOXYGEN_EXPAND_ONLY_PREDEF NO)

set(DOXYGEN_EXCLUDE_PATTERNS "*.cpp")

list(APPEND DOXYGEN_ALIASES "rst=\\verbatim embed:rst:")
list(APPEND DOXYGEN_ALIASES "endrst=\\endverbatim")
list(APPEND DOXYGEN_ALIASES "rststar=\\verbatim embed:rst:leading-asterisk")
list(APPEND DOXYGEN_ALIASES "endrststar=\\endverbatim")

set(DOXYGEN_PREDEFINED DOXYGEN_SHOULD_SKIP_THIS)

# More doxygen graphs does not affect XML
# Do not extract all, like cpp files and more
# Tweak what you want included
# Note: It seem to only affect non-XML export
set(DOXYGEN_HAVE_DOT YES)
set(DOXYGEN_UML_LOOK YES)
set(DOXYGEN_CLASS_DIAGRAMS YES)
set(DOXYGEN_CLASS_GRAPH YES)
set(DOXYGEN_COLLABORATION_GRAPH YES)
set(DOXYGEN_EXTRACT_ALL NO)
set(DOXYGEN_HIDE_UNDOC_MEMBERS YES)
set(DOXYGEN_HIDE_UNDOC_CLASSES YES)
set(DOXYGEN_HIDE_FRIEND_COMPOUNDS YES)
set(DOXYGEN_HIDE_IN_BODY_DOCS YES)

set(DOXYGEN_STRIP_FROM_PATH ${CMAKE_SOURCE_DIR}/include)
set(MY_SOURCES "../include")

doxygen_add_docs(doxygen "${MY_SOURCES}"
  COMMENT "Generating docs with Doxygen")
# CMake>=3.16: USE_STAMP_FILE to avoid building all the time?

set(DOXY_INDEX_PRIV_FILE ${DOXYGEN_OUTPUT_DIR}/xml/index.xml)
set(DOXYGEN_XML_OUTPUT xml_priv)
set(DOXYGEN_HTML_OUTPUT html_priv)

set(DOXYGEN_STRIP_FROM_PATH ${CMAKE_SOURCE_DIR})
set(MY_SOURCES "../src")

doxygen_add_docs(doxygen-priv "${MY_SOURCES}"
  COMMENT "Generating docs with Doxygen")


# --------------------------------------------------------------------
# Sphinx html generation
# --------------------------------------------------------------------

set(SPHINX_BUILD ${CMAKE_CURRENT_BINARY_DIR}/sphinx)
set(SPHINX_SOURCE ${SPHINX_BUILD}/source)
set(SPHINX_INDEX_FILE ${SPHINX_BUILD}/html/index.html)
set(SPHINX_MAN_FILE ${SPHINX_BUILD}/man/testproject.1)

string(TIMESTAMP THE_YEAR '%Y')
configure_file(conf.py.in ${SPHINX_SOURCE}/conf.py @ONLY)

add_custom_target(doc-org DEPENDS ${SPHINX_SOURCE}/index.rst)
add_dependencies(doc-org doxygen doxygen-priv)

file(GLOB_RECURSE THE_ORG_FILES
  LIST_DIRECTORIES false
  RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
  CONFIGURE_DEPENDS
  org/*.org)

# Convert org files to restructuredText using emacs
set(WITH_API_DOC "'t") # or 'nil if to disable, latter is discouraged
add_custom_command(
  OUTPUT ${SPHINX_SOURCE}/index.rst always.outdated
  COMMAND ${CMAKE_COMMAND} -E make_directory ${SPHINX_SOURCE}/rst
  COMMAND ${EMACS_EXECUTABLE} -Q --batch
  -L ${CMAKE_CURRENT_SOURCE_DIR}
  --eval "(setq out-dir \"${SPHINX_SOURCE}\")"
  --eval "(setq with-api-doc 't)"
  -l emacs-load.el
  -f jemacs-export-org-doc
  index.org
  COMMAND ${EMACS_EXECUTABLE} -Q --batch
  -L ${CMAKE_CURRENT_SOURCE_DIR}
  --eval "(setq out-dir \"${SPHINX_SOURCE}/rst\")"
  -l emacs-load.el
  -f jemacs-export-org-doc
  ${THE_ORG_FILES}
  COMMAND ${CMAKE_COMMAND} -E copy_directory static ${SPHINX_SOURCE}/static
  MAIN_DEPENDENCY index.org
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  COMMENT "Exporting org files to restructuredText"
  VERBATIM
  )


# Prepare sphinx root source directory
# Clean api build every time
# Copy static resources
# Copy markdown files
add_custom_target(doc-sources
  COMMAND ${CMAKE_COMMAND} -E remove_directory ${SPHINX_SOURCE}/api
  COMMAND ${CMAKE_COMMAND} -E remove_directory ${SPHINX_SOURCE}/api_private
  COMMAND ${CMAKE_COMMAND} -E remove_directory ${SPHINX_SOURCE}/org
  COMMAND ${CMAKE_COMMAND} -E remove_directory ${SPHINX_BUILD}/html
  COMMAND ${CMAKE_COMMAND} -E copy_directory static ${SPHINX_SOURCE}/static
  COMMAND ${CMAKE_COMMAND} -E copy_directory _templates ${SPHINX_SOURCE}/_templates
  COMMAND ${CMAKE_COMMAND} -E copy_directory _ext ${SPHINX_SOURCE}/_ext
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/data/icons/logo.png ${SPHINX_SOURCE}/static
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/data/icons/icon.ico ${SPHINX_SOURCE}/static
  COMMAND ${CMAKE_COMMAND} -E copy_directory md ${SPHINX_SOURCE}/md
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  COMMENT "DELETE generated api docs and COPY doc sources to sphinx root dir"
  )

add_custom_target(doc-html DEPENDS ${SPHINX_INDEX_FILE})
add_dependencies(doc-html doc-org doc-sources doxygen doxygen-priv)

# Generate the sphinx html
add_custom_command(
  OUTPUT ${SPHINX_INDEX_FILE} always.outdated
  COMMAND ${SPHINX_EXECUTABLE} -b html
  -Dbreathe_projects.${PROJECT_NAME}=${DOXYGEN_OUTPUT_DIRECTORY}/xml
  -Dbreathe_projects.${PROJECT_NAME}-private=${DOXYGEN_OUTPUT_DIRECTORY}/xml_priv
  ${SPHINX_SOURCE} ${SPHINX_BUILD}/html
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  MAIN_DEPENDENCY ${SPHINX_SOURCE}/conf.py
  COMMENT "Generate docs with Sphinx"
  VERBATIM
  )

install(DIRECTORY ${SPHINX_BUILD}/html
  COMPONENT doc
  DESTINATION ${CMAKE_INSTALL_DOCDIR}
  )

# If you add ALL to custom target, doc will always build when you call cmake --build .
add_custom_target(doc)
add_dependencies(doc doc-html)# doc-man)
