-- main.lua
-- @zergl, 2016/01/07

function hello()
    ngx.say("<h1>hello world! @lua</h1>")
end

local qs_args = ngx.req.get_uri_args()
local cmd = qs_args['cmd']
local update = require "apps.todo.lua.update"
local info = require "apps.todo.lua.info"
ops = {
    ["add"]     = update.add,
    ["del"]     = update.del,
    ["update"]  = update.update,
    ["print_info"] = info.print_info,
    ["hello"]   = info.hello,
}
local do_exec = ops[cmd]

local succ, err, resp = false, "opcode not supported.", nil
if do_exec then
    succ, err, resp = do_exec(qs_args)
end

--todo: fail to get return values of 'err' and 'resp'!!!
--local succ, err, resp = do_exec and do_exec(qs_args) or false,"opcode not supported.","no response."

--[[
-- debug info
echo("succ", succ)
echo("err ", err)
echo("resp", resp)
--]]

if succ then
    ngx.say('<input type=\"button\" value=\"click\" onclick=\"alert(\'you click me!!!\');\" />')
--else
--    err = err .. " not forbidden."
--    ngx.say("err:", err)
end

ngx.exit(ngx.HTTP_OK)
