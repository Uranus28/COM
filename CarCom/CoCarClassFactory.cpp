//#include "pch.h"
#include "CoCarClassFactory.h"
#include "CoCar.h"

//обращение к глобальным переменным
extern DWORD g_lockCount;
extern DWORD g_objCount;


STDMETHODIMP_(ULONG) CoCarClassFactory::AddRef()
{
	return ++m_refCount;
}

STDMETHODIMP_(ULONG) CoCarClassFactory::Release()
{
	if (--m_refCount == 0)
	{
		delete this;
		return 0;
	}
	return m_refCount;
}

STDMETHODIMP CoCarClassFactory::QueryInterface(REFIID riid, void** ppv)
{
	// Which aspect of me do they want?
	if (riid == IID_IUnknown)
	{
		*ppv = (IUnknown*)this;
	}
	else if (riid == IID_IClassFactory)
	{
		*ppv = (IClassFactory*)this;
	}
	else
	{
		*ppv = NULL;
		return E_NOINTERFACE;
	}
	((IUnknown*)(*ppv))->AddRef();
	return S_OK;
}

//создание экземпляра компонента
STDMETHODIMP CoCarClassFactory::CreateInstance(LPUNKNOWN pUnkOuter, REFIID riid, void** ppv)
{
	// необходимо убедиться, что CLSID не пустой
	if (pUnkOuter != NULL)
		return CLASS_E_NOAGGREGATION;
	CoCar* pCarObj = NULL;
	HRESULT hr;
	pCarObj = new CoCar;
	// запросим нужный интерфейс
	hr = pCarObj->QueryInterface(riid, ppv);
	// Проверка возвращаемого значения QueryInterface
	if (FAILED(hr))
		delete pCarObj;
	return hr; // S_OK or E_NOINTERFACE.
}

CoCarClassFactory::CoCarClassFactory()
{
	m_refCount = 0;
	g_objCount++;
}

CoCarClassFactory::~CoCarClassFactory()
{
	g_objCount--;
}

//блокировка программы сервера в памяти
STDMETHODIMP CoCarClassFactory::LockServer(BOOL fLock)
{
	if (fLock)
		++g_lockCount;
	else
		--g_lockCount;
	return S_OK;
}
