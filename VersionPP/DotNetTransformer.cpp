#include "stdafx.h"
#include "DotNetTransformer.h"

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN  
#include <Windows.h>
#endif

DotNetTransformer::DotNetTransformer()
{

}

DotNetTransformer::~DotNetTransformer()
{

}

std::string DotNetTransformer::getName() const
{
	return ".NET";
}

std::string DotNetTransformer::getIdentifier() const
{
	return "*";
}

bool DotNetTransformer::Transform(Version& version, const Version& currentVersion)
{
	if (version.getMajor().getStringValue().find(getIdentifier()) != std::string::npos || version.getMinor().getStringValue().find(getIdentifier()) != std::string::npos)
		throw std::exception("Only build or revision parts may contain a *.");
	boost::posix_time::ptime now = boost::posix_time::second_clock::local_time();
	unsigned int build = 0;
	unsigned int revision = 0;
	CalculateBuildRevision(now, build, revision);
	replaceIdentifier(version.getBuild(), std::to_string(build));
	replaceIdentifier(version.getRevision(), std::to_string(revision));
	if (version.getRevision().getStringValue() == "")
		version.getRevision().setStringValue(std::to_string(revision));
	return true;
}

void DotNetTransformer::CalculateBuildRevision(const boost::posix_time::ptime& dateTime, unsigned int& build, unsigned int& revision)
{
	using namespace boost;
	posix_time::ptime y2k(gregorian::date(2000, 1, 1), posix_time::time_duration(0, 0, 0));
	if (dateTime < y2k)
		throw std::exception("dateTime may not be anytime before year 2000.");

	posix_time::ptime time(dateTime);
	time += posix_time::minutes(GetDSTOffset(time));
	posix_time::time_duration diff = time - y2k;
	unsigned int totalSeconds = diff.total_seconds();
	build = (unsigned int)(totalSeconds / SECONDS_PER_DAY);
	revision = (unsigned int)((totalSeconds % SECONDS_PER_DAY) / 2);
}

boost::posix_time::ptime DotNetTransformer::CalculateBuildTime(const unsigned int build, const unsigned int revision)
{
	using namespace boost;
	posix_time::ptime time(gregorian::date(2000, 1, 1), posix_time::time_duration(0, 0, 0));
	time += gregorian::days(build);
	time += posix_time::seconds(revision * 2);
	time -= posix_time::minutes(GetDSTOffset(time));
	return time;
}

long DotNetTransformer::GetDSTOffset(const boost::posix_time::ptime& dateTime)
{
#ifdef _WIN32
	//this is the only Win32 specific function which should be replaced if ported to another platform.
	TIME_ZONE_INFORMATION tz;
	if (GetTimeZoneInformation(&tz) == TIME_ZONE_ID_DAYLIGHT)
		return tz.DaylightBias;
#endif
	return 0;
}