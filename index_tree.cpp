#include "index_tree.h"
#include "index.h"

index_tree::index_tree()
{
    create_index_tree();
}

void index_tree::build_index(const std::wstring& word)
{
    // 将当前索引设置为一级索引
    set_current_index(1);

    if (word.size() == 1)
    {
        current_index_->build_index(word);
    }
    else
    {
        for (std::size_t i = 1; i < word.size(); ++i)
        {
            current_index_->build_index(word);
        }
    }
}

void index_tree::find(const std::wstring& content, std::size_t cursor, int& count)
{
    std::size_t begin_cursor = cursor;
    // 将当前索引设置为一级索引
    set_current_index(1);

    set_active(true);
    while (active_)
    {
        current_index_->find(content, begin_cursor, cursor, count);
    }
}

void index_tree::set_current_index(int level)
{
    current_index_ = indexes_[level - 1];
}

void index_tree::set_active(bool active)
{
    active_ = active;
}

void index_tree::create_index_tree()
{
	for (int i = 1; i <= max_index_level; ++i)
	{
		auto idx = std::make_shared<index>(i, this);
		indexes_.emplace_back(idx);
	}
}
