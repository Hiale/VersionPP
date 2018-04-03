#include "stdafx.h"
#include "CppUnitTest.h"
#include <memory>
#include "TransformerManager.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace VersionPPTest
{		
	TEST_CLASS(DotNetTransformerTest)
	{
		static std::unique_ptr<TransformerManager> transformerManager;
	public:
		TEST_CLASS_INITIALIZE(Init)
		{
			transformerManager = std::make_unique<TransformerManager>();
		}

		TEST_METHOD(DotNetTransformerBuildRevision)
		{
			Version version("1.2.*");
			Version currentVersion("1.2.0.0");
			transformerManager->Transform(version, currentVersion);
			Assert::AreEqual<std::string>("1", version.getMajor().getStringValue());
			Assert::AreEqual<std::string>("2", version.getMinor().getStringValue());
			Assert::IsTrue(version.getBuild().getIntegerValue() > 0);
			Assert::IsTrue(version.getRevision().getIntegerValue() > 0);
		}

		TEST_METHOD(DotNetTransformerBuildOnly)
		{
			Version version("1.2.*.4");
			Version currentVersion("1.2.0.0");
			transformerManager->Transform(version, currentVersion);
			Assert::AreEqual<std::string>("1", version.getMajor().getStringValue());
			Assert::AreEqual<std::string>("2", version.getMinor().getStringValue());
			Assert::IsTrue(version.getBuild().getIntegerValue() > 0);
			Assert::AreEqual<std::string>("4", version.getRevision().getStringValue());
		}

		TEST_METHOD(DotNetTransformerRevisionOnly)
		{
			Version version("1.2.3.*");
			Version currentVersion("1.2.0.0");
			transformerManager->Transform(version, currentVersion);
			Assert::AreEqual<std::string>("1", version.getMajor().getStringValue());
			Assert::AreEqual<std::string>("2", version.getMinor().getStringValue());
			Assert::AreEqual<std::string>("3", version.getBuild().getStringValue());
			Assert::IsTrue(version.getRevision().getIntegerValue() > 0);
		}

		TEST_METHOD(DotNetTransformerFail)
		{
			Version version("1.*.3.4");
			Version currentVersion("1.2.0.0");
			transformerManager->Transform(version, currentVersion);
			Assert::AreEqual<std::string>("1", version.getMajor().getStringValue());
			Assert::IsFalse(version.getMinor().hasIntegerValue());
			Assert::AreEqual<std::string>("*", version.getMinor().getStringValue());
			Assert::AreEqual<std::string>("3", version.getBuild().getStringValue());
			Assert::AreEqual<std::string>("4", version.getRevision().getStringValue());
		}
	};
	std::unique_ptr<TransformerManager> DotNetTransformerTest::transformerManager;
}