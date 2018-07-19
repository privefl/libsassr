string <- "a { b { color: blue; } }"
libsassr:::sass_compile_string(string)
libsassr:::sass_compile_string(string, "test.txt")
unlink("test.txt")

libsassr:::sass_compile_file("inst/testdata/_cayman.scss")
libsassr:::sass_compile_string(string, "test.txt")
unlink("test.txt")

