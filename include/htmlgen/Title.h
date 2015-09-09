#ifndef ___TITLE_HPP___
#define ___TITLE_HPP___

#include <string>
#include "utilities/DateType.h"

namespace findscholarships {

class Title
{
public:
    enum TitleClassification
    {
        UnderGrad,
        Master,
        PhD,
        PostDoc,
        AcademicJob,
        Unclassified
    };
    
    Title();
    
    Title(const std::string& t);
    
    Title(const Title& other_title);
    
    bool
    operator==(const Title& other_title) const;
    
    TitleClassification
    classification() const;
    
    std::string
    strCategory() const;
    
    std::size_t
    classifiedIndex() const;
    
    std::string
    getClassfiedSubDir() const;
    
    std::string
    getTitle() const;
    
    std::string
    getHtmlTitle() const;
    
    std::string
    getHeadLineTitle() const;
    
    std::string
    getTitleNoSpace() const;
    
    std::string
    getFilename(const DatePtr deadline) const;
    
    std::string
    getFileLocation(const DatePtr deadline) const;
    
    std::string
    getHtmlLink(const DatePtr deadline) const;
    
    std::string
    getSingleLineNotification(const DatePtr deadline) const;
    
    std::string
    getMultipleLineNotification(const DatePtr deadline) const;
    
private:
    std::string
    getNotification(const DatePtr deadline,
                    const std::string &delim) const;
    
    std::string
    getLink(const DatePtr deadline) const;
    
private:
    std::string m_Title;
};
    
} // namespace findscholarships

#endif // ___TITLE_HPP___
