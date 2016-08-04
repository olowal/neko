--	Component.lua
--	System for creating / removing components

Component = {}

Component.Get = function( component, gameObject )
	return gameObject._components[component]
end

Component.GetFromParent = function( component, gameObject )
	if gameObject._parent then
		return gameObject._parent._components[component]
	end
	return nil
end

Component.GetFromParentRecursive = function( component, gameObject )
	local c = nil
	if gameObject._parent then
		c = gameObject._parent._components[component]
		if c == nil then
			c = Component.GetFromParentRecursive( component, gameObject._parent)
		end
	end
	return c
end

Component.Create = function( component, gameObject )
	if gameObject._components[component] then
		return false
	end
	local c = component.Alloc()
	gameObject._components[component] = c
	return true
end
