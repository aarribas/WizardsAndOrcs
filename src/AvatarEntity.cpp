//###############################################################################
// INTRODUCCION: AvatarEntity.cpp
//------------------------------------------------------------------------------
// Este codigo define una entidad Avatar, que seran los personajes jugables de
// nuestro juego. A parte de las funciones estandar que tienen todas las entidades
// (draw y update), definimos un conjunto de funciones para poder tener varias 
// animaciones, funciones para situar un avatar en el espacio, y finalmente
// funciones para controlar las acciones del avatar.
//
// PROGRESO DEL CODIGO
//------------------------------------------------------------------------------
// Fecha       Editor           Descripcion
//------------------------------------------------------------------------------
// 2012.03.20  Helio Tejedor    Codigo creado
//##############################################################################

#include "AvatarEntity.h"

#include "MyGL.h"
#include "Core.h"
#include "RectangleMesh.h"

#include <iostream>

const float AvatarEntity::CELERITY = 100;
const float AvatarEntity::PUNCH_TIMEOUT = 0.25;
const float AvatarEntity::IDLE_TIMEOUT = 0.80;
const float AvatarEntity::JAB_TIMEOUT = 0.20;
const float AvatarEntity::KICK_TIMEOUT = 0.30;
const float AvatarEntity::LOWER_TIMEOUT = 0.30;
const float AvatarEntity::MOVE_TIMEOUT = 0.75;
const float AvatarEntity::JUMP_TIMEOUT = 0.75;
const float AvatarEntity::DEFENSE_TIMEOUT = 0.20;
const float AvatarEntity::HIT_POINTS = 100;

AvatarEntity::AvatarEntity()
{
}

AvatarEntity::AvatarEntity(int (*func_playSfxSound)(std::string, Vector4), void (*func_stopSfxSound)(int), bool isOnLeft, bool isExternal, bool isStandAlone, bool automatic, int index)
	: m_curAnim(NULL)
	, m_state(IDLE)
	, m_hitPoints(HIT_POINTS)
	, m_direction(0)
	, m_jump_height(0)
	, m_moveSoundid(-1)
	, m_engaged(false)
	, m_heightCorrection(0)
	, m_automatic(false)
{
	startIdle();

	playSfxSound=func_playSfxSound;
	stopSfxSound=func_stopSfxSound;
	m_isOnLeft = isOnLeft;
	m_isExternal = isExternal;
	m_isStandAlone  = isStandAlone;
	m_action = IDLE_ACT;
	m_automatic = automatic;
	m_index = index;
}

AvatarEntity::~AvatarEntity()
{
}

void AvatarEntity::addAnim(const std::string& name, RectangleMesh *mesh)
{
	//Añadimos a nuestra tabla de hashing de animaciones la nueva animacion
	//que nos pasan como parametro
	m_anim.insert(std::pair<std::string, RectangleMesh*>(name, mesh));
	if (m_curAnim == NULL) {
		m_curAnimName = name;
		m_curAnim = mesh;
	}
}

void AvatarEntity::setAnim(const std::string& name)
{
	//Comprobamos si al animacion identificada por name existe
	std::map<std::string, RectangleMesh*>::const_iterator found = m_anim.find(name);
	if (found == m_anim.end()) {
		std::cerr << "E: anim not found " << name << std::endl;
		return;
	}
	//Si la hemos encontrado la marcamos como activa
	m_curAnimName = found->first;
	m_curAnim = found->second;
}

void AvatarEntity::draw()
{
	if (m_curAnim == NULL) {
		std::cerr << "W: anim not set" << std::endl;
		return;
	}

	//Primero de todo tenemos que posicionar el avatar dentro de la pantalla
	glPushMatrix();

	glTranslatef(m_screenPosition[0], m_screenPosition[1], m_screenPosition[2]);

	if(!m_isOnLeft) glRotatef(180.0f,0.0f,1.0f,0.0f);
	m_heightCorrection = 0;
	//pequeños ajustes dependiendo del movimiento
	if (m_curAnimName == "lower1")
	{
		glTranslatef(0, - m_curAnim->m_height/4, 0);
		m_heightCorrection = - m_curAnim->m_height/4 ;
	}
	else if (m_curAnimName == "jump1")
	{
		glTranslatef(0,15, 0);
		m_heightCorrection = 15;
	}
	else if (m_curAnimName == "jump2")
	{
		glTranslatef(0,30, 0);
		m_heightCorrection = 30;
	}
	else if (m_curAnimName == "jump3")
	{
		glTranslatef(0,60, 0);
		m_heightCorrection = 60;
	}
	else if (m_curAnimName == "jump4")
	{
		glTranslatef(0,30, 0);
		m_heightCorrection = 30;
	}
	else if (m_curAnimName == "jump5")
	{
		glTranslatef(0,15, 0);
		m_heightCorrection = 15;
	}
	else if (m_curAnimName == "jump6")
	{
		glTranslatef(0,0, 0);
		m_heightCorrection = 0;
	}
	m_curAnim->draw();
	glPopMatrix();

	if(m_state == JUMP)
	{
		glPushMatrix();
		glTranslatef(m_screenPosition[0], m_screenPosition[1] - m_curAnim->m_height/2, m_screenPosition[2]);
		m_anim["shade"]->draw();
		glPopMatrix();
	}
}

void AvatarEntity::update(const float elapsedTime)
{
	//Para actualizar el estado del avatar, miraremos primero en que estado estamos
	//Y despues llamamos a las funciones que actualizan segun el estado
	updateState();
	
switch(m_state) {
	case IDLE:
		updateIdle(elapsedTime);
		break;
	case PUNCH:
		updatePunch(elapsedTime);
		break;
	case JAB:
		updateJab(elapsedTime);
		break;
	case KICK:
		updateKick(elapsedTime);
		break;
	case LOWER:
		updateLower(elapsedTime);
		break;
	case MOVE:
		updateMove(elapsedTime);
		break;
	case JUMP:
		updateJump(elapsedTime);
		break;
	case DEFENSE:
		updateDefense(elapsedTime);
		break;
	}
}

void AvatarEntity::updateState()
{
	ActionManager::actions actions = Core::singleton().actionManager().getplayeractions(m_index);
	
	if (actions.up == false
		&& actions.defense == false
		&& actions.down == false
		&& actions.left == false
		&& actions.right == false
		&& actions.punch == false
		&& actions.kick == false
		&& actions.megapunch == false
		&& actions.up == false)
	{
		//si no hay accion debemos detener el movimiento 
		if(m_state == MOVE )
		{
			if(m_moveSoundid != -1) stopSfxSound(m_moveSoundid);
			startIdle();
		}
		else if(m_state == DEFENSE)
		{
			startIdle();
		}
		else if(m_state == LOWER)
		{
			if(m_lowerSoundid != -1) stopSfxSound(m_lowerSoundid);
			startIdle();
		}
	}
	else
	{

		if(actions.punch == true && m_state == IDLE)
		{
			startPunch();
		}
		else if(actions.megapunch == true && m_state == IDLE)
		{
			startJab();
		}
		else if(actions.kick == true && m_state == IDLE)
		{
			startKick();
		}
		else if(actions.down == true && m_state == IDLE)
		{
			if(m_state != LOWER) startLower();
		}
		else if(actions.left == true && m_state!= JUMP && actions.up == false)
		{
			m_direction = -1;
			if(m_state == IDLE || m_state == DEFENSE) startMove();
		}
		else if(actions.right == true && m_state!= JUMP && actions.up == false)
		{
			m_direction = 1;
			if(m_state == IDLE || m_state == DEFENSE) startMove();
		}
		else if(actions.left == true && actions.up == true && (m_state == IDLE || m_state == MOVE))
		{
			m_direction = -1;
			if(m_moveSoundid != -1) stopSfxSound(m_moveSoundid);
			startJump();
		}
		else if(actions.right == true && actions.up == true && (m_state == IDLE || m_state == MOVE))
		{
			m_direction = 1;
			if(m_moveSoundid != -1) stopSfxSound(m_moveSoundid);
			startJump();
		}
		else if(actions.up == true && m_state == IDLE)
		{
			m_direction = 0;
			startJump();
		}

		else if(actions.defense == true && m_state == IDLE)
		{
			if(m_moveSoundid != -1) stopSfxSound(m_moveSoundid);
			startDefense();
		}
	}

	m_action = IDLE_ACT;
}





void AvatarEntity::updateExternal(std::string message, float value)
{
	m_terrainPosition[0] = value;

	if(message == "idle#")
	{
		startIdle();
	}
	else if(message == "punch")
	{
		startPunch();
	}
	else if(message == "jab##")
	{
		startJab();
	}
	else if(message == "kick#")
	{
		startKick();
	}
	else if(message == "lower")
	{
		startLower();
	}
	else if(message == "loweS")
	{
		if(m_lowerSoundid != -1) stopSfxSound(m_lowerSoundid);
		startIdle();
	}
	else if(message == "move#")
	{
		startMove();
	}
	else if(message == "move-")
	{
		m_direction = -1;
	}
	else if(message == "move+")
	{
		m_direction = 1;
	}
	else if(message == "moveJ")
	{
		if(m_moveSoundid != -1) stopSfxSound(m_moveSoundid);
		startJump();
	}
	else if(message == "moveS")
	{
		if(m_moveSoundid != -1) stopSfxSound(m_moveSoundid);
		startIdle();
	}
	else if(message == "jump#")
	{
		startJump();
	}

	else if(message == "cover")
	{
		if(m_moveSoundid != -1) stopSfxSound(m_moveSoundid);
		startDefense();
	}

}

void AvatarEntity::updateIdle(const float elapsedTime)
{
	m_timeout -= elapsedTime;
	
	if(m_timeout < IDLE_TIMEOUT/4*3  && m_timeout > IDLE_TIMEOUT/4*2)
	{
		setAnim("idle1");
	}
	else if (m_timeout < IDLE_TIMEOUT/4*2  && m_timeout > IDLE_TIMEOUT/4)
	{
		setAnim("idle2");
	}
	else if (m_timeout < IDLE_TIMEOUT/4  && m_timeout > 0)
	{
		setAnim("idle3");
	}
	else if (m_timeout < 0)
	{
		startIdle(); //vuelta a empezar
	}

}

void AvatarEntity::updateMove(const float elapsedTime)
{
	m_timeout -= elapsedTime;

	/*if(!m_isExternal && !m_automatic)
	{
		OIS::Keyboard* keyboard = Core::singleton().inputManager().getKeyboard();

		if(keyboard->isKeyDown(keys[2]))
		{
			if(m_isStandAlone == false)
			{
				std::stringstream ss;
				ss << "moveJ" << (int)m_screenPosition[0];
				Core::singleton().networkManager().send(ss.str());
			}
			if(m_moveSoundid != -1) stopSfxSound(m_moveSoundid);
			startJump();
			return;
		}

		if (keyboard->isKeyDown(keys[4]))
		{
			m_direction =-1;
			if(m_isStandAlone == false)
			{
				std::stringstream ss;
				ss << "move-" << (int)m_screenPosition[0];
				Core::singleton().networkManager().send(ss.str());
			}

		}
		else if (keyboard->isKeyDown(keys[6]))
		{
			m_direction = 1;
			if(m_isStandAlone == false)
			{
				std::stringstream ss;
				ss << "move+" << (int)m_screenPosition[0];
				Core::singleton().networkManager().send(ss.str());
			}
		}
		else
		{
			//Core::singleton().soundManager().getChannel(m_moveSoundid)->stop();
			if(m_isStandAlone == false)
			{
				std::stringstream ss;
				ss << "moveS" << (int)m_screenPosition[0];
				Core::singleton().networkManager().send(ss.str());
			}
			//if(m_moveSoundid != -1) stopSfxSound(m_moveSoundid);
			startIdle();
		}
	}

	if(m_automatic && (distanceToEnemy < 100))
	{
		if(!m_engaged)
		{
				startIdle();
				m_engaged = !m_engaged;
		}
	}
	if(m_automatic && (distanceToEnemy > 150))
	{
		m_direction=-1;
	}
	*/
	m_deltaX = m_direction * CELERITY * elapsedTime;
	m_terrainPosition[0] += m_deltaX;

	//if movement proceed with the animations
	if(m_timeout < MOVE_TIMEOUT/5*4  && m_timeout > MOVE_TIMEOUT/5*3)
	{
		setAnim("move1");
	}
	else if (m_timeout < MOVE_TIMEOUT/5*3  && m_timeout > MOVE_TIMEOUT/5*2)
	{
		setAnim("move2");
	}
	else if (m_timeout < MOVE_TIMEOUT/5*2  && m_timeout > MOVE_TIMEOUT/5*1)
	{
		setAnim("move3");
	}
	else if (m_timeout < MOVE_TIMEOUT/5  && m_timeout > 0)
	{
		setAnim("move4");
	}
	else if (m_timeout < 0)
	{
		m_timeout=MOVE_TIMEOUT; //vuelta a empezar con la animacion
		setAnim("move1");
	}	
}


void AvatarEntity::updatePunch(const float elapsedTime)
{
	//Si estamos golpeando, lo primero que tenemos que mirar es cuanto tiempo
	//llevamos realizando el golpe. Si se ha acabado ya el golpe volvemos al 
	//estado inactivo
	m_timeout -= elapsedTime;
	/*if (m_timeout < 0)
	startIdle();*/
	if(m_timeout < PUNCH_TIMEOUT/3*2  && m_timeout > PUNCH_TIMEOUT/3)
	{
		setAnim("punch1");
	}
	else if (m_timeout < PUNCH_TIMEOUT/3  && m_timeout > 0)
	{
		setAnim("punch2");
	}
	else if (m_timeout < 0)
	{
		startIdle();
	}

}

void AvatarEntity::updateJab(const float elapsedTime)
{
	//Si estamos golpeando, lo primero que tenemos que mirar es cuanto tiempo
	//llevamos realizando el golpe. Si se ha acabado ya el golpe volvemos al 
	//estado inactivo
	m_timeout -= elapsedTime;

	if(m_timeout < JAB_TIMEOUT/3*2  && m_timeout > JAB_TIMEOUT/3)
	{
		setAnim("jab1");
	}
	else if (m_timeout < JAB_TIMEOUT/3  && m_timeout > 0)
	{
		setAnim("jab2");
	}
	else if (m_timeout < 0)
	{
		startIdle();
	}

}

void AvatarEntity::updateKick(const float elapsedTime)
{
	//Si estamos golpeando, lo primero que tenemos que mirar es cuanto tiempo
	//llevamos realizando el golpe. Si se ha acabado ya el golpe volvemos al 
	//estado inactivo
	m_timeout -= elapsedTime;

	if(m_timeout < KICK_TIMEOUT/4*3  && m_timeout > KICK_TIMEOUT/4*2)
	{
		setAnim("kick1");
	}
	else if (m_timeout < KICK_TIMEOUT/4*2  && m_timeout > KICK_TIMEOUT/4)
	{
		setAnim("kick2");
	}
	else if (m_timeout < KICK_TIMEOUT/4  && m_timeout > 0)
	{
		setAnim("kick3");
	}
	else if (m_timeout < 0)
	{
		startIdle(); //vuelta a empezar
	}


}
void AvatarEntity::updateJump(const float elapsedTime)
{
	//Si estamos golpeando, lo primero que tenemos que mirar es cuanto tiempo
	//llevamos realizando el golpe. Si se ha acabado ya el golpe volvemos al 
	//estado inactivo
	m_timeout -= elapsedTime;

	m_deltaX = m_direction * CELERITY * elapsedTime;
	m_terrainPosition[0] += m_deltaX;

	if(m_timeout < JUMP_TIMEOUT/7*6  && m_timeout > JUMP_TIMEOUT/7*5)
	{
		setAnim("jump1");
	}
	else if(m_timeout < JUMP_TIMEOUT/7*5  && m_timeout > JUMP_TIMEOUT/7*4)
	{
		setAnim("jump2");
	}
	else if(m_timeout < JUMP_TIMEOUT/7*4  && m_timeout > JUMP_TIMEOUT/7*3)
	{
		setAnim("jump3");
	}
	else if(m_timeout < JUMP_TIMEOUT/7*3  && m_timeout > JUMP_TIMEOUT/7*2)
	{
		setAnim("jump4");
	}
	else if(m_timeout < JUMP_TIMEOUT/7*2  && m_timeout > JUMP_TIMEOUT/7)
	{
		setAnim("jump5");
	}
	else if(m_timeout < JUMP_TIMEOUT/7  && m_timeout > 0)
	{
		setAnim("jump6");
	}
	else if (m_timeout < 0)
	{
		if(m_direction == 0)
		{
			startIdle(); //vuelta a empezar
		}
		else
		{
			startMove();
		}
	}


}


void AvatarEntity::updateLower(const float elapsedTime)
{
	//Si estamos agachados, comprobamos si se ha dejado de pulsar la tecla abajo
	//Si es asi volvemos al estado idle
	OIS::Keyboard* keyboard = Core::singleton().inputManager().getKeyboard();
	/*if(m_isStandAlone == true || (m_isStandAlone == false && m_isExternal == false && !m_automatic))
	{
		if (! keyboard->isKeyDown(keys[7]))
		{
			if(m_isStandAlone == false)
			{
				std::stringstream ss;
				ss << "loweS" << (int)m_screenPosition[0];
				Core::singleton().networkManager().send(ss.str());
			}
			if(m_lowerSoundid != -1) stopSfxSound(m_lowerSoundid);
			startIdle();
			return;
		}
	}*/

	m_timeout -= elapsedTime;

	if (m_timeout < LOWER_TIMEOUT/2)
	{
		setAnim("lower1");
	}

}


void AvatarEntity::updateDefense(const float elapsedTime)
{
//nothing to do.
}

void AvatarEntity::startIdle()
{
	//Inicializar el estado inactivo
	m_state = IDLE;
	m_timeout = IDLE_TIMEOUT;
	m_direction = 0;
	setAnim("idle");
	if(m_moveSoundid != -1) stopSfxSound(m_moveSoundid);
}

void AvatarEntity::startPunch()
{
	//Inicializar el estado golpear. Tenemos que inicializar un contador
	//para saber cuando terminar el golpe
	m_state = PUNCH;
	m_timeout = PUNCH_TIMEOUT;
	setAnim("punch");  
	playSfxSound("punch",m_screenPosition);

	if(m_isStandAlone == false && m_isExternal == false)
	{
		std::stringstream ss;
		ss << "punch" << (int)m_screenPosition[0];
		Core::singleton().networkManager().send(ss.str());
	}
}

void AvatarEntity::startJab()
{
	//Inicializar el estado golpear. Tenemos que inicializar un contador
	//para saber cuando terminar el golpe
	m_state = JAB;
	m_timeout = JAB_TIMEOUT;
	setAnim("jab");
	playSfxSound("jab", m_screenPosition);

	if(m_isStandAlone == false && m_isExternal == false)
	{
		std::stringstream ss;
		ss << "jab##" << (int)m_screenPosition[0];
		Core::singleton().networkManager().send(ss.str());
	}
}

void AvatarEntity::startKick()
{
	//Inicializar el estado golpear. Tenemos que inicializar un contador
	//para saber cuando terminar el golpe
	m_state = KICK;
	m_timeout = KICK_TIMEOUT;
	setAnim("kick");
	playSfxSound("kick", m_screenPosition);

	if(m_isStandAlone == false && m_isExternal == false)
	{
		std::stringstream ss;
		ss << "kick#" << (int)m_screenPosition[0];
		Core::singleton().networkManager().send(ss.str());
	}
}

void AvatarEntity::startLower()
{
	//Inicializar el estado agachar
	m_state = LOWER;
	m_timeout = LOWER_TIMEOUT;
	setAnim("lower");
	m_lowerSoundid = playSfxSound("lower", m_screenPosition);

	if(m_isStandAlone == false && m_isExternal == false)
	{
		std::stringstream ss;
		ss << "lower" << (int)m_screenPosition[0];
		Core::singleton().networkManager().send(ss.str());
	}
}

void AvatarEntity::startMove()
{
	//Inicializar el estado agachar
	m_state = MOVE;
	m_timeout = MOVE_TIMEOUT;
	setAnim("move");
	m_moveSoundid = playSfxSound("move", m_screenPosition);
	if(m_isStandAlone == false && m_isExternal == false)
	{
		std::stringstream ss;
		ss << "move#" << (int)m_screenPosition[0];
		Core::singleton().networkManager().send(ss.str());
	}
}

void AvatarEntity::startJump()
{
	//Inicializar el estado agachar
	m_state = JUMP;
	m_timeout = JUMP_TIMEOUT;
	setAnim("jump");
	playSfxSound("jump", m_screenPosition);

	//enviar mensaje
	if(m_isStandAlone == false && m_isExternal == false)
	{
		std::stringstream ss;
		ss << "jump#" << (int)m_screenPosition[0];
		Core::singleton().networkManager().send(ss.str());
	}
}

void AvatarEntity::startDefense()
{
	//Inicializar el estado agachar
	m_state = DEFENSE;
	setAnim("cover");
	m_timeout = DEFENSE_TIMEOUT;
	//enviar mensaje
	if(m_isStandAlone == false && m_isExternal == false)
	{
		std::stringstream ss;
		ss << "cover" << (int)m_screenPosition[0];
		Core::singleton().networkManager().send(ss.str());
	}
}
bool AvatarEntity::isExternal()
{
	return m_isExternal;
}

bool AvatarEntity::isOnLeft()
{
	return m_isOnLeft;
}

bool AvatarEntity::isArtificial()
{
	return m_automatic;
}

float AvatarEntity::updateHitPoints(AvatarEntity* enemy)
{
	int dircheck = 1;

	//direccion para activar el defense
	if(m_isOnLeft)dircheck = -1; 

	//is hay colission no podemos movernos mas en la direccion equivocada, evita overlaps
	if((m_state == MOVE || m_state == JUMP)&& m_direction == -dircheck)
	{
		startIdle();
	}

	//computo del danyo dependiendo del estado

	if(enemy->getState() == AvatarEntity::KICK 
		|| enemy->getState() == AvatarEntity::JAB 
		|| enemy->getState()  == AvatarEntity::PUNCH)
	{
		if(m_state == DEFENSE)
		{
			//no damage
		}
		else if ((m_state == MOVE && m_direction == dircheck))
		{
			if(m_moveSoundid != -1) stopSfxSound(m_moveSoundid);
			startDefense();
			//no damage
		}
		else
		{
			if(enemy->getState() == AvatarEntity::KICK)
			{
				m_hitPoints-=1;
			}
			if(enemy->getState() == AvatarEntity::PUNCH)
			{
				m_hitPoints-=0.8;
			}
			if(enemy->getState() == AvatarEntity::JAB)
			{
				m_hitPoints-=0.5;
			}
		}
	}
	return m_hitPoints;
				

}


float AvatarEntity::getCurAnimWidth()
{
	if (m_curAnim)
	{
		return m_curAnim->width();
	}
}


float AvatarEntity::getCurAnimHeight()
{
	if (m_curAnim)
	{
		return m_curAnim->height();
	}
}


//el siguiente código es sugerencia de David Jimenez, se lo copio porque me parece mejor que pasar a idle y no rebotar
void AvatarEntity::goBackDelta()
{
	if(isOnLeft())
	{
		if (m_deltaX >0)
		{
			m_terrainPosition[0] -= 2*m_deltaX; //2* Para conseguir un efecto rebote
		}
		else
		{
			m_terrainPosition[0] += 2*m_deltaX;
		}
	}
	else 
	{
		if (m_deltaX >0)
		{
			m_terrainPosition[0] += 2*m_deltaX; //2* Para conseguir un efecto rebote
		}
		else
		{
			m_terrainPosition[0] -= 2*m_deltaX;
		}
	}

}