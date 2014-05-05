#include "stdafx.h"
#include "DotNetVersion.h"

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN  
#include <Windows.h>
#endif

void DotNetVersion::CalculateBuildRevision(const boost::posix_time::ptime& dateTime, int& build, int& revision)
{
	using namespace boost;
	posix_time::ptime y2k(gregorian::date(2000, 1, 1), posix_time::time_duration(0, 0, 0));
	if (dateTime < y2k)
		throw std::exception("dateTime may not be anytime before year 2000.");

	posix_time::ptime time(dateTime);
	time += posix_time::minutes(GetDSTOffset(time));
	posix_time::time_duration diff = time - y2k;
	int totalSeconds = diff.total_seconds();
	build = (int)(totalSeconds / SECONDS_PER_DAY);
	revision = (int)((totalSeconds % SECONDS_PER_DAY) / 2);
}

boost::posix_time::ptime DotNetVersion::CalculateBuildTime(const int build, const int revision)
{
	using namespace boost;
	posix_time::ptime time(gregorian::date(2000, 1, 1), posix_time::time_duration(0, 0, 0));
	time += gregorian::days(build);
	time += posix_time::seconds(revision * 2);
	time -= posix_time::minutes(GetDSTOffset(time));
	return time;
}

long DotNetVersion::GetDSTOffset(const boost::posix_time::ptime& dateTime)
{
#ifdef _WIN32
	//this is the only Win32 specific function which should be replaced if ported to another platform.
	TIME_ZONE_INFORMATION tz;
	if (GetTimeZoneInformation(&tz) == TIME_ZONE_ID_DAYLIGHT)
		return tz.DaylightBias;
#endif
	return 0;
}