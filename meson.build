project('libs', 'c',
  default_options: ['c_std=c99', 'warning_level=3'],
  license: 'Apache-2.0',
  version: '0.1.0')

foreach example : ['buffer', 'vec']
  executable(example, 'examples/' + example + '.c',
    include_directories: '.')
endforeach
