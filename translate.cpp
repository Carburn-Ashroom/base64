/**
 * 实现编码和解码
 * 创建者：Carburn Ashroom
 * 2024.11.3
 */

#include "translate.h"

namespace Trans {

    unsigned char from_table(unsigned char ch)
    {
        if (isupper(ch))
            return ch-'A';
        else if (islower(ch))
            return ch-'a'+26;
        else if (isdigit(ch))
            return ch-'0'+52;
        switch (ch) {
        case '+':
            return 62;
        case '/':
            return 63;
        case '=':
            return 0;
        }
        throw Table_404_error{};
    }

    unsigned char to_table(unsigned char ch)
    {
        if (ch < 26)
            return ch+'A';
        else if (ch < 52)
            return ch-26+'a';
        else if (ch < 62)
            return ch-52+'0';
        switch (ch) {
        case 62:
            return '+';
        case 63:
            return '/';
        default:
            return '=';
        }
    }

    void Decrypt::set_data(const QString& data)
    {
        vector<unsigned char> text;
        for (auto c : data.toStdString())
            text.emplace_back(from_table(c));
        Trans::set_data(std::move(text));
    }

    string Trans::get_result()
    {
        string res;
        while (not stream->empty())
            res.push_back(parse());
        return res;
    }

    int Trans::gcd() const
    {
        int f {from};
        int t {width};
        if (f < t)
            std::swap(f, t);
        while (t != 0) {
            int l {f%t};
            f = t;
            t = l;
        }
        return f;
    }

    QString Encrypt::get()
    {
        string text {get_result()};
        for (auto i=text.rbegin(); i!=text.rend() and (*i)=='A'; ++i)
            (*i) = '=';
        return QString{text.c_str()};
    }

    void Encrypt::set_data(const QString& data)
    {
        vector<unsigned char> text;
        for (auto c : data.toStdString())
            text.push_back(c);
        int fill {};
        if (from_ratio() != 0) {
            auto left = text.size()%from_ratio();
            fill = (left!=0) ? from_ratio()-left : 0;
        }
        for (int i{}; i!=fill; ++i)
            text.push_back(0);
        Trans::set_data(std::move(text));
    }

}
