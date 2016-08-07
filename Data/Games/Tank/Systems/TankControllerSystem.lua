--	TankControllerSystem.lua
--	System for controlling a tank

TankControllerSystem = {}
TankControllerSystem.Priority = Priority.Standard
TankControllerSystem.Required = { TankControllerComponent, TankPropertyComponent }
TankControllerSystem.Optional = {}

TankControllerSystem.Run = function( c, dt )
	
end
