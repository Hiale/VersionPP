#include "stdafx.h"
#include "CppUnitTest.h"
#include <memory>
#include "TransformerManager.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace VersionPPTest
{
	TEST_CLASS(IncrementAlwaysTransformerTest)
	{
		static std::unique_ptr<TransformerManager> transformerManager;
	public:
		TEST_CLASS_INITIALIZE(Init)
		{
			transformerManager = std::make_unique<TransformerManager>();
		}

		TEST_METHOD(IncrementAlwaysTransformerMajor)
		{
			Version version("^.2.3.4");
			Version currentVersion("1.2.3.4");
			transformerManager->Transform(version, currentVersion);
			Assert::AreEqual<std::string>("2", version.getMajor().getStringValue());
			Assert::AreEqual<std::string>("2", version.getMinor().getStringValue());
			Assert::AreEqual<std::string>("3", version.getBuild().getStringValue());
			Assert::AreEqual<std::string>("4", version.getRevision().getStringValue());
		}

		TEST_METHOD(IncrementAlwaysTransformerMinor)
		{
			Version version("1.^.3.4");
			Version currentVersion("1.2.3.4");
			transformerManager->Transform(version, currentVersion);
			Assert::AreEqual<std::string>("1", version.getMajor().getStringValue());
			Assert::AreEqual<std::string>("3", version.getMinor().getStringValue());
			Assert::AreEqual<std::string>("3", version.getBuild().getStringValue());
			Assert::AreEqual<std::string>("4", version.getRevision().getStringValue());
		}

		TEST_METHOD(IncrementAlwaysTransformerMinorBuild)
		{
			Version version("1.^.^.4");
			Version currentVersion("1.2.3.4");
			transformerManager->Transform(version, currentVersion);
			Assert::AreEqual<std::string>("1", version.getMajor().getStringValue());
			Assert::AreEqual<std::string>("3", version.getMinor().getStringValue());
			Assert::AreEqual<std::string>("4", version.getBuild().getStringValue());
			Assert::AreEqual<std::string>("4", version.getRevision().getStringValue());
		}
	};
	std::unique_ptr<TransformerManager> IncrementAlwaysTransformerTest::transformerManager;
}