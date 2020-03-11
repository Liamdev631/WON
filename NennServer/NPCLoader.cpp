#include "NPCLoader.h"
#include <JsonReader.h>
#include <assert.h>
#include "EntityComponent.h"

void NPCLoader::loadNCPs(EntityComponent* entityComponent)
{
	json j;
	JsonReader::read(j, "Content/data/npcs.json");
	auto npcs = j["npcs"];
	for (int i = 0; i < 3; i++)
	{
		auto npc = npcs[i];

		// Load UID
		Entity::UID uid = npc["uid"];
		assert(uid == i);
		uid += NumberOfPlayers;
		auto& entity = entityComponent->getEntity(uid);
		entityComponent->_activeEntities.insert(uid);
		entity.active = true;

		// Load name
		npc["name"];
		string name = npc["name"];
		strcpy_s<32>(entity.name, name.c_str());

		// Load entity type
		entity.type = npc["type"];
	}
}
