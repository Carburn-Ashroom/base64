#include <vector>
#include <QString>
#include <string>

namespace Bit {     // 该名字空间负责加解密

    using std::vector;
    using std::string;

    struct Length_error {};     // 编码长度不正确

    class Stream {      // Stream类是一个二进制流
    public:
        Stream(vector<unsigned char>&& text, int bit_count) : char_bit{bit_count}, head_bit{bit_count} { set_data(std::move(text)); }
        unsigned char parse_bit(int size);      // 取出size位二进制
        bool empty() const { return data.empty(); }
    private:
        int char_bit;
        vector<unsigned char> data;
        int head_bit;
        unsigned char parse_head(int size);     // 从首部取出size位二进制。size必须小于头部当前二进制位数
        void set_data(vector<unsigned char>&& text);        // 设置数据
    };

}
