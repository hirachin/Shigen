
# include <Siv3D.hpp>
# include "Resource.h"


void Main()
{
	Resource resource(L"Data/Resource.ini");
	//resource.saveIni(L"Data/Resource.ini");

	while (System::Update())
	{
		ClearPrint();
		Println(resource);
		Println(DateTime::Now().format(L"HH:mm:ss"));
		Println(resource.getTimeStamp().format(L"HH:mm:ss"));

		resource.update();
	}
}
