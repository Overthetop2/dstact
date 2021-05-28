#include<iostream>
#include<ctime>
#include<string>

using u64 = std::uint64_t;

constexpr auto discordEpoch = 1420070400000;
constexpr auto timestampWidth = 22;
constexpr auto timestampStrBufLen = sizeof("1970-01-01T00:00:00Z");

u64 timestampFromSnowflake(u64 const snowflake) {
	return ((snowflake >> timestampWidth) + discordEpoch) / 1000;
}

std::string unixTimestampToIso8601(u64 const timestamp) {
	std::time_t const timestampCopy = timestamp;
	std::tm tmBuf {};
	
	localtime_s(&tmBuf, &timestampCopy);
	
	char buf[timestampStrBufLen] {};
	std::strftime(buf, sizeof(buf), "%Y-%m-%dT%H:%M:%SZ", &tmBuf);

	return { buf };
}

void printCreationTimeOfAccountSnowflake(u64 const snowflake) {
	auto const accountCreationDateTime = unixTimestampToIso8601(timestampFromSnowflake(snowflake));

	std::cout << snowflake << " was created on " << accountCreationDateTime << '\n';
}

int main(int const argc, char** argv) {
	try {
		for(auto i = 1; i < argc; ++i) {
			try {
				printCreationTimeOfAccountSnowflake(std::stoull(argv[i]));
			}
			catch(std::exception const& e) {
				printf("Error processing argument '%s' : %s\n", argv[i], e.what());
			}
		}
	}
	catch(...) {
		puts("An unknown error has occurred.");
	}

	return 0;
}
