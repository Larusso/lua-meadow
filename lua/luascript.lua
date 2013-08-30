
local pretty = require 'pl.pretty'

pretty.dump(direwolf)
m = getmetatable(direwolf)

pretty.dump(m)

local mediator = direwolf.Mediator()
print(mediator)

m = getmetatable(mediator)
pretty.dump(m)

mediator:move(20,30)

controller = direwolf.Controller()
controller:registerView(mediator)

local external = dofile('external.lua')
external:execute()

mediator4 = Mediator()

--[[
for i=1,1000 do
    local med = Mediator()
    med:move(2*i,6*1)
    med = nil
    --collectgarbage()
end
--]]