project('similarity-search-engine', 'cpp',
    version: '1.0',
    default_options : ['warning_level=3', 'cpp_std=c++17']
)

inc_dir = include_directories('include')

src_files = [
    'src/main.cpp',
    'src/etl.cpp',
    'src/engine.cpp'
]

executable('search-engine',
    sources : src_files,
    include_directories : inc_dir
)