#pragma once
#include "..\JYG_System_Lib_PublicDefine.h"

#include ".\CAlipayOpenAPICtrl_MacroDefine.h"
#include ".\CAlipayOpenAPICtrl_EnumDefine.h"
#include ".\CAlipayOpenAPICtrl_StructDefine.h"

#include "..\CJYGPayOpenAPICtrl\CJYGPayOpenAPICtrl_MacroDefine.h"
#include "..\CJYGPayOpenAPICtrl\CJYGPayOpenAPICtrl_EnumDefine.h"
#include "..\CJYGPayOpenAPICtrl\CJYGPayOpenAPICtrl_StructDefine.h"
class CHTTPClientWTPCtrl;
class CHTTPSessionContext;

class CAlipayOpenAPICtrl
{
public:
	CAlipayOpenAPICtrl(void);
	virtual ~CAlipayOpenAPICtrl(void);

	/*
	˵��:
		��ʼ����������
	����:
	    Tstring ISVPID                  --�����ṩ��ID
		Tstring ISVAppID;               --�����ṩ��APP��ID
		Tstring ISVPrivateKey,          --�����ṩ��APP��˽Կ
		Tstring ISVAESKey,              --�����ṩ��AES����Կ
		Tstring ISVALIPublicKey,        --�����ṩ�߰��﹫Կ,������֤Ӧ������
		ALP_Charset Charset;         --�ӿ�ͨѶ��ʹ�õ��ַ���
		ALP_SignType SignType;       --��֤��ʹ�õ�ǩ��ģʽ
		Tstring BusinessServerURL;      --ҵ��������ĸ���ַURL

	*/
	BOOL InitAlipayOpenAPICtrl_ISV(
		Tstring ISVPid,Tstring ISVAppID,Tstring ISVPrivateKey,Tstring ISVAESKey,
		Tstring ISVALIPublicKey,Tstring BusinessServerURL);

	BOOL InitAlipayOpenAPICtrl_MCH(
		Tstring MchAppID,Tstring MchPrivateKey,Tstring ALIPublicKey,Tstring BusinessServerURL);//�̻�ģʽ

	BOOL ReleaseAlipayOpenAPICtrl();

	
	//֪ͨ�ص����
	BOOL ProcAlipayBussinessRequest(CHTTPSessionContext *SessionContext);//����֧�����ҵ������
	
	//****************************************************************************************
	//�������

	/*
	˵��:
		����Ԥ��������,���ɽ����õ��տ��ά��
	����:
	    Tstring MerchantAuthToken,  --�̻���Ȩ��TOKEN
		Tstring TradeNo             --�̻�������,64���ַ����ڡ�ֻ�ܰ�����ĸ�����֡��»��ߣ��豣֤���̻��˲��ظ�
		Tstring SellerId            --����֧�����û�ID�� �����ֵΪ�գ���Ĭ��Ϊ�̻�ǩԼ�˺Ŷ�Ӧ��֧�����û�ID 
		DOUBLE  TotalAmount         --�����ܽ���λΪԪ����ȷ��С�������λ��ȡֵ��Χ[0.01,100000000] ���ͬʱ�����ˡ����۽��������ɴ��۽����������ܽ����ߣ���������������������������ܽ�=�����۽�+�����ɴ��۽� 
		DOUBLE  DiscountableAmount  --���۽��. �����Żݼ���Ľ���λΪԪ����ȷ��С�������λ��ȡֵ��Χ[0.01,100000000] �����ֵδ���룬�������ˡ������ܽ��������ɴ��۽����ֵĬ��Ϊ�������ܽ�-�����ɴ��۽� 
		Tstring Subject             --�����ı���
		Tstring Description         --����������
		Tstring StoreID             --���̵�ID
		Tstring OperatorID          --����Ա��ID
		Tstring TerminalID          --�ն˻���ID
		DWORD   TimeoutExpress      --�ñʶ��������������ʱ�䣬���ڽ��رս��ס�����Ϊ��λ
		ALP_SettleInfo &SettleInfo  --���˽��㷽ʽ��Ϣ
		vector<JYGPay_GoodInfo*> &GoodInfoList --������������Ʒ�б���Ϣ.json��ʽ. ����˵�����������Ʒ��ϸ˵���� 
		vector<ALP_PayChannel> &PayChannelList --����֧������

		vector<ALP_ExtendParam> &ExtendParamList  --ҵ����չ���� 
		Tstring BusinessParams;     --�̻�����ҵ����Ϣ������ֵҪ��֧����Լ����Ӧ���ڰ�ȫ��Ӫ���Ȳ���ֱ����������ʽΪjson��ʽ
		Tstring MerchantOrderNo     --�̻�ԭʼ�����ţ���󳤶�����32λ
		Tstring &TradeLink,     --���ش˽���ɨ����URL,�������ɶ�ά��o���ɨ��
	����ֵ:
		����ɹ�����TRUE,���ʧ�ܷ���FALSE
	��ע:
		���֧��������ʵ��2������:
		    (0)���κζ���        ----���ʱ��֧����Ԥ��������,*����ȡ������
			(1)ɨ��֧�������ɽ���----���ʱ��֧���������˽���,*���Թرս���
			(2)ȷ�϶Խ���֧������----���ʱ��֧��������˽���,*�����˿��

		��������û���κζ���,��ô֧������û��������������.��ֻ��Ԥ��������
		����֧����ʵ�����ɽ��׵ĵ��Ӷ��᷵��AliTradeNo.
	*/

	BOOL RequestCreatePreTrade(
		Tstring MerchantAuthToken,
		Tstring TradeNo,Tstring SellerId,DOUBLE TradeAmount,DWORD TradeQuantity,DOUBLE DiscountableAmount,
		Tstring Subject,Tstring Description,Tstring StoreID,Tstring OperatorID,Tstring TerminalID,
		DWORD TimeoutExpress,vector<JYGPay_GoodInfo*> &GoodInfoList,vector<ALP_SettleInfo*> &SettleInfoList,
		vector<ALP_PayChannel> &PayChannelList,vector<ALP_ExtendParam*> &ExtendParamList,
		Tstring BusinessParams,Tstring MerchantOrderNo,Tstring &TradeLink,Tstring &ResultDesc);//����Ԥ��������������ά��

	//��������Э������
	static BOOL CreatePreTradeProtocol(
		Tstring AppID,Tstring PrivateKey,Tstring TradeNotifyURL,
		Tstring TradeNo,Tstring SellerId,DOUBLE TradeAmount,DWORD TradeQuantity,DOUBLE DiscountableAmount,
		Tstring Subject,Tstring Description,Tstring StoreID,Tstring OperatorID,Tstring TerminalID,
		DWORD TimeoutExpress,vector<JYGPay_GoodInfo*> &GoodInfoList,vector<ALP_SettleInfo*> &SettleInfoList,
		vector<ALP_PayChannel> &PayChannelList,vector<ALP_ExtendParam*> &ExtendParamList,
		Tstring BusinessParams,Tstring MerchantOrderNo,string &TradeProtocol,Tstring &ResultDesc);

	//--------------------------------
	/*
	˵��:
		����ʵ�ʴ�������,�ɹ��᷵��AliTradeNo
	����:
	    Tstring MerchantAuthToken,  --�̻���Ȩ��TOKEN
		Tstring TradeNo             --�̻�������,64���ַ����ڡ�ֻ�ܰ�����ĸ�����֡��»��ߣ��豣֤���̻��˲��ظ�
		Tstring SellerId            --����֧�����û�ID�� �����ֵΪ�գ���Ĭ��Ϊ�̻�ǩԼ�˺Ŷ�Ӧ��֧�����û�ID 
		DOUBLE  TotalAmount         --�����ܽ���λΪԪ����ȷ��С�������λ��ȡֵ��Χ[0.01,100000000] ���ͬʱ�����ˡ����۽��������ɴ��۽����������ܽ����ߣ���������������������������ܽ�=�����۽�+�����ɴ��۽� 
		DOUBLE  DiscountableAmount  --���۽��. �����Żݼ���Ľ���λΪԪ����ȷ��С�������λ��ȡֵ��Χ[0.01,100000000] �����ֵδ���룬�������ˡ������ܽ��������ɴ��۽����ֵĬ��Ϊ�������ܽ�-�����ɴ��۽� 
		Tstring Subject             --�����ı���
		Tstring Description         --����������
		Tstring StoreID             --���̵�ID
		Tstring OperatorID          --����Ա��ID
		Tstring TerminalID          --�ն˻���ID
		DWORD   TimeoutExpress      --�ñʶ��������������ʱ�䣬���ڽ��رս��ס�����Ϊ��λ
		ALP_SettleInfo &SettleInfo  --���㷽ʽ��Ϣ
		Alipay_LogisticsType LogisticsType,--��������
		ALP_RecvAddressInfo &RecvAddress,  --�ջ���ַ,���û���򱣳ֿ�ֵ
		vector<JYGPay_GoodInfo*> &GoodInfoList --������������Ʒ�б���Ϣ.json��ʽ. ����˵�����������Ʒ��ϸ˵���� 
		vector<ALP_PayChannel> &PayChannelList --����֧������

		vector<ALP_ExtendParam> &ExtendParamList  --ҵ����չ���� 
		Tstring BusinessParams;     --�̻�����ҵ����Ϣ������ֵҪ��֧����Լ����Ӧ���ڰ�ȫ��Ӫ���Ȳ���ֱ����������ʽΪjson��ʽ
		Tstring MerchantOrderNo     --�̻�ԭʼ�����ţ���󳤶�����32λ
		Tstring &AliTradeNo,        --���ش˽��׵İ��ｻ�׶�����
	����ֵ:
		����ɹ�����TRUE,���ʧ�ܷ���FALSE
	��ע:
		�����������������,����Ҫ������Һ����ҵ�֧����ID���ܴ����ɹ�,
		�������ȷʵ�ᱻ֧����������������AliTradeNo,���Թرպ�ȡ��.
	*/
	BOOL RequestCreateTrade(
		Tstring MerchantAuthToken,
		Tstring TradeNo,Tstring SellerId,Tstring BuyerID,DOUBLE TotalAmount,DOUBLE DiscountableAmount,
		Tstring Subject,Tstring Description,Tstring StoreID,Tstring OperatorID,Tstring TerminalID,
		DWORD TimeoutExpress,vector<JYGPay_GoodInfo*> &GoodInfoList,vector<ALP_SettleInfo*> &SettleInfoList,
		Alipay_LogisticsType LogisticsType,ALP_RecvAddressInfo &RecvAddress,
		vector<ALP_PayChannel> &PayChannelList,vector<ALP_ExtendParam*> &ExtendParamList,
		Tstring BusinessParams,Tstring MerchantOrderNo,Tstring &AliTradeNo,Tstring &ResultDesc);
	//--------------------------------
	//����H5�ֻ���վ֧��,
	BOOL RequestCreateH5Trade(
		Tstring TradeNo,DOUBLE TradeAmount,
		Tstring Subject,Tstring Description,Tstring StoreID,
		DWORD TimeoutExpress,vector<ALP_PayChannel> &PayChannelList,
		Tstring ReturnURL,Tstring ReturnParam,Tstring &RedirectURL,Tstring &ResultDesc);
	//--------------------------------
	/*
	˵��:
		����ȡ��Ԥ�����Ľ���
	����:
		Tstring MerchantAuthToken,          --�̻���Ȩ��TOKEN
		Tstring TradeNo,                    --�̻�������,64���ַ����ڡ�ֻ�ܰ�����ĸ�����֡��»��ߣ��豣֤���̻��˲��ظ�
		Tstring AliTradeNo,                 --֧�������׺ţ����̻������Ų���ͬʱΪ��
	����ֵ:
		����ɹ�����TRUE,���ʧ�ܷ���FALSE	
	��ע:
		ʵ�ʲ�������,�˽ӿڿ�������ȡ��Ԥ�����Ľ���,Ҳ���������ر�ʵ�����Ľ���,�Ƽ��ô˽ӿ�
	*/
	BOOL RequestCancelTrade(Tstring MerchantAuthToken,Tstring TradeNo,Tstring &ResultDesc);
	//--------------------------------
	/*
	˵��:
		���ڽ��״������û���һ��ʱ����δ����֧�����ɵ��øýӿ�ֱ�ӽ�δ����Ľ��׽��йرա�
	����:
		Tstring MerchantAuthToken,          --�̻���Ȩ��TOKEN
		Tstring TradeNo,                    --�̻�������,64���ַ����ڡ�ֻ�ܰ�����ĸ�����֡��»��ߣ��豣֤���̻��˲��ظ�
		Tstring AliTradeNo,                 --֧�������׺ţ����̻������Ų���ͬʱΪ��
		Tstring OperatorID,                 --����Ա��ID
	����ֵ:
		����ɹ�����TRUE,���ʧ�ܷ���FALSE	
	��ע:
		ʵ�ʲ���,�˽ӿڽ��ܹر�ʵ�����Ľ���
	*/
	BOOL RequestCloseTrade(Tstring MerchantAuthToken,Tstring TradeNo,Tstring AliTradeNo,Tstring OperatorID,Tstring &ResultDesc);
	//--------------------------------
	/*
	˵��:
		�����ָ�����׽����˿�
	����:
		Tstring MerchantAuthToken,    --�̻���Ȩ��TOKEN
		Tstring RefundIdentity,       --��ʶһ���˿�����ͬһ�ʽ��׶���˿���Ҫ��֤Ψһ�����貿���˿��˲����ش��� 
		Tstring TradeNo,              --�̻�������,64���ַ����ڡ�ֻ�ܰ�����ĸ�����֡��»��ߣ��豣֤���̻��˲��ظ�
		Tstring AliTradeNo,           --֧�������׺ţ����̻������Ų���ͬʱΪ��
		DOUBLE  RefundAmount,         --��Ҫ�˿�Ľ��ý��ܴ��ڶ������,��λΪԪ��֧����λС�� 
		Tstring RefundCurrency,       --�����˿������Ϣ USD CNY
		Tstring RefundReason,         --�˿��ԭ��˵��
		Tstring StoreID               --���̵�ID
		Tstring OperatorID            --����Ա��ID
		Tstring TerminalID            --�ն˻���ID
		vector<JYGPay_GoodInfo*> &GoodInfoList,  --������������Ʒ�б���Ϣ.json��ʽ. ����˵�����������Ʒ��ϸ˵���� 
		ALP_RefundTradeInfo &_ALP_RefundTradeInfo  --�������˿�����Ľ�����Ϣ
		Tstring &ResultDesc
	����ֵ:
		����ɹ�����TRUE,���ʧ�ܷ���FALSE
	��ע:
		������ɺ�,�˿��ʱ�䷶Χ��3����,�����˿�ʱ�䷶Χ�޷��޸�,���ڷ����˿���Ҫ���̻�����ȨTOKEN,������޷��Լ���ɵ�
	*/
	BOOL RequestRefundTrade(
		Tstring MerchantAuthToken,
		Tstring RefundIdentity,
		Tstring TradeNo,Tstring AliTradeNo,DOUBLE RefundAmount,Tstring RefundCurrency,Tstring RefundReason,
		Tstring StoreID,Tstring OperatorID,Tstring TerminalID,vector<JYGPay_GoodInfo*> &GoodInfoList,ALP_RefundTradeInfo **_ALP_RefundTradeInfo,Tstring &ResultDesc);
	BOOL ReturnRefundTrade(ALP_RefundTradeInfo **_ALP_RefundTradeInfo);
	//--------------------------------
	/*
	˵��:
		��ѯ�˿�Ľ�����Ϣ
	����:
		Tstring MerchantAuthToken,    --�̻���Ȩ��TOKEN
		Tstring RefundIdentity,       --��ʶһ���˿�����ͬһ�ʽ��׶���˿���Ҫ��֤Ψһ�����貿���˿��˲����ش��� 
		Tstring TradeNo,              --�̻�������,64���ַ����ڡ�ֻ�ܰ�����ĸ�����֡��»��ߣ��豣֤���̻��˲��ظ�
		Tstring AliTradeNo,           --֧�������׺ţ����̻������Ų���ͬʱΪ��
		DOUBLE &TotalAmount,          --�����˽��׵��ܼ�
		ALP_RefundTradeInfo **_ALP_RefundTradeInfo  --�������˿�����Ľ�����Ϣ(���ֲ�ȫ)
	����ֵ
		����ɹ�����TRUE,���ʧ�ܷ���FALSE
	*/
	//--------------------------------
	BOOL QueryRefundTradeInfo(
		Tstring MerchantAuthToken,
		Tstring TradeNo,
		Tstring AliTradeNo,
		Tstring RefundIdentity,DOUBLE &TotalAmount,ALP_RefundTradeInfo **_ALP_RefundTradeInfo,Tstring &ResultDesc);//��ѯָ�����׵��˿����

	
	//--------------------------------
	/*
	˵��:
		��ѯ������Ϣ
	����
		TradeNo --����֧��ʱ������̻�������,��֧�������׺Ų���ͬʱΪ�ա�
		AliTradeNo--֧�������׺ţ����̻������Ų���ͬʱΪ�� 	2014112611001004680 073956707
		orgpid--���м���ģʽ�����ã����������벻Ҫʹ��,˫��ͨ���ò���ָ����Ҫ��ѯ�Ľ��������յ�������pid;
		ALP_TradeInfo &TradeInfo  --�����˽��׵���Ϣ,ע��Ҫ�ͷ��ڲ�FundBillList
	����ֵ:
		�ɹ�����TRUE,ʧ�ܷ���FALSE
	��ע:
	    ʵ�ʲ���,�˽ӿ�ֻ�ܲ�ѯ�Ѿ�ʵ�ʴ����Ľ���,Ԥ���������޷��鵽.
		�ýӿ��ṩ����֧����֧�������Ĳ�ѯ���̻�����ͨ���ýӿ�������ѯ����״̬�������һ����ҵ���߼���
		��Ҫ���ò�ѯ�ӿڵ������ ���̻���̨�����硢�������ȳ����쳣���̻�ϵͳ����δ���յ�֧��֪ͨ�� 
		����֧���ӿں󣬷���ϵͳ�����δ֪����״̬����� ����alipay.trade.pay������INPROCESS��״̬�� 
		����alipay.trade.cancel֮ǰ����ȷ��֧��״̬��

	*/
	BOOL RequestAlipayTradeInfo(Tstring MerchantAuthToken,Tstring TradeNo,Tstring AliTradeNo,Tstring orgpid,ALP_TradeInfo **TradeInfo,Tstring &ResultDesc);//��ѯָ���Ľ�����Ϣ
	BOOL ReturnAlipayTradeInfo(ALP_TradeInfo **TradeInfo);

	//******************************************************************************************
	//�ʽ����
	/*
	˵��:
		����������.
	����:
		Tstring MerchantAuthToken,       --�̻���Ȩ��TOKEN
		Tstring SettleIdentity,          --����ķ��˱�ʶ
		Tstring TradeNo,                 --�̻�������,64���ַ����ڡ�ֻ�ܰ�����ĸ�����֡��»��ߣ��豣֤���̻��˲��ظ�
		Tstring AliTradeNo,              --֧�������׺ţ����̻������Ų���ͬʱΪ��
		Tstring OperatorID,              --������ID
		vector<ALP_SettleTradeInfo*> &SettleTradeList,        --���������Ϣ�б�
		Tstring &ResultDesc
	����ֵ
		����ɹ�����TRUE,���ʧ�ܷ���FALSE
	*/
	BOOL RequestSettleTrade(Tstring MerchantAuthToken,Tstring SettleIdentity,Tstring TradeNo,Tstring AliTradeNo,Tstring OperatorID,vector<ALP_SettleTradeInfo*> &SettleTradeList,Tstring &ResultDesc);

	/*
	˵��:
		ͨ��֧�����˻�����ת�� 
	����:
		Tstring MerchantAuthToken,         --�̻���Ȩ��TOKEN
		Tstring TransferID,                --ת�˲�����ʶID
		ALP_TransferType PayeeType,     --ת���տ�������
		Tstring PayeeAccount,              --ת���տ����˻�,��ת���տ����������ʹ��,������տ������ͬһ���˻���
		DOUBLE TransAmout,                 --ת�˽��
		Tstring ShowPayerName,             --�����������ʾ���տ���˵�����ҳ��������ֶβ�������Ĭ����ʾ�����֧������֤������λ���ơ�
		Tstring VerifyPayeeName,           --�տ��ʵ�����������������Ϊ�գ����У����˻���֧�����Ǽǵ�ʵ���Ƿ����տ��ʵ����һ�¡� 
		Tstring TransRemake,               --ת�˱�ע�������Ϊ��ҵ�˻�����ת�˽��ﵽ�����ڵ��ڣ�50000Ԫ������Ϊ�ա��տ�ɼ�����չʾ���տ��û�����֧�����С� 
		Tstring &AliTransferID             --�ɹ����ذ���ת��ID
		Tstring &ResultDesc
	����ֵ
		����ɹ�����TRUE,���ʧ�ܷ���FALSE
	*/
	BOOL RequestFundTransfer(
		Tstring MerchantAuthToken,Tstring TransferID,ALP_TransferType PayeeType,Tstring PayeeAccount,
		DOUBLE TransAmout,Tstring ShowPayerName,Tstring VerifyPayeeName,Tstring TransRemake,Tstring &AliTransferID,Tstring &ResultDesc);
	
	BOOL QueryFundTransferStatus(	
		Tstring MerchantAuthToken,Tstring TransferID,Tstring AliTransferID,
		ALP_FundTransferInfo &TransferInfo,Tstring &ResultDesc);//��ѯת�˲��������Ϣ

	//******************************************************************************************
	//�������
	/*
	˵��:
		Ϊ�����̻����ٲ��ˣ�֧���̻�ͨ�����ӿڻ�ȡ�̻������˵����ص�ַ
	����:
		
		Tstring MerchantAuthToken  --�̻���Ȩ��TOKEN
		Alipay_BillType BillType       --Ҫ���ص��˵�����
		SYSTEMTIME BillDate        --��ѯ������ʱ��
		Tstring SavePathFile,      --������ļ�·��
		
	����ֵ:
		����ɹ�����TRUE,���ʧ�ܷ���FALSE
	��ע:
		�˵���������֧���������˵������˵�����֧������˵�:
		��1�����˵������˵���֧�����ص����˵���ֻ������ǰһ��24��ǰ���˵���T+1�������ڸ�ʽ�磺2018-01-05
		ע�������ڵڶ���10:00�Ժ�����
		��2�����˵������˵���֧�����ص����˵���ֻ��������һ�µ��˵���Ϣ�����ڸ�ʽ�磺2018-01��
		ע�����˵�һ����ڴ���4�ջ�֮�����ɣ��������4�Ż�����������ء�
	*/
	BOOL DownLoadTradeBillList(Tstring MerchantAuthToken,Alipay_BillType BillType,SYSTEMTIME BillDate,Tstring SavePathFile,Tstring &ResultDesc);

	
	//******************************************************************************************
	//��Ȩ���
	BOOL GenerateGuestAuthLink(Tstring MerchantAppID,Tstring Credeit,DWORD AuthScope,Tstring &AuthLink);//���ɿͻ���Ȩ����,���������Ҫ�����ͻ����ʲ���Ȩ
	BOOL GenerateMerchantAuthLink(Tstring &AuthLink);//�����̻���Ȩ����,���������Ҫ�����̻�����Ȩ
	
	/*
	˵��:
		�����̻���Ȩ���ȡ��ȨTOKEN
	����:
		Tstring AppAuthCode,         --�̻�����Ȩ��
		BOOL ReflashToken,           --�����ˢ��TOKEN��ΪTRUE,����ǻ�ȡTOKEN��ΪFALSE
		MerchantAuthInfo &AuthInfo   --�������̻���Ȩ��Ϣ
	����ֵ:
		�ɹ�����TRUE,ʧ�ܷ���FALSE
	��ע:
		ע��:Ӧ����Ȩ��app_auth_codeΨһ�ģ�app_auth_codeʹ��һ�κ�ʧЧ��һ�죨������app_auth_code��ʼ��24Сʱ��δ��ʹ���Զ����ڣ� 
		ˢ�����ƺ����ǻᱣ֤�ϵ�app_auth_token��ˢ�¿�ʼ10�����ڿɼ���ʹ�ã��뼰ʱ�滻Ϊ����token
	*/
	BOOL RequestMerchantAuthToken(Tstring MerchantAuthCode,BOOL ReflashToken,ALP_MerchantAuthInfo **AuthInfo,Tstring &ResultDesc);//ͨ��AppAuthCode���AppAuthToken
	BOOL ReturnMerchantAuthToken(ALP_MerchantAuthInfo **AuthInfo);

	/*
	˵��:
		���ݹ˿���Ȩ������ȨTOKEN
	����:
		Tstring GuestAuthCode,       --�û�����Ȩ��
		BOOL ReflashToken,           --�����ˢ��TOKEN��ΪTRUE,����ǻ�ȡTOKEN��ΪFALSE
		GuestAuthInfo **AuthInfo,    --�����˹˿���Ȩ��Ϣ
		Tstring &ResultDesc
	����ֵ:
		�ɹ�����TRUE,ʧ�ܷ���FALSE
	��ע:
	*/
	BOOL RequestGuestAuthToken(Tstring GuestAuthCode,Tstring MerchantAuthToken,BOOL ReflashToken,ALP_GuestAuthInfo **AuthInfo,Tstring &ResultDesc);
	BOOL ReturnGuestAuthToken(ALP_GuestAuthInfo **AuthInfo);

	BOOL RegisterMerchantAuthCallBack(OnMerchantAuthCallBack fn,VOID *CustomParam);//ע���̻���ɵ�����Ӧ����Ȩ�Ľ���ص�
	BOOL RegisterGuestVerifyCallBack(OnGuestVerifyCallBack fn,VOID *CustomParam);//���˿������Ϣ��Ȩ��,֪ͨ�ⲿ��������֤�˻ص�,��ֹ�طŹ���
	BOOL RegisterGuestAuthCallBack(OnGuestAuthCallBack fn,VOID *CustomParam);//ע��˿���ɵ�������Ϣ��Ȩ�Ľ���ص�
	BOOL RegisterScanCodePayCallBack(OnScanCodePayCallBack fn,VOID *CustomParam);//ע�ᵱ���ɨ��֧���Ľ���ص�
	BOOL RegisterAliPayTradeExternProtocol(OnAliPayTradeExternProtocol fn,VOID *CustomParam);

	static BOOL AlphaSortFun(string Object1,string Object2);
private:
	BOOL InitFlag;
	BOOL ISV_MCH;//����ģʽISV=������ģʽ MCH=�̻�ģʽ
	Tstring ISVPID;
	Tstring ISVAESKey;

	Tstring AppID;
	Tstring PrivateKey;
	Tstring ALIPublicKey;
	
	ALP_Charset Charset;
	ALP_SignType SignType;
	Tstring BusinessServerURL;
	
	BOOL CreateRequestSignature(Tstring AppID,Tstring Method,Tstring Content,CHTTPClientWTPCtrl *HttpEngine);//������������ǩ��
	BOOL VerifyResponsSignature(string keyword,string RawResponseInfo);//У��Ӧ������ǩ��
	BOOL VerifyNotifySignature(string Content);//У��֪ͨ������ǩ��

	BOOL EncodeAuthContext(Tstring MerchantAppID,Tstring MerchantAuthToken,Tstring Credeit,Tstring &GuestContext);//������Ȩ������
	BOOL DecodeAuthContext(Tstring GuestContext,Tstring &MerchantAppID,Tstring &MerchantAuthToken,Tstring &Credeit);//������Ȩ������

	
	Tstring StringCodeConvert(BOOL EnDe,Tstring source);//ת���ַ�������

	//{
		//�̻�Ӧ����Ȩ�ص�
		BOOL ProcALP_MerchantAuthCallBackHandle(CHTTPSessionContext *SessionContext,Tstring &ResultDesc);//�����̻���Ȩ�ص�ҵ��
		BOOL RequestMerchantAuthDetail(Tstring MerchantAuthToken,ALP_MerchantAuthInfo *AuthInfo,Tstring &ResultDesc);//��ѯ��ǰ�̻���Ȩ����ϸ��Ϣ
		
		//�ͻ���Ϣ��Ȩ�ص�
		BOOL ProcALP_GuestAuthCallBackHandle(CHTTPSessionContext *SessionContext,Tstring &ResultDesc);
		BOOL RequestGuestAuthDetail(Tstring GuestAuthToken,Tstring MerchantAuthToken,ALP_GuestAuthInfo *AuthInfo,Tstring &ResultDesc);//��ѯ��ǰ�ͻ���Ȩ����ϸ��Ϣ

		//����֧����Ϣ�ص�
		BOOL ProcALP_ScanCodePayCallBackHandle(CHTTPSessionContext *SessionContext,Tstring &ResultDesc);//����ͻ�����֧���ص�ҵ��

		//{�ص��������
		OnMerchantAuthCallBack MerchantAuthCallBack;
		VOID *MerchantAuthCustomParam;
		OnGuestVerifyCallBack  GuestVerifyCallBack;
		VOID *GuestVerifyCustomParam;
		OnGuestAuthCallBack    GuestAuthCallBack;
		VOID *GuestAuthCustomParam;
		OnScanCodePayCallBack  ScanCodePayCallBack;
		VOID *ScanCodePayCustomParam;

		OnAliPayTradeExternProtocol AliPayTradeExternProtocolCallBack;
		VOID *AliPayTradeExternProtocolCustomParam;
		//}
	//}
};
