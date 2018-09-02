#include <cwalk.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

int relative_check()
{
  const char *relative_paths[] = {"..", "test", "test/test", "../another_test",
    "./simple", ".././simple"};
  const char *absolute_paths[] = {"/", "/test", "/../test/", "/../another_test",
    "/./simple", "/.././simple"};
  int i;

  cwk_path_set_style(CWK_STYLE_UNIX);

  for (i = 0; i < ARRAY_SIZE(relative_paths); ++i) {
    if (!cwk_path_is_relative(relative_paths[i])) {
      return EXIT_FAILURE;
    }
  }

  for (i = 0; i < ARRAY_SIZE(absolute_paths); ++i) {
    if (cwk_path_is_relative(absolute_paths[i])) {
      return EXIT_FAILURE;
    }
  }

  return EXIT_SUCCESS;
}

int relative_equal()
{
  char result[FILENAME_MAX];
  size_t length;

  cwk_path_set_style(CWK_STYLE_UNIX);

  length = cwk_path_get_relative("/path/same", "/path/same",
    result, sizeof(result));
  if(length != 1) {
    return EXIT_FAILURE;
  }

  if(strcmp(result, ".") != 0){
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

int relative_long_target()
{
  char result[FILENAME_MAX];
  size_t length;

  cwk_path_set_style(CWK_STYLE_UNIX);

  length = cwk_path_get_relative("/path/long/one", "/path/long/one/two",
    result, sizeof(result));
  if(length != 3) {
    return EXIT_FAILURE;
  }

  if(strcmp(result, "two") != 0){
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

int relative_long_base()
{
  char result[FILENAME_MAX];
  size_t length;

  cwk_path_set_style(CWK_STYLE_UNIX);

  length = cwk_path_get_relative("/path/long/one/two", "/path/long/one",
    result, sizeof(result));
  if(length != 2) {
    return EXIT_FAILURE;
  }

  if(strcmp(result, "..") != 0){
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

int relative_relative()
{
  char result[FILENAME_MAX];
  size_t length;

  cwk_path_set_style(CWK_STYLE_UNIX);

  length = cwk_path_get_relative("./this/is/path_one", "./this/is/path_two",
    result, sizeof(result));
  if(length != 11) {
    return EXIT_FAILURE;
  }

  if(strcmp(result, "../path_two") != 0){
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

int relative_simple()
{
  char result[FILENAME_MAX];
  size_t length;

  cwk_path_set_style(CWK_STYLE_UNIX);

  length = cwk_path_get_relative("/this/is/path_one", "/this/is/path_two",
    result, sizeof(result));
  if(length != 11) {
    return EXIT_FAILURE;
  }

  if(strcmp(result, "../path_two") != 0){
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}