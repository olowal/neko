--	core.lua
--	Define in what order sub-systems will compile

--	This adds the application path to the directory "require" is checking for
package.path = ";" .. Application.GetPath() .. "/?.lua;" .. package.path

require "Scripts/Core/System/class"
require "Scripts/Core/System/Priority"
require "Scripts/Core/System/System"
require "Scripts/Core/System/MessageSystem"
require "Scripts/Core/System/Component"
require "Scripts/Core/System/GameObject"
require "Scripts/Core/Math/Vec2"
