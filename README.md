DFA
===============================================

## Usage

```cpp

#include "dfa.h"

int main()
{
    dfa d;

    // 增加敏感词
    d.add_word("中国人");
    d.add_word("人民");
    d.add_word("人民共产党");
    d.add_word("共产党");

    // 增加待分析文本
    d.add_content("中国人民共产党");

    return 0;
}

```

## Output

    count: 4
