#include "PlayerModelInventory.h"

const int PlayerModelInventory::INVENTORY_MORE_COINS = 1;

const int PlayerModelInventory::INVENTORY_MORE_PROTECTION = 5;

const int PlayerModelInventory::INVENTORY_MORE_GEMS = 1;

const int PlayerModelInventory::INVENTORY_MORE_BOOTS = 1;

const int PlayerModelInventory::INVENTORY_MORE_LIFE_POTIONS = 1;

PlayerModelInventory::PlayerModelInventory():
	m_coins(0),
	m_protection(0),
	m_gems(0),
	m_boots(0),
	m_potions(0)
{
}

PlayerModelInventory::~PlayerModelInventory()
{
}