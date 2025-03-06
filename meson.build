project('date', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3',
                     'cpp_std=c++17'])
inc = include_directories('include')
date_sources =[
  'src/main.cpp', 'src/date.cpp'
]

exe = executable('date', date_sources,
  include_directories : inc,
  install : true)

test('basic', exe)
