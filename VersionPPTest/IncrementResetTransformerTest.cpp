#include "stdafx.h"
#include "CppUnitTest.h"
#include <memory>
#include "TransformerManager.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace VersionPPTest
{
	TEST_CLASS(IncrementResetTransformerTest)
	{
		static std::unique_ptr<TransformerManager> transformerManager;
	public:
		TEST_CLASS_INITIALIZE(Init)
		{
			transformerManager = std::unique_ptr<TransformerManager>(new TransformerManager);
		}

		TEST_METHOD(IncrementResetTransformerMajor)
		{
			Version version("+.2.3.4");
			Version currentVersion("1.2.3.4");
			transformerManager->Transform(version, currentVersion);
			Assert::AreEqual<std::string>("2", version.getMajor().getStringValue());
			Assert::AreEqual<std::string>("2", version.getMinor().getStringValue());
			Assert::AreEqual<std::string>("3", version.getBuild().getStringValue());
			Assert::AreEqual<std::string>("4", version.getRevision().getStringValue());
		}

		TEST_METHOD(IncrementResetTransformerMinor)
		{
			Version version("1.+.3.4");
			Version currentVersion("1.2.3.4");
			transformerManager->Transform(version, currentVersion);
			Assert::AreEqual<std::string>("1", version.getMajor().getStringValue());
			Assert::AreEqual<std::string>("3", version.getMinor().getStringValue());
			Assert::AreEqual<std::string>("3", version.getBuild().getStringValue());
			Assert::AreEqual<std::string>("4", version.getRevision().getStringValue());
		}

		TEST_METHOD(IncrementResetTransformerMinorBuild)
		{
			Version version("1.+.+.4");
			Version currentVersion("1.2.3.4");
			transformerManager->Transform(version, currentVersion);
			Assert::AreEqual<std::string>("1", version.getMajor().getStringValue());
			Assert::AreEqual<std::string>("3", version.getMinor().getStringValue());
			Assert::AreEqual<std::string>("0", version.getBuild().getStringValue());
			Assert::AreEqual<std::string>("4", version.getRevision().getStringValue());
		}
	};
	std::unique_ptr<TransformerManager> IncrementResetTransformerTest::transformerManager;
}