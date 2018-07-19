################################################################################

OUTPUT_STYLES = c("compact" = 2, "compressed" = 3, "expanded" = 1, "nested" = 0)

################################################################################

#' Compile Sass source code (from a string)
#'
#' @param string Sass source code (as a string) to compile.
#' @param outfile Path to store resulting CSS. Default is `""` and just prints
#'   in standard output.
#' @param output_style An optional coding style of the compiled result. Choose
#'   one of: `"nested"` (default), `"expanded"`, `"compact"`, `"compressed"`.
#' @param precision Optional precision for numbers. Default is `5`.
#'
#' @export
#'
#' @examples
#' string <- "a { b { color: blue; } }"
#' sass_compile_string(string)
sass_compile_string <- function(string, outfile = "",
                                output_style = "nested",
                                precision = 5) {

  output_style <- match.arg(output_style, names(OUTPUT_STYLES))
  status <- sass_compile_string_rcpp(
    string, outfile,
    OUTPUT_STYLES[output_style], precision
  )
  invisible(status)
}

################################################################################

#' Compile Sass source code (from a file)
#'
#' @inheritParams sass_compile_string
#' @param filename File path containing Sass source code to compile.
#'
#' @export
#'
#' @examples
#' string <- "a { b { color: blue; } }"
#' write(string, tmp <- tempfile())
#' sass_compile_file(paste0(tmp, 1))
sass_compile_file <- function(filename, outfile = "",
                              output_style = "nested",
                              precision = 5) {

  output_style <- match.arg(output_style, names(OUTPUT_STYLES))
  status <- sass_compile_file_rcpp(
    filename, outfile,
    OUTPUT_STYLES[output_style], precision
  )
  invisible(status)
}

################################################################################
