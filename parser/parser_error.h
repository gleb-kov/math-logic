#ifndef MATLOG_PARSER_ERROR_H
#define MATLOG_PARSER_ERROR_H

#include <stdexcept>

class parser_error : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
    using std::runtime_error::what;
};

#endif //MATLOG_PARSER_ERROR_H
