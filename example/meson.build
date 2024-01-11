bar_srcs = files(
  'bar.cpp'
)

fs = import('fs')
css_file = fs.copyfile('bar.css', 'bar.css')

executable('bar', bar_srcs, css_file,
  dependencies: [gtk, gtk_layer_shell, mcw],
  include_directories: incdir)
