#include "dfa.h"
#include "index_tree.h"
#include "converter.h"

bool dfa::add_word(const std::string& word)
{
    if (word.empty())
    {
        return false;
    }

    // 将string转换成wstring方便处理
    std::wstring wword = converter::string_to_wstring(word);
	if (wword.size() > max_index_level + 1)
	{
		return false;
	}

    // 获取索引树，不存在则创建索引树
    auto tree = get_index_tree(wword[0]);
    if (tree == nullptr)
    {
        tree = create_index_tree(wword[0]);
    }

    // 构建索引
    tree->build_index(wword);

    return true;
}

void dfa::add_content(const std::string& content)
{
    // 将string转换成wstring方便处理
    std::wstring wcontent = converter::string_to_wstring(content);

    int count = 0;
    for (std::size_t cursor = 0; cursor < wcontent.size(); ++cursor)
    {
        auto tree = get_index_tree(wcontent[cursor]);
        if (tree != nullptr)
        {
            tree->find(wcontent, cursor, count);
        }
    }

    std::cout << "count: " << count << std::endl;
}

std::shared_ptr<index_tree> dfa::get_index_tree(wchar_t key)
{
    auto iter = index_trees_.find(key);
    if (iter != index_trees_.end())
    {
        return iter->second;
    }
    return nullptr;
}

std::shared_ptr<index_tree> dfa::create_index_tree(wchar_t key)
{
    auto iter = index_trees_.find(key);
    if (iter == index_trees_.end())
    {
        auto tree = std::make_shared<index_tree>();
        index_trees_.emplace(key, tree);
        return tree;
    }
    return iter->second;
}
