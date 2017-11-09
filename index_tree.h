/**
 * @file index_tree.h
 * @brief 索引树
 * @author chxuan, 787280310@qq.com
 * @version 1.0.0
 * @date 2017-11-09
 */
#pragma once

#include <memory>
#include <vector>

const int max_index_level = 20;

class index;

class index_tree
{
public:
    index_tree();
    // 构建索引
    void build_index(const std::wstring& word);
    // 查找敏感词
    void find(const std::wstring& content, std::size_t cursor, int& count);
    // 设置当前索引
    void set_current_index(int level);
    // 设置是否有效
    void set_active(bool active);

private:
    // 创建索引树
	void create_index_tree();

private:
	std::vector<std::shared_ptr<index>> indexes_;
	std::shared_ptr<index> current_index_;
    bool active_;
};
