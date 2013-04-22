#include <gtest/gtest.h>
#include "Options.h"

class OptionFixture : public ::testing::Test
{
public:
    OptionFixture()
        : m_stackOps("-overwrite -target /tmp")
        , m_pHeapOps(NULL)
    {}

    virtual void SetUp()
    {
        m_pHeapOps = new Options("-overwrite false -source /usr"); //!!!
    }

    virtual void TearDown()
    {
        delete m_pHeapOps;
    }

    Options m_stackOps;
    Options* m_pHeapOps;
};

TEST_F(OptionFixture, WithoutUnite)
{
    EXPECT_EQ(2, m_stackOps.GetOptions().size());
    EXPECT_EQ("true", m_stackOps.GetOption("overwrite"));
    EXPECT_EQ("/tmp", m_stackOps.GetOption("target"));

    EXPECT_EQ(2, m_pHeapOps->GetOptions().size());
    EXPECT_EQ("/usr", m_pHeapOps->GetOption("source"));
    EXPECT_EQ("false", m_pHeapOps->GetOption("overwrite"));
}

TEST_F(OptionFixture, AddStackOpsToHeapOps)
{
    m_pHeapOps->Add(m_stackOps);

    EXPECT_EQ(3, m_pHeapOps->GetOptions().size());
    EXPECT_EQ("/usr", m_pHeapOps->GetOption("source"));
    EXPECT_EQ("true", m_pHeapOps->GetOption("overwrite"));
    EXPECT_EQ("/tmp", m_pHeapOps->GetOption("target"));
}

TEST_F(OptionFixture, AddHeapOpsToStackOps)
{
    m_stackOps.Add(*m_pHeapOps);

    EXPECT_EQ(3, m_stackOps.GetOptions().size());
    EXPECT_EQ("/usr", m_stackOps.GetOption("source"));
    EXPECT_EQ("false", m_stackOps.GetOption("overwrite"));
    EXPECT_EQ("/tmp", m_stackOps.GetOption("target"));
}

