project('ufjfmltk_cli', 'cpp',
  version : '1.0',
  default_options : ['warning_level=0', 'cpp_std=c++17'])

cpp_compiler = meson.get_compiler('cpp')
ufjfmltk = cpp_compiler.find_library('ufjfmltk', required:false)

if not ufjfmltk.found() # Method from object called
   ufjfmltk = dependency('ufjfmltk')
endif

executable('ufjfmltk_cli', 'main.cpp',
           dependencies : ufjfmltk
           )
