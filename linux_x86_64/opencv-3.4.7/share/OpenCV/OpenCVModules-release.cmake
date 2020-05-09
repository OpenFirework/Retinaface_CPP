#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "libjpeg-turbo" for configuration "Release"
set_property(TARGET libjpeg-turbo APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(libjpeg-turbo PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/share/OpenCV/3rdparty/lib/liblibjpeg-turbo.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS libjpeg-turbo )
list(APPEND _IMPORT_CHECK_FILES_FOR_libjpeg-turbo "${_IMPORT_PREFIX}/share/OpenCV/3rdparty/lib/liblibjpeg-turbo.a" )

# Import target "libtiff" for configuration "Release"
set_property(TARGET libtiff APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(libtiff PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C;CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/share/OpenCV/3rdparty/lib/liblibtiff.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS libtiff )
list(APPEND _IMPORT_CHECK_FILES_FOR_libtiff "${_IMPORT_PREFIX}/share/OpenCV/3rdparty/lib/liblibtiff.a" )

# Import target "libwebp" for configuration "Release"
set_property(TARGET libwebp APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(libwebp PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/share/OpenCV/3rdparty/lib/liblibwebp.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS libwebp )
list(APPEND _IMPORT_CHECK_FILES_FOR_libwebp "${_IMPORT_PREFIX}/share/OpenCV/3rdparty/lib/liblibwebp.a" )

# Import target "libjasper" for configuration "Release"
set_property(TARGET libjasper APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(libjasper PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/share/OpenCV/3rdparty/lib/liblibjasper.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS libjasper )
list(APPEND _IMPORT_CHECK_FILES_FOR_libjasper "${_IMPORT_PREFIX}/share/OpenCV/3rdparty/lib/liblibjasper.a" )

# Import target "IlmImf" for configuration "Release"
set_property(TARGET IlmImf APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(IlmImf PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/share/OpenCV/3rdparty/lib/libIlmImf.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS IlmImf )
list(APPEND _IMPORT_CHECK_FILES_FOR_IlmImf "${_IMPORT_PREFIX}/share/OpenCV/3rdparty/lib/libIlmImf.a" )

# Import target "libprotobuf" for configuration "Release"
set_property(TARGET libprotobuf APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(libprotobuf PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/share/OpenCV/3rdparty/lib/liblibprotobuf.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS libprotobuf )
list(APPEND _IMPORT_CHECK_FILES_FOR_libprotobuf "${_IMPORT_PREFIX}/share/OpenCV/3rdparty/lib/liblibprotobuf.a" )

# Import target "quirc" for configuration "Release"
set_property(TARGET quirc APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(quirc PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/share/OpenCV/3rdparty/lib/libquirc.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS quirc )
list(APPEND _IMPORT_CHECK_FILES_FOR_quirc "${_IMPORT_PREFIX}/share/OpenCV/3rdparty/lib/libquirc.a" )

# Import target "ittnotify" for configuration "Release"
set_property(TARGET ittnotify APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(ittnotify PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/share/OpenCV/3rdparty/lib/libittnotify.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS ittnotify )
list(APPEND _IMPORT_CHECK_FILES_FOR_ittnotify "${_IMPORT_PREFIX}/share/OpenCV/3rdparty/lib/libittnotify.a" )

# Import target "opencv_world" for configuration "Release"
set_property(TARGET opencv_world APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(opencv_world PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libopencv_world.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS opencv_world )
list(APPEND _IMPORT_CHECK_FILES_FOR_opencv_world "${_IMPORT_PREFIX}/lib/libopencv_world.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
