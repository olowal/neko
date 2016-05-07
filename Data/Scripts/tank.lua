--	tank.lua

player = function()

local gameObject = GameObject.Alloc()
local comp = Components

comp.Sprite.Alloc(gameObject, {filename = "tank", x=0,y=0,w=120,h=120}, Game.device)

local obj = 
	{
		sprite = nil,
		trans = nil,
		GetComponents = nil,
		Run = nil
	}

	obj.GetComponents = function(obj)
		if obj.sprite == nil then
			obj.sprite = Sprite.Alloc(obj)
			Sprite.LoadTexture(obj.sprite, "tank")
			Sprite.SetDimension(obj.sprite, 0, 0, 64, 64)
		end

		if obj.trans == nil then
			obj.trans = Transform.Alloc(obj)
		end
		if obj.sprite ~= nil and obj.trans ~= nil then
			return true
		end
		return false
	end

	obj.Run = function(obj)
		TestRun(obj)
	end

	return obj
end


TestRun = function(obj)
	local angle = 10

	if Input.IsKeyDown(Input.KC_D) == true then
		Transform.Rotate(obj.trans, angle)
	elseif Input.IsKeyDown(Input.KC_A) == true then
		Transform.Rotate(obj.trans, -angle)
	end

	local move = false
	local dir = 0.0

	if Input.IsKeyDown(Input.KC_W) == true then
		move = true
		dir = 1.0
	elseif Input.IsKeyDown(Input.KC_S) == true then
		move = true
		dir = -1.0
	end

	if move == true then
		angle = Transform.GetAngle(obj.trans)
		local vel = 2
		local x = (math.cos(math.Deg2Rad(angle - 90)) * vel) * dir
		local y = (math.sin(math.Deg2Rad(angle - 90)) * vel) * dir
		Transform.Translate(obj.trans, x, y)
	end
end
