#pragma once
#include "CoreMinimal.h"
#include "CoreTypes.h"
#include "ResearchTree.generated.h"

UENUM(BlueprintType)
enum class EResearchField : uint8
{
	Logistics, Armor, Communications, Recon, Mobility, AirDefense,
	Engineering, Medical, Automation
};

/** A single research node with prerequisites and a real, applied gameplay effect. */
USTRUCT(BlueprintType)
struct RESEARCH_API FResearchNode
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Research")
	FName ResearchId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Research")
	EResearchField Field = EResearchField::Logistics;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Research")
	TArray<FName> Prerequisites;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Research")
	float CostIndustrialPoints = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Research")
	float DurationDays = 10.f;
	/** Gameplay tag consumed by the relevant system, e.g. "Logistics.RouteCapacity+10%". */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Research")
	FString AppliedEffectTag;
};

/** Per-faction research progress state. */
USTRUCT(BlueprintType)
struct RESEARCH_API FFactionResearchState
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Research")
	TSet<FName> CompletedResearch;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Research")
	FName ActiveResearchId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Research")
	float ProgressDaysAccumulated = 0.f;
};

/**
 * Data-driven research tree. Multiple mutually exclusive paths force real
 * trade-offs (e.g. Armor vs. Mobility), and every completed node applies a
 * concrete effect tag other systems read at runtime.
 */
UCLASS()
class RESEARCH_API UResearchTreeSystem : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Research")
	void RegisterNode(const FResearchNode& Node);

	UFUNCTION(BlueprintCallable, Category = "Research")
	bool CanStartResearch(const FFactionResearchState& State, FName ResearchId) const;

	UFUNCTION(BlueprintCallable, Category = "Research")
	bool TickResearch(UPARAM(ref) FFactionResearchState& State, float DeltaDays, TArray<FString>& OutNewlyAppliedEffects);

	UPROPERTY()
	TArray<FResearchNode> Nodes;

private:
	const FResearchNode* FindNode(FName Id) const;
};
