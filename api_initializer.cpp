#include "api_initializer.h"

API_initializer::API_initializer()
{
    Aws::InitAPI(m_options);
}

API_initializer::~API_initializer()
{
    ShutdownAPI(m_options);
}
