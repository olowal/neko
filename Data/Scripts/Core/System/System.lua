--	System.lua
--	Base logic for game systems

System = {}
System._systems = {}	--	list of available systems
System._modified = {}

System.GetComponents = function( gameObject )
	local s = System._systems
	for _, sys in pairs(s) do

	end
end

System.Run = function( dt )

end

System._AddModified = function( gameObject )
	table.insert(System._modified, gameObject)
end
