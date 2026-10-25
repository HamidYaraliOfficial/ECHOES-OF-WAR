#include "DoctrineSystem.h"

void UDoctrineSystem::RegisterDoctrine(const FDoctrineProfile& Profile)
{
	Doctrines.Add(Profile);
}

bool UDoctrineSystem::GetDoctrine(FName DoctrineId, FDoctrineProfile& OutProfile) const
{
	for (const FDoctrineProfile& Profile : Doctrines)
	{
		if (Profile.DoctrineId == DoctrineId) { OutProfile = Profile; return true; }
	}
	return false;
}
