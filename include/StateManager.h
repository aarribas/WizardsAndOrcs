#include <IState.h>
#include <map>
class StateManager
{
	friend class Core;
private:
	std::map<const char*, IState*> m_states;
	IState* m_current;
public:
	StateManager() : m_current(NULL) { }
	void registerState(const char* name, IState* state)
	{
		m_states[name] = state;
	}
	void changeTo(const char* name)
	{
		if (m_current != NULL) m_current->leave();
		m_current = m_states[name];
		m_current->enter();
	}
	void update(const float timeElapsed)
	{
		if (m_current != NULL)
			m_current->update(timeElapsed);
	}
	void display()
	{
		if (m_current != NULL)
			m_current->display();
	}
	void reshape(int width, int height)
	{
		if (m_current != NULL)
			m_current->reshape(width, height);
	}
};