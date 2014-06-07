#include "stdafx.h"
#include "CppUnitTest.h"
#include <memory>
#include "Version.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace VersionPPTest
{
	TEST_CLASS(VersionTest)
	{
	public:

		TEST_METHOD(ToStringSimple)
		{
			Version version("1.2.3.4");
			Assert::AreEqual<std::string>("1|2|3|4", version.ToString("|"));
		}

		TEST_METHOD(ToStringShortened)
		{
			Version version("1.2");
			Assert::AreEqual<std::string>("1,2", version.ToString(","));
		}

		TEST_METHOD(ToStrictString)
		{
			Version version("1.2");
			Assert::AreEqual<std::string>("1.2.0.0", version.ToStrictString("."));
		}

		//TEST_METHOD(ParseFail)
		//{
		//	Version version("1.2");
		//	Assert::AreEqual<std::string>("1,2", version.ToString(","));
		//}
	};
}