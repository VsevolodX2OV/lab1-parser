//Copyright 2021 by Winter Solider


#ifndef INCLUDE_STUDENT_HPP_
#define INCLUDE_STUDENT_HPP_

#include <string>
#include <vector>

#include "Title.hpp"
using nlohmann::json;

struct Student {
 public:
  Student();
  Student(std::string _name, std::any _group, std::any _avg, std::any debt);
  bool operator==(Student const & student) const;
  std::string name;
  std::any group;
  std::any avg;
  std::any debt;
};


void print(Student& student, std::ostream& os);


void print(std::string s1, std::string s2, std::string s3,
           std::string s4, std::ostream& os);


void print(std::vector<Student>& students, std::ostream& os);


void parse_JSON(const json& j, Student& s);


std::vector<Student> pasrJson(json& data);
#endif  //INCLUDE_STUDENT_HPP_
