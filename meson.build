project('cnbt', 'c')

libcnbt_include = include_directories('include')
subdir('src') # defines libcnbt_sources
libcnbt_lib = library('cnbt', libcnbt_sources, include_directories : [libcnbt_include], override_options : ['c_std=c99'])
libcnbt_dep = declare_dependency(include_directories : [libcnbt_include], link_with : [libcnbt_lib])
