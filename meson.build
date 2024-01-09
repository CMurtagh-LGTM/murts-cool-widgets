project('murts-cool-widgets', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3'])

subdir('src')

incdir = include_directories('include')

gtk = dependency('gtkmm-4.0')
gtk_layer_shell = dependency(
  'gtk4-layer-shell',
  fallback: ['gtk4-layer-shell', 'gtk_layer_shell'],
  default_options: ['introspection=false','vapi=false']
)
wayland = dependency('wayland-client')
sig = dependency('sigc++-3.0')

json = dependency('nlohmann_json', fallback: 'nlohmann_json')

mcw = library('murts-cool-widgets', srcs,
  dependencies: [gtk, gtk_layer_shell, wayland, sig, json],
  include_directories: incdir)

subdir('example')
