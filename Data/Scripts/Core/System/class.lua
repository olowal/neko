-- Class system
function class(...)
	local super = ...
	if select('#', ...) >= 1 and super == nil then
		error("trying to inherit from nil", 2)
	end
    local class_table = {}
    
    class_table.super = super
    class_table.__index = class_table
    setmetatable(class_table, super)
    
    class_table.new = function (klass, ...)
        local object = {}
        setmetatable(object, class_table)
        if object.init then
            object:init(...)
        end
        return object
    end
    return class_table
end
