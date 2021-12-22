#include <gtest/gtest.h>

#include <GSCrossPlatform/GS_CrossPlatformString.h>

using namespace CrossPlatform;

class CrossPlatformStringTests : public ::testing::Test {
public:

    CrossPlatformStringTests()
            : _string(nullptr), _codePoints(nullptr) {}

protected:

    virtual Void SetUp() {
        _string = new UString(U"Привет!");

        _codePoints = new Vector<CodePoint>({
            0x041F, 0x0440, 0x0438, 0x0432, 0x0435, 0x0442, 0x0021
        });
    }

    virtual Void TearDown() {
        delete _string;

        delete _codePoints;
    }

protected:

    UString *_string;

    Vector<CodePoint> *_codePoints;
};

TEST_F(CrossPlatformStringTests, CodePoints) {
    auto symbols = _string->getSymbols();
    auto codePoints = *_codePoints;

    for (auto index = 0; index < symbols.size() && index < _codePoints->size(); ++index) {
        ASSERT_EQ(symbols[index].getCodePoint(), codePoints[index]);
    }
}

I32 main() {
    ::testing::InitGoogleTest();

    return RUN_ALL_TESTS();
}
