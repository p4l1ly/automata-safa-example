cmake_minimum_required(VERSION 3.16)

project(
  automata-safa-example
  VERSION 0.1.0
  DESCRIPTION "Example of use and installation of automata-safa-capnp"
  LANGUAGES CXX
)

find_package(CapnProto REQUIRED)
find_library(AutomataSafaCapnp automata-safa-capnp REQUIRED)
find_path(AutomataSafaCapnpInclude automata-safa-capnp REQUIRED)

add_executable(
  automata-safa-example
  main.c++
)
target_include_directories(
  automata-safa-example
  PRIVATE "${AutomataSafaCapnpInclude}"
)
target_link_libraries(
  automata-safa-example
  PRIVATE CapnProto::capnp CapnProto::capnp-rpc "${AutomataSafaCapnp}"
)
set_property(TARGET automata-safa-example PROPERTY CXX_STANDARD 20)
