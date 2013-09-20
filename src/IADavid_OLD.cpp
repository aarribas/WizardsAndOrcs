#include "IADavid.h"
#include "ActionManager.h"
#include "Core.h"
#include <cstdlib>
#include <ctime>

const int IA::CLOSE_RANGE=45;
const float IA::IA_UPDATE_RATE=0.5;
const float IA::MAX_LIFE_RATE=4;
const float IA::DIFFICULTY_UPDATE_RATE=10;

IA::IA()
{
}

IA::~IA()
{
}

void IA::Init(int PlayerId, bool CommonMovesOnly, int Difficulty, const Vector4 &Position, InterfaceLogicInfo* LogicInfo)
{
	DifficultyFactor[0]=0;
	DifficultyFactor[1]=0;
	KnowledgeTable.PlayerId=PlayerId;
	KnowledgeTable.CommonMovesOnly=CommonMovesOnly;
	KnowledgeTable.Difficulty=Difficulty;
	PreviousDifficulty=Difficulty;
	KnowledgeTable.Position=Position;
	pLogicInfo=LogicInfo;
	UpdateKnowledge();
	IAupdaterate=IA_UPDATE_RATE;
	DifficultyRate=DIFFICULTY_UPDATE_RATE;
	Idle();
}

void IA::Update(float timeElapsed)
{
	
	if (KnowledgeTable.Difficulty==1) //Normal mode, probabilidades variables dependiendo de la vida y el tiempo restante
	{
		AdjustDifficulty();
	}	
	
	if (IAupdaterate==IA_UPDATE_RATE)
	{
		/* initialize random seed: */
		srand ( time(NULL) );

		/* generate random number: */
		RandomNumber = rand() % 100;

		if (KnowledgeTable.Difficulty>0)
		{
			//Comprobamos si estamos perdiendo vida demasiado rapido
			PreviousLife=KnowledgeTable.Life;
			UpdateKnowledge();
			float LifeRate=(PreviousLife-KnowledgeTable.Life)/IAupdaterate;
			if (LifeRate>MAX_LIFE_RATE)
			{
				FastLifeLossReaction();	
			}
			else
			{
				EvaluateMainTree();
			}	
		}
		else
		{
				EvaluateMainTree();
		}
		

		//Si hemos subido la dificultad de forma variable la volvemos a bajar al cabo de DIFFICULTY_UPDATE_RATE segundos
		if ((PreviousDifficulty==1) && (KnowledgeTable.Difficulty==2))
		{
				DifficultyRate-=timeElapsed;
				if (DifficultyRate<0)
				{
					DifficultyRate=DIFFICULTY_UPDATE_RATE;
					KnowledgeTable.Difficulty=PreviousDifficulty;
				}
		}
	}
	
	IAupdaterate -=timeElapsed;

	if (IAupdaterate<0)
	{
		Idle(); //Cada IA_UPDATE_RATE obligamos a la IA a pararse
		IAupdaterate=IA_UPDATE_RATE;
	}
}

void IA::UpdateKnowledge()
{
	KnowledgeTable.Position=pLogicInfo->GetPosition(KnowledgeTable.PlayerId);
	KnowledgeTable.EnemyPosition=pLogicInfo->GetPosition(KnowledgeTable.PlayerId-1);
	KnowledgeTable.Life=pLogicInfo->GetPlayerLife(KnowledgeTable.PlayerId);
	KnowledgeTable.EnemyLife=pLogicInfo->GetPlayerLife(KnowledgeTable.PlayerId-1);
	KnowledgeTable.Round=pLogicInfo->GetRound();
	KnowledgeTable.RoundTime=pLogicInfo->GetRoundTime();
	KnowledgeTable.MyState=pLogicInfo->GetPlayerState(KnowledgeTable.PlayerId);
	KnowledgeTable.EnemyState=pLogicInfo->GetPlayerState(KnowledgeTable.PlayerId-1);
	KnowledgeTable.Collision=pLogicInfo->GetCollision();
	KnowledgeTable.DistanceBetweenPlayers=pLogicInfo->GetDistanceBetweenPlayers();
	KnowledgeTable.MinXPos=pLogicInfo->GetMinXPos();
	KnowledgeTable.MaxXPos=pLogicInfo->GetMaxXPos();
}

void IA::EvaluateMainTree()
{
	//Cerca
	if (KnowledgeTable.DistanceBetweenPlayers<CLOSE_RANGE)
	{
		if (KnowledgeTable.CommonMovesOnly)
		{
			EvaluateCloseRangeTree();
		}
		else
		{
			//TODO FULL MODE
		}
	}
	else
	{
		if (KnowledgeTable.CommonMovesOnly)
		{
			EvaluateFarRangeTree();
		}
		else
		{
			//TODO FULL MODE
		}
	}
}

void IA::EvaluateCloseRangeTree()
{
	
	int ProbabilityPunch=25+DifficultyFactor[0];
	int ProbabilityKick=20+DifficultyFactor[0];
	int ProbabilityIdle=20-DifficultyFactor[0];
	int ProbabilityFlee=5;
	int ProbabilityDefense=30-DifficultyFactor[0];
	
	if (KnowledgeTable.Difficulty==0) //Easy
	{
		ProbabilityIdle+=20; //Nos defendemos un 20% menos
		ProbabilityDefense-=20;
		ProbabilityFlee+=8;
		ProbabilityKick-=8; //Huimos un 8% mas y golpeamos un 8% menos
	}
	else if (KnowledgeTable.Difficulty==2) //Hard
	{
		ProbabilityPunch+=18; //Atacamos un 30% más
		ProbabilityKick+=12;
		ProbabilityFlee+=5; //Huimos un 5% más
		ProbabilityDefense-=16; // 16% menos de defensa que gastamos en ataque
		ProbabilityIdle-=19; //Solo un 1% de no hacer nada		
	}

	bool isEnemyAttacking;
	isEnemyAttacking=(KnowledgeTable.EnemyState==InterfaceLogicInfo::PUNCH || KnowledgeTable.EnemyState==InterfaceLogicInfo::KICK
		|| KnowledgeTable.EnemyState==InterfaceLogicInfo::MEGAPUNCH || KnowledgeTable.EnemyState==InterfaceLogicInfo::DEATHRAY);
	
	if (!isEnemyAttacking)
	{
		if (RandomNumber<ProbabilityPunch)
		{
			Punch();
		}
		else if (RandomNumber>=ProbabilityPunch && RandomNumber<(ProbabilityPunch+ProbabilityKick))
		{
			Kick();
		}
		else if (RandomNumber>=(ProbabilityPunch+ProbabilityKick) && RandomNumber<(ProbabilityPunch+ProbabilityKick+ProbabilityIdle))
		{
			Idle();
		}	
		else if (RandomNumber>=(ProbabilityPunch+ProbabilityKick+ProbabilityIdle) && RandomNumber<(ProbabilityPunch+ProbabilityKick+ProbabilityIdle+ProbabilityFlee))
		{
			Flee();
		}	
		else if (RandomNumber>=(100-ProbabilityDefense))
		{
			Defense();
		}	
	}
	else if (isEnemyAttacking)
	{
		if (KnowledgeTable.Collision)
		{
			Idle();
		}
		else
		{
			/*ProbabilityIdle=50-DifficultyFactor[1];
			ProbabilityDefense=40+(int)(2*DifficultyFactor[1]/3);
			ProbabilityFlee=10+(int)(DifficultyFactor[1]/3);*/
			ProbabilityPunch=25+DifficultyFactor[1];
			ProbabilityKick=20+DifficultyFactor[1];
			ProbabilityIdle=20-DifficultyFactor[1];
			ProbabilityFlee=5;
			ProbabilityDefense=30-DifficultyFactor[1];

			if (KnowledgeTable.Difficulty==0) //Easy
			{
				ProbabilityIdle+=20; //Nos defendemos un 20% menos
				ProbabilityDefense-=20;
				ProbabilityFlee+=8;
				ProbabilityKick-=8; //Huimos un 8% mas y golpeamos un 8% menos
			}
			else if (KnowledgeTable.Difficulty==2) //Hard
			{
				ProbabilityPunch+=18; //Atacamos un 20% más
				ProbabilityKick+=12;
				ProbabilityFlee+=5; //Huimos un 5% más
				ProbabilityDefense-=16; // 16% menos de defensa que gastamos en ataque
				ProbabilityIdle-=-9; //Solo un 1% de no hacer nada		
			}

			//if (KnowledgeTable.Difficulty==0) //Easy
			//{
			//	ProbabilityIdle+=20; //Huimos y nos defendemos un 20% menos
			//	ProbabilityDefense-=15;
			//	ProbabilityFlee+=10;
			//}
			//else if (KnowledgeTable.Difficulty==2) //Hard
			//{
			//	ProbabilityIdle-=40; //Huimos y nos defendemos un 40% más
			//	ProbabilityDefense+=25;
			//	ProbabilityFlee+=15;
			//}
			
			if (RandomNumber<ProbabilityPunch)
			{
				Punch();
			}
			else if (RandomNumber>=ProbabilityPunch && RandomNumber<(ProbabilityPunch+ProbabilityKick))
			{
				Kick();
			}
			else if (RandomNumber>=(ProbabilityPunch+ProbabilityKick) && RandomNumber<(ProbabilityPunch+ProbabilityKick+ProbabilityIdle))
			{
				Idle();
			}	
			else if (RandomNumber>=(ProbabilityPunch+ProbabilityKick+ProbabilityIdle) && RandomNumber<(ProbabilityPunch+ProbabilityKick+ProbabilityIdle+ProbabilityFlee))
			{
				Flee();
			}	
			else if (RandomNumber>=(100-ProbabilityDefense))
			{
				Defense();
			}	
			
			/*if (RandomNumber<ProbabilityIdle)
			{
				Idle();
			}
			else if (RandomNumber>=ProbabilityIdle && RandomNumber<(ProbabilityIdle+ProbabilityDefense))
			{
				Defense();
			}
			else if (RandomNumber>=(100-ProbabilityFlee))
			{
				Flee();
			}*/
		}
	}

}

void IA::EvaluateFarRangeTree()
{
	int ProbabilityIdle=10;
	int ProbabilityApproach=50;
	int ProbabilityFlee=40;
	
	if (KnowledgeTable.Difficulty==0) //Easy
	{
		ProbabilityIdle+=10; //Huimos y no hacemos nada un 20% mas
		ProbabilityFlee+=10;
		ProbabilityApproach-=20;
		
	}
	else if (KnowledgeTable.Difficulty==2) //Hard
	{
		ProbabilityApproach+=25; //Nos acercamos a luchar un 25% mas
		ProbabilityIdle-=10;
		ProbabilityFlee-=15;
	}

	if (RandomNumber<ProbabilityIdle)
	{
		Idle();
	}
	if (RandomNumber>=ProbabilityIdle && RandomNumber<(ProbabilityIdle+ProbabilityApproach))
	{
		Approach();
	}
	if (RandomNumber>=(100-ProbabilityFlee))
	{
		Flee();
	}
}

void IA::AdjustDifficulty()
{
	int LifeThreshold[3]={5,10,16};
	//Los primeros 25 segundos del round dificultad constante

	if (KnowledgeTable.RoundTime>75)
	{
		if ((KnowledgeTable.Life+LifeThreshold[2])<KnowledgeTable.EnemyLife)
		{
			FastLifeLossReaction();
		}
	}
	if ((KnowledgeTable.RoundTime<75) && (KnowledgeTable.RoundTime>50))
	{
		if (((KnowledgeTable.Life+LifeThreshold[2])<KnowledgeTable.EnemyLife) && (DifficultyFactor[0]<10))
		{
			DifficultyFactor[0]+=(int)((KnowledgeTable.EnemyLife-KnowledgeTable.Life)/8);
		}
		else if ((DifficultyFactor[0]>0) && (RandomNumber<75))
		//Si tenemos más vida un 75% de las veces bajamos la dificultad
		{
			DifficultyFactor[0]--;
		}
	}
	else if ((KnowledgeTable.RoundTime<50) && (KnowledgeTable.RoundTime>25))
	{
		//Más dificil a medida que avanza el tiempo
		if (((KnowledgeTable.Life+LifeThreshold[1])<KnowledgeTable.EnemyLife)  && (DifficultyFactor[0]<10))
		{
			DifficultyFactor[0]+=(int)((KnowledgeTable.EnemyLife-KnowledgeTable.Life)/4);
		}
		else if ((DifficultyFactor[0]>0) && (RandomNumber<50))
		//Si tenemos más vida un 50% de las veces bajamos la dificultad
		{
			DifficultyFactor[0]--;
		}
	}
	else if ((KnowledgeTable.RoundTime<25) && (KnowledgeTable.RoundTime>10))
	{
		//Más dificil a medida que avanza el tiempo
		if (((KnowledgeTable.Life+LifeThreshold[0])<KnowledgeTable.EnemyLife)  && (DifficultyFactor[0]<10))
		{
			DifficultyFactor[0]+=(int)((KnowledgeTable.EnemyLife-KnowledgeTable.Life)/2);
		}
		else if ((DifficultyFactor[0]>0) && (RandomNumber<25))
		//Si tenemos más vida un 25% de las veces bajamos la dificultad
		{
			DifficultyFactor[0]--;
		}
	}
	else if (KnowledgeTable.RoundTime<10)
	{
		//Los ultimos 10 segundos pasamos a dificultad Hard si vamos perdiendo
		if (KnowledgeTable.Life<KnowledgeTable.EnemyLife)
		{
			KnowledgeTable.Difficulty=2;
		}
	}

}

void IA::FastLifeLossReaction()
{
	//Comprobamos si estamos acorralados
	float CorneredThreshold=64;
	bool Cornered=(((KnowledgeTable.PlayerId==1) && (KnowledgeTable.Position[0]+CorneredThreshold>KnowledgeTable.MaxXPos)) 
		||((KnowledgeTable.PlayerId==0) && (KnowledgeTable.Position[0]-CorneredThreshold<KnowledgeTable.MinXPos)));
	if (Cornered)
	{
		if (RandomNumber<40)
		{
			Punch();
		}
		else if (RandomNumber<75)
		{
			Kick();
		}
		else
		{
			Defense();
		}
		
		if (DifficultyFactor[1]<10)
		{
			DifficultyFactor[1]++;	//Cada vez que nos accorralan subimos la dificultad en distancias cortas	
		}
	}
	else
	{
		//No estamos accorralados pero estamos perdiendo vida demasiado rapido
		PreviousDifficulty=KnowledgeTable.Difficulty;
		KnowledgeTable.Difficulty=2;
		EvaluateMainTree();
	}
}


//Action functions
void IA::Idle()
{
	ActionManager::actions IAActions;
	
	IAActions.up=false;
	IAActions.down=false;
	IAActions.left=false;
	IAActions.right=false;
	
	IAActions.punch=false;
	IAActions.kick=false;
	IAActions.defense=false;
	
	IAActions.megapunch=false;
	IAActions.deathray=false;
	
	Core::singleton().actionManager().setplayeractions(1,IAActions);
}

void IA::Approach()
{
	ActionManager::actions IAActions;
		
	IAActions.up=false;
	IAActions.down=false;
	IAActions.left=false;
	IAActions.right=false;
	
	IAActions.punch=false;
	IAActions.kick=false;
	IAActions.defense=false;
	
	IAActions.megapunch=false;
	IAActions.deathray=false;
	
	if (KnowledgeTable.PlayerId==1)
	{
		if (KnowledgeTable.Position[0]>KnowledgeTable.MinXPos)
		{
			IAActions.left=true;
			Core::singleton().actionManager().setplayeractions(1,IAActions);
		}
		else
		{
			Idle();
		}
	}
	else
	{
		if (KnowledgeTable.Position[0]<KnowledgeTable.MaxXPos)
		{
			IAActions.right=true;
			Core::singleton().actionManager().setplayeractions(1,IAActions);
		}
		else
		{
			Idle();
		}
	}
	
}

void IA::Flee()
{
	
	ActionManager::actions IAActions;
		
	IAActions.up=false;
	IAActions.down=false;
	IAActions.left=false;
	IAActions.right=false;
	
	IAActions.punch=false;
	IAActions.kick=false;
	IAActions.defense=false;
	
	IAActions.megapunch=false;
	IAActions.deathray=false;
	
	if (KnowledgeTable.PlayerId==0)
	{
		if (KnowledgeTable.Position[0]>KnowledgeTable.MinXPos)
		{
			IAActions.left=true;
			Core::singleton().actionManager().setplayeractions(1,IAActions);
		}
		else
		{
			Idle();
		}
	}
	else
	{
		if (KnowledgeTable.Position[0]<KnowledgeTable.MaxXPos)
		{
			IAActions.right=true;
			Core::singleton().actionManager().setplayeractions(1,IAActions);
		}
		else
		{
			Idle();
		}
	}
}

void IA::Punch()
{
	ActionManager::actions IAActions;
	
	IAActions.up=false;
	IAActions.down=false;
	IAActions.left=false;
	IAActions.right=false;
	
	IAActions.punch=true;
	IAActions.kick=false;
	IAActions.defense=false;
	
	IAActions.megapunch=false;
	IAActions.deathray=false;
	
	Core::singleton().actionManager().setplayeractions(1,IAActions);
}

void IA::Kick()
{
	ActionManager::actions IAActions;
	
	IAActions.up=false;
	IAActions.down=false;
	IAActions.left=false;
	IAActions.right=false;
	
	IAActions.punch=false;
	IAActions.kick=true;
	IAActions.defense=false;
	
	IAActions.megapunch=false;
	IAActions.deathray=false;
	
	Core::singleton().actionManager().setplayeractions(1,IAActions);
}

void IA::Defense()
{
	ActionManager::actions IAActions;
	
	IAActions.up=false;
	IAActions.down=false;
	IAActions.left=false;
	IAActions.right=false;
	
	IAActions.punch=false;
	IAActions.kick=false;
	IAActions.defense=true;
	
	IAActions.megapunch=false;
	IAActions.deathray=false;
	
	Core::singleton().actionManager().setplayeractions(1,IAActions);
}