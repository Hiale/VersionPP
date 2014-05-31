#pragma once

#include "Transformer.h"

#define BOOST_DATE_TIME_NO_LIB
#include "boost/date_time.hpp"
#include "VersionPart.h"

class DotNetTransformer : public Transformer
{
public:
	DotNetTransformer();
	~DotNetTransformer();
	virtual std::string getName() const;
	virtual std::string getIdentifier() const;
	virtual bool Transform(Version& version, const Version& currentVersion);
private:
	static void CalculateBuildRevision(const boost::posix_time::ptime& time, unsigned int& build, unsigned int& revision);
	static boost::posix_time::ptime CalculateBuildTime(const unsigned int build, const unsigned int revision);
	static long GetDSTOffset(const boost::posix_time::ptime& dateTime);
	const static int SECONDS_PER_DAY = 86400;
};

