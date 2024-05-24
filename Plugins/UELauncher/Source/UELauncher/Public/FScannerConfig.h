// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Filters/AssetFilter.h"
#include "Misc/AssetFilterData.h"
#include "FScannerConfig.generated.h"

// 规则匹配

UENUM(BlueprintType)
enum class EMatchLogic
{
	Necessary,
	Optional
};

UENUM(BlueprintType)
enum class ENameMatchMode
{
	StartWith,
	EndWith,
	Wildcard
};

UENUM(BlueprintType)
enum class EPathMatchMode
{
	WithIn,
	Wildcard
};

UENUM(BlueprintType)
enum class EPropertyMatchRule
{
	Equal,
	NotEqual
};


UCLASS(Blueprintable, BlueprintType)
class UOperatorBase : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	bool Match(UObject* Object, const FString& AssetType);
};


USTRUCT(BlueprintType)
struct UELAUNCHER_API FScannerConfig
{
	GENERATED_BODY()

public:
	// 当前配置的名字
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="配置名", Category="Base")
	FString ConfigName;

	// 开启所有 Rule 使用的全局扫描配置，开启后每个规则中的资源配置不生效
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="启动全局资源", Category="Global")
	bool bByGlobalScanFilters = false;

	// 屏蔽每个规则中配置的资源，仅使用全局资源
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="屏蔽每个规则中配置的资源", Category="Global",
		meta=(EditCondition="bByGlobalScanFilters"))
	bool bBlockRuleFilter = false;

	// 依赖 bByGlobalScanFilters，所有 Rule 使用的全局扫描配置（会忽略每个 Rule 中指定的扫描配置）
	// UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="全局扫描配置", Category="Global",
	// 	meta=(EditCondition="bByGlobalScanFilters"))
	// FAssetFilter GlobalScanFilters;

	// 在所有规则中都忽略的资源（路径、某个资源）
	// UPROPERTY(EditAnywhere,BlueprintReadWrite,DisplayName="全局忽略扫描配置",Category="Global",meta=(EditCondition="bByGlobalScanFilters"))
	// TArray<FAssetFilters> GlobalIgnoreFilters;

	// 启用 GIT 版本检测
	// UPROPERTY(EditAnywhere,BlueprintReadWrite,DisplayName="Git仓库扫描配置",Category="Global",meta=(EditCondition="bByGlobalScanFilters"))
	// FGitChecker GitChecker;

	// 开启规则白名单，只检测某些规则
	// UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="启动白名单", Category="Global")
	// bool bRuleWhiteList = false;

	// 白名单规则 ID 列表，注意：从 0 开始，RuleTable 里的 ID 要 - 1
	// UPROPERTY(EditAnywhere,BlueprintReadWrite,DisplayName="白名单列表")
	// TArray<FAssetFilters>RuleWhileListIDs;

	// 是否启用规则数据表（建议）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="启用规则数据表", Category="RulesTable")
	bool bUseRulesTable = false;

	// 指定一个 FScannerMatchRule 的 Datatable
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="规则数据表", Category="RulesTable",
		meta=(RequiredAssetDataTags="RowStructure=ScannerMatchRule", EditCondition="bUseRulesTable"))
	TSoftClassPtr<class UDataTable> ImportRulesTable;

	// FScannerMatchRule 规则数组，用于指定资源检查规则
	// UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="规则列表", Category="Rules")
	// TArray<FScannerMatchRule> ScannerRules;

	// 是否保存配置文件
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="存储配置文件", Category="Save")
	bool bSaveConfig = true;

	// 是否保存本次执行的结果
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="存储扫描结果", Category="Save")
	bool bSaveResult = true;

	// Config 和 Result 的存储路径
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="存储路径", Category="Save")
	FDirectoryPath SavePath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="独立运行模式", Category="Advanced")
	bool bStandaloneMode = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Advanced")
	FString AdditionalExecCommand;
};

USTRUCT(BlueprintType)
struct FGitChecker
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="启用 Git 仓库扫描")
	bool bGitCheck;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="记录提交人")
	bool bRecordCommiter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="GIT 仓库地址")
	FString RepoDir;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Git 提交记录比对（Begin/End Commit HASH）")
	bool bDiffCommit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="检查开始的 Git Commit HASH")
	uint8 BeginCommitHash;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="检查结束的 Git Commit HASH")
	uint8 EndCommitHash;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="检查待提交文件")
	bool bUncommitFiles;
};

USTRUCT(BlueprintType)
struct FNameRule
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ENameMatchMode MatchMode;

	// 匹配规则，是必须的还是可选的，Necessary是必须匹配所有的规则，Optional则只需要匹配规则中的一个
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EMatchLogic MatchLogic;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditCondition="MatchLogic == EMatchLogic::Optional"))
	int32 OptionalRuleMatchNum = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> Rules;
};

USTRUCT(BlueprintType)
struct FNameMatchRule
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FNameRule> Rules;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bReverseCheck;
};

USTRUCT(BlueprintType)
struct FPathRule
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EPathMatchMode MatchMode;

	// 匹配规则，是必须的还是可选的，Necessary是必须匹配所有的规则，Optional则只需要匹配规则中的一个
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EMatchLogic MatchLogic;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditCondition="MatchLogic == EMatchLogic::Optional"))
	int32 OptionalRuleMatchNum = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (RelativeToGameContentDir, LongPackageName))
	TArray<FString> Rules;
};

USTRUCT(BlueprintType)
struct FPathMatchRule
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FPathRule> Rules;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bReverseCheck;
};

USTRUCT(BlueprintType)
struct FPropertyMatchMapping
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="匹配模式")
	EPropertyMatchRule MatchRule;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="属性名称")
	FString PropertyName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="值")
	FString MatchValue;
};

USTRUCT(BlueprintType)
struct FPropertyRule
{
	GENERATED_USTRUCT_BODY()

public:
	// 匹配规则，是必须的还是可选的，Necessary是必须匹配所有的规则，Optional则只需要匹配规则中的一个
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EMatchLogic MatchLogic;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditCondition="MatchLogic == EMatchLogic::Optional"))
	int32 OptionalRuleMatchNum = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FPropertyMatchMapping> Rules;
};

USTRUCT(BlueprintType)
struct FPropertyMatchRule
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FPropertyRule> Rules;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bReverseCheck;
};

USTRUCT(BlueprintType)
struct FFileCommiter
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString File;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Commiter;
};

// Rule Matched info
USTRUCT(BlueprintType)
struct FRuleMatchedInfo
{
	GENERATED_USTRUCT_BODY()

public:
	FRuleMatchedInfo(): RuleName(TEXT("")), RuleDescribe(TEXT("")), RuleID(-1)
	{
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString RuleName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString RuleDescribe;
	// 该规则在配置数组中的下标
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 RuleID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, transient)
	TArray<FAssetData> Assets;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> AssetPackageNames;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FFileCommiter> AssetsCommiter;
};

// final result
USTRUCT(BlueprintType)
struct FMatchedResult
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FRuleMatchedInfo> MatchedAssets;
};


class FCustomPropertyMatchMappingDetails : public IPropertyTypeCustomization
{
public:
	// 重载接口
	virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder,
	                               IPropertyTypeCustomizationUtils& CustomizationUtils) override;
	virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow,
	                             IPropertyTypeCustomizationUtils& CustomizationUtils) override;

	static TSharedRef<IPropertyTypeCustomization> MakeInstance()
	{
		return MakeShareable(new FCustomPropertyMatchMappingDetails);
	}
};


USTRUCT(BlueprintType)
struct FScannerMatchRule
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="规则名")
	FString RuleName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="规则描述信息")
	FString RuleDescribe;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="是否启用当前规则")
	bool bEnableRule;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="该规则的优先级")
	int32 Priority;

	// 比如设置不同目录下的贴图规格不同，就要求只在某些目录下的资源才使用本规则扫描。
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="必须匹配规则中的 Filter 目录")
	bool bGlobalAssetMustMatchFilter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="指定扫描资源路径")
	TArray<FDirectoryPath> ScanFilters;

	// 建议每个规则只指定一个类型
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="指定要扫描的资源类型")
	TArray<UClass*> ScanAssetTypes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="用于指定命名匹配规则")
	TArray<FNameMatchRule> NameMatchRules;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="用于指定资源的路径匹配规则")
	TArray<FPathMatchRule> PathMatchRules;

	// 可以指定 C++/ 蓝图类
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="自定义匹配规则")
	TSubclassOf<UOperatorBase> CustomRules;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="本规则的忽略列表")
	TArray<FString> IgnoreFilters;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="是否开启对扫描结果的后处理")
	bool bEnablePostProcessor;

	// UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="指定对当前规则扫描的结果的后处理")
	// TArray<TSubclassOf<UScannnerPostProcessorBase>> PostProcessor;
};
