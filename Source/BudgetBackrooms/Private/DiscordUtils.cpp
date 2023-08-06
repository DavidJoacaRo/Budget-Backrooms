#include "DiscordUtils.h"

void UDiscordUtils::ConvertDateToUnix(FDateTime date, int64& timestamp)
{
	timestamp = date.ToUnixTimestamp();

	// FDateTime::ToUnixTimestamp spits out some weird values if you didn't initialize the date in blueprints
	if (timestamp < 0)
		timestamp = 0;
}
