#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include <QDebug>

#include <comdef.h>
#include <comutil.h>

#include <dshow.h>

QStringList getCaptureDevices(GUID catGuid);

// ���������� ������ ��������� �����-������� � ������� json
QStringList getVideoCaptureDevices()
{
    return getCaptureDevices(CLSID_VideoInputDeviceCategory);
}

// ���������� ������ ��������� �����-������� � ������� json
QStringList getAudioCaptureDevices()
{
    return getCaptureDevices(CLSID_AudioInputDeviceCategory);
}

QStringList getCaptureDevices(GUID catGuid) //, QList<IMoniker*>& monList)
{
    // Create the System Device Enumerator.
    QStringList list;
    HRESULT hr;
    ICreateDevEnum *pDevEnum = NULL;
    IEnumMoniker *pEnum = NULL;

    // ����-���������
    if( catGuid == CLSID_VideoInputDeviceCategory){
        list.append("VS-A");
        list.append("VS-B");
    }else{
        list.append("AS-A");
        list.append("AS-B");
    }

    //

    hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC_SERVER,
                          IID_ICreateDevEnum, (void **)&pDevEnum);
    //CHECK(hr, "create SystemDeviceEnum");

    // ���������� ������ �����-����������
    hr = pDevEnum->CreateClassEnumerator(catGuid,&pEnum, 0);
    //CHECK(hr, "create ClassEnumerator");

    if(pEnum == NULL)
        qDebug() << "bad pEnum";

    IMoniker *pMoniker = NULL;
    while ( (pEnum != NULL) && pEnum->Next(1, &pMoniker, NULL) == S_OK)
    {
        IPropertyBag *pPropBag;
        hr = pMoniker->BindToStorage(0, 0, IID_IPropertyBag, (void **)&pPropBag);
        if (SUCCEEDED(hr))
        {
                    // To retrieve the filter's friendly name, do the following:
            VARIANT varName;
            VariantInit(&varName);
            hr = pPropBag->Read(L"FriendlyName", &varName, 0);
            if (SUCCEEDED(hr))
            {
                char* pN = _com_util::ConvertBSTRToString(varName.bstrVal);
                QString txt = QString::fromLocal8Bit(pN); // ����� ���������� ������ ���������

                list.append(txt);
            }

            VariantClear(&varName);

            pPropBag->Release();
        }
        pMoniker->Release();
    }

    if(pEnum != NULL)
        pEnum->Release();

    if(pDevEnum != NULL)
        pDevEnum->Release();

    return list;
}

#endif // UTILS_H
