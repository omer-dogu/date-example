project('date', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3',
                     'cpp_std=c++17'])

date_sources =[
  'src/main.cpp'
]

exe = executable('date', date_sources,
  include_directories : 'include',
  install : true)

test('basic', exe)
