#include "interfaces.h"
#include "iid.h"
#include <iostream>

using namespace std;

int main()
{
	//инициализация СОМ
	CoInitialize(NULL); // This parameter is reserved, 
	// and should be NULL

	HRESULT hr;
	IClassFactory* pCF = NULL;
	ICreateCar* pICreateCar = NULL;
	IStats* pStats = NULL;
	IEngine* pEngine = NULL;

	//получение необходимого интерфейса фабрики классов(заданного идентификатором CLSID 
	hr = CoGetClassObject(CLSID_CoCar, CLSCTX_INPROC_SERVER,
		NULL, IID_IClassFactory, (void**)&pCF);

	// Make a CoCar & get ICreateCar.(создание экземпляра CoCar + освобождение интерфейса фабрики классов)
	hr = pCF->CreateInstance(NULL, IID_ICreateCar,
		(void**)&pICreateCar);
	pCF->Release();

	if (SUCCEEDED(hr))
	{
		pICreateCar->SetMaxSpeed(30);
		BSTR petName = SysAllocString(L"Shazzam!");
		pICreateCar->SetPetName(petName);
		SysFreeString(petName);

		// Now get IStats(hr= CreateInstance возвращает указатель на интерфейс ICreateCar и применяется метод QuertyInterface
		hr = pICreateCar->QueryInterface(IID_IStats,
			(void**)&pStats);
		pICreateCar->Release();
	}

	if (SUCCEEDED(hr))
	{
		// Show my car!
		pStats->DisplayStats();
		hr = pStats->QueryInterface(IID_IEngine,//получение указателя на IEngine
			(void**)&pEngine);
	}

	if (SUCCEEDED(hr))
	{
		int curSp = 0;
		int maxSp = 0;
		pEngine->GetMaxSpeed(&maxSp);

		do	// Zoom!
		{
			pEngine->SpeedUp();
			pEngine->GetCurSpeed(&curSp);
			cout << "Speed is: " << curSp << endl;
		} while (curSp <= maxSp);

		// Gotta convert to char array.
		char buff[80];
		BSTR bstr;
		pStats->GetPetName(&bstr);
		WideCharToMultiByte(CP_ACP, NULL, bstr, -1, buff,
			80, NULL, NULL);
		cout << buff << " has blown up! Lead Foot!" << endl << endl;
		SysFreeString(bstr);

		if (pEngine) pEngine->Release();
		if (pStats) pStats->Release();
	}

	CoUninitialize();
	return 0;
}
