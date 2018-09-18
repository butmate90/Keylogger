#ifndef __HELPER_H__
#define __HELPER_H__

#include <ctime>
#include <string>
#include <sstream>
#include <fstream>

class Helper {
public:
	struct DateTime {
		DateTime() {
			time_t ms;
			time(&ms);

			struct tm *info = localtime(&ms);
			D = info->tm_mday;
			m = info->tm_mon + 1;
			Y = 1900 + info->tm_year;
			M = info->tm_min;
			H = info->tm_hour;
			S = info->tm_sec;
		}
		DateTime(int D, int m, int Y, int M, int H, int S) : D(D), m(m), Y(Y), M(M), H(H), S(S){}

		DateTime now() {
			return DateTime();
		}

		template <typename T>std::string toString(const T& e) {
			std::ostringstream s;
			s << e;
			return s.str();
		}

		std::string GetDateString() {
			return std::string(D < 10 ? "0" : "") + toString(D) + "." +
				std::string(m < 10 ? "0" : "") + toString(m) + "." + toString(Y);
		}

		std::string GetTimeString() {
			return std::string(H < 10 ? "0" : "") + toString(H) + ":" +
				std::string(M < 10 ? "0" : "") + toString(M) + ":" +
				std::string(S < 10 ? "0" : "") + toString(S);
		}

		std::string GetDateTimeString() {
			return GetDateString() + " " + GetTimeString();
		}

		int D, m, Y, M, H, S;
	};

	static void writeAppLog(const std::string& s) {
		std::ofstream file("AppLog.txt", std::ios::app);
		file << "[" << Helper::DateTime().GetDateTimeString() << "]" <<
			"\n" << s << "\n" << "\n";
		file.close();
	}
};

#endif	//__HELPER_H__
