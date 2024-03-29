# CMakeList.txt used by the Checked C version of clang/LLVM.
# This copies the Checked C header files to the system header
# directory for clang so that they can easily be found/used.
#
# Checked C does not require runtime system changes, and it would
# be unnecesarily heavyweight to require people to pick up a new
# library just to get the Checked C include wrpaper files.
# So we place the header files with the compiler.

set(files
  assert_tainted.h
  errno_tainted.h
  fenv_tainted.h
  inttypes_tainted_internal.h
  math_tainted.h
  signal_tainted.h
  stdio_tainted.h
  stdlib_tainted.h
  string_tainted.h
  threads_tainted.h
  time_tainted.h
  unistd_tainted.h
  _builtin_stdio_tainted.h
        _builtin_string_tainted.h
        checkcbox_extensions.h

  )

set(posix_arpa_files
        arpa/inet_tainted.h
  )

set(posix_sys_files
        sys/socket_tainted.h
)

# Hack - compute the CLANG version from the LLVM version.  The
# CLANG_VERSION variable is not available at this point during the build.

string(REGEX MATCH "[0-9]+\\.[0-9]+(\\.[0-9]+)?" CHECKEDC_CLANG_VERSION
  ${PACKAGE_VERSION})

set(output_dir ${LLVM_LIBRARY_OUTPUT_INTDIR}/clang/${CHECKEDC_CLANG_VERSION}/include)

set(out_files)
foreach( f ${files} ${posix_arpa_files} ${posix_sys_files} )
  set( src ${CMAKE_CURRENT_SOURCE_DIR}/${f} )
  set( dst ${output_dir}/${f} )
  add_custom_command(OUTPUT ${dst}
    DEPENDS ${src}
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${src} ${dst}
    COMMENT "Copying CHECKCBOX's ${f}...")
  list(APPEND out_files ${dst})
endforeach( f )

add_custom_target(checkcbox-headers ALL DEPENDS ${out_files})
set_target_properties(checkcbox-headers PROPERTIES FOLDER "Misc")

install(
  FILES ${files}
  COMPONENT checkcbox-headers
  PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ
  DESTINATION lib${LLVM_LIBDIR_SUFFIX}/clang/${CHECKEDC_CLANG_VERSION}/include
  )

install(
  FILES ${posix_arpa_files}
  COMPONENT clang-headers
  PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ
  DESTINATION lib${LLVM_LIBDIR_SUFFIX}/clang/${CHECKEDC_CLANG_VERSION}/include/arpa
  )

install(
  FILES ${posix_sys_files}
  COMPONENT clang-headers
  PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ
  DESTINATION lib${LLVM_LIBDIR_SUFFIX}/clang/${CHECKEDC_CLANG_VERSION}/include/sys
  )

if (NOT CMAKE_CONFIGURATION_TYPES) # don't add this for IDE's.
  add_custom_target(install-checkcbox-headers
    DEPENDS checkcbox-headers
    COMMAND "${CMAKE_COMMAND}"
            -DCMAKE_INSTALL_COMPONENT=checkcbox-headers
            -P "${CMAKE_BINARY_DIR}/cmake_install.cmake")
endif()
