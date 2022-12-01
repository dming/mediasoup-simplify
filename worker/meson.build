project(
  'mediasoup-worker',
  ['c', 'cpp'],
  default_options : [
    'warning_level=1',
    'cpp_std=c++11',
    'default_library=static',
  ],
  meson_version: '>= 0.58',
)

cpp_args = [
  host_machine.endian() == 'little' ? '-DMS_LITTLE_ENDIAN' : '-DMS_BIG_ENDIAN',
]

if host_machine.system() == 'windows'
  cpp_args += [
    '-DNOMINMAX', # Don't define min and max macros (windows.h)
    # Don't bloat namespace with incompatible winsock versions.
    '-DWIN32_LEAN_AND_MEAN',
    # Don't warn about usage of insecure C functions.
    '-D_CRT_SECURE_NO_WARNINGS',
    '-D_SCL_SECURE_NO_WARNINGS',
    # Introduced in VS 2017 15.8, allow overaligned types in aligned_storage.
    '-D_ENABLE_EXTENDED_ALIGNED_STORAGE',
  ]
endif

if get_option('ms_log_trace')
  cpp_args += [
    '-DMS_LOG_TRACE',
  ]
endif

if get_option('ms_log_file_line')
  cpp_args += [
    '-DMS_LOG_FILE_LINE',
  ]
endif

common_sources = [
  'src/lib.cpp',
  'src/DepLibUV.cpp',
  'src/Logger.cpp',
  'src/MediaSoupErrors.cpp',
  'src/Settings.cpp',
  'src/Worker.cpp',
  'src/Utils/File.cpp',
  'src/Utils/IP.cpp',
  'src/Utils/String.cpp',
  'src/handles/SignalsHandler.cpp',
  'src/handles/TcpConnectionHandler.cpp',
  'src/handles/TcpServerHandler.cpp',
  'src/handles/Timer.cpp',
  'src/handles/UdpSocketHandler.cpp',
  'src/handles/UnixStreamSocket.cpp',
  'src/Channel/ChannelNotifier.cpp',
  'src/Channel/ChannelRequest.cpp',
  'src/Channel/ChannelSocket.cpp',
  'src/PayloadChannel/Notification.cpp',
  'src/PayloadChannel/PayloadChannelNotifier.cpp',
  'src/PayloadChannel/PayloadChannelRequest.cpp',
  'src/PayloadChannel/PayloadChannelSocket.cpp',
]

cpp = meson.get_compiler('cpp')

nlohmann_json_proj = subproject(
  'nlohmann_json',
  default_options: [
    'warning_level=0',
  ],
)

libuv_proj = subproject(
  'libuv',
  default_options: [
    'warning_level=0',
    'build_tests=false',
    'build_benchmarks=false',
  ],
)

abseil_cpp_proj = subproject(
  'abseil-cpp',
  default_options: [
    'warning_level=0',
  ],
)


dependencies = [
  abseil_cpp_proj.get_variable('absl_container_dep'),
  nlohmann_json_proj.get_variable('nlohmann_json_dep'),
  libuv_proj.get_variable('libuv_dep'),
]

link_whole = [
  abseil_cpp_proj.get_variable('absl_container_lib'),
  libuv_proj.get_variable('libuv'),
]

if host_machine.system() == 'windows'
  wingetopt_proj = subproject(
    'wingetopt',
    default_options: [
      'warning_level=0',
    ],
  )

  dependencies += [
    wingetopt_proj.get_variable('wingetopt_dep'),
  ]
  link_whole += [
    wingetopt_proj.get_variable('wingetopt_lib'),
  ]
endif

libmediasoup_worker = library(
  'libmediasoup-worker',
  name_prefix: '',
  build_by_default: false,
  install: true,
  install_tag: 'libmediasoup-worker',
  dependencies: dependencies,
  sources: common_sources,
  include_directories: include_directories('include'),
  cpp_args: cpp_args,
  link_whole: link_whole,
)

executable(
  'mediasoup-worker',
  build_by_default: true,
  install: true,
  install_tag: 'mediasoup-worker',
  dependencies: dependencies,
  sources: common_sources + ['src/main.cpp'],
  include_directories: include_directories('include'),
  cpp_args: cpp_args + ['-DMS_EXECUTABLE'],
)