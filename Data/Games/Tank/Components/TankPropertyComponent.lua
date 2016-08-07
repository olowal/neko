--	TankPropertyComponent.lua
--	Data definition and creation for TankPropertyComponent

TankPropertyComponent = {}
TankPropertyComponent.Alloc = function()
	local c = 
	{
		rotationSpeed = 1.0,
		movementSpeed = 1.0
	}
	return c
end
