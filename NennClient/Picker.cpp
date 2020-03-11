#include "Picker.h"
#include "GameClient.h"
#include "CameraComponent.h"
#include "GraphicsComponent.h"
#include "IDFlags.h"
#include <string>
#include "GameStateComponent.h"
#include "EntityModel.h"
#include <assert.h>
#include <Irrlicht\irrlicht.h>

Picker::Picker(const GameClient* client)
	: ClientComponent(client), _selectedSceneNode(nullptr)
{
	_pickerDisplay = new PickerDisplay(client);
}

Picker::~Picker()
{
	delete _pickerDisplay;
	for (auto& o : _objects)
		removePickedObject(o);
}

void Picker::preTick()
{

}

void Picker::tick()
{

}

void Picker::postTick()
{
	wstring targetString = L"NO TARGET";
	
	// Release the selected scene node
	if (_selectedSceneNode)
	{
		_selectedSceneNode->drop();
		_selectedSceneNode = nullptr;
	}

	// Ray trace for a new selected scene node
	scene::ISceneCollisionManager* collisionManager = _client->component_graphics->getSceneManager()->getSceneCollisionManager();
	ISceneNode* node = collisionManager->getSceneNodeFromCameraBB(_client->component_camera->getCameraNode(), IDFlags::IsPickable);
	
	// If there is a new selected node, grab a reference to it
	if (_objects.find(static_cast<PickerNode*>(node)) != _objects.end())
	{
		_selectedSceneNode = static_cast<PickerNode*>(node);
		_selectedSceneNode->grab();
	}
		/*
		if (_selectedSceneNode->data.type == PickerObjectType::Entity)
		{
			targetString = L"Entity!";
		}
	}	

	_targetText->setText(targetString.c_str());*/

	_pickerDisplay->update();
}

PickerNode* Picker::getSelectedSceneNode() const
{
	return _selectedSceneNode;
}

void Picker::addPickedObject(PickerNode* node)
{
	node->grab();
	node->setID(node->getID() | IDFlags::IsPickable);
	_objects.insert(node);
}

void Picker::removePickedObject(PickerNode* node)
{
	node->drop();
	_objects.erase(node);
}
