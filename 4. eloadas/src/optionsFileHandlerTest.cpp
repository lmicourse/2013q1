#include <gmock/gmock.h>

#include "IFile.h"
#include "Options.h"
#include "OptionsFileHandler.h"

using ::testing::Return;
using ::testing::_;

class MockFile : public IFile
{
public:
    MOCK_CONST_METHOD0(ReadLine, std::string());
    MOCK_METHOD1(WriteLine, bool(const std::string&));
};

class OptionsFileHandlerTest : public ::testing::Test
{
public:
    OptionsFileHandlerTest()
        : m_sourceLine("source=/usr")
        , m_targetLine("target=/tmp")
        , m_overwriteTrue("overwrite=true")
        , m_overwriteFalse("overwrite=false")
        , m_file()
        , m_fileHandler(m_file)
    {}

    std::string m_sourceLine;
    std::string m_targetLine;
    std::string m_overwriteTrue;
    std::string m_overwriteFalse;
    MockFile    m_file;
    OptionsFileHandler m_fileHandler;
};

TEST_F(OptionsFileHandlerTest, EmptyFile)
{
    EXPECT_CALL(m_file, ReadLine()).WillRepeatedly(Return(""));

    Options ops = m_fileHandler.Read();

    EXPECT_EQ(0, ops.GetOptions().size());
}


TEST_F(OptionsFileHandlerTest, ReadOneOption)
{
    EXPECT_CALL(m_file, ReadLine())
            .WillOnce(Return(m_overwriteFalse))
            .WillRepeatedly(Return(""));

    Options ops = m_fileHandler.Read();

    EXPECT_EQ(1, ops.GetOptions().size());
    EXPECT_EQ("false", ops.GetOption("overwrite"));
}

TEST_F(OptionsFileHandlerTest, ReadFourOption)
{
    EXPECT_CALL(m_file, ReadLine())
            .WillOnce(Return(m_overwriteFalse))
            .WillOnce(Return(m_sourceLine))
            .WillOnce(Return(m_targetLine))
            .WillOnce(Return(m_overwriteTrue))
            .WillRepeatedly(Return(""));

    Options ops = m_fileHandler.Read();

    EXPECT_EQ(3, ops.GetOptions().size());
    EXPECT_EQ("/usr", ops.GetOption("source"));
    EXPECT_EQ("/tmp", ops.GetOption("target"));
    EXPECT_EQ("true", ops.GetOption("overwrite"));
}

TEST_F(OptionsFileHandlerTest, WriteNoOption)
{
    EXPECT_CALL(m_file, WriteLine(_)).Times(0);

    Options ops("");

    EXPECT_FALSE(m_fileHandler.Write(ops));
}

TEST_F(OptionsFileHandlerTest, WriteOneOption)
{
    EXPECT_CALL(m_file, WriteLine(m_overwriteTrue)).WillOnce(Return(true));

    Options ops("-overwrite");

    EXPECT_TRUE(m_fileHandler.Write(ops));
}

TEST_F(OptionsFileHandlerTest, WriteThreeOption)
{
    EXPECT_CALL(m_file, WriteLine(m_overwriteFalse)).Times(0);
    EXPECT_CALL(m_file, WriteLine(m_overwriteTrue)).WillOnce(Return(true));
    EXPECT_CALL(m_file, WriteLine(m_targetLine)).WillOnce(Return(true));
    EXPECT_CALL(m_file, WriteLine(m_sourceLine)).WillOnce(Return(true));

    Options ops("-overwrite false -source /usr -overwrite -target /tmp");

    EXPECT_TRUE(m_fileHandler.Write(ops));
}

TEST_F(OptionsFileHandlerTest, WriteError)
{
    EXPECT_CALL(m_file, WriteLine(m_overwriteTrue)).WillOnce(Return(false));

    Options ops("-overwrite");

    EXPECT_FALSE(m_fileHandler.Write(ops));
}
