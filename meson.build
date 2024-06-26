project('murts-cool-widgets', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3', 'cpp_std=c++20'])

cmake = import('cmake')

gtk = dependency('gtkmm-4.0')
gtk_layer_shell = dependency(
  'gtk4-layer-shell',
  fallback: ['gtk4-layer-shell', 'gtk_layer_shell'],
  default_options: {'introspection':false,'vapi':false}
)
wayland = dependency('wayland-client')
sig = dependency('sigc++-3.0')
json = dependency('nlohmann_json', fallback: 'nlohmann_json')
curl = dependency('libcurl')
libxml = dependency(
  'libxml++',
  default_options: {'build-deprecated-api':false, 'build-examples':false, 'build-tests':false}
)

sdbuscpp_proj_opts = cmake.subproject_options()
sdbuscpp_proj_opts.add_cmake_defines({'SDBUSCPP_BUILD_CODEGEN': true})
sdbuscpp_proj = cmake.subproject('sdbus-cpp', options: sdbuscpp_proj_opts)
sdbuscpp = sdbuscpp_proj.dependency('sdbus-c++')

subdir('src')
subdir('protocol')

incdir = include_directories('include')

mcw_lib = library('murts-cool-widgets', srcs, sdbus_cpp_xml2cpp_src,
  dependencies: [gtk, gtk_layer_shell, wayland, sig, json, curl, libxml, sdbuscpp],
  include_directories: incdir)

mcw = declare_dependency(
  sources: sdbus_cpp_xml2cpp_src,
  link_with: mcw_lib,
  dependencies: [sdbuscpp]
)

subdir('example')
