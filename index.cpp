#include "index.h"
#include "index_tree.h"

index::index(int level, index_tree* tree) : level_(level), index_tree_(tree)
{

}

void index::build_index(const std::wstring& word)
{
    // 对只有一个字符敏感词的做特殊处理
    if (word.size() == 1)
    {
        if (!find_key(word[0]))
        {
            // 将一级索引的value设置为'\0'
            index_.emplace(word[0], character{ L'\0', true, word });
        }
        return;
    }

    // 判断索引是否已经建立
    if (is_exist_index(word))
    {
        // 判断是否需要进入下一级索引
        if (is_enter_next_index(word.size()))
        {
            // 进入下一级索引
            enter_next_index(level_ + 1);
        }
        else
        {
            // 已经到了词尾并将is_word_end设置成true
            set_word_end(word);
        }
        return;
    }

    // 判断是否到了词尾
    bool is_end = is_word_end(word.size());
    index_.emplace(word[level_ - 1], character{ word[level_], is_end, (is_end ? word : L"") });
    if (!is_end)
    {
        // 进入下一级索引
        enter_next_index(level_ + 1);
    }
}

void index::find(const std::wstring& content, std::size_t begin_cursor, std::size_t& cursor, int& count)
{
    // 判断是否是一个字符的敏感词
    if (level_ == 1 && find_value(content[cursor], L'\0'))
    {
        ++count;
    }

    // 判断是否到了文本尾
    if (!is_content_end(cursor, content.size()))
    {
        character ch;
        if (find_character(content[cursor], content[cursor + 1], ch))
        {
            if (ch.is_word_end && equal_word(ch.word, content, begin_cursor, cursor - begin_cursor + 2))
            {
                ++count;
            }

            // 进入下一级索引
            enter_next_index(level_ + 1);
        }
        else
        {
            // 当前索引树结束，进入下一个索引树
            index_tree_->set_active(false);
        }
    }
    else
    {
        // 当前索引树结束，进入下一个索引树
        index_tree_->set_active(false);
    }

    ++cursor;
}

bool index::is_exist_index(const std::wstring& word)
{
    auto range = index_.equal_range(word[level_ - 1]);
    for (auto iter = range.first; iter != range.second; ++iter)
    {
        if (iter->second.value == word[level_])
        {
            return true;
        }
    }
    return false;
}

bool index::is_enter_next_index(std::size_t size)
{
    if (size > level_ + 1)
    {
        return true;
    }
    return false;
}

void index::enter_next_index(std::size_t level)
{
    index_tree_->set_current_index(level);
}

bool index::is_word_end(std::size_t word_size)
{
    if (word_size == level_ + 1)
    {
        return true;
    }
    return false;
}

void index::set_word_end(const std::wstring& word)
{
    auto range = index_.equal_range(word[level_ - 1]);
    for (auto iter = range.first; iter != range.second; ++iter)
    {
        if (iter->second.value == word[level_])
        {
            iter->second.is_word_end = true;
            iter->second.word = word;
        }
    }
}

bool index::find_key(wchar_t key)
{
    auto iter = index_.find(key);
    if (iter != index_.end())
    {
        return true;
    }
    return false;
}

bool index::find_value(wchar_t key, wchar_t value)
{
    auto range = index_.equal_range(key);
    for (auto iter = range.first; iter != range.second; ++iter)
    {
        if (iter->second.value == value)
        {
            return true;
        }
    }
    return false;
}

bool index::find_character(wchar_t key, wchar_t value, character& ch)
{
    auto range = index_.equal_range(key);
    for (auto iter = range.first; iter != range.second; ++iter)
    {
        if (iter->second.value == value)
        {
            ch = iter->second;
            return true;
        }
    }
    return false;
}

bool index::is_content_end(std::size_t cursor, std::size_t content_size)
{
    if (cursor + 1 >= content_size)
    {
        return true;
    }
    return false;
}

bool index::equal_word(const std::wstring& word, const std::wstring& content, std::size_t begin, std::size_t size)
{
    return word == content.substr(begin, size);
}
