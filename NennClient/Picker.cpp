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
		_selectedSceneNode->setMaterialFlag(EMF_LIGHTING, true);
		_selectedSceneNode->drop();
		_selectedSceneNode = nullptr;
	}

	// Ray trace for a new selected scene node
	scene::ISceneCollisionManager* collisionManager = _client->component_graphics->getSceneManager()->getSceneCollisionManager();
	_selectedSceneNode = collisionManager->getSceneNodeFromCameraBB(_client->component_camera->getCameraNode(), IDFlags::IsPickable);
	
	// If there is a new selected node, grab a reference to it
	if (_selectedSceneNode)
	{
		_selectedSceneNode->grab();
		_selectedSceneNode->setMaterialFlag(EMF_LIGHTING, false);

		auto e = _objectTable.find(_selectedSceneNode);
		assert(e != _objectTable.end());
		PickerTableEntry entry = e->second;

		if (entry.type == PickerObjectType::Entity)
		{
			targetString = L"Entity!";
		}
	}	

	_targetText->setText(targetString.c_str());
}

scene::ISceneNode* Picker::getSelectedSceneNode() const
{
	return _selectedSceneNode;
}

void Picker::addPickedObject(scene::ISceneNode* node, PickerTableEntry entry)
{
	_objectTable[node] = entry;
	node->setID(node->getID() | IDFlags::IsPickable);
}

void Picker::removePickedObject(scene::ISceneNode* node)
{
	_objectTable.erase(node);
}
