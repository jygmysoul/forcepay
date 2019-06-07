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
	说明:
		初始化环境参数
	参数:
	    Tstring ISVPID                  --服务提供者ID
		Tstring ISVAppID;               --服务提供者APP的ID
		Tstring ISVPrivateKey,          --服务提供者APP的私钥
		Tstring ISVAESKey,              --服务提供者AES的秘钥
		Tstring ISVALIPublicKey,        --服务提供者阿里公钥,用于验证应答数据
		ALP_Charset Charset;         --接口通讯所使用的字符集
		ALP_SignType SignType;       --验证所使用的签名模式
		Tstring BusinessServerURL;      --业务服务器的根地址URL

	*/
	BOOL InitAlipayOpenAPICtrl_ISV(
		Tstring ISVPid,Tstring ISVAppID,Tstring ISVPrivateKey,Tstring ISVAESKey,
		Tstring ISVALIPublicKey,Tstring BusinessServerURL);

	BOOL InitAlipayOpenAPICtrl_MCH(
		Tstring MchAppID,Tstring MchPrivateKey,Tstring ALIPublicKey,Tstring BusinessServerURL);//商户模式

	BOOL ReleaseAlipayOpenAPICtrl();

	
	//通知回调相关
	BOOL ProcAlipayBussinessRequest(CHTTPSessionContext *SessionContext);//处理支付相关业务请求
	
	//****************************************************************************************
	//交易相关

	/*
	说明:
		请求预创建交易,生成交易用的收款二维码
	参数:
	    Tstring MerchantAuthToken,  --商户授权的TOKEN
		Tstring TradeNo             --商户订单号,64个字符以内、只能包含字母、数字、下划线；需保证在商户端不重复
		Tstring SellerId            --卖家支付宝用户ID。 如果该值为空，则默认为商户签约账号对应的支付宝用户ID 
		DOUBLE  TotalAmount         --订单总金额，单位为元，精确到小数点后两位，取值范围[0.01,100000000] 如果同时传入了【打折金额】，【不可打折金额】，【订单总金额】三者，则必须满足如下条件：【订单总金额】=【打折金额】+【不可打折金额】 
		DOUBLE  DiscountableAmount  --打折金额. 参与优惠计算的金额，单位为元，精确到小数点后两位，取值范围[0.01,100000000] 如果该值未传入，但传入了【订单总金额】，【不可打折金额】则该值默认为【订单总金额】-【不可打折金额】 
		Tstring Subject             --订单的标题
		Tstring Description         --订单的描述
		Tstring StoreID             --商铺的ID
		Tstring OperatorID          --操作员的ID
		Tstring TerminalID          --终端机的ID
		DWORD   TimeoutExpress      --该笔订单允许的最晚付款时间，逾期将关闭交易。分钟为单位
		ALP_SettleInfo &SettleInfo  --分账结算方式信息
		vector<JYGPay_GoodInfo*> &GoodInfoList --订单包含的商品列表信息.json格式. 其它说明详见：“商品明细说明” 
		vector<ALP_PayChannel> &PayChannelList --可用支付渠道

		vector<ALP_ExtendParam> &ExtendParamList  --业务扩展参数 
		Tstring BusinessParams;     --商户传入业务信息，具体值要和支付宝约定，应用于安全，营销等参数直传场景，格式为json格式
		Tstring MerchantOrderNo     --商户原始订单号，最大长度限制32位
		Tstring &TradeLink,     --返回此交易扫描码URL,用于生成二维码給买家扫描
	返回值:
		如果成功返回TRUE,如果失败返回FALSE
	备注:
		买家支付动作其实分2个动作:
		    (0)无任何动作        ----这个时候支付宝预创建交易,*可以取消交易
			(1)扫码支付宝生成交易----这个时候支付宝创建了交易,*可以关闭交易
			(2)确认对交易支付费用----这个时候支付宝完成了交易,*可以退款交易

		但如果买家没有任何动作,那么支付宝并没有真正创建交易.这只是预创建交易
		凡是支付宝实际生成交易的单子都会返回AliTradeNo.
	*/

	BOOL RequestCreatePreTrade(
		Tstring MerchantAuthToken,
		Tstring TradeNo,Tstring SellerId,DOUBLE TradeAmount,DWORD TradeQuantity,DOUBLE DiscountableAmount,
		Tstring Subject,Tstring Description,Tstring StoreID,Tstring OperatorID,Tstring TerminalID,
		DWORD TimeoutExpress,vector<JYGPay_GoodInfo*> &GoodInfoList,vector<ALP_SettleInfo*> &SettleInfoList,
		vector<ALP_PayChannel> &PayChannelList,vector<ALP_ExtendParam*> &ExtendParamList,
		Tstring BusinessParams,Tstring MerchantOrderNo,Tstring &TradeLink,Tstring &ResultDesc);//请求预创建交易生产二维码

	//构建交易协议数据
	static BOOL CreatePreTradeProtocol(
		Tstring AppID,Tstring PrivateKey,Tstring TradeNotifyURL,
		Tstring TradeNo,Tstring SellerId,DOUBLE TradeAmount,DWORD TradeQuantity,DOUBLE DiscountableAmount,
		Tstring Subject,Tstring Description,Tstring StoreID,Tstring OperatorID,Tstring TerminalID,
		DWORD TimeoutExpress,vector<JYGPay_GoodInfo*> &GoodInfoList,vector<ALP_SettleInfo*> &SettleInfoList,
		vector<ALP_PayChannel> &PayChannelList,vector<ALP_ExtendParam*> &ExtendParamList,
		Tstring BusinessParams,Tstring MerchantOrderNo,string &TradeProtocol,Tstring &ResultDesc);

	//--------------------------------
	/*
	说明:
		请求实际创建交易,成功会返回AliTradeNo
	参数:
	    Tstring MerchantAuthToken,  --商户授权的TOKEN
		Tstring TradeNo             --商户订单号,64个字符以内、只能包含字母、数字、下划线；需保证在商户端不重复
		Tstring SellerId            --卖家支付宝用户ID。 如果该值为空，则默认为商户签约账号对应的支付宝用户ID 
		DOUBLE  TotalAmount         --订单总金额，单位为元，精确到小数点后两位，取值范围[0.01,100000000] 如果同时传入了【打折金额】，【不可打折金额】，【订单总金额】三者，则必须满足如下条件：【订单总金额】=【打折金额】+【不可打折金额】 
		DOUBLE  DiscountableAmount  --打折金额. 参与优惠计算的金额，单位为元，精确到小数点后两位，取值范围[0.01,100000000] 如果该值未传入，但传入了【订单总金额】，【不可打折金额】则该值默认为【订单总金额】-【不可打折金额】 
		Tstring Subject             --订单的标题
		Tstring Description         --订单的描述
		Tstring StoreID             --商铺的ID
		Tstring OperatorID          --操作员的ID
		Tstring TerminalID          --终端机的ID
		DWORD   TimeoutExpress      --该笔订单允许的最晚付款时间，逾期将关闭交易。分钟为单位
		ALP_SettleInfo &SettleInfo  --结算方式信息
		Alipay_LogisticsType LogisticsType,--物流类型
		ALP_RecvAddressInfo &RecvAddress,  --收货地址,如果没有则保持空值
		vector<JYGPay_GoodInfo*> &GoodInfoList --订单包含的商品列表信息.json格式. 其它说明详见：“商品明细说明” 
		vector<ALP_PayChannel> &PayChannelList --可用支付渠道

		vector<ALP_ExtendParam> &ExtendParamList  --业务扩展参数 
		Tstring BusinessParams;     --商户传入业务信息，具体值要和支付宝约定，应用于安全，营销等参数直传场景，格式为json格式
		Tstring MerchantOrderNo     --商户原始订单号，最大长度限制32位
		Tstring &AliTradeNo,        --返回此交易的阿里交易订单号
	返回值:
		如果成功返回TRUE,如果失败返回FALSE
	备注:
		这个是真正创建交易,必须要给出买家和卖家的支付宝ID才能创建成功,
		这个交易确实会被支付创建起来并返回AliTradeNo,可以关闭和取消.
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
	//创建H5手机网站支付,
	BOOL RequestCreateH5Trade(
		Tstring TradeNo,DOUBLE TradeAmount,
		Tstring Subject,Tstring Description,Tstring StoreID,
		DWORD TimeoutExpress,vector<ALP_PayChannel> &PayChannelList,
		Tstring ReturnURL,Tstring ReturnParam,Tstring &RedirectURL,Tstring &ResultDesc);
	//--------------------------------
	/*
	说明:
		用于取消预创建的交易
	参数:
		Tstring MerchantAuthToken,          --商户授权的TOKEN
		Tstring TradeNo,                    --商户订单号,64个字符以内、只能包含字母、数字、下划线；需保证在商户端不重复
		Tstring AliTradeNo,                 --支付宝交易号，和商户订单号不能同时为空
	返回值:
		如果成功返回TRUE,如果失败返回FALSE	
	备注:
		实际测试下来,此接口可以用来取消预创建的交易,也可以用来关闭实创建的交易,推荐用此接口
	*/
	BOOL RequestCancelTrade(Tstring MerchantAuthToken,Tstring TradeNo,Tstring &ResultDesc);
	//--------------------------------
	/*
	说明:
		用于交易创建后，用户在一定时间内未进行支付，可调用该接口直接将未付款的交易进行关闭。
	参数:
		Tstring MerchantAuthToken,          --商户授权的TOKEN
		Tstring TradeNo,                    --商户订单号,64个字符以内、只能包含字母、数字、下划线；需保证在商户端不重复
		Tstring AliTradeNo,                 --支付宝交易号，和商户订单号不能同时为空
		Tstring OperatorID,                 --操作员的ID
	返回值:
		如果成功返回TRUE,如果失败返回FALSE	
	备注:
		实际测试,此接口仅能关闭实创建的交易
	*/
	BOOL RequestCloseTrade(Tstring MerchantAuthToken,Tstring TradeNo,Tstring AliTradeNo,Tstring OperatorID,Tstring &ResultDesc);
	//--------------------------------
	/*
	说明:
		请求对指定交易进行退款
	参数:
		Tstring MerchantAuthToken,    --商户授权的TOKEN
		Tstring RefundIdentity,       --标识一次退款请求，同一笔交易多次退款需要保证唯一，如需部分退款，则此参数必传。 
		Tstring TradeNo,              --商户订单号,64个字符以内、只能包含字母、数字、下划线；需保证在商户端不重复
		Tstring AliTradeNo,           --支付宝交易号，和商户订单号不能同时为空
		DOUBLE  RefundAmount,         --需要退款的金额，该金额不能大于订单金额,单位为元，支持两位小数 
		Tstring RefundCurrency,       --订单退款币种信息 USD CNY
		Tstring RefundReason,         --退款的原因说明
		Tstring StoreID               --商铺的ID
		Tstring OperatorID            --操作员的ID
		Tstring TerminalID            --终端机的ID
		vector<JYGPay_GoodInfo*> &GoodInfoList,  --订单包含的商品列表信息.json格式. 其它说明详见：“商品明细说明” 
		ALP_RefundTradeInfo &_ALP_RefundTradeInfo  --返回了退款操作的交易信息
		Tstring &ResultDesc
	返回值:
		如果成功返回TRUE,如果失败返回FALSE
	备注:
		交易完成后,退款的时间范围是3个月,而且退款时间范围无法修改,好在发起退款需要有商户的授权TOKEN,买家是无法自己完成的
	*/
	BOOL RequestRefundTrade(
		Tstring MerchantAuthToken,
		Tstring RefundIdentity,
		Tstring TradeNo,Tstring AliTradeNo,DOUBLE RefundAmount,Tstring RefundCurrency,Tstring RefundReason,
		Tstring StoreID,Tstring OperatorID,Tstring TerminalID,vector<JYGPay_GoodInfo*> &GoodInfoList,ALP_RefundTradeInfo **_ALP_RefundTradeInfo,Tstring &ResultDesc);
	BOOL ReturnRefundTrade(ALP_RefundTradeInfo **_ALP_RefundTradeInfo);
	//--------------------------------
	/*
	说明:
		查询退款的交易信息
	参数:
		Tstring MerchantAuthToken,    --商户授权的TOKEN
		Tstring RefundIdentity,       --标识一次退款请求，同一笔交易多次退款需要保证唯一，如需部分退款，则此参数必传。 
		Tstring TradeNo,              --商户订单号,64个字符以内、只能包含字母、数字、下划线；需保证在商户端不重复
		Tstring AliTradeNo,           --支付宝交易号，和商户订单号不能同时为空
		DOUBLE &TotalAmount,          --返回了交易的总价
		ALP_RefundTradeInfo **_ALP_RefundTradeInfo  --返回了退款操作的交易信息(部分不全)
	返回值
		如果成功返回TRUE,如果失败返回FALSE
	*/
	//--------------------------------
	BOOL QueryRefundTradeInfo(
		Tstring MerchantAuthToken,
		Tstring TradeNo,
		Tstring AliTradeNo,
		Tstring RefundIdentity,DOUBLE &TotalAmount,ALP_RefundTradeInfo **_ALP_RefundTradeInfo,Tstring &ResultDesc);//查询指定交易的退款情况

	
	//--------------------------------
	/*
	说明:
		查询交易信息
	参数
		TradeNo --订单支付时传入的商户订单号,和支付宝交易号不能同时为空。
		AliTradeNo--支付宝交易号，和商户订单号不能同时为空 	2014112611001004680 073956707
		orgpid--银行间联模式下有用，其它场景请不要使用,双联通过该参数指定需要查询的交易所属收单机构的pid;
		ALP_TradeInfo &TradeInfo  --返回了交易的信息,注意要释放内部FundBillList
	返回值:
		成功返回TRUE,失败返回FALSE
	备注:
	    实际测试,此接口只能查询已经实际创建的交易,预创建交易无法查到.
		该接口提供所有支付宝支付订单的查询，商户可以通过该接口主动查询订单状态，完成下一步的业务逻辑。
		需要调用查询接口的情况： 当商户后台、网络、服务器等出现异常，商户系统最终未接收到支付通知； 
		调用支付接口后，返回系统错误或未知交易状态情况； 调用alipay.trade.pay，返回INPROCESS的状态； 
		调用alipay.trade.cancel之前，需确认支付状态；

	*/
	BOOL RequestAlipayTradeInfo(Tstring MerchantAuthToken,Tstring TradeNo,Tstring AliTradeNo,Tstring orgpid,ALP_TradeInfo **TradeInfo,Tstring &ResultDesc);//查询指定的交易信息
	BOOL ReturnAlipayTradeInfo(ALP_TradeInfo **TradeInfo);

	//******************************************************************************************
	//资金相关
	/*
	说明:
		请求结算分账.
	参数:
		Tstring MerchantAuthToken,       --商户授权的TOKEN
		Tstring SettleIdentity,          --定义的分账标识
		Tstring TradeNo,                 --商户订单号,64个字符以内、只能包含字母、数字、下划线；需保证在商户端不重复
		Tstring AliTradeNo,              --支付宝交易号，和商户订单号不能同时为空
		Tstring OperatorID,              --操作者ID
		vector<ALP_SettleTradeInfo*> &SettleTradeList,        --结算分账信息列表
		Tstring &ResultDesc
	返回值
		如果成功返回TRUE,如果失败返回FALSE
	*/
	BOOL RequestSettleTrade(Tstring MerchantAuthToken,Tstring SettleIdentity,Tstring TradeNo,Tstring AliTradeNo,Tstring OperatorID,vector<ALP_SettleTradeInfo*> &SettleTradeList,Tstring &ResultDesc);

	/*
	说明:
		通过支付宝账户进行转账 
	参数:
		Tstring MerchantAuthToken,         --商户授权的TOKEN
		Tstring TransferID,                --转账操作标识ID
		ALP_TransferType PayeeType,     --转账收款人类型
		Tstring PayeeAccount,              --转账收款人账户,与转账收款人类型配合使用,付款方和收款方不能是同一个账户。
		DOUBLE TransAmout,                 --转账金额
		Tstring ShowPayerName,             --付款方姓名。显示在收款方的账单详情页。如果该字段不传，则默认显示付款方的支付宝认证姓名或单位名称。
		Tstring VerifyPayeeName,           --收款方真实姓名。如果本参数不为空，则会校验该账户在支付宝登记的实名是否与收款方真实姓名一致。 
		Tstring TransRemake,               --转账备注。当付款方为企业账户，且转账金额达到（大于等于）50000元，不能为空。收款方可见，会展示在收款用户的收支详情中。 
		Tstring &AliTransferID             --成功返回阿里转账ID
		Tstring &ResultDesc
	返回值
		如果成功返回TRUE,如果失败返回FALSE
	*/
	BOOL RequestFundTransfer(
		Tstring MerchantAuthToken,Tstring TransferID,ALP_TransferType PayeeType,Tstring PayeeAccount,
		DOUBLE TransAmout,Tstring ShowPayerName,Tstring VerifyPayeeName,Tstring TransRemake,Tstring &AliTransferID,Tstring &ResultDesc);
	
	BOOL QueryFundTransferStatus(	
		Tstring MerchantAuthToken,Tstring TransferID,Tstring AliTransferID,
		ALP_FundTransferInfo &TransferInfo,Tstring &ResultDesc);//查询转账操作情况信息

	//******************************************************************************************
	//对账相关
	/*
	说明:
		为方便商户快速查账，支持商户通过本接口获取商户离线账单下载地址
	参数:
		
		Tstring MerchantAuthToken  --商户授权的TOKEN
		Alipay_BillType BillType       --要下载的账单类型
		SYSTEMTIME BillDate        --查询的日期时间
		Tstring SavePathFile,      --保存的文件路径
		
	返回值:
		如果成功返回TRUE,如果失败返回FALSE
	备注:
		账单下载日期支持下载日账单，月账单，不支持年度账单:
		（1）日账单：日账单不支持下载当日账单，只能下载前一日24点前的账单（T+1），日期格式如：2018-01-05
		注：建议在第二日10:00以后下载
		（2）月账单：月账单不支持下载当月账单，只能下载上一月的账单信息，日期格式如：2018-01。
		注：月账单一般会在次月4日或之后生成，建议次月4号或后面日期下载。
	*/
	BOOL DownLoadTradeBillList(Tstring MerchantAuthToken,Alipay_BillType BillType,SYSTEMTIME BillDate,Tstring SavePathFile,Tstring &ResultDesc);

	
	//******************************************************************************************
	//授权相关
	BOOL GenerateGuestAuthLink(Tstring MerchantAppID,Tstring Credeit,DWORD AuthScope,Tstring &AuthLink);//生成客户授权链接,这个链接需要传给客户访问并授权
	BOOL GenerateMerchantAuthLink(Tstring &AuthLink);//生成商户授权链接,这个链接需要传给商户打开授权
	
	/*
	说明:
		根据商户授权码获取授权TOKEN
	参数:
		Tstring AppAuthCode,         --商户的授权码
		BOOL ReflashToken,           --如果是刷新TOKEN则为TRUE,如果是获取TOKEN则为FALSE
		MerchantAuthInfo &AuthInfo   --返回了商户授权信息
	返回值:
		成功返回TRUE,失败返回FALSE
	备注:
		注意:应用授权的app_auth_code唯一的；app_auth_code使用一次后失效，一天（从生成app_auth_code开始的24小时）未被使用自动过期； 
		刷新令牌后，我们会保证老的app_auth_token从刷新开始10分钟内可继续使用，请及时替换为最新token
	*/
	BOOL RequestMerchantAuthToken(Tstring MerchantAuthCode,BOOL ReflashToken,ALP_MerchantAuthInfo **AuthInfo,Tstring &ResultDesc);//通过AppAuthCode获得AppAuthToken
	BOOL ReturnMerchantAuthToken(ALP_MerchantAuthInfo **AuthInfo);

	/*
	说明:
		根据顾客授权码获得授权TOKEN
	参数:
		Tstring GuestAuthCode,       --用户的授权码
		BOOL ReflashToken,           --如果是刷新TOKEN则为TRUE,如果是获取TOKEN则为FALSE
		GuestAuthInfo **AuthInfo,    --返回了顾客授权信息
		Tstring &ResultDesc
	返回值:
		成功返回TRUE,失败返回FALSE
	备注:
	*/
	BOOL RequestGuestAuthToken(Tstring GuestAuthCode,Tstring MerchantAuthToken,BOOL ReflashToken,ALP_GuestAuthInfo **AuthInfo,Tstring &ResultDesc);
	BOOL ReturnGuestAuthToken(ALP_GuestAuthInfo **AuthInfo);

	BOOL RegisterMerchantAuthCallBack(OnMerchantAuthCallBack fn,VOID *CustomParam);//注册商户完成第三方应用授权的结果回调
	BOOL RegisterGuestVerifyCallBack(OnGuestVerifyCallBack fn,VOID *CustomParam);//当顾客完成信息授权后,通知外部调用者验证此回调,防止重放攻击
	BOOL RegisterGuestAuthCallBack(OnGuestAuthCallBack fn,VOID *CustomParam);//注册顾客完成第三方信息授权的结果回调
	BOOL RegisterScanCodePayCallBack(OnScanCodePayCallBack fn,VOID *CustomParam);//注册当买家扫描支付的结果回调
	BOOL RegisterAliPayTradeExternProtocol(OnAliPayTradeExternProtocol fn,VOID *CustomParam);

	static BOOL AlphaSortFun(string Object1,string Object2);
private:
	BOOL InitFlag;
	BOOL ISV_MCH;//运行模式ISV=服务商模式 MCH=商户模式
	Tstring ISVPID;
	Tstring ISVAESKey;

	Tstring AppID;
	Tstring PrivateKey;
	Tstring ALIPublicKey;
	
	ALP_Charset Charset;
	ALP_SignType SignType;
	Tstring BusinessServerURL;
	
	BOOL CreateRequestSignature(Tstring AppID,Tstring Method,Tstring Content,CHTTPClientWTPCtrl *HttpEngine);//创建请求数据签名
	BOOL VerifyResponsSignature(string keyword,string RawResponseInfo);//校验应答数据签名
	BOOL VerifyNotifySignature(string Content);//校验通知答数据签名

	BOOL EncodeAuthContext(Tstring MerchantAppID,Tstring MerchantAuthToken,Tstring Credeit,Tstring &GuestContext);//加密授权上下文
	BOOL DecodeAuthContext(Tstring GuestContext,Tstring &MerchantAppID,Tstring &MerchantAuthToken,Tstring &Credeit);//解密授权上下文

	
	Tstring StringCodeConvert(BOOL EnDe,Tstring source);//转换字符串编码

	//{
		//商户应用授权回调
		BOOL ProcALP_MerchantAuthCallBackHandle(CHTTPSessionContext *SessionContext,Tstring &ResultDesc);//处理商户授权回调业务
		BOOL RequestMerchantAuthDetail(Tstring MerchantAuthToken,ALP_MerchantAuthInfo *AuthInfo,Tstring &ResultDesc);//查询当前商户授权的详细信息
		
		//客户信息授权回调
		BOOL ProcALP_GuestAuthCallBackHandle(CHTTPSessionContext *SessionContext,Tstring &ResultDesc);
		BOOL RequestGuestAuthDetail(Tstring GuestAuthToken,Tstring MerchantAuthToken,ALP_GuestAuthInfo *AuthInfo,Tstring &ResultDesc);//查询当前客户授权的详细信息

		//交易支付信息回调
		BOOL ProcALP_ScanCodePayCallBackHandle(CHTTPSessionContext *SessionContext,Tstring &ResultDesc);//处理客户交易支付回调业务

		//{回调函数相关
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
