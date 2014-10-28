#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include <string>

using namespace std;

class Component;

class GameObject
{
public:
	GameObject();
	~GameObject();
	
	void init();
	void update();
	void render();
	void destroy();
	
	const std::string& getName();
	void setName(std::string& name);
	void addComponent(Component * component);
protected:
	//std::string m_Type;
	//bool m_Active;
private:
	std::string m_Name;
	vector<Component*> m_Components;
};




#endif