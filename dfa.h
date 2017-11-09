/**
 * @file dfa.h
 * @brief dfa算法类
 * @author chxuan, 787280310@qq.com
 * @version 1.0.0
 * @date 2017-11-09
 */
#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <unordered_map>

class index_tree;

class dfa
{
public:
    // 增加敏感词
    bool add_word(const std::string& word);
    // 增加文本
    void add_content(const std::string& content);

private:
    // 获取索引树
    std::shared_ptr<index_tree> get_index_tree(wchar_t key);
    // 创建索引树
    std::shared_ptr<index_tree> create_index_tree(wchar_t key);

private:
    std::unordered_map<wchar_t, std::shared_ptr<index_tree>> index_trees_;
};
