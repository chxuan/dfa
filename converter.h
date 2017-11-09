/**
 * @file converter.h
 * @brief string和wstring相互转化工具
 * @author chxuan, 787280310@qq.com
 * @version 1.0.0
 * @date 2017-11-09
 */
#pragma once

#include <codecvt>
#include <locale>

class converter
{
public:
    static std::wstring string_to_wstring(const std::string& str)
    {
        std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
        return converter.from_bytes(str);
    }

    static std::string wstring_to_string(const std::wstring& str)
    {
        std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
        return converter.to_bytes(str);
    }

    static std::string wchar_to_string(wchar_t ch)
    {
        wchar_t arr[2] = {'\0'};
        arr[0] = ch;
        std::wstring str(arr);
        return wstring_to_string(str);
    }
};


