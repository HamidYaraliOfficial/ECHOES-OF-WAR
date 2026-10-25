#pragma once

#include "CoreMinimal.h"
#include "CoreTypes.generated.h"

/**
 * Shared identifiers and enums used across every simulation module.
 * All gameplay-facing IDs use FName/FString so they remain stable across
 * Save/Load, modding, and localization without depending on engine object
 * pointers (which are not safe to persist).
 */

USTRUCT(BlueprintType)
struct ECHOESOFWARCORE_API FRegionId
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IDs")
	FName Value = NAME_None;

	bool operator==(const FRegionId& Other) const { return Value == Other.Value; }
};
FORCEINLINE uint32 GetTypeHash(const FRegionId& Id) { return GetTypeHash(Id.Value); }

USTRUCT(BlueprintType)
struct ECHOESOFWARCORE_API FFactionId
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IDs")
	FName Value = NAME_None;

	bool operator==(const FFactionId& Other) const { return Value == Other.Value; }
};
FORCEINLINE uint32 GetTypeHash(const FFactionId& Id) { return GetTypeHash(Id.Value); }

USTRUCT(BlueprintType)
struct ECHOESOFWARCORE_API FUnitId
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IDs")
	FGuid Value;

	bool operator==(const FUnitId& Other) const { return Value == Other.Value; }
};
FORCEINLINE uint32 GetTypeHash(const FUnitId& Id) { return GetTypeHash(Id.Value); }

USTRUCT(BlueprintType)
struct ECHOESOFWARCORE_API FCommanderId
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IDs")
	FGuid Value;
};

UENUM(BlueprintType)
enum class EUnitCategory : uint8
{
	Infantry, MechanizedInfantry, Tank, Artillery, AntiAir, Recon,
	Engineer, SpecialForces, LogisticsUnit, Medical, Drone,
	ElectronicWarfare, Support
};

UENUM(BlueprintType)
enum class EOrderType : uint8
{
	Move, Attack, Defend, Hold, Scout, Patrol, Escort, Ambush,
	Support, Resupply, Repair, Retreat, Fortify, RegroupAt, CeaseFire
};

UENUM(BlueprintType)
enum class EOperationType : uint8
{
	Offensive, Defensive, ReconInForce, Encirclement, Breakthrough,
	Withdrawal, Counterattack, Holding
};

UENUM(BlueprintType)
enum class EWeatherType : uint8
{
	Clear, Rain, Storm, Fog, Snow, Sandstorm, HeatWave
};

UENUM(BlueprintType)
enum class ETerrainType : uint8
{
	Plains, Hills, Mountains, Forest, Urban, Marsh, Desert, River, Coast
};

UENUM(BlueprintType)
enum class EInfrastructureType : uint8
{
	Road, Bridge, Railway, PowerGrid, CommsRelay, Airport, Port, Factory, Warehouse, Hospital
};

UENUM(BlueprintType)
enum class EIntelSourceType : uint8
{
	Scout, Drone, Radar, ObservationPost, Satellite, Signals, HumanIntel, EngagedUnit
};

UENUM(BlueprintType)
enum class EDiplomaticStance : uint8
{
	War, Hostile, Neutral, Ceasefire, Trade, Alliance
};

UENUM(BlueprintType)
enum class ECommandRank : uint8
{
	Commander, GeneralOfficer, FieldOfficer, JuniorOfficer, NCO
};

UENUM(BlueprintType)
enum class EUILanguage : uint8
{
	English, Persian, Chinese
};

UENUM(BlueprintType)
enum class ETextDirection : uint8
{
	LeftToRight, RightToLeft
};

UENUM(BlueprintType)
enum class EUITheme : uint8
{
	Windows11, Light, Dark, HighContrast, BlueCommand, RedAlert
};

/** Generic [0..1] clamped rating used for morale, loyalty, security, etc. */
USTRUCT(BlueprintType)
struct ECHOESOFWARCORE_API FNormalizedRating
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rating")
	float Value = 0.5f;

	void Add(float Delta) { Value = FMath::Clamp(Value + Delta, 0.f, 1.f); }
};

/** A single logged event usable by the War Chronicle / AAR / Replay systems. */
USTRUCT(BlueprintType)
struct ECHOESOFWARCORE_API FWarLogEntry
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Log")
	FDateTime SimulatedTimestamp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Log")
	FName CategoryTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Log")
	FString LocalizationKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Log")
	TMap<FString, FString> Parameters;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Log")
	FFactionId RelatedFaction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Log")
	FRegionId RelatedRegion;
};
