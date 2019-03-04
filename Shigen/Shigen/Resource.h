#pragma once
# include <Siv3D.hpp>
# include <chrono>

class Resource
{
	int m_a;
	int m_b;
	int m_c;
	int m_d;

public:

	Resource() :m_a(0), m_b(0), m_c(0), m_d(0) {}

	Resource(const FilePath& _path)
	{
		loadIni(_path);
	}


	bool loadIni(const FilePath& _path)
	{
		INIReader ini(_path);

		if (!ini) { return false; }

		m_a = ini.getOr<int>(L"Resource.a", 0);
		m_b = ini.getOr<int>(L"Resource.b", 0);
		m_c = ini.getOr<int>(L"Resource.c", 0);
		m_d = ini.getOr<int>(L"Resource.d", 0);
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
		ini.close();
		return true;
	}

	int getA()const { return m_a; }
	int getB()const { return m_b; }
	int getC()const { return m_c; }
	int getD()const { return m_d; }
};

template <class CharType>
inline std::basic_ostream<CharType>& operator << (std::basic_ostream<CharType>& os, const Resource& r)
{
	return os << CharType('(') << r.getA() << CharType(',') << r.getB() << CharType(',') << r.getC() << CharType(',') << r.getD() << CharType(')');
}
