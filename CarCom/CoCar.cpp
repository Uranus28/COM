
#include <stdio.h>
#include "CoCar.h"

extern DWORD g_objCount; //кол-во объектов



STDMETHODIMP CoCar::QueryInterface(REFIID riid, void** pIFace)
{
	// Which aspect of me do they want? 

	if (riid == IID_IUnknown)
	{
		*pIFace = (IUnknown*)(IEngine*)this;
		MessageBox(NULL, L"Handed out IUnknown", L"QI", MB_OK |
			MB_SETFOREGROUND);
	}

	else if (riid == IID_IEngine)
	{
		*pIFace = (IEngine*)this;
		MessageBox(NULL, L"Handed out IEngine", L"QI", MB_OK |
			MB_SETFOREGROUND);
	}


	else if (riid == IID_IStats)
	{
		*pIFace = (IStats*)this;
		MessageBox(NULL, L"Handed out IStats", L"QI", MB_OK |
			MB_SETFOREGROUND);
	}


	else if (riid == IID_ICreateCar)
	{
		*pIFace = (ICreateCar*)this;
		MessageBox(NULL, L"Handed out ICreateCar", L"QI", MB_OK |
			MB_SETFOREGROUND);
	}
	else
	{
		*pIFace = NULL;
		return E_NOINTERFACE;
	}
	//если функция предоставила интерфейс, то необходимо вызвать AddRef() 
	((IUnknown*)(*pIFace))->AddRef();

	return S_OK;
}

//добавление к счетчику единицы
STDMETHODIMP_(DWORD) CoCar::AddRef()
{
	++m_refCount;
	return m_refCount;
}

//отнимает единицы и проверяет на окончательный сброс
STDMETHODIMP_(DWORD) CoCar::Release()
{
	if (--m_refCount == 0)
	{
		delete this;
		return 0;
	}
	else
		return m_refCount;
}

CoCar::CoCar() : m_refCount(0), m_currSpeed(0), m_maxSpeed(0)
{
	++g_objCount;
	//инициализация
	m_petName = SysAllocString(L"Default Pet Name");
}
CoCar::~CoCar()
{
	--g_objCount;
	if (m_petName)
		//удаление
		SysFreeString(m_petName);
	MessageBox(NULL, L"CoCar is dead", L"Destructor", MB_OK |
		MB_SETFOREGROUND);
}

// IEngine

STDMETHODIMP CoCar::SpeedUp()//увеличение скорости на 10
{
	m_currSpeed += 10;
	return S_OK;
}
STDMETHODIMP CoCar::GetMaxSpeed(int* maxSpeed)//получение максимальной скорости
{
	*maxSpeed = m_maxSpeed;
	return S_OK;
}
STDMETHODIMP CoCar::GetCurSpeed(int* curSpeed)//получение скорости
{
	*curSpeed = m_currSpeed;
	return S_OK;
}

// ICreateCar

//принимает заданную клиентом BSTR и помещает ее во внутренний буфер BSTR
STDMETHODIMP CoCar::SetPetName(BSTR petName)
{
	SysReAllocString(&m_petName, petName);
	return S_OK;
}

//устанавливает максимальную скорость
STDMETHODIMP CoCar::SetMaxSpeed(int maxSp)
{
	if (maxSp <= MAX_SPEED)
		m_maxSpeed = maxSp;
	return S_OK;
}

//IStats

// Возвращает клиенту копию внутреннего буфера BSTR 
STDMETHODIMP CoCar::GetPetName(BSTR* petName)
{
	*petName = SysAllocString(m_petName);
	return S_OK;
}

//отображение текущей скорости и имени машины, преобразовывая Unicode-строку в ANSI.
STDMETHODIMP CoCar::DisplayStats()
{
	// Need to transfer a BSTR to a char array. 
	char buff[MAX_NAME_LENGTH];
	WideCharToMultiByte(CP_ACP, 0, m_petName, -1, buff, MAX_NAME_LENGTH, nullptr, nullptr);
	MessageBoxA(nullptr, buff, "Pet name", MB_OK | MB_SETFOREGROUND);
	memset(buff, 0, sizeof buff);

	sprintf_s(buff, "%d", m_maxSpeed);
	MessageBoxA(nullptr, buff, "Max speed", MB_OK | MB_SETFOREGROUND);

	return S_OK;
}
