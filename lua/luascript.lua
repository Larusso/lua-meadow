
local pretty = require 'pl.pretty'
local direwolf = require 'direwolf'

print("ns direwolf:")
pretty.dump(direwolf)

local mediatorClass = direwolf.Mediator
local mt_m = getmetatable(mediatorClass)

print("metatable mediator class:")
pretty.dump(mt_m);


local mediator = direwolf.Mediator:new()

print("mediator instance:")
print(mediator)
pretty.dump(mediator)

local mt = getmetatable(mediator)

print("metatable mediator metatable:")
pretty.dump(mt)

local mt_self = getmetatable(mediator.__self)

print(mediator.__self)
print(mt_self)

print("metatable mediator __self:")
pretty.dump(mt_self)

--mediator:printType()
