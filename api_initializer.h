#ifndef API_INITIALIZER_H
#define API_INITIALIZER_H

#include <aws/core/Aws.h>

class API_initializer
{
public:
    API_initializer();
    ~API_initializer();
private:
    Aws::SDKOptions m_options{};
};

#endif // API_INITIALIZER_H
