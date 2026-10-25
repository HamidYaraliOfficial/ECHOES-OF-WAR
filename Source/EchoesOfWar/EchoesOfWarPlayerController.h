#pragma once
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CoreTypes.h"
#include "OrderSystem.h"
#include "EchoesOfWarPlayerController.generated.h"

/**
 * Player entry point for issuing Strategic/Operational/Tactical commands.
 * Multiplayer-ready: in a networked session every mutating call here is
 * forwarded as an FCommandRequest to the server rather than applied
 * locally (see Networking module); in single-player it applies directly.
 */
UCLASS()
class ECHOESOFWAR_API AEchoesOfWarPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Command")
	void IssueUnitOrder(const FUnitOrder& Order);

	UFUNCTION(BlueprintCallable, Category = "Command")
	void SetActiveMapMode(bool bStrategicMap);

protected:
	virtual void SetupInputComponent() override;
};
