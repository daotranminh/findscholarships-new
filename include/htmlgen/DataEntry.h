#ifndef ___DATA_ENTRY_HPP___
#define ___DATA_ENTRY_HPP___

#include "htmlgen/Title.h"

namespace findscholarships {

class DataEntry
{
public:
    DataEntry(const Title& title,
              const std::string& olink,
              bool is_new = false);
    
    const Title&
    getTitle() const;
    
    bool
    isNew() const;
    
    const std::string&
    getOrigLink() const;
    
private:
    Title m_Title;
    std::string m_OrigLink; // original link where this scholarship is crawled. Just to be on the safe side.
    bool m_IsNew;
};
    
} // namespace findscholarships

#endif // ___DATA_ENTRY_HPP___
