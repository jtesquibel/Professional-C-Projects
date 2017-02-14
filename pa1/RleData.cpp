#include "RleData.h"

void RleData::Compress(const char* input, size_t inSize)
{
	// TODO
    delete [] mData;
    mSize = 0;
    int runSize;
    mData = new char[inSize*2];
    
    for (int i = 0; i < inSize; i++)
    {
        runSize = 0;
        char temp = input[i];
        char temp2 = input[i+1];
       
        if (temp == temp2)
        {
            // then there is a positive run of at least 2
            
            runSize = 2;
            while (true)
            {
                if (runSize == 127)
                {
                    break;
                }
                char temp3 = input[i+runSize];
                if (temp3 == '\0')
                {
                    break;
                }
                if (temp == temp3)
                {
                    runSize++;
                }
                else
                {
                    break;
                }
            }
            
            mData[mSize] = runSize;
            mSize++;
            mData[mSize] = temp;
            mSize++;
            
            i = i+runSize-1;
            
        }
        else
        {
            // there is no initial run
            char temp3 = input[i+2];
            
            // check if there is a run after a single char
            if (temp2 == temp3)
            {
                // then there is a positive run of at least 2 but write the original char
                mData[mSize] = 1;
                mSize++;
                mData[mSize] = temp;
                mSize++;
                i++;
                
                runSize = 2;
                while (true)
                {
                    char temp4 = input[i+runSize];
                    if (temp2 == temp4)
                    {
                        runSize++;
                    }
                    else
                    {
                        break;
                    }
                }
                
                mData[mSize] = runSize;
                mSize++;
                mData[mSize] = temp2;
                mSize++;

                i = i+runSize-1;
            }
            else
            {
                // then there is a negative run of at least 3

                runSize = 3;
                
                while (true)
                {
                    if (runSize == 127 || runSize == inSize) // fd = -3, fc = -4
                    {
                        break;
                    }
                    char temp4 = input[i+runSize];
                    if (temp4 == '\0')
                    {
                        break;
                    }
                    if (input[i+runSize-1] != temp4)
                    {
                        char temp5 = input[i+runSize+1];
                        if (temp4 == temp5)
                        {
                            break;
                        }
                        else
                        {
                            runSize++;
                        }
                    }
                    else
                    {
                        break;
                    }
                }
                int negRunSize = -runSize;
                // std::cout << "runsize = " << runSize << std::endl;

                mData[mSize] = negRunSize;
                mSize++;
                
                
                for (int j = i; j < i+runSize; j++)
                {
                    mData[mSize] = input[j];
                    mSize++;
                }
                
                i = i+runSize-1;

            }
            
        }
        
    }
    

    
    
    
}

void RleData::Decompress(const char* input, size_t inSize, size_t outSize)
{
	// TODO
    delete [] mData;
    mSize = 0;
    mData = new char[outSize];
    int num;
    
    std::cout << "insize = " << inSize << std::endl;
    
    
    for (int i = 0; i < inSize; i++)
    {
        num = (int)input[i];
        // std::cout << "Num = " << num << std::endl;
        if (num > 0)
        {
            // positive run
            char temp = input[i+1];

            if (temp == '\0')
            {
                break;
            }
            
            if (mSize > outSize)
            {
                std::cout << "Too big" << std::endl;
            }
            for (int j = 0; j < num; j++)
            {
                mData[mSize] = temp;
                mSize++;
            }

            i = i+1;
        }
        else if (num < 0)
        {
            // negative run
            int num2 = -num;
            for (int j = 0; j < num2; j++)
            {
                mData[mSize] = input[j+i+1];
                mSize++;
            }
            i = i+num2;
        }
        
        
    }
}

std::ostream& operator<< (std::ostream& stream, const RleData& rhs)
{
	for (int i = 0; i < rhs.mSize; i++)
	{
		stream << rhs.mData[i];
	}
	return stream;
}
