//
//  Password.hpp
//  password-mac
//
//  Created by Jonathan Esquibel on 2/6/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#ifndef Password_hpp
#define Password_hpp

#include <stdio.h>
#include "string"

class Password
{
public:
    Password(int entry, std::string h, std::string sol);
    
    int row;
    std::string hash;
    std::string solution;
    
};

#endif /* Password_hpp */
