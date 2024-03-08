#include <common/Common.hpp>

class MessageGroup {
public:
    struct Header {
        u32 signature;
        u32 dataType;
        u32 dataSize;
        u32 numBlocks;
        u8 charset;
        u8 pad[0xf];
    };

    struct Block {
        u32 kind;
        u32 size;
        u8 data[];
    };

    enum BlockKind {
        BLOCK_KIND_INF = 'INF1',
        BLOCK_KIND_DAT = 'DAT1',
        BLOCK_KIND_STR = 'STR1',
        BLOCK_KIND_MID = 'MID1',
    };

    struct Entry {
        u32 offset;
        u8 attributes;
    };

    struct Inf {
        u16 numEntries;
        u16 entrySize;
        u16 groupID;
        u8 defaultColor;
        Entry entries[];
    };

    struct Mid {
        u16 numEntries;
        u8 format;
        u8 info;
        u32 pad;
        u32 messageIds[];
    };

    const Header* header;
    const Inf* inf;
    const wchar_t* dat;
    const void* str;
    const Mid* mid;
};
size_assert(MessageGroup, 0x14);
