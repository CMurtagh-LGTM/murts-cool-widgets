sdbus_cpp_xml2cpp = sdbuscpp_proj.target('sdbus_c++_xml2cpp')

sdbus_cpp_xml2cpp_gen = generator(
  sdbus_cpp_xml2cpp,
  output : '@BASENAME@.hpp',
  arguments : ['@INPUT@', '--proxy=@OUTPUT@']
)

sdbus_cpp_xml2cpp_src = sdbus_cpp_xml2cpp_gen.process('org.mpris.MediaPlayer2.xml')
