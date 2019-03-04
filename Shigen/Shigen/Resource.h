#pragma once
# include <Siv3D.hpp>
# include <chrono>

class Resource
{
	int m_a;
	int m_b;
	int m_c;
	int m_d;

	DateTime m_timeStamp;

	FilePath m_path;

	DateTime StringToDateTime(const String& _dateStr)
	{
		const auto splitDateTime = _dateStr.split(L' ');

		if (splitDateTime.size() != 2) { return DateTime(); }

		const auto splitDate = splitDateTime[0].split(L'/');
		const auto splitTime = splitDateTime[1].split(L':');

		if (splitDate.size() != 3 || splitTime.size() != 3) { return DateTime(); }

		const int32 year = Parse<int32>(splitDate[0]);
		const int32 month = Parse<int32>(splitDate[1]);
		const int32 date = Parse<int32>(splitDate[2]);

		const int32 hour = Parse<int32>(splitTime[0]);
		const int32 min = Parse<int32>(splitTime[1]);
		const int32 sec = Parse<int32>(splitTime[2]);

		const DateTime datetime(year, month, date, hour, min, sec);

		return datetime;
	}


public:

	Resource() :m_a(0), m_b(0), m_c(0), m_d(0),m_timeStamp(DateTime::Now()) {}

	Resource(const FilePath& _path):m_path(_path)
	{
		loadIni(_path);
	}

	~Resource()
	{
		saveIni(m_path);
	}

	DateTime getTimeStamp()const { return m_timeStamp; }

	bool loadIni(const FilePath& _path)
	{
		INIReader ini(_path);

		if (!ini) { return false; }

		m_a = ini.getOr<int>(L"Resource.a", 0);
		m_b = ini.getOr<int>(L"Resource.b", 0);
		m_c = ini.getOr<int>(L"Resource.c", 0);
		m_d = ini.getOr<int>(L"Resource.d", 0);
		m_timeStamp = StringToDateTime(ini.getOr<String>(L"Resource.timeStamp", DateTime::Now().format()));
		ini.close();
		return true;
	}

	bool saveIni(const FilePath& _path)
	{
		INIWriter ini(_path);

		ini.write(L"Resource", L"a", m_a);
		ini.write(L"Resource", L"b", m_b);
		ini.write(L"Resource", L"c", m_c);
		ini.write(L"Resource", L"d", m_d);
		ini.write(L"Resource", L"timeStamp", m_timeStamp.format());

		ini.close();
		return true;
	}

	int getA()const { return m_a; }
	int getB()const { return m_b; }
	int getC()const { return m_c; }
	int getD()const { return m_d; }


	void update()
	{
		const auto duration_ms = DateTime::Now() - m_timeStamp;
		const auto duration_min = DurationCast<Minutes, Microseconds>(duration_ms);
		
		const auto interval_min = Minutes(1);


		if (duration_min >= interval_min)
		{
			for (auto d_min = duration_min; d_min >= interval_min; d_min -= interval_min)
			{
				m_a += 3;
				m_b += 3;
				m_c += 3;
				m_d += 1;
				m_timeStamp = DateTime::Now();
			}
		}

		

	}
};

template <class CharType>
inline std::basic_ostream<CharType>& operator << (std::basic_ostream<CharType>& os, const Resource& r)
{
	return os << CharType('(') << r.getA() << CharType(',') << r.getB() << CharType(',') << r.getC() << CharType(',') << r.getD() << CharType(')');
}
