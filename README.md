# gas

+ **author:** Arne (gojira) Simon [arne_simon@gmx.de]

gas is a implementation of neuronal gas.

+ https://en.wikipedia.org/wiki/Neural_gas

## dependencies

+ [logging](https://github.com/gojira83/logging)
+ [yaml-cpp](https://github.com/jbeder/yaml-cpp)

## building

The [ninja](https://ninja-build.org/)  build system is used.
Via default the [clang++]() compiler ist used, if you want to use another compiler
you have to edit the *build.ninja* file by yourself.

```bash
    $ ninja
```
