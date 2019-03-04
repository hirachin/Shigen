
# include <Siv3D.hpp>
# include "Resource.h"


void Main()
{
	Resource resource(L"Data/Resource.ini");
	resource.saveIni(L"Data/Resource.ini");

	while (System::Update())
	{
		ClearPrint();
		Println(resource);
	}
}
