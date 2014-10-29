#include "GameObject.h"
#include "Component.h"


GameObject::GameObject()
{

}

GameObject::~GameObject()
{

}

void GameObject::init()
{
	for (auto iter = m_Components.begin(); iter != m_Components.end(); iter++)
	{
		(*iter)->init();
	}
}

void GameObject::update()
{
	for (auto iter = m_Components.begin(); iter != m_Components.end(); iter++)
	{
		(*iter)->init();
	}
}

void GameObject::render()
{
	for (auto iter = m_Components.begin(); iter != m_Components.end(); iter++)
	{
		(*iter)->init();
	}
}

void GameObject::destroy()
{
	auto iter = m_Components.begin();
	while (iter != m_Components.end())
	{
		(*iter)->destroy();
		if ((*iter))
		{
			delete(*iter);
			(*iter) = NULL;
			iter = m_Components.erase(iter);
		}
		else
		{
			iter++;
		}
	}
}

void GameObject::addComponent(Component * component)
{
	m_Components.push_back(component);
}

const std::string& GameObject::getName()
{
	return m_Name;
}

