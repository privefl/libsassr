#include "sass/context.h"
#include <Rcpp.h>
using namespace Rcpp;

// [[Rcpp::export]]
int sass_compile_string(std::string str) {

  // https://stackoverflow.com/a/7352642/6103040
  char* chr = strdup(str.c_str());
  struct Sass_Data_Context* ctx = sass_make_data_context(chr);
  free(chr);
  return sass_compile_data_context(ctx);;
}
