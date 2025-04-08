#include "IGameObject.h"
#include "SceneBase.h"
#include "IShape.h"
#include <algorithm>


//IComponent::IComponent(IComposite* parent) : m_parent(nullptr)
//{
//    setParent(parent);
//}
//
//IComponent::~IComponent()
//{
//    setParent(nullptr);
//}
//
//IComponent* IComponent::getParent()
//{
//    return m_parent;
//}
//
//const IComponent* IComponent::getParent() const
//{
//    return m_parent;
//}
//
//void IComponent::setParent(IComposite* parent)
//{
//    if (m_parent == parent)
//        return;
//
//    if (m_parent)
//        m_parent->remove(this);
//
//    m_parent = parent;
//
//    if (m_parent)
//        m_parent->add(this);
//}
//
//RootScene* IComponent::getRoot()
//{
//    auto* current = this;
//    while (current->getParent() != nullptr)
//    {
//        current = current->getParent();
//    }
//    return static_cast<RootScene*>(current);
//}
//
//const RootScene* IComponent::getRoot() const
//{
//    auto* current = this;
//    while (current->getParent() != nullptr)
//    {
//        current = current->getParent();
//    }
//    return static_cast<const RootScene*>(current);
//}
//
//IComposite::IComposite(IComposite* parent) : IComponent(parent)
//{
//}
//
//IComposite::~IComposite()
//{
//    auto childrenCopy = m_children;
//    m_children.clear();
//
//    for (auto* child : childrenCopy)
//    {
//        delete child;
//    }
//}
//
//void IComposite::Update(const float& deltatime)
//{
//    auto childrenCopy = m_children;
//    for (auto& child : childrenCopy)
//    {
//        if (std::find(m_children.begin(), m_children.end(), child) != m_children.end())
//            child->Update(deltatime);
//    }
//}
//
//void IComposite::ProcessInput(const sf::Event& event)
//{
//    auto childrenCopy = m_children;
//    for (auto& child : childrenCopy)
//    {
//        if (std::find(m_children.begin(), m_children.end(), child) != m_children.end())
//            child->ProcessInput(event);
//    }
//}
//
//void IComposite::Render()
//{
//    auto childrenCopy = m_children;
//    for (auto& child : childrenCopy)
//    {
//        if (std::find(m_children.begin(), m_children.end(), child) != m_children.end())
//            child->Render();
//    }
//}
//
//std::vector<IComponent*> IComposite::getChildren()
//{
//    return m_children;
//}
//
//const std::vector<IComponent*> IComposite::getChildren() const
//{
//    return m_children;
//}
//
//std::vector<IComponent*> IComposite::getFullTree()
//{
//    std::vector<IComponent*> result;
//    result.reserve(m_children.size() * 2);
//    AddFullTree(result, getChildren());
//    return result;
//}
//
//void IComposite::add(IComponent* data)
//{
//    if (std::find(m_children.begin(), m_children.end(), data) == m_children.end())
//    {
//        m_children.push_back(data);
//    }
//}
//
//void IComposite::remove(IComponent* data)
//{
//    auto it = std::find(m_children.begin(), m_children.end(), data);
//    if (it != m_children.end())
//    {
//        m_children.erase(it);
//    }
//}
//
//void IComposite::AddFullTree(std::vector<IComponent*>& toAdd, std::vector<IComponent*> iterate)
//{
//    for (auto it : iterate)
//    {
//        toAdd.push_back(it);
//        if (it->GetComponentType() == Component::IComposite)
//        {
//            AddFullTree(toAdd, static_cast<IComposite*>(it)->getChildren());
//        }
//    }
//}
//
//RootScene::RootScene(ISceneBase* scene) : IComposite(nullptr), m_scene(scene)
//{
//}
//
//ISceneBase* RootScene::getScene()
//{
//    return m_scene;
//}
//
//ILeaf::ILeaf(IComposite* parent) : IComponent(parent)
//{
//}
//
//IGameObject::IGameObject(IComposite* scene) 
//    : m_scene(scene)
//    , m_shape(nullptr)
//    , m_needDestroy(false)
//    , ILeaf(scene)
//{
//}
//
//IGameObject::~IGameObject()
//{
//    delete m_shape;
//    m_shape = nullptr;
//}
//
//AABB IGameObject::GetBoundingBox()
//{
//    return m_shape ? m_shape->GetBoundingBox() : AABB({ 0.0f, 0.0f }, { 0.0f, 0.0f });
//}
//
//IShapeSFML* IGameObject::getShape()
//{
//    return m_shape;
//}
//
//bool IGameObject::NeedDestroy()
//{
//    return m_needDestroy;
//}
//
//void IGameObject::destroy()
//{
//    m_needDestroy = true;
//}
//
//DestructibleObject::DestructibleObject( const float& life)
//    : m_life(life)
//{
//}
//
//GameObjectType DestructibleObject::globalGameObjectType()
//{
//    return GameObjectType::DestructibleObject;
//}
//
//NonDestructibleObject::NonDestructibleObject()
//    
//{
//}
//
//GameObjectType NonDestructibleObject::globalGameObjectType()
//{
//    return GameObjectType::NonDestructibleObject;
//}





IComponent::IComponent(IComposite* parent)
	:m_parent(nullptr)
{
	setParent(parent);
}

IComponent::~IComponent()
{
	setParent(nullptr);
}

IComponent* IComponent::getParent()
{
	return m_parent;
}

const IComponent* IComponent::getParent() const
{
	return m_parent;
}

std::vector<IComponent*> IComposite::getFullTree()
{
    std::vector<IComponent*> result;
    result.reserve(m_children.size() * 2);
    AddFullTree(result, getChildren());
    return result;
}

void IComposite::AddFullTree(std::vector<IComponent*>& toAdd, std::vector<IComponent*> iterate)
{
    for (auto it : iterate)
    {
        toAdd.push_back(it);
        if (it->GetComponentType() == Component::IComposite)
        {
            AddFullTree(toAdd, static_cast<IComposite*>(it)->getChildren());
        }
    }
}

void IComponent::setParent(IComposite* parent)
{
	if (m_parent)
		m_parent->remove(this);

	m_parent = parent;

	if (m_parent)
		m_parent->add(this);
}

RootScene* IComponent::getRoot()
{
	auto* curent = this;
	while (curent->getParent() != nullptr)
	{
		curent = curent->getParent();
	}
	return static_cast<RootScene*>(curent);
}

const RootScene* IComponent::getRoot() const
{
	auto* curent = this;
	while (curent->getParent() != nullptr)
	{
		curent = curent->getParent();
	}
	return static_cast<const RootScene*>(curent);
}

IComposite::IComposite(IComposite* parent)
	: IComponent(nullptr)
{

}

IComposite::~IComposite()
{
	for (std::make_signed_t<size_t> i = m_children.size() - 1; i >= 0; --i)
	{
		delete m_children[i];
	}
	m_children.clear();
}


std::vector<IComponent*> IComposite::getChildren()
{
	return m_children;
}

const std::vector<IComponent*> IComposite::getChildren() const
{
	return m_children;
}

void IComposite::add(IComponent* data)
{
	m_children.push_back(data);
}

void IComposite::remove(IComponent* data)
{
	auto it = std::find(m_children.begin(), m_children.end(), data);
	if (it == m_children.end())
		throw;
	m_children.erase(it);
}


ILeaf::ILeaf(IComposite* parent)
	:IComponent(parent)
{
}


RootScene::RootScene(ISceneBase* scene) : IComposite(nullptr), m_scene(scene)
{
}

ISceneBase* RootScene::getScene()
{
	return m_scene;
}

const ISceneBase* RootScene::getScene() const
{
	return m_scene;
}



IGameObject::IGameObject(IComposite* scene)
	:IComponent(nullptr)
	, m_scene(scene)
	, m_shape(nullptr)
	, m_needDestroy(false)
{
}

IGameObject::~IGameObject()
{
	delete m_shape;
	m_shape = nullptr;
}

AABB IGameObject::GetBoundingBox()
{
	return m_shape ? m_shape->GetBoundingBox() : AABB({ 0.0f, 0.0f }, { 0.0f, 0.0f });
}

IShapeSFML* IGameObject::getShape()
{
	return m_shape;
}

bool IGameObject::NeedDestroy()
{
	return m_needDestroy;
}

void IGameObject::destroy()
{
	m_needDestroy = true;
}