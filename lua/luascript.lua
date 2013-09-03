
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
pretty.dump(mediator)

local mt = getmetatable(mediator)

print("metatable mediator metatable:")
pretty.dump(mt)

local mt2 = getmetatable(mt)

mediator:printType()
