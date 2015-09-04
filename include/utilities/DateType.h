#ifndef __DATE_TYPE_HPP__
#define __DATE_TYPE_HPP__

//#include <boost/shared_ptr.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>

typedef boost::gregorian::date Date_t;
//for C++11
typedef std::shared_ptr<Date_t> DatePtr;
//typedef boost::shared_ptr<Date_t> DatePtr;

#endif // __DATE_TYPE_HPP__
