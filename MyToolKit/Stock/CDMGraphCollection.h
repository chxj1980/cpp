// �����Ϳ������á�����ࡱ�����ļ�������ɵ� IDispatch ��װ��

//#import "d:\\workspace_c3\\MyToolKit\\Unicode Debug\\DMGraph.dll" no_namespace
// CDMGraphCollection ��װ��

class CDMGraphCollection : public COleDispatchDriver
{
public:
	CDMGraphCollection(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
	CDMGraphCollection(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CDMGraphCollection(const CDMGraphCollection& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// ����
public:

	// ����
public:


	// IDMGraphCollection ����
public:
	long get_Count()
	{
		long result;
		InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Item(long index)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, index);
		return result;
	}
	long get_Selected()
	{
		long result;
		InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_Selected(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	LPDISPATCH Add()
	{
		LPDISPATCH result;
		InvokeHelper(0x4, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void Delete(long index)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, parms, index);
	}

	// IDMGraphCollection ����
public:

};
