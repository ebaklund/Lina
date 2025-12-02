
#include "CppUnitTest.h"
#include "BD.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace BD;

template<>
std::wstring Microsoft::VisualStudio::CppUnitTestFramework::ToString<BD::DM>(const BD::DM& q)
{
    switch (q)
    {
    case DM::True:
        return L"DM::True";
    case DM::False:
        return L"DM::False";
    case DM::Neither:
        return L"DM::Neither";
    case DM::Both:
        return L"DM::Both";
    default:
        return L"Unknown BD::DM Value";
    }
}

namespace BDTests
{
	TEST_CLASS(DMTests)
	{
	public:
		
		TEST_METHOD(IsDefined)
		{
            Assert::AreEqual(DM::True, DM::True);
            Assert::AreEqual(DM::False, DM::False);
            Assert::AreEqual(DM::Neither, DM::Neither);
            Assert::AreEqual(DM::Both, DM::Both);
        }
	};
}
