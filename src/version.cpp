#include "sass/version.h"
#include <Rcpp.h>
using namespace Rcpp;


// [[Rcpp::export]]
std::string version() {
  return LIBSASS_LANGUAGE_VERSION;
}


/*** R
version()
*/
