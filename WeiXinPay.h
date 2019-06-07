#pragma once

#include "..\JYG_System_Lib_PublicDefine.h"


#include ".\CWeiXinPayOpenAPICtrl_MacroDefine.h"
#include ".\CWeiXinPayOpenAPICtrl_EnumDefine.h"
#include ".\CWeiXinPayOpenAPICtrl_StructDefine.h"

#include "..\CJYGPayOpenAPICtrl\CJYGPayOpenAPICtrl_MacroDefine.h"
#include "..\CJYGPayOpenAPICtrl\CJYGPayOpenAPICtrl_EnumDefine.h"
#include "..\CJYGPayOpenAPICtrl\CJYGPayOpenAPICtrl_StructDefine.h"
template <class TKey,class TValue> class CMapCtrl;
class CHTTPClientWTPCtrl;
class CTinyXmlCtrl;
class CAlipayOpenAPICtrl;
class CHTTPSessionContext;
class CWeiXinPayOpenAPICtrl
{
public:
	CWeiXinPayOpenAPICtrl(void);
	virtual ~CWeiXinPayOpenAPICtrl(void);
	
	friend class CWeiXinPayBusinessServiceCtrl;
	//������̻�ֱ��ģʽ,��ISVAppID,ISVMchIDӦ�ô��̻���,�ڵ��ýӿ�ʱ��AppID,MchID��������
	//����Ƿ�����ģʽ,��ISVAppID,ISVMchIDӦ�ô������̵�,�ڵ��ýӿ�ʱ��AppID,MchID��Ҫ����Ϊ�̻���
	//���Ҫʹ�÷�����ģʽ,������2����ͬ�Ĺ��ں�
	//ע��΢��֧����Ҫ�Ȱ�װ֤�鵽ϵͳ��.
	BOOL InitWeiXinPayOpenAPICtrl_ISV(
		Tstring ISVAppID,Tstring ISVMchID,
		Tstring ISVToken,Tstring ISVAPIKey,
		Tstring ISVAESKey,Tstring ISVCertP12_B64,
		Tstring BusinessServerURL);

	BOOL InitWeiXinPayOpenAPICtrl_MCH(
		Tstring MCHAppID,Tstring MCHID,
		Tstring MCHAPIKey,Tstring MCHCertP12_B64,
		Tstring BusinessServerURL);

	BOOL ReleaseWeiXinPayOpenAPICtrl();

	/*
	˵��:
		����Ԥ��������,���ɽ����õ��տ��ά��
	����:
		Tstring Merchant,             //΢��֧��������̻���
		Tstring TradeNo,              //�̻�������,64���ַ����ڡ�ֻ�ܰ�����ĸ�����֡��»��ߣ��豣֤���̻��˲��ظ�
		Tstring ProductID,            //NATIVEʱ���˲����ش����˲���Ϊ��ά���а�������ƷID���̻����ж��塣
		Tstring Subject,              //��Ʒ������ ���ֶ��밴�չ淶���ݣ�������������涨
		Tstring Description,          //��Ʒ��ϸ����������ʹ�õ�Ʒ�Żݵ��̻������ֶα��밴�չ淶�ϴ����������Ʒ�Żݲ���˵����(��Ѷ��ֵ����-QQ��Ա��ֵ 	)
		Tstring TerminalID,           //�Զ������������Ϊ�ն��豸��(�ŵ�Ż������豸ID)��PC��ҳ���ں���֧�����Դ�"WEB"
		Tstring ExtendParam,          //�������ݣ��ڲ�ѯAPI��֧��֪ͨ��ԭ�����أ�����Ϊ�Զ������ʹ�á�
		DOUBLE  TotalAmount,          //�����ܽ���λΪԪ�����֧�����
		BOOL    NoCreditPay,          //�������û�����ʹ�����ÿ�֧��
		BOOL    NeedReceipt,          //֧���ɹ���Ϣ��֧������ҳ�����ֿ�Ʊ��ڡ���Ҫ��΢��֧���̻�ƽ̨��΢�Ź���ƽ̨��ͨ���ӷ�Ʊ���ܣ������ֶβſ���Ч
		SYSTEMTIME TradeStartTime,    //��������ʱ�䣬��ʽΪyyyyMMddHHmmss
		DWORD TradeExpire,            //����ʧЧʱ�䣬���ӵ�λ
		Tstring GoodsTag,             //�����Żݱ�ǣ�ʹ�ô���ȯ�������Żݹ���ʱ��Ҫ�Ĳ�����˵���������ȯ�������Ż�
		Tstring &PrePayID             --΢�����ɵ�Ԥ֧���Ự��ʶ�����ں����ӿڵ�����ʹ�ã���ֵ��Ч��Ϊ2Сʱ
		Tstring &TradeLink,       --���ش˽���ɨ����URL,�������ɶ�ά��o���ɨ��

	��ע:
	    ����ʧЧʱ������Զ����Ŷ��Եģ�������Ӧ��֧����ʱ����һ���ش�����prepay_idֻ����Сʱ����Ч�ڣ�
		����������ʱ�䳬��2Сʱ��ʱ����Ҫ���������µ��ӿڻ�ȡ�µ�prepay_id���������ʱ�����
	*/
	BOOL CreatePreTrade(
		Tstring MchAppID,Tstring MchID,Tstring TradeNo,Tstring ProductID,Tstring Subject,Tstring Description,
		Tstring TerminalID,Tstring ExtendParam,DOUBLE  TradeAmount,DWORD TradeQuantity,vector<JYGPay_GoodInfo*> &GoodInfoList,
		BOOL    NoCreditPay,BOOL    NeedReceipt,SYSTEMTIME TradeStartTime,DWORD TradeExpire,   
		Tstring GoodsTag,JYGPay_PayMode PayMode,Tstring ClientIP,Tstring &PrePayID,Tstring &TradeLink,Tstring &ResultDesc);
	
	//��������Э������
	static BOOL CreatePreTradeProtocol(
		Tstring MchAppID,Tstring MchID,Tstring APIKey,Tstring Nonce,Tstring TradeNotifyURL,
		Tstring TradeNo,Tstring ProductID,Tstring Subject,Tstring Description,
		Tstring TerminalID,Tstring ExtendParam,DOUBLE  TradeAmount,DWORD TradeQuantity,vector<JYGPay_GoodInfo*> &GoodInfoList,
		BOOL    NoCreditPay,BOOL    NeedReceipt,SYSTEMTIME TradeStartTime,DWORD TradeExpire,    
		Tstring GoodsTag,JYGPay_PayMode PayMode,Tstring ClientIP,string &TradeProtocol,Tstring &ResultDesc);
	
	//����ɨ��URL,���׼ȷ��,���ں�����Ҫ��
	BOOL GetShotTradeLink(Tstring MchAppID,Tstring MchID,Tstring TradeLink,Tstring &ShotScanCode,Tstring &ResultDesc);

	

	/*
	˵��:
		����ȡ��Ԥ�����Ľ���
	����:
		Tstring MerchantAuthToken,          --�̻���Ȩ��TOKEN
		Tstring TradeNo,                    --�̻�������,64���ַ����ڡ�ֻ�ܰ�����ĸ�����֡��»��ߣ��豣֤���̻��˲��ظ�
	����ֵ:
		����ɹ�����TRUE,���ʧ�ܷ���FALSE	
	*/
	BOOL RequestCancelTrade(Tstring MchAppID,Tstring MchID,Tstring TradeNo,Tstring &ResultDesc);


	/*
	˵��:
		�����ָ�����׽����˿�
	����:
		Tstring MerchantAuthToken,    --�̻���Ȩ��TOKEN
		Tstring RefundID,       --��ʶһ���˿�����ͬһ�ʽ��׶���˿���Ҫ��֤Ψһ�����貿���˿��˲����ش��� 
		Tstring TradeNo,              --�̻�������,64���ַ����ڡ�ֻ�ܰ�����ĸ�����֡��»��ߣ��豣֤���̻��˲��ظ�
		Tstring AliTradeNo,           --֧�������׺ţ����̻������Ų���ͬʱΪ��
		DOUBLE  TotalAmount,          --�����ܽ���λΪԪ�����֧�����
		DOUBLE  RefundAmount,         --��Ҫ�˿�Ľ��ý��ܴ��ڶ������,��λΪԪ��֧����λС�� 
		Tstring RefundCurrency,       --�����˿������Ϣ USD CNY
		Tstring RefundReason,         --�˿��ԭ��˵��
		Alipay_RefundTradeInfo &_Alipay_RefundTradeInfo  --�������˿�����Ľ�����Ϣ
		Tstring &ResultDesc
	����ֵ:
		����ɹ�����TRUE,���ʧ�ܷ���FALSE
	��ע:
		������ɺ�,�˿��ʱ�䷶Χ��6����,�����˿�ʱ�䷶Χ�޷��޸�,���ڷ����˿���Ҫ���̻�����ȨTOKEN,������޷��Լ���ɵ�
	*/
	BOOL RequestRefundTrade(
		Tstring MchAppID,Tstring MchID,
		Tstring RefundID,
		Tstring TradeNo,Tstring WeiTradeNo,DOUBLE  TotalAmount,DOUBLE RefundAmount,Tstring RefundCurrency,
		Tstring RefundReason,WXP_RefundTradeInfo **RefundTradeInfo,Tstring &ResultDesc);
	BOOL ReturnRefundTrade(WXP_RefundTradeInfo **RefundTradeInfo);
	BOOL QueryRefundTradeInfo(
		Tstring MchAppID,Tstring MchID,Tstring TradeNo,Tstring WeiTradeNo,
		Tstring RefundID,Tstring WeiRefundID,WXP_RefundTradeInfo **RefundTradeInfo,Tstring &ResultDesc);//��ѯ�˿���Ϣ


	/*
	˵��:
		��ѯ������Ϣ
	����
		TradeNo --����֧��ʱ������̻�������,��֧�������׺Ų���ͬʱΪ�ա�
		AliTradeNo--֧�������׺ţ����̻������Ų���ͬʱΪ�� 	2014112611001004680 073956707
		Alipay_TradeInfo &TradeInfo  --�����˽��׵���Ϣ,ע��Ҫ�ͷ��ڲ�FundBillList
	����ֵ:
		�ɹ�����TRUE,ʧ�ܷ���FALSE
	*/
	BOOL RequestWeiXinTradeInfo(Tstring MchAppID,Tstring MchID,Tstring TradeNo,Tstring WeiTradeNo,WXP_TradeInfo **TradeInfo,Tstring &ResultDesc);//��ѯָ���Ľ�����Ϣ
	BOOL ReturnWeiXinTradeInfo(WXP_TradeInfo **TradeInfo);
	
	//**************************************֧��֪ͨ�ص����***************************************************

	BOOL ProcWeiXinPayBusinessRequest(CHTTPSessionContext *SessionContext);//����֧�����ҵ������

	BOOL RegisterRefundPayCallBack(OnWeiXinRefundTradeCallBack fn,VOID *CustomParam);//ע�ᵱ�����˿�Ļص�
	BOOL RegisterScanCodePayCallBack(OnWeiXinScanCodePayCallBack fn,VOID *CustomParam);//ע�ᵱ���ɨ��֧���Ľ���ص�
	BOOL RegisterDevAuthCallBack(OnWeiXinDevAuthCallBack fn,VOID *CustomParam);//ע��΢�ſ�������֤�ص�
	BOOL RegisterWeiXinPayTradeExternProtocol(OnWeiXinPayTradeExternProtocol fn,VOID *CustomParam);

private:
	BOOL InitFlag;
	BOOL ISV_MCH;
	Tstring AppID; //΢�Ź��ں��ϵĹ����˺�ID����ҵ��corpid��Ϊ��appId��
	Tstring MchID; //
	Tstring DevToken;//΢�Ź��ں��Ͽ��������õ�����(Token)
	Tstring APIKey;//΢��֧�������õ�API��Կ
	Tstring AESKey;
	Tstring CertName;
	BYTE   *CertP12DataBuff;
	DWORD   CertP12DataSize;
	Tstring BusinessServerURL;//ҵ��������ĸ���ַURL

	HCERTSTORE CertStoreHandle;
	PCCERT_CONTEXT CertContext;

	inline BOOL CreateRequestSignature(CTinyXmlCtrl *RequestContent);//������������ǩ��
	BOOL VerifyResposeSignature(CTinyXmlCtrl *ResposeContent);//У��Ӧ������ǩ��

	static Tstring WXDateTimeToString(SYSTEMTIME &dt);

	static BOOL AlphaSortFun(string Object1,string Object2);

	//---------------------------------------------
	BOOL ProcDevAuthCallBackHandle(CHTTPSessionContext *SessionContext,Tstring &ResultDesc);//΢�ſ�������֤HANDLE
	BOOL ProcScanCodePayCallBackHandle(CHTTPSessionContext *SessionContext,Tstring &ResultDesc);//����ͻ�����֧���ص�ҵ��
	BOOL ProcRefundTradeCallBackHandle(CHTTPSessionContext *SessionContext,Tstring &ResultDesc);//�������˿�Ļص�ҵ��

	//{�ص��������
	OnWeiXinScanCodePayCallBack  WeiXinScanCodePayCallBack;
	VOID *WeiXinScanCodePayCustomParam;

	OnWeiXinDevAuthCallBack WeiXinDevAuthCallBack;
	VOID *WeiXinDevAuthCustomParam;

	OnWeiXinRefundTradeCallBack WeiXinRefundTradeCallBack;
	VOID *WeiXinRefundTradeCustomParam;

	OnWeiXinPayTradeExternProtocol WeiXinPayTradeExternProtocolCallBack;
	VOID *WeiXinPayTradeExternProtocolCustomParam;
	//}
	
};
