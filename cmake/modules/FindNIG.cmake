find_path(LIBNIG_INCLUDES nfe_api.h
        PATH_SUFFIXES nig)
find_library(LIBNIG_LIBRARIES nig)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(LIBNIG DEFAULT_MSG LIBNIG_LIBRARIES LIBNIG_INCLUDES)
mark_as_advanced(LIBNIG_LIBRARIES LIBNIG_INCLUDES)

if(LIBNIG_FOUND)
    if(NOT TARGET NIG::NIG)
        add_library(NIG::NIG UNKNOWN IMPORTED)
        set_target_properties(NIG::NIG PROPERTIES
                IMPORTED_LINK_INTERFACE_LANGUAGES "C"
                INTERFACE_INCLUDE_DIRECTORIES "${LIBNIG_INCLUDES}"
				INTERFACE_LINK_LIBRARIES "${LIBNIG_LIBRARIES}"
         )
    endif()
endif()
