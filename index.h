/**
 * @file index.h
 * @brief 索引
 * @author chxuan, 787280310@qq.com
 * @version 1.0.0
 * @date 2017-11-09
 */
#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

class index_tree;

struct character
{
	wchar_t value;
	bool is_word_end;
    std::wstring word;
};

class index
{
public:
    index(int level, index_tree* tree);
    // 构建索引
    void build_index(const std::wstring& word);
    // 查找敏感词
    void find(const std::wstring& content, std::size_t begin_cursor, std::size_t& cursor, int& count);

private:
    // 判断是否已经存在索引了
	bool is_exist_index(const std::wstring& word);
    // 是否需要跳转到下一级索引
	bool is_enter_next_index(std::size_t size);
    // 进入下一级索引
    void enter_next_index(std::size_t level);
    // 判断是否到了敏感词词尾
	bool is_word_end(std::size_t word_size);
    // 设置敏感词词尾标识, 即is_word_end=true
	void set_word_end(const std::wstring& word);
    // 查找key
	bool find_key(wchar_t key);
    // 查找key-value
	bool find_value(wchar_t key, wchar_t value);
    // 查找character
	bool find_character(wchar_t key, wchar_t value, character& ch);
    // 判断是否到了文本尾
    bool is_content_end(std::size_t cursor, std::size_t content_size);
    // 判断找到的敏感词和真实的敏感词是否相等
    bool equal_word(const std::wstring& word, const std::wstring& content, std::size_t begin, std::size_t size);

private:
	std::unordered_multimap<wchar_t, character> index_;
    std::size_t level_;
	index_tree* index_tree_;
};

