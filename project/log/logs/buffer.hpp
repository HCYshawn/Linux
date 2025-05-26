#include <vector>
#include "util.hpp"

namespace bitlog
{
#define DEFAULT_BUFFER_SIZE (100 * 1024 * 1024)

    class Buffer
    {
    public:
        Buffer()
        {
        }

        // 向缓冲区写入数据
        void push(const char *data, size_t len)
        {
        }

        // 返回可读数据的地址
        const char *begin()
        {
        }

        // 返回可读数据的长度
        size_t readAbleSize()
        {
        }

        // 对读写指针进行向后偏移操作
        void moveWriter(size_t len)
        {
        }

        void moveReader(size_t len)
        {
        }

        // 重置读写位置，初始化缓冲区
        void reset()
        {
        }

        // 实现交换操作
        void swap(const Buffer &buffer)
        {
        }

        // 判断缓冲区是否为空
        bool empty()
        {
        }

    private:
        void moveWriter(size_t len)
        {
        }

    private:
        std::vector<char> _buffer;
        size_t _reader_idx; // 当前可读数据的指针--本质是下标
        size_t _writer_idx; // 当前可写数据的指针
    };
}