#pragma once
#include "CoreMinimal.h"
#include "CoreTypes.h"
#include "CommandHierarchy.generated.h"

/** A commanding officer's persistent stats. Losing an experienced one should hurt. */
USTRUCT(BlueprintType)
struct UNITS_API FCommanderProfile
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Commander")
	FCommanderId Id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Commander")
	FText Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Commander")
	ECommandRank Rank = ECommandRank::JuniorOfficer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Commander", meta = (ClampMin = "0", ClampMax = "1"))
	float Leadership = 0.5f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Commander", meta = (ClampMin = "0", ClampMax = "1"))
	float Discipline = 0.5f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Commander", meta = (ClampMin = "0", ClampMax = "1"))
	float LogisticsSkill = 0.5f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Commander", meta = (ClampMin = "0", ClampMax = "2"))
	float RiskTolerance = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Commander", meta = (ClampMin = "0", ClampMax = "1"))
	float Experience = 0.1f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Commander")
	bool bIsCaptured = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Commander")
	bool bIsKIA = false;
};

/** One link in the chain of command: who reports to whom, and which units they command. */
USTRUCT(BlueprintType)
struct UNITS_API FCommandNode
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Command")
	FCommanderId CommanderId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Command")
	FCommanderId ReportsTo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Command")
	TArray<FUnitId> DirectlyCommandedUnits;
};

UCLASS()
class UNITS_API UCommandHierarchySystem : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Command")
	void PromoteCommander(UPARAM(ref) FCommanderProfile& Commander);

	UFUNCTION(BlueprintCallable, Category = "Command")
	void HandleCommanderCasualty(UPARAM(ref) FCommanderProfile& Commander, bool bCaptured);

	/** Overall command-quality multiplier applied to units under this commander. */
	UFUNCTION(BlueprintCallable, Category = "Command")
	float GetCommandQualityMultiplier(const FCommanderProfile& Commander) const;

	UPROPERTY()
	TArray<FCommandNode> Hierarchy;
};
