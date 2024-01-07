project('murts-cool-widgets', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3'])

subdir('src')

incdir = include_directories('include')

gtk = dependency('gtkmm-3.0')
gtk_layer_shell = dependency('gtk-layer-shell-0')

mcw = library('murts-cool-widgets', srcs,
  dependencies: [gtk, gtk_layer_shell],
  include_directories: incdir)

subdir('example')
