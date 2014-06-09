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

		TEST_METHOD(ConstructorEmpty)
		{
			Version version;
			Assert::AreEqual<std::string>("1", version.ToString("."));
			Assert::AreEqual<std::string>("1.0.0.0", version.ToStrictString("."));
		}

		TEST_METHOD(ConstructorEmptyString)
		{
			Version version("");
			Assert::AreEqual<std::string>("1", version.ToString("."));
			Assert::AreEqual<std::string>("1.0.0.0", version.ToStrictString("."));
		}

		TEST_METHOD(ConstructorMajor)
		{
			Version version(1);
			Assert::AreEqual<std::string>("1", version.ToString("."));
			Assert::AreEqual<std::string>("1.0.0.0", version.ToStrictString("."));
		}

		TEST_METHOD(ConstructorMajorMinor)
		{
			Version version(1, 2);
			Assert::AreEqual<std::string>("1.2", version.ToString("."));
			Assert::AreEqual<std::string>("1.2.0.0", version.ToStrictString("."));
		}

		TEST_METHOD(ConstructorWithoutRevision)
		{
			Version version(1, 2, 3);
			Assert::AreEqual<std::string>("1.2.3", version.ToString("."));
			Assert::AreEqual<std::string>("1.2.3.0", version.ToStrictString("."));
		}

		TEST_METHOD(ParseFail)
		{
			Version version("NotValidVersion");
			Assert::AreEqual<std::string>("NotValidVersion", version.ToString("."));
			Assert::AreEqual<std::string>("0.0.0.0", version.ToStrictString("."));
		}
	};
}