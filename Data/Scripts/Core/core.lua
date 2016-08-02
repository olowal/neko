--	core.lua
--	Define in what order sub-systems will compile

package.path = ";" .. Application.GetPath() .. "/?.lua;" .. package.path

require "Scripts/System/class"
--require "Scripts/System/MessageSystem"
--require "Scripts/Math/Vec2"
