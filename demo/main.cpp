#include "Student.hpp"
#include "Title.hpp"
#include "iostream"

int main(int argc, char** argv)
{
  nlohmann::json data = inputJson(argc, argv);
  std::vector<Student> students = pasrJson(data);
  print(students, std::cout);
}
