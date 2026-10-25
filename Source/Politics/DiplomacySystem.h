#pragma once
#include "CoreMinimal.h"
#include "CoreTypes.h"
#include "DiplomacySystem.generated.h"

/** Bilateral relationship state between two factions. */
USTRUCT(BlueprintType)
struct POLITICS_API FDiplomaticRelation
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Diplomacy")
	FFactionId FactionA;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Diplomacy")
	FFactionId FactionB;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Diplomacy")
	EDiplomaticStance Stance = EDiplomaticStance::Neutral;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Diplomacy", meta = (ClampMin = "-1", ClampMax = "1"))
	float Reputation = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Diplomacy")
	TArray<FString> AgreementLog;
};

UENUM(BlueprintType)
enum class EDiplomaticProposalType : uint8
{
	Alliance, Ceasefire, TradeAgreement, IntelligenceSharing, MilitaryAid
};

/**
 * Computes whether a diplomatic proposal is likely to be accepted, based on
 * reputation, relative strategic interest (territory/resources at stake)
 * and prior decisions - not a hidden coin flip.
 */
UCLASS()
class POLITICS_API UDiplomacySystem : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Diplomacy")
	float EvaluateProposalAcceptance(const FDiplomaticRelation& Relation, EDiplomaticProposalType ProposalType,
		float ProposerStrategicPressure, float TargetStrategicPressure) const;

	UFUNCTION(BlueprintCallable, Category = "Diplomacy")
	void ApplyOutcome(UPARAM(ref) FDiplomaticRelation& Relation, EDiplomaticProposalType ProposalType, bool bAccepted);
};
