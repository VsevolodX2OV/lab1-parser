//Copyright 2021 by Winter Solider

#include "Student.hpp"
#include <iomanip>
#include <utility>

auto get_name(const json& j) -> std::string;
auto get_debt(const json& j) -> std::any;
auto get_avg(const json& j) -> std::any;
auto get_group(const json& j) -> std::any;

Student::Student(std::string _name, std::any _group, std::any _avg, std::any _debt) {
  name = std::move(_name);
  group = std::move(_group);
  avg = std::move(_avg);
  debt = std::move(_debt);
}

bool anyDate(std::any a1, std::any a2)
{
  if (a1.type() != a2.type())
    return false;
  if (a1.type() == typeid(std::string))
    return std::any_cast<std::string>(a1)== std::any_cast<std::string>(a2);
  if (a1.type() == typeid(nullptr))
    return true;
  if (a1.type() == typeid(double))
    return std::any_cast<double>(a1) == std::any_cast<double>(a2);
  if (a1.type() == typeid(size_t))
   return std::any_cast<size_t>(a1) == std::any_cast<size_t>(a2);
  if (a1.type() == typeid(std::vector<std::string>))
    return
        std::any_cast<std::vector<std::string>>(a1)
           == std::any_cast<std::vector<std::string>>(a2);
  return false;
}

bool Student::operator==(const Student& student) const
{
      bool n =  name == student.name;
      bool g = anyDate(group, student.group);
      bool a = anyDate(avg, student.avg);
      bool d = anyDate(debt, student.debt);
      return n && g && a && d;
}

void parse_JSON(const json& j, Student& s) {
  s.name = get_name(j.at("name"));
  s.group = get_group(j.at("group"));
  s.avg = get_avg(j.at("avg"));
  s.debt = get_debt(j.at("debt"));
}
