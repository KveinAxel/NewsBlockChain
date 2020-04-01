#include "gtest/gtest.h"
#include "service/compressor/Compressor.h"

// 测试还原性
TEST(TestCompressor, testReverse) {

    // 获得压缩器
    std::string data("test the compressor");
    Compressor compressor(data);
    compressor.compress();

    // 压缩成功
    ASSERT_TRUE(compressor.isCompleted());
    std::string serializedDict = compressor.getSerializedDict();
    std::vector<uint32_t> bytes = compressor.getBytes();
    uint32_t filler = compressor.getFiller();

    // 根据压缩信息构造解压器
    Compressor decompressor(serializedDict, bytes, filler);
    decompressor.decompress();

    // 解压成功
    ASSERT_TRUE(decompressor.isCompleted());

    // 信息还原
    ASSERT_EQ(data, decompressor.getData());
}
