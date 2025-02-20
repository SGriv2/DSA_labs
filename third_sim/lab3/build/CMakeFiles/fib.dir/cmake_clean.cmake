file(REMOVE_RECURSE
  "libfib.a"
  "libfib.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/fib.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
