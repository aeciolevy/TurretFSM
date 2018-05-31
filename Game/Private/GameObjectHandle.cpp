#include "Game\Public\GameObjectHandle.h"
#include "Game\Public\GameObjectInventory.h"

bool GameObjectHandle::IsValid() const
{
	return GameObjectInventory::Instance()->Exists(mHash);
}

GameObject* GameObjectHandle::Get() const
{

	return GameObjectInventory::Instance()->Lookup(mHash);
}