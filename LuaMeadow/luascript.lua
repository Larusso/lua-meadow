
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
