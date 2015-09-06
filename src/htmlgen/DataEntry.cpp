#include "DataEntry.h"  // htmlgen

DataEntry::DataEntry(const Title& title,
                     const std::string& olink,
                     bool is_new /* = false */)
: m_Title(title),
m_OrigLink(olink),
m_IsNew(is_new)
{ }



const Title&
DataEntry::getTitle() const
{
    return m_Title;
}



bool
DataEntry::isNew() const
{
    return m_IsNew;
}



const std::string&
DataEntry::getOrigLink() const
{
    return m_OrigLink;
}
