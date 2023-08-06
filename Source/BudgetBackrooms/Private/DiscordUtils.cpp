


#include "DiscordUtils.h"

void UDiscordUtils::GetUnixTimestamp(int64& timestamp)
{
	timestamp = FDateTime::UtcNow().ToUnixTimestamp();
}