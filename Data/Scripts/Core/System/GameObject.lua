--	GameObject.lua
--	Utility functions for managing game objects. GameObject is an int (index) which is from the engine. The class GameObject is created from the engine before compiling this chunk.

GameObject = {}
GameObject._gameObjects = {}

local _init_game_object = function( index, parent )
	local gameObject = {}
	gameObject._components = {}
	gameObject._index = index
	gameObject._parent = parent or false
	return gameObject
end

GameObject.Create = function()
	local index = _GameObject.Create()
	local gameObject = _init_game_object( index )
	table.insert(GameObject._gameObjects, gameObject)
	return gameObject
end

GameObject.CreateChild = function( parent )
	local index = _GameObject.CreateChild( parent._index )
	local gameObject = _init_game_object( index, parent )
	table.insert(GameObject._gameObjects, gameObject)
	return gameObject
end
