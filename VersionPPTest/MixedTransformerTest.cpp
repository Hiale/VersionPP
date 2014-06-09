#include "stdafx.h"
#include "CppUnitTest.h"
#include <memory>
#include "TransformerManager.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace VersionPPTest
{
	TEST_CLASS(MixedTransformerTest)
	{
		static std::unique_ptr<TransformerManager> transformerManager;
	public:
		TEST_CLASS_INITIALIZE(Init)
		{
			transformerManager = std::unique_ptr<TransformerManager>(new TransformerManager);
		}

		TEST_METHOD(MixedTransformerDotNetReset)
		{
			Version version("1.2.*.+");
			Version currentVersion("1.2.3.4");
			transformerManager->Transform(version, currentVersion);
			Assert::AreEqual<std::string>("1", version.getMajor().getStringValue());
			Assert::AreEqual<std::string>("2", version.getMinor().getStringValue());
			Assert::IsTrue(version.getBuild().getIntegerValue() > 0);
			Assert::AreEqual<std::string>("0", version.getRevision().getStringValue());
		}

		TEST_METHOD(MixedTransformerDotNetIncrement)
		{
			Version version("1.2.*.^");
			Version currentVersion("1.2.3.4");
			transformerManager->Transform(version, currentVersion);
			Assert::AreEqual<std::string>("1", version.getMajor().getStringValue());
			Assert::AreEqual<std::string>("2", version.getMinor().getStringValue());
			Assert::IsTrue(version.getBuild().getIntegerValue() > 0);
			Assert::AreEqual<std::string>("5", version.getRevision().getStringValue());
		}

		TEST_METHOD(MixedTransformerIncrementDotNet)
		{
			Version version("1.+.*");
			Version currentVersion("1.2.3.4");
			transformerManager->Transform(version, currentVersion);
			Assert::AreEqual<std::string>("1", version.getMajor().getStringValue());
			Assert::AreEqual<std::string>("3", version.getMinor().getStringValue());
			Assert::IsTrue(version.getBuild().getIntegerValue() > 0);
			Assert::IsTrue(version.getRevision().getIntegerValue() > 0);
		}

	};
	std::unique_ptr<TransformerManager> MixedTransformerTest::transformerManager;
}