// �����Ϳ������á�����ࡱ�����ļ�������ɵ� IDispatch ��װ��

//#import "d:\\workspace_c3\\MyToolKit\\Unicode Debug\\DMGraph.dll" no_namespace
// CIDMGraphCtrlEvents ��װ��

class CIDMGraphCtrlEvents : public COleDispatchDriver
{
public:
	CIDMGraphCtrlEvents(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
	CIDMGraphCtrlEvents(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CIDMGraphCtrlEvents(const CIDMGraphCtrlEvents& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// ����
public:

	// ����
public:


	// _IDMGraphCtrlEvents ����
public:
	void CursorPosition(double X, double Y)
	{
		static BYTE parms[] = VTS_R8 VTS_R8 ;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, parms, X, Y);
	}
	void TrackModeChanged(long lNewState)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, parms, lNewState);
	}
	void Click()
	{
		InvokeHelper(DISPID_CLICK, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}

	// _IDMGraphCtrlEvents ����
public:

};
