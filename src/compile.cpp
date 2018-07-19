/******************************************************************************/

// Adapted from https://github.com/sass/sassc/blob/master/sassc.c

/******************************************************************************/

#include "sass/context.h"
#include <Rcpp.h>

/******************************************************************************/

struct Sass_Options* make_options(int output_style, int precision) {

  struct Sass_Options* options = sass_make_options();

  sass_option_set_output_style(options, (Sass_Output_Style)output_style);
  sass_option_set_precision(options, precision);

  return options;
}

/******************************************************************************/

int output(int error_status,
           const char* error_message,
           const char* output_string,
           const char* outfile) {

  if (error_status) {
    if (error_message) {
      fprintf(stderr, "%s", error_message);
    } else {
      fprintf(stderr, "An error occurred; no error message available.\n");
    }
    return 1;
  } else if (output_string) {
    if(outfile) {
      FILE* fp = fopen(outfile, "wb");
      if(!fp) {
        perror("Error opening output file");
        return 1;
      }
      if(fprintf(fp, "%s", output_string) < 0) {
        perror("Error writing to output file");
        fclose(fp);
        return 1;
      }
      fclose(fp);
    }
    else {
#ifdef _WIN32
      setmode(fileno(stdout), O_BINARY);
#endif
      printf("%s", output_string);
    }
    return 0;
  } else {
    fprintf(stderr, "Unknown internal error.\n");
    return 2;
  }
}

/******************************************************************************/

int compile_string(struct Sass_Options* options,
                   char* source_string,
                   char* outfile) {

  struct Sass_Data_Context* ctx = sass_make_data_context(source_string);
  struct Sass_Context* ctx_out = sass_data_context_get_context(ctx);
  sass_data_context_set_options(ctx, options);
  sass_compile_data_context(ctx);
  int ret = output(
    sass_context_get_error_status(ctx_out),
    sass_context_get_error_message(ctx_out),
    sass_context_get_output_string(ctx_out),
    outfile
  );
  sass_delete_data_context(ctx);
  return ret;
}


// [[Rcpp::export]]
int sass_compile_string_rcpp(std::string string,
                             std::string outfile,
                             int output_style,
                             int precision) {

  // input
  char* source_string = strdup(string.c_str());

  // output (stdout if "")
  char *outfile2;
  if (outfile == "") {
    outfile2 = 0;
  } else {
    outfile2 = strdup(outfile.c_str());
  }

  // options of sass -> need to add more
  struct Sass_Options* options = make_options(output_style, precision);

  // compile
  int status = compile_string(options, source_string, outfile2);

  // cleanup
  sass_delete_options(options);

  return status;
}

/******************************************************************************/

int compile_file(struct Sass_Options* options, char* input_path, char* outfile) {

  struct Sass_File_Context* ctx = sass_make_file_context(input_path);
  struct Sass_Context* ctx_out = sass_file_context_get_context(ctx);
  if (outfile) sass_option_set_output_path(options, outfile);
  const char* srcmap_file = sass_option_get_source_map_file(options);
  sass_option_set_input_path(options, input_path);
  sass_file_context_set_options(ctx, options);

  sass_compile_file_context(ctx);

  int ret = output(
    sass_context_get_error_status(ctx_out),
    sass_context_get_error_message(ctx_out),
    sass_context_get_output_string(ctx_out),
    outfile
  );

  if (ret == 0 && srcmap_file) {
    ret = output(
      sass_context_get_error_status(ctx_out),
      sass_context_get_error_message(ctx_out),
      sass_context_get_source_map_string(ctx_out),
      srcmap_file
    );
  }

  sass_delete_file_context(ctx);
  return ret;
}


// [[Rcpp::export]]
int sass_compile_file_rcpp(std::string filename,
                           std::string outfile = "",
                           int output_style = 0,
                           int precision = 5) {

  // input
  char* input_path = strdup(filename.c_str());

  // output (stdout if "")
  char *outfile2;
  if (outfile == "") {
    outfile2 = 0;
  } else {
    outfile2 = strdup(outfile.c_str());
  }

  // options of sass -> need to add more
  struct Sass_Options* options = make_options(output_style, precision);

  // compile
  int status = compile_file(options, input_path, outfile2);

  // cleanup
  sass_delete_options(options);

  return status;
}

/******************************************************************************/
