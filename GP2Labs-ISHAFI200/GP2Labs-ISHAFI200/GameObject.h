#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include <string>

using namespace std;

class Component;
class Mesh;
class Material;
class Camera;
class Transform;

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
	void setName(const std::string& name);
	void addComponent(Component * component);

	Mesh * getMesh();
	Material * getMaterial();
	Camera * getCamera();
	Transform * getTransform();

	void setMesh(Mesh * mesh);
	void setMaterial(Material * material);
	void setCamera(Camera * camera);
	void setTransform(Transform * transform);
protected:
private:
	std::string m_Name;
	vector<Component*> m_Components;
	
	Mesh *m_Mesh;
	Material *m_Material;
	Camera *m_Camera;
	Transform *m_Transform;

};

#endif