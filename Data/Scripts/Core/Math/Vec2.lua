--	Vec2.lua
--	LUA implementation of a vector2 class/table

Vec2 = {}
Vec2.Alloc = function(x,y)
	local _x = x or 0.0
	local _y = y or 0.0
	local v = { x = _x, y = _y }
	return v
end

Vec2.SetZero = function(v)
	v.x = 0.0
	v.y = 0.0
end

Vec2.Abs = function(v)
	return math.sqrt((v.x*v.x)+(v.y*v.y))
end

Vec2.AbsSquared = function(v)
	return ((v.x*v.x)+(v.y*v.y))
end

Vec2.GetNormalized = function(v)
	local d = math.sqrt((v.x*v.x)+(v.y*v.y))	--	same as Abs()
	if d <= 0.0 then
		return { x = 1.0, y = 0.0 }
	else
		local x = v.x / d
		local y = v.y / d
		return { x = x, y = y }
	end
end
