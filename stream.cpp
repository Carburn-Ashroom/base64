/**
 * 实现二进制流
 * 创建者：Carburn Ashroom
 * 2024.11.2
 */

#include "stream.h"

namespace Bit {
    
    unsigned char Stream::parse_bit(int size)
    {
        unsigned char res {};
        while (size >= head_bit) {
            res <<= head_bit;
            res += data.back();
            data.pop_back();
            size -= head_bit;
            head_bit = char_bit;
            if (empty() and size!=0)
                throw Length_error{};
        }
        if (size != 0) {
            res <<= size;
            res += parse_head(size);
        }
        return res;
    }
    
    unsigned char Stream::parse_head(int size)
    {
        head_bit -= size;
        unsigned char res {static_cast<unsigned char>(data.back()>>head_bit)};
        unsigned char mask {static_cast<unsigned char>(res<<head_bit)};
        data.back() -= mask;
        return res;
    }
    
    void Stream::set_data(vector<unsigned char>&& text)
    {
        std::reverse(text.begin(), text.end());
        data = text;
    }
    
}
