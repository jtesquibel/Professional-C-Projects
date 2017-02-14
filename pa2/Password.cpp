//
//  Password.cpp
//  password-mac
//
//  Created by Jonathan Esquibel on 2/6/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#include "Password.hpp"

Password::Password(int entry, std::string h, std::string sol)
{
    this->row = entry;
    this->hash = h;
    this->solution = sol;
}
