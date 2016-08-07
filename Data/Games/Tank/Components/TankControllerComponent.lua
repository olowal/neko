--	TankControllerComponent.lua
--	Data definition and creation for TankControllerComponent

TankControllerComponent = {}
TankControllerComponent.Alloc = function()
	local c = 
	{
		throttle = 0.0,
		turn = 0.0,
		fire = false
	}
	return c
end
