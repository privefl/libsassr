string <- "a { b { color: blue; } }"
# x <- libsassr:::sass_compile_string(string)

tmp <- tempfile()
write(string, tmp)
libsassr:::sass_compile_file(tmp)

# y <- utf8::as_utf8(x)
# utf8::utf8_valid(y)
# utf8::utf8_format(y)
# utf8::utf8_normalize(y)
# utf8::utf8_print(y)
# rawToChar(as.raw(utf8ToInt(x)))
# charToRaw(xx <- iconv(x, "latin1", "UTF-8"))
# iconv(x, "UTF-8", "ISO_8859-2")
# iconv(x, "UTF-8", "LATIN2")
# iconv(x, "latin1", "UTF-8")
