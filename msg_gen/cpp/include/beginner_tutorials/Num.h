/* Auto-generated by genmsg_cpp for file /home/ypane/indigo_workspace/sandbox/beginner_tutorials/msg/Num.msg */
#ifndef BEGINNER_TUTORIALS_MESSAGE_NUM_H
#define BEGINNER_TUTORIALS_MESSAGE_NUM_H
#include <string>
#include <vector>
#include <map>
#include <ostream>
#include "ros/serialization.h"
#include "ros/builtin_message_traits.h"
#include "ros/message_operations.h"
#include "ros/time.h"

#include "ros/macros.h"

#include "ros/assert.h"


namespace beginner_tutorials
{
template <class ContainerAllocator>
struct Num_ {
  typedef Num_<ContainerAllocator> Type;

  Num_()
  : num(0)
  , first_name()
  , last_name()
  , age(0)
  , score(0)
  {
  }

  Num_(const ContainerAllocator& _alloc)
  : num(0)
  , first_name(_alloc)
  , last_name(_alloc)
  , age(0)
  , score(0)
  {
  }

  typedef int64_t _num_type;
  int64_t num;

  typedef std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  _first_name_type;
  std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  first_name;

  typedef std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  _last_name_type;
  std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  last_name;

  typedef uint8_t _age_type;
  uint8_t age;

  typedef uint32_t _score_type;
  uint32_t score;


  typedef boost::shared_ptr< ::beginner_tutorials::Num_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::beginner_tutorials::Num_<ContainerAllocator>  const> ConstPtr;
}; // struct Num
typedef  ::beginner_tutorials::Num_<std::allocator<void> > Num;

typedef boost::shared_ptr< ::beginner_tutorials::Num> NumPtr;
typedef boost::shared_ptr< ::beginner_tutorials::Num const> NumConstPtr;


template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const  ::beginner_tutorials::Num_<ContainerAllocator> & v)
{
  ros::message_operations::Printer< ::beginner_tutorials::Num_<ContainerAllocator> >::stream(s, "", v);
  return s;}

} // namespace beginner_tutorials

namespace ros
{
namespace message_traits
{
template<class ContainerAllocator> struct IsMessage< ::beginner_tutorials::Num_<ContainerAllocator> > : public TrueType {};
template<class ContainerAllocator> struct IsMessage< ::beginner_tutorials::Num_<ContainerAllocator>  const> : public TrueType {};
template<class ContainerAllocator>
struct MD5Sum< ::beginner_tutorials::Num_<ContainerAllocator> > {
  static const char* value() 
  {
    return "379cbe21d44c48c3d9a5a30aa0ddaafb";
  }

  static const char* value(const  ::beginner_tutorials::Num_<ContainerAllocator> &) { return value(); } 
  static const uint64_t static_value1 = 0x379cbe21d44c48c3ULL;
  static const uint64_t static_value2 = 0xd9a5a30aa0ddaafbULL;
};

template<class ContainerAllocator>
struct DataType< ::beginner_tutorials::Num_<ContainerAllocator> > {
  static const char* value() 
  {
    return "beginner_tutorials/Num";
  }

  static const char* value(const  ::beginner_tutorials::Num_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct Definition< ::beginner_tutorials::Num_<ContainerAllocator> > {
  static const char* value() 
  {
    return "int64 num\n\
string first_name\n\
string last_name\n\
uint8 age\n\
uint32 score\n\
\n\
";
  }

  static const char* value(const  ::beginner_tutorials::Num_<ContainerAllocator> &) { return value(); } 
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

template<class ContainerAllocator> struct Serializer< ::beginner_tutorials::Num_<ContainerAllocator> >
{
  template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
  {
    stream.next(m.num);
    stream.next(m.first_name);
    stream.next(m.last_name);
    stream.next(m.age);
    stream.next(m.score);
  }

  ROS_DECLARE_ALLINONE_SERIALIZER;
}; // struct Num_
} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::beginner_tutorials::Num_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const  ::beginner_tutorials::Num_<ContainerAllocator> & v) 
  {
    s << indent << "num: ";
    Printer<int64_t>::stream(s, indent + "  ", v.num);
    s << indent << "first_name: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::stream(s, indent + "  ", v.first_name);
    s << indent << "last_name: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::stream(s, indent + "  ", v.last_name);
    s << indent << "age: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.age);
    s << indent << "score: ";
    Printer<uint32_t>::stream(s, indent + "  ", v.score);
  }
};


} // namespace message_operations
} // namespace ros

#endif // BEGINNER_TUTORIALS_MESSAGE_NUM_H

