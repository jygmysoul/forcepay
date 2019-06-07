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
	//如果是商户直接模式,则ISVAppID,ISVMchID应该传商户的,在调用接口时候AppID,MchID不用设置
	//如果是服务商模式,则ISVAppID,ISVMchID应该传服务商的,在调用接口时候AppID,MchID需要设置为商户的
	//如果要使用服务商模式,必须有2个不同的公众号
	//注意微信支付需要先安装证书到系统中.
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
	说明:
		请求预创建交易,生成交易用的收款二维码
	参数:
		Tstring Merchant,             //微信支付分配的商户号
		Tstring TradeNo,              //商户订单号,64个字符以内、只能包含字母、数字、下划线；需保证在商户端不重复
		Tstring ProductID,            //NATIVE时，此参数必传。此参数为二维码中包含的商品ID，商户自行定义。
		Tstring Subject,              //商品简单描述 该字段请按照规范传递，具体请见参数规定
		Tstring Description,          //商品详细描述，对于使用单品优惠的商户，改字段必须按照规范上传，详见“单品优惠参数说明”(腾讯充值中心-QQ会员充值 	)
		Tstring TerminalID,           //自定义参数，可以为终端设备号(门店号或收银设备ID)，PC网页或公众号内支付可以传"WEB"
		Tstring ExtendParam,          //附加数据，在查询API和支付通知中原样返回，可作为自定义参数使用。
		DOUBLE  TotalAmount,          //订单总金额，单位为元，详见支付金额
		BOOL    NoCreditPay,          //可限制用户不能使用信用卡支付
		BOOL    NeedReceipt,          //支付成功消息和支付详情页将出现开票入口。需要在微信支付商户平台或微信公众平台开通电子发票功能，传此字段才可生效
		SYSTEMTIME TradeStartTime,    //订单生成时间，格式为yyyyMMddHHmmss
		DWORD TradeExpire,            //订单失效时间，分钟单位
		Tstring GoodsTag,             //订单优惠标记，使用代金券或立减优惠功能时需要的参数，说明详见代金券或立减优惠
		Tstring &PrePayID             --微信生成的预支付会话标识，用于后续接口调用中使用，该值有效期为2小时
		Tstring &TradeLink,       --返回此交易扫描码URL,用于生成二维码給买家扫描

	备注:
	    订单失效时间是针对订单号而言的，由于在应答支付的时候有一个必传参数prepay_id只有两小时的有效期，
		所以在重入时间超过2小时的时候需要重新请求下单接口获取新的prepay_id。其他详见时间规则
	*/
	BOOL CreatePreTrade(
		Tstring MchAppID,Tstring MchID,Tstring TradeNo,Tstring ProductID,Tstring Subject,Tstring Description,
		Tstring TerminalID,Tstring ExtendParam,DOUBLE  TradeAmount,DWORD TradeQuantity,vector<JYGPay_GoodInfo*> &GoodInfoList,
		BOOL    NoCreditPay,BOOL    NeedReceipt,SYSTEMTIME TradeStartTime,DWORD TradeExpire,   
		Tstring GoodsTag,JYGPay_PayMode PayMode,Tstring ClientIP,Tstring &PrePayID,Tstring &TradeLink,Tstring &ResultDesc);
	
	//构建交易协议数据
	static BOOL CreatePreTradeProtocol(
		Tstring MchAppID,Tstring MchID,Tstring APIKey,Tstring Nonce,Tstring TradeNotifyURL,
		Tstring TradeNo,Tstring ProductID,Tstring Subject,Tstring Description,
		Tstring TerminalID,Tstring ExtendParam,DOUBLE  TradeAmount,DWORD TradeQuantity,vector<JYGPay_GoodInfo*> &GoodInfoList,
		BOOL    NoCreditPay,BOOL    NeedReceipt,SYSTEMTIME TradeStartTime,DWORD TradeExpire,    
		Tstring GoodsTag,JYGPay_PayMode PayMode,Tstring ClientIP,string &TradeProtocol,Tstring &ResultDesc);
	
	//精简扫码URL,提高准确度,现在好像不需要了
	BOOL GetShotTradeLink(Tstring MchAppID,Tstring MchID,Tstring TradeLink,Tstring &ShotScanCode,Tstring &ResultDesc);

	

	/*
	说明:
		用于取消预创建的交易
	参数:
		Tstring MerchantAuthToken,          --商户授权的TOKEN
		Tstring TradeNo,                    --商户订单号,64个字符以内、只能包含字母、数字、下划线；需保证在商户端不重复
	返回值:
		如果成功返回TRUE,如果失败返回FALSE	
	*/
	BOOL RequestCancelTrade(Tstring MchAppID,Tstring MchID,Tstring TradeNo,Tstring &ResultDesc);


	/*
	说明:
		请求对指定交易进行退款
	参数:
		Tstring MerchantAuthToken,    --商户授权的TOKEN
		Tstring RefundID,       --标识一次退款请求，同一笔交易多次退款需要保证唯一，如需部分退款，则此参数必传。 
		Tstring TradeNo,              --商户订单号,64个字符以内、只能包含字母、数字、下划线；需保证在商户端不重复
		Tstring AliTradeNo,           --支付宝交易号，和商户订单号不能同时为空
		DOUBLE  TotalAmount,          --订单总金额，单位为元，详见支付金额
		DOUBLE  RefundAmount,         --需要退款的金额，该金额不能大于订单金额,单位为元，支持两位小数 
		Tstring RefundCurrency,       --订单退款币种信息 USD CNY
		Tstring RefundReason,         --退款的原因说明
		Alipay_RefundTradeInfo &_Alipay_RefundTradeInfo  --返回了退款操作的交易信息
		Tstring &ResultDesc
	返回值:
		如果成功返回TRUE,如果失败返回FALSE
	备注:
		交易完成后,退款的时间范围是6个月,而且退款时间范围无法修改,好在发起退款需要有商户的授权TOKEN,买家是无法自己完成的
	*/
	BOOL RequestRefundTrade(
		Tstring MchAppID,Tstring MchID,
		Tstring RefundID,
		Tstring TradeNo,Tstring WeiTradeNo,DOUBLE  TotalAmount,DOUBLE RefundAmount,Tstring RefundCurrency,
		Tstring RefundReason,WXP_RefundTradeInfo **RefundTradeInfo,Tstring &ResultDesc);
	BOOL ReturnRefundTrade(WXP_RefundTradeInfo **RefundTradeInfo);
	BOOL QueryRefundTradeInfo(
		Tstring MchAppID,Tstring MchID,Tstring TradeNo,Tstring WeiTradeNo,
		Tstring RefundID,Tstring WeiRefundID,WXP_RefundTradeInfo **RefundTradeInfo,Tstring &ResultDesc);//查询退款信息


	/*
	说明:
		查询交易信息
	参数
		TradeNo --订单支付时传入的商户订单号,和支付宝交易号不能同时为空。
		AliTradeNo--支付宝交易号，和商户订单号不能同时为空 	2014112611001004680 073956707
		Alipay_TradeInfo &TradeInfo  --返回了交易的信息,注意要释放内部FundBillList
	返回值:
		成功返回TRUE,失败返回FALSE
	*/
	BOOL RequestWeiXinTradeInfo(Tstring MchAppID,Tstring MchID,Tstring TradeNo,Tstring WeiTradeNo,WXP_TradeInfo **TradeInfo,Tstring &ResultDesc);//查询指定的交易信息
	BOOL ReturnWeiXinTradeInfo(WXP_TradeInfo **TradeInfo);
	
	//**************************************支付通知回调相关***************************************************

	BOOL ProcWeiXinPayBusinessRequest(CHTTPSessionContext *SessionContext);//处理支付相关业务请求

	BOOL RegisterRefundPayCallBack(OnWeiXinRefundTradeCallBack fn,VOID *CustomParam);//注册当交易退款的回调
	BOOL RegisterScanCodePayCallBack(OnWeiXinScanCodePayCallBack fn,VOID *CustomParam);//注册当买家扫描支付的结果回调
	BOOL RegisterDevAuthCallBack(OnWeiXinDevAuthCallBack fn,VOID *CustomParam);//注册微信开发者验证回调
	BOOL RegisterWeiXinPayTradeExternProtocol(OnWeiXinPayTradeExternProtocol fn,VOID *CustomParam);

private:
	BOOL InitFlag;
	BOOL ISV_MCH;
	Tstring AppID; //微信公众号上的公众账号ID（企业号corpid即为此appId）
	Tstring MchID; //
	Tstring DevToken;//微信公众号上开发者设置的令牌(Token)
	Tstring APIKey;//微信支付上设置的API密钥
	Tstring AESKey;
	Tstring CertName;
	BYTE   *CertP12DataBuff;
	DWORD   CertP12DataSize;
	Tstring BusinessServerURL;//业务服务器的根地址URL

	HCERTSTORE CertStoreHandle;
	PCCERT_CONTEXT CertContext;

	inline BOOL CreateRequestSignature(CTinyXmlCtrl *RequestContent);//创建请求数据签名
	BOOL VerifyResposeSignature(CTinyXmlCtrl *ResposeContent);//校验应答数据签名

	static Tstring WXDateTimeToString(SYSTEMTIME &dt);

	static BOOL AlphaSortFun(string Object1,string Object2);

	//---------------------------------------------
	BOOL ProcDevAuthCallBackHandle(CHTTPSessionContext *SessionContext,Tstring &ResultDesc);//微信开发者验证HANDLE
	BOOL ProcScanCodePayCallBackHandle(CHTTPSessionContext *SessionContext,Tstring &ResultDesc);//处理客户交易支付回调业务
	BOOL ProcRefundTradeCallBackHandle(CHTTPSessionContext *SessionContext,Tstring &ResultDesc);//处理交易退款的回调业务

	//{回调函数相关
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
