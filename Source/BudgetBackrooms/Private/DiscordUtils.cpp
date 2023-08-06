#include "DiscordUtils.h"

void UDiscordUtils::ConvertDateToUnix(FDateTime date, int64& timestamp)
{
	timestamp = date.ToUnixTimestamp();

	// FDateTime::ToUnixTimestamp spits out some weird values if you didn't initialize the date in blueprints
	if (timestamp < 0)
		timestamp = 0;
}

void UDiscordUtils::GetRandomString(int32 Length, FString& RandomString)
{
	const FString characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	FString Result = "";
	for (int32 i = 0; i < Length; i++) {
		Result += characters[FMath::RandRange(0, characters.Len())];
	}
	RandomString = Result;
}