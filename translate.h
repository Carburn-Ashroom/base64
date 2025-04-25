#ifndef TRANSLATE_H
#define TRANSLATE_H

#include <optional>

#include "config.h"
#include "stream.h"

namespace Trans {       // 该名字空间负责实现编码和解码

    using std::vector;
    using std::string;
    using std::optional;

    struct Table_404_error {};      // 无效密码字符

    unsigned char from_table(unsigned char ch);     // 从编码表中获取字符编号
    unsigned char to_table(unsigned char ch);       // 查找编号所对应的字符

    class Trans {       // Trans类是一个翻译器基类
    public:
        Trans(int from, int to) : from{from}, width{to} { }
        virtual QString get() = 0;      // 获取翻译后的文字
        virtual ~Trans() { }
    protected:
        virtual unsigned char parse() { return stream->parse_bit(width); }
        void set_data(vector<unsigned char>&& data) { stream = Bit::Stream{std::move(data),from}; }
        int from_ratio() const { return width/gcd(); }
        int to_ratio() const { return from/gcd(); }
        string get_result();        // 获取结果字符串
    private:
        optional<Bit::Stream> stream;
        int from;
        int width;
        int gcd() const;        // from和width的最大公因数
    };

    class Encrypt : public Trans {      // Encrypt是一个编码器
    public:
        explicit Encrypt(const QString& text, int from_bit =b64_text, int to_bit =b64_pass) : Trans{from_bit,to_bit} { set_data(text); }
        QString get() override;     // 获取翻译后的文字
    private:
        unsigned char parse() override { return to_table(Trans::parse()); }
        void set_data(const QString& data);     // 设置初始流
    };

    class Decrypt : public Trans {      // Decrypt是一个解码器
    public:
        explicit Decrypt(const QString& pass, int from =b64_pass, int to =b64_text) : Trans{from,to} { set_data(pass); }
        QString get() override { return QString{get_result().c_str()}; }
    private:
        void set_data(const QString& data);     // 设置初始流
    };

}

#endif // TRANSLATE_H
