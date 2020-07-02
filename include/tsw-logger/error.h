/**
  * @file error.h
  * @author Artiom N.(cl)2017
  * @brief Exception class definition, assert's defines and other error-dealing stuff.
  *
  */

#pragma once

#include <cassert>
#include <exception>
#include <string>
#include <typeinfo>

// Thanks to Alexey Konovalov.
#include <boost/current_function.hpp>

#include <boost/exception/all.hpp>


#ifndef NDEBUG
#   define TSW_ASSERT(expression) assert(expression)
#else
#   define TSW_ASSERT(expression) (void)(expression)
#endif

#define TSW_THROW(E, ...) BOOST_THROW_EXCEPTION(E(__VA_ARGS__))
#define TSW_THROW_EXCEPTION(...) BOOST_THROW_EXCEPTION(tsw::Exception(__VA_ARGS__))


namespace tsw
{

class Exception : public std::runtime_error, public boost::exception
{
public:
    //Exception(const char* file, const int line, const char *function, const char *message) {}
    //Exception(const char *format, ...) : boost::exception(), std::runtime_error(message) {}
    Exception(const char *message) : boost::exception(), std::runtime_error(message) {}
    Exception(const std::string &message) : boost::exception(), std::runtime_error(message) {}
    virtual ~Exception() {}

};

}

