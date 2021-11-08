//Copyright 2021 by Winter Solider
#define TEST_CPP_
#ifdef TEST_CPP_

#include <gtest/gtest.h>
#include <Student.hpp>
#include "Title.hpp"

#ifndef _JSON_DIR
#define JSON_DIR "nobody"
#else
#define JSON_DIR _JSON_DIR
#endif


TEST(printTest, StudentItem)
{
  std::stringstream ss;
  Student s("test", (std::string)"test", (size_t)3, std::vector<std::string>());
  print(s, ss);
  ASSERT_EQ("| test                | test      | 3         | 0         |\n"
      "|---------------------|-----------|-----------|-----------|\n",  ss.str());
}
TEST(printTest, StudentsArray) {
    std::stringstream ss;
    std::vector<Student> students;
    students.emplace_back("test", (std::string)"test",
                          (size_t)3, std::vector<std::string>());
    students.emplace_back("test", (size_t)4,
                          (double)3.33, std::vector<std::string>());
    print(students, ss);
    ASSERT_EQ("| name                | group     | avg       | debt      |\n"
        "|---------------------|-----------|-----------|-----------|\n"
        "| test                | test      | 3         | 0         |\n"
        "|---------------------|-----------|-----------|-----------|\n"
        "| test                | 4         | 3.33      | 0         |\n"
        "|---------------------|-----------|-----------|-----------|\n",  ss.str());
}
TEST(printTest, json)
{
  std::string jsonData = "{\n"
      "  \"items\": [\n"
      "    {\n"
      "      \"name\": \"Vsevolod Ovchinnikov\",\n"
      "      \"group\": \"UI2-32\",\n"
      "      \"avg\": \"10.05\",\n"
      "      \"debt\": null\n"
      "    },\n"
      "    {\n"
      "      \"name\": \"Last Guardian\",\n"
      "      \"group\": 99,\n"
      "      \"avg\": 99.99,\n"
      "      \"debt\": \"all\"\n"
      "    }\n"
      "  ],\n"
      "  \"_meta\": {\n"
      "    \"count\": 2\n"
      "  }\n"
      "}";
  nlohmann::json _json = json::parse(jsonData);
  std::vector<Student> students_parsed = pasrJson(_json);
  std::stringstream ss;
  print(students_parsed, ss);
  ASSERT_EQ("| name                | group     | avg       | debt      |\n"
      "|---------------------|-----------|-----------|-----------|\n"
      "| Vsevolod Ovchinnikov| UI2-32    | 10.05     | null      |\n"
      "|---------------------|-----------|-----------|-----------|\n"
      "| Last Guardian       | 99        | 99.99     | all       |\n"
      "|---------------------|-----------|-----------|-----------|\n", ss.str());
}

TEST(parseTest, jsonParse)
{
  std::string jsonData = "{\n"
      "  \"items\": [\n"
      "    {\n"
      "      \"name\": \"Vsevolod Ovchinnikov\",\n"
      "      \"group\": \"UI2-32\",\n"
      "      \"avg\": \"10.05\",\n"
      "      \"debt\": null\n"
      "    },\n"
      "    {\n"
      "      \"name\": \"Last Guardian\",\n"
      "      \"group\": 99,\n"
      "      \"avg\": 99.99,\n"
      "      \"debt\": \"all\"\n"
      "    }\n"
      "  ],\n"
      "  \"_meta\": {\n"
      "    \"count\": 2\n"
      "  }\n"
      "}";
    nlohmann::json _json = json::parse(jsonData);
    std::vector<Student> students_parsed = pasrJson(_json);
    std::vector<Student> student_inited = {
        Student("Vsevolod Ovchinnikov", (std::string)"UI2-32",
                (std::string)"10.05", nullptr),
        Student("Last Guardian", (size_t)99,
                (double)99.99, (std::string)"all")
    };
    ASSERT_EQ(student_inited, students_parsed);
}
TEST(parseTest, fromFile)
{
  std::string jsonData = "{\n"
      "  \"items\": [\n"
      "    {\n"
      "      \"name\": \"Vsevolod Ovchinnikov\",\n"
      "      \"group\": \"32\",\n"
      "      \"avg\": \"10.05\",\n"
      "      \"debt\":  [\n"
      "        \"Bash\",\n"
      "        \"Rust\",\n"
      "        \"Mac\"\n"
      "      ]\n"
      "    },\n"
      "    {\n"
      "      \"name\": \"Last Guardian\",\n"
      "      \"group\": 99,\n"
      "      \"avg\": 99.99,\n"
      "      \"debt\": \"all\"\n"
      "    }\n"
      "  ],\n"
      "  \"_meta\": {\n"
      "    \"count\": 2\n"
      "  }\n"
      "}";
  nlohmann::json json1 = json::parse(jsonData);
  std::string path = JSON_DIR;
  path+="/test1.json";
  char* argv[] ={(char*)"", (char*)(path.c_str())};
  nlohmann::json json2 = inputJson(2, argv);
  ASSERT_EQ(json1, json2) << "Test passed!";
}

TEST(errorCheck, lessArgsTest)
{
  try {
    std::string path = JSON_DIR;
    path+="/test1.json";
    char* argv[] ={(char*)"", (char*)(path.c_str())};
    nlohmann::json json2 = inputJson(1, argv);
    FAIL() << "Expected: The file path was not passed";
  }
  catch(std::runtime_error const & err) {
    EXPECT_EQ(err.what(),std::string("The file path was not passed"));
  }
  catch(...) {
    FAIL() << "Expected The file path was not passed";
  }
}

TEST(errorCheck, _metaCheck)
{
  try {
    std::string path = JSON_DIR;
    path+="/test2.json";
    char* argv[] ={(char*)"", (char*)(path.c_str())};
    nlohmann::json json2 = inputJson(2, argv);
    FAIL() << "Expected: _meta value does not match the array size";
  }
  catch(std::runtime_error const & err) {
    EXPECT_EQ(err.what(),std::string("_meta value does not match the array size"));
  }
  catch(...) {
    FAIL() << "Expected: _meta value does not match the array size";
  }
}
#endif // TEST_CPP_