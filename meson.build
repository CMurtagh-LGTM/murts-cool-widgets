project('murts-cool-widgets', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3'])

subdir('src')

incdir = include_directories('include')

gtk = dependency('gtk4')
gtk_layer_shell = dependency(
  'gtk4-layer-shell',
  fallback: ['gtk4-layer-shell', 'gtk_layer_shell'],
  default_options: ['introspection=false','vapi=false']
)
wayland = dependency('wayland-client')
json = dependency('nlohmann_json', fallback: 'nlohmann_json')

mcw = library('murts-cool-widgets', srcs,
  dependencies: [gtk, gtk_layer_shell, wayland, json],
  include_directories: incdir)

subdir('example')
