#include <iostream>
#include "willhabentracker/DataItem.hpp"

namespace willhabentracker {

DataItem:: DataItem(const std::string &url,
                    const std::string &title,
                    const std::string &description,
                    const float &price)
: m_IsNew(false),
m_URL(url),
m_Title(title),
m_Description(description),
m_Price(price)
{ }



std::ostream&
operator<<(std::ostream &os, const DataItem &di)
{
    os << di.m_Title << std::endl << std::endl
    << di.m_URL << std::endl << std::endl
    << "Price: " << di.m_Price << std::endl << std::endl
    << di.m_Description;
    
    return os;
}



bool
DataItem::operator==(const DataItem &other)
{
    return (m_URL == other.m_URL &&
            m_Title == other.m_Title &&
            m_Description == other.m_Description &&
            m_Price == other.m_Price);
}

} // namespace willhabentracker