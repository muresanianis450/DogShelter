//
// Created by mures on 3/23/2025.
//
#include <iostream>
#include <string>
#pragma once
#ifndef DOG_H
#define DOG_H




class Dog {
    private:
  int age;
  std::string name;
  std::string breed;
  std::string photography; //variable to store the link to an online source


    public:
      Dog(); //default constructor
  Dog(const std::string &name, const std::string &breed, int age, const std::string &photography);
  ~Dog(); //destructor
      Dog(const Dog &d); //copy constructor

    //setter methods
      void setAge(int age);
      void setName(const std::string &name);
      void setBreed(const std::string &breed);
        void setPhotography(const std::string &photography);

    //getter methods
    int getAge() const;
    const std::string &getName() const;
    const std::string &getBreed() const;
    const std::string &getPhotography() const;
    bool operator==(const Dog& d) const;
    // Friend declarations for input and output operators
    friend std::istream& operator>>(std::istream& is, Dog& dog);
    friend std::ostream& operator<<(std::ostream& os, const Dog& dog);

};



#endif //DOG_H
