#ifndef __MEIDA_H__
#define __MEIDA_H__
#include <memory>

#include "utility.h"

class Meida
{
    public:
    Meida();
    ~Meida();

    bool openStream(std::shared_ptr<dt::OpenRealStreamParam> param);
    bool closeStream(std::string callid);
};
#endif