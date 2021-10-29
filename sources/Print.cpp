//Copyright 2021 by Winter Solider

#include "Student.hpp"
#include <iomanip>

std::string toString(std::any& item);

void print(std::string s1, std::string s2,
           std::string s3, std::string s4, std::ostream& os)
{
  os << "| " << std::setw(20) << std::left << s1 << "| "
     <<  std::setw(10) << std::left << s2 << "| "
     <<  std::setw(10) << std::left << s3 << "| "
     <<  std::setw(10) << std::left << s4 << "|\n"
     << "|---------------------|-----------|-----------|-----------|\n";
}

void print(Student& student, std::ostream& os)
{
  print(student.name, toString(student.group), toString(student.avg),
        toString(student.debt), os);
}


void print(std::vector<Student>& students, std::ostream& os)
{
  print("name", "group", "avg", "debt", os);
  for (Student& student : students) {
    print(student, os);
  }
}
