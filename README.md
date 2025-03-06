# Date

Date Example

## Requirements

- git
- gcc == 11.2
- conan == 2.11
- meson == 1.6
- ninja == 1.12.1
- clang-format == 19.1.7
- pip == 24.1.2
- python == 3.12

## Runtime dependencies

See [conanfile](conanfile.txt)

## Build

Install dependencies by conan

```
conan install conanfile.txt --output=build --build=missing
```

> To override build type append 
> `-s build_type=Debug` for debug
> `-s build_type=Release` for release

Configure build

```
meson setup --native-file build/conan_meson_native.ini build
```

Compile

```
meson compile -C build
```

## Run

```
./build/date
```
