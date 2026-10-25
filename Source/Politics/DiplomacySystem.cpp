#include "DiplomacySystem.h"

float UDiplomacySystem::EvaluateProposalAcceptance(const FDiplomaticRelation& Relation, EDiplomaticProposalType ProposalType,
	float ProposerStrategicPressure, float TargetStrategicPressure) const
{
	float Base = 0.5f + Relation.Reputation * 0.3f;

	switch (ProposalType)
	{
		case EDiplomaticProposalType::Ceasefire:
			// More attractive to a faction under heavy pressure.
			Base += TargetStrategicPressure * 0.4f;
			break;
		case EDiplomaticProposalType::Alliance:
			Base += (Relation.Reputation > 0.f ? 0.2f : -0.3f);
			break;
		case EDiplomaticProposalType::TradeAgreement:
			Base += 0.1f;
			break;
		case EDiplomaticProposalType::IntelligenceSharing:
			Base += Relation.Reputation * 0.2f;
			break;
		case EDiplomaticProposalType::MilitaryAid:
			Base += ProposerStrategicPressure > TargetStrategicPressure ? 0.15f : -0.1f;
			break;
	}

	return FMath::Clamp(Base, 0.02f, 0.98f);
}

void UDiplomacySystem::ApplyOutcome(FDiplomaticRelation& Relation, EDiplomaticProposalType ProposalType, bool bAccepted)
{
	if (!bAccepted)
	{
		Relation.Reputation = FMath::Clamp(Relation.Reputation - 0.05f, -1.f, 1.f);
		return;
	}

	switch (ProposalType)
	{
		case EDiplomaticProposalType::Alliance: Relation.Stance = EDiplomaticStance::Alliance; break;
		case EDiplomaticProposalType::Ceasefire: Relation.Stance = EDiplomaticStance::Ceasefire; break;
		case EDiplomaticProposalType::TradeAgreement: Relation.Stance = EDiplomaticStance::Trade; break;
		default: break;
	}
	Relation.Reputation = FMath::Clamp(Relation.Reputation + 0.1f, -1.f, 1.f);
	Relation.AgreementLog.Add(FString::Printf(TEXT("Proposal type %d accepted"), (int32)ProposalType));
}
