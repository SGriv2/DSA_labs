file(REMOVE_RECURSE
  "libh_files.a"
  "libh_files.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/h_files.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
