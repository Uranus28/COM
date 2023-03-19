#pragma once
#include "interfaces.h"
#include "iid.h"
#include <windows.h>

const int MAX_SPEED = 500;

const int MAX_NAME_LENGTH = 40;



class CoCar : public IEngine, public ICreateCar, public IStats
{
private:
	BSTR m_petName; // ������������� ����� SysAllocString(),  
	// �������� � ����� ����� SysFreeString() 
	int m_maxSpeed; // ������������ �������� 
	int m_currSpeed; // ������� �������� ����r
	DWORD m_refCount; //���-�� ��������
	ITypeInfo* _typeInfo{};

public:
	CoCar();
	virtual ~CoCar();

	// IUnknown
	STDMETHODIMP QueryInterface(REFIID riid, void** pIFace);
	STDMETHODIMP_(DWORD)AddRef();
	STDMETHODIMP_(DWORD)Release();

	// IEngine
	STDMETHODIMP SpeedUp();
	STDMETHODIMP GetMaxSpeed(int* maxSpeed);
	STDMETHODIMP GetCurSpeed(int* curSpeed);

	// IStats
	STDMETHODIMP DisplayStats();
	STDMETHODIMP GetPetName(BSTR* petName);

	// ICreateCar
	STDMETHODIMP SetPetName(BSTR petName);
	STDMETHODIMP SetMaxSpeed(int maxSp);
};


