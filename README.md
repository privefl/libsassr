# libsassr

An R package to wrap the LibSass C++ library.

**This is in early stage development.**

## Installation

- Clone this repo
- In a terminal: `git submodule update --init --recursive`
- In a terminal: `make -C inst/include/libsass`
- In R: `devtools::document()`
- In R: `devtools::install()`

## Example

```{r}
library(libsassr)

string <- "a { b { color: blue; } }"
sass_compile_string(string)

write(string, tmp <- tempfile())
sass_compile_file(tmp)

sass_compile_file(tmp, "test.css")

unlink("test.css")
```
