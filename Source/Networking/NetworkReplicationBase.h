#pragma once
#include "CoreMinimal.h"
#include "NetworkReplicationBase.generated.h"

/**
 * Base interface every server-authoritative command (orders, production
 * requests, diplomacy proposals) implements: a client-issued FCommandRequest
 * is validated and applied on the server, then the resulting world delta is
 * broadcast as a snapshot - clients never resolve gameplay locally, only
 * predict/interpolate for responsiveness. Anti-cheat rests on this single
 * chokepoint: no gameplay-affecting decision is ever trusted from a client.
 */
USTRUCT(BlueprintType)
struct NETWORKING_API FCommandRequest
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Networking")
	FName CommandType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Networking")
	FString PayloadJson;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Networking")
	int32 ClientSequenceId = 0;
};

UINTERFACE(MinimalAPI, Blueprintable)
class UServerAuthoritativeCommand : public UInterface
{
	GENERATED_BODY()
};

class NETWORKING_API IServerAuthoritativeCommand
{
	GENERATED_BODY()
public:
	/** Runs ONLY on the server. Returns false (and applies nothing) if the
	 *  request fails validation - the standard anti-cheat chokepoint. */
	virtual bool ValidateAndApply(const FCommandRequest& Request) = 0;
};
