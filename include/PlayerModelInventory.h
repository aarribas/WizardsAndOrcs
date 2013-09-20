#pragma once 

class PlayerModelInventory
{
	friend class PlayerModel;
public:

	PlayerModelInventory();
	~PlayerModelInventory();

public:

static const int INVENTORY_MORE_COINS;
static const int INVENTORY_MORE_PROTECTION;
static const int INVENTORY_MORE_GEMS;
static const int INVENTORY_MORE_BOOTS;
static const int INVENTORY_MORE_LIFE_POTIONS;

public:

	void addCoins(){if(m_coins<101)m_coins+=INVENTORY_MORE_COINS;} 
	void addProtection(){if(m_protection<101)m_protection+=INVENTORY_MORE_PROTECTION;}
	void addGems(){if(m_gems<101)m_gems+=INVENTORY_MORE_GEMS;}
	void addBoots(){if(m_boots<101)m_boots+=INVENTORY_MORE_BOOTS;}
	void addPotions(){if(m_boots<101)m_potions+=INVENTORY_MORE_LIFE_POTIONS;}
	int getCoins(){return m_coins;} 
	int getProtection(){return m_protection;}
	int getGems(){return m_gems;}
	int getBoots(){return m_boots;}
	int getPotions(){return m_potions;}

public:
	int m_coins;
	int m_protection;
	int m_gems;
	int m_boots;
	int m_potions;

};