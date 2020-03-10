#include "Picker.h"
#include "GameClient.h"
#include "CameraComponent.h"
#include "GraphicsComponent.h"
#include "IDFlags.h"
#include <string>
#include "GameStateComponent.h"
#include "EntityModel.h"
#include <assert.h>

Picker::Picker(const GameClient* client)
	: ClientComponent(client), _selectedSceneNode(nullptr)
{
	_targetText = _client->component_graphics->getGUI()->addStaticText(L"", recti(10, 10, 100, 18), false, false);
}

Picker::~Picker()
{

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
	if (_objectTable.find(static_cast<PickerNode*>(node)) != _objectTable.end())
	{
		_selectedSceneNode = static_cast<PickerNode*>(node);
		_selectedSceneNode->grab();

		if (_selectedSceneNode->data.type == PickerObjectType::Entity)
		{
			targetString = L"Entity!";
		}
	}	

	_targetText->setText(targetString.c_str());
}

PickerNode* Picker::getSelectedSceneNode() const
{
	return _selectedSceneNode;
}

void Picker::addPickedObject(PickerNode* node)
{
	node->grab();
	node->setID(node->getID() | IDFlags::IsPickable);
	_objectTable.insert(node);
}

void Picker::removePickedObject(PickerNode* node)
{
	node->drop();
	_objectTable.erase(node);
}
