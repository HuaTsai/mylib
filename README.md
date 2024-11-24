# mylib

- Tool ccmake: `sudo apt install cmake-curses-gui`
- After install the debian file, developer can use the package library via cmake

  ```cmake
  find_package(mylib REQUIRED)
  message(STATUS "MYLIB_INCLUDE_DIRS: ${MYLIB_INCLUDE_DIRS}")
  message(STATUS "MYLIB_INCLUDE_DIRS: ${MYLIB_LIBRARIES}")
  add_executable(main main.cc)
  target_link_libraries(main mylib::mylib)
  ```

