#pragma once

#define BOOST_DATE_TIME_NO_LIB
#include "boost/date_time.hpp"

class DotNetVersion
{
public:
	static void CalculateBuildRevision(const boost::posix_time::ptime& time, int& build, int& revision);
	static boost::posix_time::ptime CalculateBuildTime(const int build, const int revision);
private:
	static long GetDSTOffset(const boost::posix_time::ptime& dateTime);
	const static int SECONDS_PER_DAY = 86400;
};

