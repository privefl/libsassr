#include "sass/context.h"
#include <Rcpp.h>
using namespace Rcpp;

// [[Rcpp::export]]
std::string sass_compile_string(std::string str,
                                int output_style = 0,
                                int precision = 5,
                                bool source_comments = false,
                                bool is_indented_syntax_src = false,
                                bool source_map_contents = false,
                                bool source_map_embed = false,
                                bool omit_source_map_url = true) {

  Rcout << str << std::endl;

  struct Sass_Data_Context* data_ctx;
  struct Sass_Context* ctx;


  // https://stackoverflow.com/a/7352642/6103040
  Rcout << "OK1" << std::endl;
  char* chr = strdup(str.c_str());

  Rcout << chr << std::endl;

  Rcout << "OK3" << std::endl;
  data_ctx = sass_make_data_context(chr);
  Rcout << "OK3" << std::endl;
  // struct Sass_Options* ctx_opt = sass_context_get_options(ctx);

  for (int i = 0; i < 1e15; i++);

  // transform input
  Sass_Output_Style sass_output_style = (Sass_Output_Style)output_style;

  struct Sass_Options* ctx_opt = sass_context_get_options(ctx);

  // configure context
  if (precision > -1) {
    // if we set a precision libsass will use that blindly, with
    // 0 being a valid precision - i.e. the precision of "integer"
    sass_option_set_precision(ctx_opt, precision);
  }
  sass_option_set_output_style(ctx_opt, sass_output_style);
  sass_option_set_source_comments(ctx_opt, source_comments);
  sass_option_set_source_map_embed(ctx_opt, source_map_embed);
  sass_option_set_source_map_contents(ctx_opt, source_map_contents);
  sass_option_set_omit_source_map_url(ctx_opt, omit_source_map_url);
  sass_option_set_is_indented_syntax_src(ctx_opt, is_indented_syntax_src);
  // sass_option_set_indent(ctx_opt, indent);
  // sass_option_set_linefeed(ctx_opt, linefeed);
  // sass_option_set_input_path(ctx_opt, input_path);
  // sass_option_set_output_path(ctx_opt, output_path);
  // sass_option_set_include_path(ctx_opt, include_paths);
  // sass_option_set_source_map_file(ctx_opt, source_map_file);
  // sass_option_set_source_map_root(ctx_opt, source_map_root);

  Rcout << "OK4" << std::endl;
  int status = sass_compile_data_context(data_ctx);


  // Rcout << chr << std::endl;

  Rcout << "OK5" << std::endl;
  sass_delete_data_context(data_ctx);
  // sass_delete_context(ctx);
  Rcout << "OK6" << std::endl;
  ctx = sass_data_context_get_context(data_ctx);
  std::string res = chr;
  Rcout << "OK7" << std::endl;
  // free(chr);
  Rcout << "OK8" << std::endl;
  return res;
}


// [[Rcpp::export]]
void sass_compile_file(std::string filename) {

  struct Sass_File_Context* file_ctx;
  struct Sass_Context* ctx;


  // https://stackoverflow.com/a/7352642/6103040
  Rcout << "OK1" << std::endl;
  const char* chr = filename.c_str();

  Rcout << chr << std::endl;

  Rcout << "OK3" << std::endl;
  file_ctx = sass_make_file_context(chr);
  Rcout << "OK3" << std::endl;
  int status = sass_compile_file_context(file_ctx);

  Rcout << "OK5" << std::endl;
  sass_delete_file_context(file_ctx);
  // sass_delete_context(ctx);
  Rcout << "OK7" << std::endl;
  // free(chr);
  Rcout << "OK8" << std::endl;
}
