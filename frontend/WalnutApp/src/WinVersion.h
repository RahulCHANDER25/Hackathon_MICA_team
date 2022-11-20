#pragma once

struct VersionInfo
{
	VersionInfo() : Major(0), Minor(0), BuildNum(0) {}
	unsigned int Major;
	unsigned int Minor;
	unsigned int BuildNum;
};

class WinVersion
{
public:
	static bool GetVersion(VersionInfo& info);
	static bool IsBuildNumGreaterOrEqual(unsigned int buildNumber);
};