JSON READER
  simple json reader intended to be used for small
  json requests. it won't parse the json, it won't
  try to check if it's valid, just grab values
  if found and possible.

NOTES
  - no memory is allocated.
  - NULL can be safely used for all parameters.
  - strings MUST be NULL terminated.
  - not meant to be used with primitive arrays
    but instead, objects and array of objects.
  - no validations are done when reading.
    if a value can't be read, the default
    (zero, empty string) will be retrieved.

INSTALLATION
  to install, just copy json_reader.h/c in your
  project.

HOW TO USE IT
  check main.c for code usage example (you can 
  build it with build.bat)