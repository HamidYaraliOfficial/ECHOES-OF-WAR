#pragma once
#include "CoreMinimal.h"
#include "CoreTypes.h"
#include "AdvisorSystem.generated.h"

UENUM(BlueprintType)
enum class EAdvisorRole : uint8
{
	Intelligence, LogisticsOfficer, Operations, Economic, Political, MilitaryResearch
};

/** One piece of advice generated purely from current simulation data. */
USTRUCT(BlueprintType)
struct UI_API FAdvisorBriefing
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Advisor")
	EAdvisorRole Role = EAdvisorRole::Operations;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Advisor")
	FString LocalizationKey;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Advisor")
	TMap<FString, FString> Params;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Advisor", meta = (ClampMin = "0", ClampMax = "1"))
	float Urgency = 0.f;
};

/**
 * War Cabinet advisors: each role surfaces a different slice of the same
 * underlying simulation data (never invents information), and the player
 * always makes the final call - advisors only prioritize and summarize.
 */
UCLASS()
class UI_API UAdvisorSystem : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Advisor")
	void SubmitBriefing(const FAdvisorBriefing& Briefing);

	UFUNCTION(BlueprintCallable, Category = "Advisor")
	TArray<FAdvisorBriefing> GetBriefingsForRole(EAdvisorRole Role) const;

	UFUNCTION(BlueprintCallable, Category = "Advisor")
	TArray<FAdvisorBriefing> GetMostUrgent(int32 MaxCount) const;

	UPROPERTY()
	TArray<FAdvisorBriefing> ActiveBriefings;
};
