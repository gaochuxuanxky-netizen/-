#pragma once

#include "model/User.h"

class UserDao
{
public:
    User load();
    bool save(const User &user);
};
