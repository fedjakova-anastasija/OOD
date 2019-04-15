#pragma once
#include <string>

const std::string IMAGE = "image.png";
const std::string HTML_FILE = "test.html";
const std::string PATH = boost::filesystem::current_path().string() + "/";

const std::string IMAGE_PATH = PATH + IMAGE;
const std::string FILE_PATH = PATH + HTML_FILE;