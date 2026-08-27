# learning-opengl

## Build Targets

* 01_hello_window
* 02_shader
* 03_program
* 04_context
* 05_hello_triangle
* 06_buffer
* 07_texture
* 08_transformation
* 09_camera
* 10_interactive_camera
* 11_imgui

## Configure

```shell
cmake -B build
```

## Build all

```shell
cmake --build build
```

## Build target

```shell
cmake --build build --target <TARGET_NAME>
```

## Executable path

### GNU

```shell
build/bin/<TARGET_NAME>
```

### MSVC

```shell
build/bin/<BUILD_TYPE>/<TARGET_NAME>
```
