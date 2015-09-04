#include "ParserSax.h"

void htmlcxx::HTML::ParserSax::parse(const std::string &html)
{
    parse(html.c_str(), html.c_str() + html.length());
}
